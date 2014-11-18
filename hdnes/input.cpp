#include "StdAfx.h"
#include "sysState.h"


input::input(void)
{
	controller[0][BUTTON_A].assignedKey = SDLK_z;
	controller[0][BUTTON_B].assignedKey = SDLK_x;
	controller[0][BUTTON_SELECT].assignedKey = SDLK_a;
	controller[0][BUTTON_START].assignedKey = SDLK_s;
	controller[0][BUTTON_UP].assignedKey = SDLK_UP;
	controller[0][BUTTON_DOWN].assignedKey = SDLK_DOWN;
	controller[0][BUTTON_LEFT].assignedKey = SDLK_LEFT;
	controller[0][BUTTON_RIGHT].assignedKey = SDLK_RIGHT;
	
	controller[1][BUTTON_A].assignedKey = SDLK_UNKNOWN;
	controller[1][BUTTON_B].assignedKey = SDLK_UNKNOWN;
	controller[1][BUTTON_SELECT].assignedKey = SDLK_UNKNOWN;
	controller[1][BUTTON_START].assignedKey = SDLK_UNKNOWN;
	controller[1][BUTTON_UP].assignedKey = SDLK_UNKNOWN;
	controller[1][BUTTON_DOWN].assignedKey = SDLK_UNKNOWN;
	controller[1][BUTTON_LEFT].assignedKey = SDLK_UNKNOWN;
	controller[1][BUTTON_RIGHT].assignedKey = SDLK_UNKNOWN;

	setting[SETTING_SCREENCAP].assignedKey = SDLK_PRINT;
	setting[SETTING_END_EMU].assignedKey = SDLK_ESCAPE;
	setting[SETTING_SAVE_STATE].assignedKey = SDLK_F1;
	setting[SETTING_LOAD_STATE].assignedKey = SDLK_F2;

	setting[SETTING_PAUSE].assignedKey = SDLK_F3;
	setting[SETTING_RUN_FRAME].assignedKey = SDLK_F4;
	setting[SETTING_CAP_DATA].assignedKey = SDLK_F5;
	setting[SETTING_CONT_CAP].assignedKey = SDLK_F6;
}


input::~input(void)
{
}

void input::Init(){
	for(Uint8 i = 0; i < BUTTON_COUNT; ++i){
		controller[0][i].currentState = false;
		controller[0][i].recordedState = false;
		controller[1][i].currentState = false;
		controller[1][i].recordedState = false;
	}
	currentRead1P = 0;
	currentRead2P = 0;
	readReady = false;
}

void input::handleEvent(SDL_Event event){
    button* eventButton;
    int settingKey;
	switch( event.type ){
      case SDL_KEYDOWN:
		//find if controller key pressed
		eventButton = findKeyButton(event.key.keysym.sym);
		if(eventButton != NULL) {
			eventButton->currentState = true;
		}
            
		//find setting key pressed
		settingKey = findSettingButton(event.key.keysym.sym);
		if(settingKey != -1) {
			switch (settingKey) {
				case SETTING_SCREENCAP:
					vid->capScreenFlag = true;
					break;
				case SETTING_END_EMU:
					gm->continuePlay = false;
					break;
                case SETTING_SAVE_STATE:
                    gm->saveStateFlag = true;
                    break;
                case SETTING_LOAD_STATE:
                    gm->loadStateFlag = true;
                    break;

				case SETTING_PAUSE:
					gm->waitPauseCommand = (gm->pauseFrame == 1 ? 0 : 1);
					break;
				case SETTING_RUN_FRAME:
					gm->waitPauseCommand = 2;
					break;
				case SETTING_CAP_DATA:
					vid->capDataFlag = true;
					break;
				case SETTING_CONT_CAP:
					vid->contCapFlag = !vid->contCapFlag;
					vid->contCapCounter = 0;
					break;
				default:
					break;
			}
		}
            

		break;
      case SDL_KEYUP:
		eventButton = findKeyButton(event.key.keysym.sym);
		if(eventButton != NULL) eventButton->currentState = false;
        break;
	case SDL_QUIT:
		gm->continuePlay = false;

      default:
        break;
    }

}

button* input::findKeyButton(SDLKey key){
	for(Uint8 i = 0; i < BUTTON_COUNT; ++i){
		for(Uint8 j = 0; j < 2; ++j){
			if(controller[j][i].assignedKey == key) 
				return &controller[j][i];
		}
	}
	return NULL;
}

int input::findSettingButton(SDLKey key){
	for(int i = 0; i < SETTING_COUNT; ++i){
        if(setting[i].assignedKey == key) return i;
	}
	return -1;
}


Uint8 input::readReg(Uint8 address){
	Uint8 value = 0x00;
	if(address == 0x16){
		value = (controller[0][currentRead1P].recordedState? 0x01: 0x00);
		if(readReady) ++currentRead1P;
	}
	if(address == 0x17){
		value = (controller[1][currentRead2P].recordedState? 0x01: 0x00);
		if(readReady) ++currentRead2P;
	}
	return value;
}


void input::writeReg(Uint8 address, Uint8 data){
	if(address == 0x16){
		if((data & 0x01) != 0){
			for(Uint8 i = 0; i < BUTTON_COUNT; ++i){
				for(Uint8 j = 0; j < 2; ++j){
					controller[j][i].recordedState = controller[j][i].currentState;
				}
			}
			currentRead1P = 0;
			currentRead2P = 0;
			readReady = false;
		}
		else{
			readReady = true;
		}
	}
}

void input::readConfig(string value){
    vector<string> lineTokens;
    
    split(value, ',', lineTokens);
    if (lineTokens[0].compare("controller") == 0) {
        controller[stoi(lineTokens[1])][stoi(lineTokens[2])].assignedKey = (SDLKey)stoi(lineTokens[3]);
    }
    if (lineTokens[0].compare("setting") == 0) {
        setting[stoi(lineTokens[1])].assignedKey = (SDLKey)stoi(lineTokens[2]);
    }
    
}

void input::saveConfig(fstream* inifile){
	for(Uint8 i = 0; i < BUTTON_COUNT; ++i){
		for(Uint8 j = 0; j < 2; ++j){
			(*inifile) << "input:controller," + to_string((long double)j) + "," + to_string((long double)i) + "," + to_string((long double)(controller[j][i].assignedKey)) + "\n";
		}
	}
	for(Uint8 i = 0; i < SETTING_COUNT; ++i){
        (*inifile) << "input:setting," + to_string((long double)i) + "," + to_string((long double)(setting[i].assignedKey)) + "\n";
	}
    
}

