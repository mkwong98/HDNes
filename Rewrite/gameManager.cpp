#include "gameManager.h"

using namespace std;

gameManager::gameManager(){
    //create core parts
    //create emu parts
    vid = new video();

    if(!this->loadConfig()){
        //if does not have config file then save the default
        this->saveConfig();
    }

    //create gui
    ui = new mainFrameImp(NULL);
    ui->gm = this;
    ui->Show(true);
}

gameManager::~gameManager(){
    //save config file
    this->saveConfig();

    //gui is destory already

    //destory emu parts
    delete(vid);

    //destory core parts
}

void gameManager::runGame(){
    //load rom
    //init core parts
    //init emu parts
    vid->startGame();
    //while is running
    //  handle input
    //      handle game ui events like save and load state
    //  run core parts
    //  when frame ready
    //      out put frame
    //      regulate frame rate
    //clean up
    vid->endGame();
}


bool gameManager::loadConfig(){
    //if has config file then open file and have each emu part read it
    fstream fs;
    fs.open("config.ini", fstream::in);
    if(fs.is_open()){
        vid->loadConfig(&fs);
        fs.close();
        return true;
    }
    else{
        fs.clear();
        return false;
    }
}

void gameManager::saveConfig(){
    fstream fs;
    fs.open("config.ini", fstream::out);
    vid->saveConfig(&fs);
    fs.close();
}

