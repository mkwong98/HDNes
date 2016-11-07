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
#include "wx\dlgInputImp.h"


using namespace std;

gameManager* gameManager::gm;

gameManager::gameManager(){
    //create emu parts
    vid = new video();
    romF = new gameFile();
    inp = new input();

    if(!this->loadConfig()){
        //if does not have config file then save the default
        this->saveConfig();
    }
    //load game specific config
    loadGameConfig();
    //create gui
    ui = new mainFrameImp(NULL);
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
    //while is running
    //  handle input
    //      handle game ui events like save and load state
    //  run core parts
    //  when frame ready
    //      out put frame
    //      regulate frame rate
    //clean up
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


bool gameManager::loadConfig(){
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
    dlgInputImp* i = new dlgInputImp(ui);
    i->ShowModal();


    saveGameConfig();
}

bool gameManager::loadGameConfig(){
    //if has config file then open file and have each emu part read it
    fstream fs;
    string line;
    string lineHdr;
    if(romF->romPath.compare("") == 0) return false;
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
        return true;
    }
    else{
        fs.clear();
        return false;
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
