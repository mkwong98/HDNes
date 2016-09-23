#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "wx\wx.h"
#include "wx\mainFrameImp.h"

class game_manager
{
    public:
        game_manager();
        ~game_manager();

        void run_game();

    protected:

    private:
        mainFrameImp * ui;
};

#endif // GAME_MANAGER_H
