#include "mainApp.h"
#include "gameManager.h"

IMPLEMENT_APP(mainApp)

mainApp::mainApp(void){

    SDL_SetMainReady();
	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK) < 0){
		initOK = false;
	}
	else{
		initOK = true;
	}
}

mainApp::~mainApp(void){
    if(initOK){
        delete(gameManager::gm);
        SDL_Quit();
    }
}

bool mainApp::OnInit(){
	if(initOK){
        gameManager::gm = new gameManager();
		return true;
	}
	else{
		return false;
	}
}


