#include "mainApp.h"

IMPLEMENT_APP(mainApp)

mainApp::mainApp(void){

    SDL_SetMainReady();
	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK) < 0){
		initOK = false;
	}
	else{
		SDL_Quit();
		initOK = true;
	}
}


mainApp::~mainApp(void){
}

bool mainApp::OnInit(){
	if(initOK){
        mainFrameImp *frame = new mainFrameImp(NULL);
        frame->Show( true );
		return true;
	}
	else{
		return false;
	}
}


