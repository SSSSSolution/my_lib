#include "r_audio/wav.h"
#include "rlog.h"
#include <fstream>
#include <iostream>

namespace reality
{
    namespace audio
    {

    Wav::Wav(const std::string &file_path)
        : m_file_path(file_path),
          m_loaded(false)
    {

    }

    Wav::~Wav()
    {
        if (m_data.data != nullptr)
        {
            free(m_data.data);
        }
    }

    bool Wav::load()
    {
        if (m_loaded)
        {
            return true;
        }

        try {
            std::ifstream ifs(m_file_path);
            ifs.seekg(0, ifs.end);
            auto len = ifs.tellg();
            ifs.seekg(0, ifs.beg);
            RLOG(INFO, "file length: %d", len);

            m_data.data = (char *)malloc(len * sizeof(char));
            if (m_data.data == nullptr)
            {
                RLOG(ERROR, "alloc memory failed");
                return false;
            }
            ifs.read(m_data.data, len);
            if (len < 44)
            {
                throw std::runtime_error("not a wav file");
            }

            // parse RIFF chunk
            m_data.chunk_id[0] = m_data.data[0];
            m_data.chunk_id[1] = m_data.data[1];
            m_data.chunk_id[2] = m_data.data[2];
            m_data.chunk_id[3] = m_data.data[3];
            RLOG(INFO, "chunk id: %s", m_data.chunk_id);
            if (std::string("RIFF") != m_data.chunk_id)
            {
                throw std::runtime_error("not a wav file");
            }

            m_data.chunk_size = *reinterpret_cast<unsigned int*>(&(m_data.data[4]));
            RLOG(INFO, "chunk size: %d", m_data.chunk_size);

            m_data.format[0] = m_data.data[8];
            m_data.format[1] = m_data.data[9];
            m_data.format[2] = m_data.data[10];
            m_data.format[3] = m_data.data[11];
            RLOG(INFO, "format: %s", m_data.format);
            if (std::string("WAVE") != m_data.format)
            {
                throw std::runtime_error("not a wav file");
            }

            // parse FMT sub-chunk
            m_data.sub_chunk1_id[0] = m_data.data[12];
            m_data.sub_chunk1_id[1] = m_data.data[13];
            m_data.sub_chunk1_id[2] = m_data.data[14];
            m_data.sub_chunk1_id[3] = m_data.data[15];
            RLOG(INFO, "sub_chunk1_id: %s", m_data.sub_chunk1_id);
            if (std::string("fmt ") != m_data.sub_chunk1_id)
            {
                throw std::runtime_error("not a wav file");
            }

            m_data.sub_chunk1_size = *reinterpret_cast<unsigned int*>(&(m_data.data[16]));
            RLOG(INFO, "sub_chunk1_size: %d", m_data.sub_chunk1_size);
            if (m_data.sub_chunk1_size != 16)
            {
                throw std::runtime_error("not a pcm wav file");
            }

            m_data.audio_format = *reinterpret_cast<unsigned short*>(&(m_data.data[20]));
            RLOG(INFO, "audio_format: %d", m_data.audio_format);
            if (m_data.audio_format != 1)
            {
                throw std::runtime_error("not a pcm wav file");
            }

            m_data.number_channels = *reinterpret_cast<unsigned short*>(&(m_data.data[22]));
            RLOG(INFO, "number_channels: %d", m_data.number_channels);

            m_data.sample_rate = *reinterpret_cast<unsigned int *>(&(m_data.data[24]));
            RLOG(INFO, "sample_rate: %d", m_data.sample_rate);

            // byte_rate = sample_rate * num_channels * bit_per_sample / 8
            m_data.byte_rate = *reinterpret_cast<int *>(&(m_data.data[28]));
            RLOG(INFO, "byte_rate: %d", m_data.byte_rate);

            // block align = num_channels * bits_per_sample / 8
            m_data.block_align = *reinterpret_cast<unsigned short *>(&(m_data.data[32]));
            RLOG(INFO, "block_align: %d", m_data.block_align);

            m_data.bits_per_sample = *reinterpret_cast<unsigned short *>(&(m_data.data[34]));
            RLOG(INFO, "bits_per_sample: %d", m_data.bits_per_sample);

            // parse "data" sub chunk
            m_data.sub_chunk2_id[0] = m_data.data[36];
            m_data.sub_chunk2_id[1] = m_data.data[37];
            m_data.sub_chunk2_id[2] = m_data.data[38];
            m_data.sub_chunk2_id[3] = m_data.data[39];
            RLOG(INFO, "sub_chunk2_id: %s", m_data.sub_chunk2_id);
//            if (std::string("data") != data.sub_chunk2_id)
//            {
//                throw std::runtime_error("not a wav file");
//            }

            m_data.sub_chunk2_size = *reinterpret_cast<unsigned int *>(&(m_data.data[40]));
            RLOG(INFO, "sub_chunk2_size: %d", m_data.sub_chunk2_size);

            m_data.pcm_data = &(m_data.data[44]);
        }  catch (const std::exception &e) {
            RLOG(ERROR, "capture exception: %s", e.what());
            if (m_data.data != nullptr)
            {
                free(m_data.data);
                m_data.data = nullptr;
            }
            return false;
        }

        m_data.frame_count = (m_data.chunk_size + 8 - 44) / m_data.block_align;
        RLOG(INFO, "frame count: %d", m_data.frame_count);
        m_loaded = true;
        return true;
    }

    const WavData &Wav::get_data()
    {
        return m_data;
    }

    }
}
