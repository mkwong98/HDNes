#include "gameManager.h"
#include "core\memBus.h"
#include "core\cart.h"
#include "core\cart.h"
#include "core\cpu.h"
#include "core\ppu.h"
#include "core\apu.h"
#include "core\gamepad.h"
#include "emu\video.h"
#include "emu\audio.h"
#include "emu\gameFile.h"
#include "emu\input.h"
#include "wx\mainFrameImp.h"
#include "wx\frmWaitInputImp.h"


using namespace std;

gameManager* gameManager::gm;

gameManager::gameManager(){
    //create emu parts
    vid = new video();
    aud = new audio();
    inp = new input();
    romF = new gameFile();

    emu[0] = vid;
    emu[1] = aud;
    emu[2] = inp;
    emu[3] = romF;


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
    for(int i = 0; i < EMU_PART_COUNT; ++i){
        delete(emu[i]);
    }
}

void gameManager::showUI(){
    ui->updateDisplay();
    ui->Show(true);

}

void gameManager::runSingleCycle(){
    ap->runCycle();
    pp->runCycle();
    pp->runCycle();
    pp->runCycle();
}


void gameManager::runGame(){
    Uint32 frameTicks;
    Uint8 ticksRemain;
    Uint8 instructLen;
    Uint8 cyclesToRun;

    //load rom
    //init core parts
    rom = cart::getCartFromROMFile(romF->romPath);
    if(!rom) return;
    cp = new cpu();
    pp = new ppu();
    ap = new apu();
    gp = new gamepad();
    mb = new memBus();
    cp->init();
    pp->init();
    ap->init();
    gp->init();
    mb->init();

    //init emu parts
    for(int i = 0; i < EMU_PART_COUNT; ++i){
        emu[i]->startGame();
    }

    gameState = GAME_STATE_RUNNING;
    frameTicks = SDL_GetTicks();
    ticksRemain = 0;
    while(gameState != GAME_STATE_STOPPED){
        inp->handleUserInput();
        if(gameState != GAME_STATE_PAUSED){
            if(!pp->frameReady){
                cyclesToRun = cp->getNextInstructionLength();
                for(Uint8 i = 0; i < cyclesToRun; ++i){
                    runSingleCycle();
                }
                cp->runInstruction();
                if(cp->hasExtraCycle()){
                    runSingleCycle();
                }
            }

            if(pp->frameReady && (frameTicks < SDL_GetTicks())){
                //output frame

                //calculate the time of next frame
                frameTicks += TICKS_PER_FRAME_NTSC;
                //add one tick for fractional part of ticks per frame
                if(ticksRemain >= TICKS_REMAIN_NTSC){
                    ++frameTicks;
                    ticksRemain -= TICKS_REMAIN_NTSC;
                }
                ticksRemain += TICKS_FRACTION_NTSC;

                //handle user actions

                //check save state is requested

                //check load state is requested
            }
        }


    //while is running
    //  handle input
    //      handle game ui events like save and load state
    //  run core parts
    //  when frame ready
    //      out put frame
    //      regulate frame rate
    //clean up


    }

    for(int i = 0; i < EMU_PART_COUNT; ++i){
        emu[i]->endGame();
    }

    //delete core parts
    delete(rom);
    delete(cp);
    delete(pp);
    delete(ap);
    delete(gp);
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
            for(int i = 0; i < EMU_PART_COUNT; ++i){
                 if(lineHdr.compare(emu[i]->partName()) == 0){
                    emu[i]->loadConfig(&fs);
                }
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
    for(int i = 0; i < EMU_PART_COUNT; ++i){
        emu[i]->saveConfig(&fs);
    }
    fs.close();
}

void gameManager::romSelected(const string& romName){
    //save game specific config for the current game
    saveGameConfig();
    romF->romPath = romName;

    for(int i = 0; i < EMU_PART_COUNT; ++i){
        emu[i]->initGameConfig();
    }
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
            for(int i = 0; i < EMU_PART_COUNT; ++i){
                if(lineHdr.compare(emu[i]->partName()) == 0){
                    emu[i]->loadConfig(&fs);
                }
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
    for(int i = 0; i < EMU_PART_COUNT; ++i){
        emu[i]->saveGameConfig(&fs);
    }
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

void gameManager::setUseMusicHDPack(bool use){
    aud->setUseHDPack(use);
}

void gameManager::setVolume(int vol){
    aud->setVolume(vol);
}



