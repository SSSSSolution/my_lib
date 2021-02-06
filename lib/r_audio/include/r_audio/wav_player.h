#ifndef REALITY_AUDIO_WAV_PALYER
#define REALITY_AUDIO_WAV_PALYER

#include <memory>

namespace reality
{
    namespace audio
    {
    class Wav;
    class WavPlayer
    {
    public:
        WavPlayer();
        ~WavPlayer();

        bool play(std::shared_ptr<Wav> wav);
        void stop() {};
        void pause() {};

    private:
        struct Impl;
        std::unique_ptr<Impl> m_impl;

    };

    }
}
#endif
