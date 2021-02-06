#include <alsa/asoundlib.h>
#include <iostream>
#include <rlog.h>

int main(int argc, char **argv)
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
        exit(1);
    }

    err = snd_pcm_hw_params_malloc(&hw_params);
    if (err < 0)
    {
        RLOG(ERROR, "cannot allocate hardware parameter structure: %s",
             snd_strerror(err));
        exit(1);
    }

    err = snd_pcm_hw_params_any(handle, hw_params);
    if (err < 0)
    {
        RLOG(ERROR, "cannot initialize hardware parameter structure: %s",
             snd_strerror(err));
        exit(1);
    }

    err = snd_pcm_hw_params_set_access(handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
    if (err < 0)
    {
        RLOG(ERROR, "cannot set access type: %s",
             snd_strerror(err));
        exit(1);
    }

    err = snd_pcm_hw_params_set_format(handle, hw_params, SND_PCM_FORMAT_S16_LE);
    if (err < 0)
    {
        RLOG(ERROR, "cannot set sample format: %s",
             snd_strerror(err));
        exit(1);
    }

    unsigned int rate = 44100;
    err = snd_pcm_hw_params_set_rate_near(handle, hw_params, &rate, nullptr);
    RLOG(INFO, "sample rate: %d", rate);
    if (err < 0)
    {
        RLOG(ERROR, "cannot set sample rate: %s",
             snd_strerror(err));
        exit(1);
    }

    err = snd_pcm_hw_params_set_channels(handle, hw_params, 2);
    if (err < 0)
    {
        RLOG(ERROR, "cannot set channel count %s",
             snd_strerror(err));
        exit(1);
    }

    err = snd_pcm_hw_params(handle, hw_params);
    if (err < 0)
    {
        RLOG(ERROR, "cannot set parameters: %s",
             snd_strerror(err));
        exit(1);
    }

    snd_pcm_hw_params_free(hw_params);

    err = snd_pcm_prepare(handle);
    if (err < 0)
    {
        RLOG(ERROR, "cannot prepare audio interface for use: %s",
             snd_strerror(err));
        exit(1);
    }


    short buf[128];
    for (int i = 0; i < 1000; i++)
    {
        if (err = snd_pcm_writei(handle, buf, 128) != 128)
        {
            RLOG(ERROR, "write to audio interface failed: %s",
                 snd_strerror(err));
            exit(1);
        }
    }

    snd_pcm_close(handle);
    return 0;
}




























