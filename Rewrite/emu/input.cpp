#include "input.h"

using namespace std;


input::input(){
    //open all joy sticks
    int num_joy = SDL_NumJoysticks();
    SDL_Joystick* j;
    for(int i = 0; i < num_joy; i++){
        j = SDL_JoystickOpen(i);
        if(j){
            joysticks.push_back(j);
        }
    }

    for(int i = 0; i < KEY_IDX_CNT; i++){
        keyMaps[i].type = SDL_USEREVENT;
    }

    //default for player 1
    changeKeyMapToKeyboard(KEY_IDX_P1_UP, SDLK_UP);
    changeKeyMapToKeyboard(KEY_IDX_P1_DOWN, SDLK_DOWN);
    changeKeyMapToKeyboard(KEY_IDX_P1_LEFT, SDLK_LEFT);
    changeKeyMapToKeyboard(KEY_IDX_P1_RIGHT, SDLK_RIGHT);
    changeKeyMapToKeyboard(KEY_IDX_P1_SELECT, SDLK_a);
    changeKeyMapToKeyboard(KEY_IDX_P1_START, SDLK_s);
    changeKeyMapToKeyboard(KEY_IDX_P1_A, SDLK_z);
    changeKeyMapToKeyboard(KEY_IDX_P1_B, SDLK_x);

    changeKeyMapToKeyboard(KEY_IDX_F1_RESET, SDLK_F1);
    changeKeyMapToKeyboard(KEY_IDX_F1_PAUSE, SDLK_PAUSE);
}

input::~input(){
    //close all joy sticks
    for (vector<SDL_Joystick*>::iterator it = joysticks.begin(); it != joysticks.end(); ++it){
        if (SDL_JoystickGetAttached(*it)){
            SDL_JoystickClose(*it);
        }
    }
}

void input::initGameConfig(){

}


string input::partName(){
    return string("input");
}


void input::saveConfigLines(fstream* fs){
}

void input::saveGameConfigLines(fstream* fs){
}

void input::loadConfigVal(const string& hdr, const string& value){
}

void input::startGame(){

}

void input::endGame(){

}

void input::changeKeyMapToKeyboard(Uint8 keyIdx, SDL_Keycode keyCode){
    keyMaps[keyIdx].type = SDL_KEYDOWN;
    keyMaps[keyIdx].keyCode = keyCode;
}

string input::inputName(keyMap km){
    string kname;
    switch(km.type){
    case SDL_USEREVENT:
        kname = "------";
        break;
    case SDL_KEYDOWN:
        kname = "Keyboard:" + string(SDL_GetKeyName(km.keyCode)) ;
        break;
    }
    return kname;
}

string input::inputNameForKeyIdx(int keyIdx){
    return inputName(keyMaps[keyIdx]);
}
