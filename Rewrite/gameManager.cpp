#include "gameManager.h"
#include "core\memBus.h"
#include "core\cart.h"
#include "core\cart.h"
#include "core\cpu.h"
#include "core\ppu.h"
#include "core\apu.h"
#include "emu\video.h"
#include "emu\gameFile.h"
#include "emu\input.h"
#include "wx\mainFrameImp.h"
#include "wx\frmWaitInputImp.h"


using namespace std;

gameManager* gameManager::gm;

gameManager::gameManager(){
    //create emu parts
    vid = new video();
    romF = new gameFile();
    inp = new input();

    loadConfig();
    //load game specific config
    loadGameConfig();
    //create gui
    ui = new mainFrameImp(NULL);
    gameState = GAME_STATE_STOPPED;
}

gameManager::~gameManager(){
    //save config file
    this->saveConfig();
    this->saveGameConfig();

    //gui is destory already

    //destory emu parts
    delete(vid);
    delete(romF);
}

void gameManager::showUI(){
    ui->updateDisplay();
    ui->Show(true);

}

void gameManager::runGame(){
    //load rom
    //init core parts
    rom = cart::getCartFromROMFile(romF->romPath);
    if(!rom) return;
    cp = new cpu();
    pp = new ppu();
    ap = new apu();
    mb = new memBus();

    //init emu parts
    vid->startGame();
    romF->startGame();
    inp->startGame();

    gameState = GAME_STATE_RUNNING;
    while(gameState != GAME_STATE_STOPPED){
        inp->handleUserInput();
    //while is running
    //  handle input
    //      handle game ui events like save and load state
    //  run core parts
    //  when frame ready
    //      out put frame
    //      regulate frame rate
    //clean up


    }

    vid->endGame();
    romF->endGame();
    inp->endGame();

    //delete core parts
    delete(rom);
    delete(cp);
    delete(pp);
    delete(ap);
    delete(mb);
}


void gameManager::loadConfig(){
    //if has config file then open file and have each emu part read it
    fstream fs;
    string line;
    string lineHdr;
    fs.open("config.ini", fstream::in);
    if(fs.is_open()){
        while(getline(fs, line)){
            lineHdr = emuPart::getConfigLineHdr(line);
            if(lineHdr.compare(vid->partName()) == 0){
                vid->loadConfig(&fs);
            }
            if(lineHdr.compare(romF->partName()) == 0){
                romF->loadConfig(&fs);
            }
            if(lineHdr.compare(inp->partName()) == 0){
                inp->loadConfig(&fs);
            }
        }
        fs.close();
    }
    else{
        fs.clear();
        //if does not have config file then save the default
        saveConfig();
    }
}

void gameManager::saveConfig(){
    fstream fs;
    fs.open("config.ini", fstream::out);
    vid->saveConfig(&fs);
    romF->saveConfig(&fs);
    inp->saveConfig(&fs);
    fs.close();
}

void gameManager::romSelected(const string& romName){
    //save game specific config for the current game
    saveGameConfig();
    romF->romPath = romName;

    vid->initGameConfig();
    romF->initGameConfig();
    inp->initGameConfig();
    //load config for new game
    loadGameConfig();
}

void gameManager::setInputForKey(int idx){
    //show dialog box
    frmWaitInputImp* i = new frmWaitInputImp(ui);
    i->Show();
    waitForInput(idx);
    i->Destroy();
}

void gameManager::waitForInput(int idx){
    int windowX, windowY, windowW, windowH;
    ui->GetPosition(&windowX, &windowY);
    ui->GetSize(&windowW, &windowH);

    SDL_Window *window;
    window = SDL_CreateWindow(
        "",                                 // window title
        windowX,           // initial x position
        windowY,           // initial y position
        windowW,                               // width, in pixels
        windowH,                               // height, in pixels
        SDL_WINDOW_BORDERLESS                  // flags - see below
    );

    inp->getKeyMapInput(idx);
    ui->updateDisplay();
    SDL_DestroyWindow(window);
}

void gameManager::loadGameConfig(){
    //if has config file then open file and have each emu part read it
    fstream fs;
    string line;
    string lineHdr;
    if(romF->romPath.compare("") == 0) return;
    fs.open(emuPart::getFileName(romF->romPath) + ".ini", fstream::in);
    if(fs.is_open()){
        while(getline(fs, line)){
            lineHdr = emuPart::getConfigLineHdr(line);
            if(lineHdr.compare(vid->partName()) == 0){
                vid->loadConfig(&fs);
            }
            if(lineHdr.compare(romF->partName()) == 0){
                romF->loadConfig(&fs);
            }
            if(lineHdr.compare(inp->partName()) == 0){
                inp->loadConfig(&fs);
            }
        }
        fs.close();
    }
    else{
        fs.clear();
        saveGameConfig();
    }
}

void gameManager::saveGameConfig(){
    if(romF->romPath.compare("") == 0) return;
    fstream fs;
    fs.open(emuPart::getFileName(romF->romPath) + ".ini", fstream::out);
    vid->saveGameConfig(&fs);
    romF->saveGameConfig(&fs);
    inp->saveGameConfig(&fs);
    fs.close();
}

void gameManager::functionKeyPressed(Uint8 keyIdx){
    switch(keyIdx){
    case KEY_IDX_F0_STOP:
        gameState = GAME_STATE_STOPPED;
        break;
    }
}

void gameManager::changeSaveStateSlot(int slot){
    romF->currentStateSlot = slot;
}

void gameManager::changeUseRotateState(bool use){
    romF->rotateState = use;
}

void gameManager::changeOverwriteBat(bool overwrite){
    romF->overwriteBat = overwrite;
}

void gameManager::setScreenSize(Uint8 sizeIdx){
    vid->setScreenSize(sizeIdx);
}

void gameManager::setconCapRate(Uint16 rate){
    vid->setconCapRate(rate);
}

void gameManager::setUseHDPack(bool use){
    vid->setUseHDPack(use);
}

void gameManager::setGenHDData(bool use){
    vid->setGenHDData(use);
}

void gameManager::setIgnoreEdge(bool use){
    vid->setIgnoreEdge(use);
}



