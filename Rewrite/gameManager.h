#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "wx\wx.h"
#include "wx\mainFrameImp.h"

#include "classList.h"
#include "emu\video.h"
#include "emu\gameFile.h"

class gameManager
{
    public:
        mainFrameImp* ui;
        video* vid;
        gameFile* romF;


        gameManager();
        ~gameManager();

        void runGame();
        void romSelected(const string& romName);
    protected:

    private:
        bool loadConfig();
        void saveConfig();
        bool loadGameConfig();
        void saveGameConfig();

};

#endif // GAME_MANAGER_H
