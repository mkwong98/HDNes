#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <string>
#include <wx\wx.h>
#include "wx\mainFrameImp.h"

#include "classList.h"

using namespace std;

class gameManager
{
    public:
        static gameManager* gm;

        mainFrameImp* ui;
        video* vid;
        gameFile* romF;

        cart* rom;
        cpu* cp;
        ppu* pp;
        apu* ap;
        memBus* mb;

        gameManager();
        ~gameManager();

        void showUI();
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
