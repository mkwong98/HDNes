#include "mainApp.h"
#include "gameManager.h"

IMPLEMENT_APP(mainApp)

mainApp::mainApp(void){
    SDL_SetMainReady();
	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK) < 0){
		initState = 0;
	}
	else{
		initState = 1;
	}
}

mainApp::~mainApp(void){
    if(initState == 2) delete(gameManager::gm);
    if(initState >= 1) SDL_Quit();
}

bool mainApp::OnInit(){
	if(initState == 1){
        gameManager::gm = new gameManager();
        initState = 2;
        gameManager::gm->showUI();
		return true;
	}
	else{
		return false;
	}
}


