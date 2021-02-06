#include "r_audio/wav.h"
#include "r_audio/wav_player.h"
#include "rlog.h"

using namespace reality::audio;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        RLOG(ERROR, "Usage: %s wav_file", argv[0]);
        exit(1);
    }

    std::shared_ptr<Wav> wav = std::make_shared<Wav>(argv[1]);
    if (!wav->load())
    {
        RLOG(ERROR, "wav file(%s) load failed", argv[1]);
        exit(1);
    }

    WavPlayer wav_player;
    if (!wav_player.play(wav))
    {
        RLOG(ERROR, "play wav(%s) failed", argv[1]);
        exit(1);
    }

}
