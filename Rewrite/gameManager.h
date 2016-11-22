#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <wx\wx.h>

#include "common.h"
#include "classList.h"

#define GAME_STATE_STOPPED          0
#define GAME_STATE_RUNNING          1
#define GAME_STATE_PAUSED           2
#define GAME_STATE_ADVANCE_BY_FRAME 3

using namespace std;

class gameManager
{
    public:
        static gameManager* gm;

        mainFrameImp* ui;
        video* vid;
        gameFile* romF;
        input* inp;
        audio* aud;

        cart* rom;
        cpu* cp;
        ppu* pp;
        apu* ap;
        memBus* mb;

        int gameState;

        gameManager();
        ~gameManager();

        void showUI();

        void runGame();
        void changeSaveStateSlot(int slot);
        void changeUseRotateState(bool use);
        void changeOverwriteBat(bool overwrite);
        void romSelected(const string& romName);

        void setInputForKey(int idx);
        void waitForInput(int idx);
        void functionKeyPressed(Uint8 keyIdx);

        void setScreenSize(Uint8 sizeIdx);
        void setconCapRate(Uint16 rate);
        void setUseHDPack(bool use);
        void setGenHDData(bool use);
        void setIgnoreEdge(bool use);

        void setUseMusicHDPack(bool use);
        void setVolume(int vol);
    protected:

    private:
        void loadConfig();
        void saveConfig();
        void loadGameConfig();
        void saveGameConfig();

};

#endif // GAME_MANAGER_H
