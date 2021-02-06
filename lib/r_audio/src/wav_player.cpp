#include "r_audio/wav_player.h"
#include "r_audio/wav.h"
#include "rlog.h"
#include <alsa/asoundlib.h>

namespace reality
{
    namespace audio
    {
    struct WavPlayer::Impl
    {
        Impl() {}
        ~Impl() {}
    };

    WavPlayer::WavPlayer()
    {
        m_impl = std::make_unique<Impl>();
    }

    WavPlayer::~WavPlayer() = default;

    bool WavPlayer::play(std::shared_ptr<Wav> wav)
    {
        snd_pcm_t *handle;
        snd_pcm_hw_params_t *hw_params;

        // open pcm device
        auto err = snd_pcm_open(&handle, "default",
                                SND_PCM_STREAM_PLAYBACK, 0);
        if (err < 0)
        {
            RLOG(ERROR, "failed to open pcm device %s",
                 snd_strerror(err));
            return false;
        }

        err = snd_pcm_hw_params_malloc(&hw_params);
        if (err < 0)
        {
            RLOG(ERROR, "cannot allocate hardware parameter structure: %s",
                 snd_strerror(err));
            return false;
        }

        err = snd_pcm_hw_params_any(handle, hw_params);
        if (err < 0)
        {
            RLOG(ERROR, "cannot initialize hardware parameter structure: %s",
                 snd_strerror(err));
            return false;
        }

        err = snd_pcm_hw_params_set_access(handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
        if (err < 0)
        {
            RLOG(ERROR, "cannot set access type: %s",
                 snd_strerror(err));
            return false;
        }

        snd_pcm_format_t format;
        const auto &data = wav->get_data();
        if (data.bits_per_sample == 16)
        {
            format = SND_PCM_FORMAT_S16_LE;
        }
        else
        {
            RLOG(ERROR, "please add more format support");
            return false;
        }
        err = snd_pcm_hw_params_set_format(handle, hw_params, format);
        if (err < 0)
        {
            RLOG(ERROR, "cannot set sample format: %s",
                 snd_strerror(err));
            return false;
        }

        unsigned int rate = wav->get_data().sample_rate;
        err = snd_pcm_hw_params_set_rate_near(handle, hw_params, &rate, nullptr);
        RLOG(INFO, "sample rate: %d", rate);
        if (err < 0)
        {
            RLOG(ERROR, "cannot set sample rate: %s",
                 snd_strerror(err));
            return false;
        }

        unsigned int channels = wav->get_data().number_channels;
        err = snd_pcm_hw_params_set_channels(handle, hw_params, channels);
        if (err < 0)
        {
            RLOG(ERROR, "cannot set channel count %s",
                 snd_strerror(err));
            return false;
        }

        err = snd_pcm_hw_params(handle, hw_params);
        if (err < 0)
        {
            RLOG(ERROR, "cannot set parameters: %s",
                 snd_strerror(err));
            return false;
        }

        snd_pcm_hw_params_free(hw_params);

        err = snd_pcm_prepare(handle);
        if (err < 0)
        {
            RLOG(ERROR, "cannot prepare audio interface for use: %s",
                 snd_strerror(err));
            return false;
        }

        int byte_per_frame = wav->get_data().block_align;
        int frames_to_deliver;
        int leave_frame = wav->get_data().frame_count;
        char *p_data = wav->get_data().pcm_data;
        while (1)
        {
            err = snd_pcm_wait(handle, 1000);
            if (err < 0)
            {
                RLOG(ERROR, "alsa poll failed");
                break;
            }
            // find out how much space is available for playback data
            frames_to_deliver = snd_pcm_avail_update(handle);
            if (frames_to_deliver < 0)
            {
                if (frames_to_deliver == -EPIPE)
                {
                    RLOG(ERROR, "an xrun occured");
                    break;;
                }
                else
                {
                    RLOG(ERROR,"unknown ALSA avail update return value: %d",
                         frames_to_deliver);
                    break;
                }
            }
            frames_to_deliver = frames_to_deliver > 4096 ? 4096 : frames_to_deliver;
            if (leave_frame < frames_to_deliver)
            {
                frames_to_deliver = leave_frame;
            }
            err = snd_pcm_writei(handle, p_data, frames_to_deliver);
            if (err < 0)
            {
                RLOG(ERROR, "pcm write failed");
                break;
            }
            leave_frame -= frames_to_deliver;
            if (leave_frame <= 0)
            {
                RLOG(INFO, "play finished");
                break;
            }
            RLOG(DEBUG, "leave frame: %d", leave_frame);
            p_data += frames_to_deliver * byte_per_frame;
        }

        snd_pcm_close(handle);
        return true;
    }
    }
}
