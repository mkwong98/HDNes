#ifndef AUDIO_H
#define AUDIO_H

#include "emuPart.h"


class audio : public emuPart
{
    public:
        bool useHDPack;
        int volume;

        audio();
        virtual ~audio();
        string partName();

        void saveConfigLines(fstream* fs);
        void saveGameConfigLines(fstream* fs);
        void loadConfigVal(const string& hdr, const string& value);
        void initGameConfig();

        void startGame();
        void endGame();

        void setVolume(int vol);
        void setUseHDPack(bool use);

    protected:

    private:
};

#endif // AUDIO_H
