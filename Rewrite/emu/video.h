#ifndef VIDEO_H
#define VIDEO_H

#include "../classList.h"
#include "emuPart.h"

class video : public emuPart
{
    public:
        Uint8 screenSize;
        Uint8 conCapRate;
        bool useHDPack;
        bool autoCaptureForHD;
        bool ignoreEdge;

        video();
        virtual ~video();
        string partName();

        void saveConfigLines(fstream* fs);
        void saveGameConfigLines(fstream* fs);
        void loadConfigVal(const string& hdr, const string& value);
        void initGameConfig();

        void startGame();
        void endGame();
    protected:

    private:
        SDL_Window* displayWindow;
        SDL_GLContext glcontext;
};

#endif // VIDEO_H
