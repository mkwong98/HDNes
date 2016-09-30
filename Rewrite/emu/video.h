#ifndef VIDEO_H
#define VIDEO_H

#include "../classList.h"
#include <emuPart.h>

class video : public emuPart
{
    public:
        video();
        virtual ~video();

        void loadConfig(fstream* fs);
        void saveConfig(fstream* fs);

        void startGame();
        void endGame();
    protected:

    private:
        SDL_Window* displayWindow;
        SDL_GLContext glcontext;
};

#endif // VIDEO_H
