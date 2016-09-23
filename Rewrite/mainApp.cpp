#include "mainApp.h"
#include "game_manager.h"

IMPLEMENT_APP(mainApp)

game_manager *gm;

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
        delete(gm);
        SDL_Quit();
    }
}

bool mainApp::OnInit(){
	if(initOK){
        gm = new game_manager();
		return true;
	}
	else{
		return false;
	}
}


