#include "mainApp.h"
#include "sysState.h"

IMPLEMENT_APP(mainApp)

opcode opArr[256];

mainApp::mainApp(void)
{
	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK) < 0){
		initOK = false;
	}
	else{
		inputCore = new input();
		vid = new video();
		mixer = new audio();
		romDat = new cart();
		memDat = new memory();

		//must wait others
		setting = new sysSetting();
		SDL_Quit();
		initOK = true;
	}
}


mainApp::~mainApp(void)
{
	delete setting;
	delete inputCore;
	delete mixer;
	delete vid;
	delete romDat;
	delete memDat;
}

bool mainApp::OnInit()
{
 // start doing stuff
	if(initOK){
		mainForm = new fraHDNesImp();
		mainForm->Show(true);
		guiForm = mainForm;
		return true;
	}
	else{
		return false;
	}
}


