#ifndef REALITY_AUDIO_WAV_H
#define REALITY_AUDIO_WAV_H

#include <string>

namespace reality {
    namespace audio
    {

    struct WavData
    {
        char *data = nullptr;

        char chunk_id[5] = {0};
        unsigned int chunk_size;
        char format[5] = {0};
        char sub_chunk1_id[5] = {0};
        unsigned int sub_chunk1_size;
        unsigned short audio_format;
        unsigned short number_channels;
        unsigned int sample_rate;
        unsigned int byte_rate;
        unsigned short block_align;
        unsigned short bits_per_sample;
        char sub_chunk2_id[5] = {0};
        unsigned int sub_chunk2_size;

        char *pcm_data;
        int frame_count;
    };

    class Wav
    {
    public:
        Wav(const std::string &file_path);
        ~Wav();

        bool load();
        bool reload() {return true;};

        const WavData &get_data();

    private:
        std::string m_file_path;
        bool m_loaded;

        WavData m_data;

    };
    }
}

#endif
