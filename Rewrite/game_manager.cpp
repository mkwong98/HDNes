#include "game_manager.h"

game_manager::game_manager(){
    //create core parts
    //create emu parts
    //if has config file then open file and have each emu part read it
    //if does not have config file then load default and save it

    //create gui
    ui = new mainFrameImp(NULL);
    ui->Show(true);
}

game_manager::~game_manager(){
    //save config file

    //gui is destory already

    //destory emu parts
    //destory core parts
}

void game_manager::run_game(){
    //load rom
    //init core parts
    //init emu parts
    //while is running
    //  handle input
    //      handle game ui events like save and load state
    //  run core parts
    //  when frame ready
    //      out put frame
    //      regulate frame rate
    //clean up
}

