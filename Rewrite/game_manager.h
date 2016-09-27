#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "wx\wx.h"
#include "wx\mainFrameImp.h"

#include "classList.h"
#include "emu\video.h"

class game_manager
{
    public:
        game_manager();
        ~game_manager();

        void run_game();

    protected:

    private:
        mainFrameImp* ui;
        video* vid;
};

#endif // GAME_MANAGER_H
