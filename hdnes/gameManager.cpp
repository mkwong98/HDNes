#include "stdafx.h"
#include "sysState.h"

using namespace std;

gameManager::gameManager()
{
	if(initialize()){
		cpuCore = new cpu();
		ppuCore = new ppu();
		apuCore = new apu();
		clockRatio = 3;
	}
	loadStateFlag = false;
	saveStateFlag = false;
}

gameManager::~gameManager(void)
{
	delete apuCore;
	delete ppuCore;
	delete cpuCore;
	cleanup();
}

void gameManager::start(){
	SDL_Event event;

    if (romDat->romLoaded) {
        vid->init();
        cpuCore->init();
        ppuCore->init();
        apuCore->init();
        mixer->init();
        inputCore->Init();

        continuePlay = true;
		pauseFrame = 0;
		waitPauseCommand = -1;
        while(continuePlay){
			if(pauseFrame != 1 && !vid->waitFrame){
				cpuCore->runClock();
				ppuCore->runCatchUp(cpuCore->getCodeRunCycle() * clockRatio);
				apuCore->runCatchUp(cpuCore->getCodeRunCycle());
                mmc->runCatchUp(cpuCore->getCodeRunCycle());
				cpuCore->runCode();

				if(ppuCore->signalNMI){
					cpuCore->runNMI();
					ppuCore->signalNMI = false;
				}
			}
            if(ppuCore->signalFrameReady){
                vid->displayFrame();
				if(pauseFrame > 1) 
					--pauseFrame;
				if(waitPauseCommand != -1){ 
					pauseFrame = waitPauseCommand;
					if(waitPauseCommand > 0){
						guiForm->refreshRAMGUI();
					}
					waitPauseCommand = -1;
				}
				if(pauseFrame != 1 && !vid->waitFrame){
					vid->clearScreenData();
					ppuCore->signalFrameReady = false;
					cpuCore->resetCycleCount();
					ppuCore->resetCycleCount();
					apuCore->resetCycleCount();
					mmc->resetCycleCount();
				}
            }
			if(pauseFrame != 1 && !vid->waitFrame){
				cpuCore->runIRQ();
                
                if (loadStateFlag) {
                    loadState();
                }
                if (saveStateFlag) {
                    saveState();
                }
                
			}
            while( SDL_PollEvent( &event ) ){
                inputCore->handleEvent(event);
            }
        }
        vid->cleanUp();
		romDat->saveBat();
    }
	delete gm;
	gm = NULL;
}

bool gameManager::initialize(){
	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK) < 0){
		return false;
	}	
	return true;
}

void gameManager::cleanup(){
	SDL_Quit();
}

void gameManager::saveState(){
	fstream statefile;
    string filename = getROMDirPath() + "\\" + getROMName() + ".sta";
    
	statefile.open(filename, ios::out | ios::binary | ios::trunc);
	if (statefile.is_open()){
        romDat->saveState(&statefile);
        memDat->saveState(&statefile);
        mmc->saveState(&statefile);
        cpuCore->saveState(&statefile);
        ppuCore->saveState(&statefile);
        apuCore->saveState(&statefile);
		statefile.close();
	}
    saveStateFlag = false;
}

void gameManager::loadState(){
	fstream statefile;
    string filename = getROMDirPath() + "\\" + getROMName() + ".sta";
    
	statefile.open(filename, ios::in | ios::binary);
	if (statefile.is_open()){
        romDat->loadState(&statefile);
        memDat->loadState(&statefile);
        mmc->loadState(&statefile);
        cpuCore->loadState(&statefile);
        ppuCore->loadState(&statefile);
        apuCore->loadState(&statefile);
		vid->init();
		
		statefile.close();

	}
    loadStateFlag = false;
}

