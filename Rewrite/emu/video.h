#ifndef VIDEO_H
#define VIDEO_H

#include "../classList.h"
#include <emu_part.h>

class video : public emu_part
{
    public:
        video();
        virtual ~video();

        void loadConfig(fstream* statefile);
        void saveConfig(fstream* statefile);

        void startGame();
        void endGame();
    protected:

    private:
        SDL_Window* displayWindow;
        SDL_GLContext glcontext;
};

#endif // VIDEO_H
