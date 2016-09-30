#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "wx\wx.h"
#include "wx\mainFrameImp.h"

#include "classList.h"
#include "emu\video.h"

class gameManager
{
    public:
        gameManager();
        ~gameManager();

        void runGame();
    protected:

    private:
        mainFrameImp* ui;
        video* vid;
        bool loadConfig();
        void saveConfig();

};

#endif // GAME_MANAGER_H
