#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <wx\wx.h>
#include "wx\mainFrameImp.h"

#include "classList.h"
#include "core\cart.h"
#include "emu\video.h"
#include "emu\gameFile.h"

class gameManager
{
    public:
        static gameManager* gm;

        mainFrameImp* ui;
        video* vid;
        gameFile* romF;

        cart* rom;

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
