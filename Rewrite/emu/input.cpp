#include "input.h"
#include "../gameManager.h"

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
    for(int i = 0; i < KEY_IDX_CNT; i++){
        saveConfigLine(fs, intToString(i), inputMapToConfigStr(keyMaps[i]));
    }
}

void input::saveGameConfigLines(fstream* fs){
}

void input::loadConfigVal(const string& hdr, const string& value){
    keyMaps[stringToInt(hdr)] = inputConfigStrToMap(value);
}

void input::startGame(){

}

void input::endGame(){

}

void input::changeKeyMapToKeyboard(Uint8 keyIdx, SDL_Keycode keyCode){
    keyMaps[keyIdx].type = SDL_KEYDOWN;
    keyMaps[keyIdx].keyCode = keyCode;
}

void input::getKeyMapInput(Uint8 keyIdx){
    bool waiting = true;

    SDL_Event e;
    while(waiting){
        while (SDL_PollEvent(&e)) {
            switch(e.type){
            case SDL_KEYDOWN:
                if(e.key.keysym.sym != SDLK_ESCAPE){
                    changeKeyMapToKeyboard(keyIdx, e.key.keysym.sym);
                }
                waiting = false;
                break;

            case SDL_JOYAXISMOTION:
                if((e.jaxis.value > KEY_MAP_MIN_AXIS_POSITIVE) || (e.jaxis.value < KEY_MAP_MIN_AXIS_NEGATIVE)){
                    keyMaps[keyIdx].type = SDL_JOYAXISMOTION;
                    keyMaps[keyIdx].jID = e.jaxis.which;
                    keyMaps[keyIdx].partID = e.jaxis.axis;
                    keyMaps[keyIdx].direction = (e.jaxis.value > KEY_MAP_MIN_AXIS_POSITIVE ? KEY_MAP_DIR_AXIS_POSITIVE : KEY_MAP_DIR_AXIS_NEGATIVE);
                    waiting = false;
                }
                break;

            case SDL_JOYHATMOTION:
                if(e.jhat.value != SDL_HAT_CENTERED){
                    keyMaps[keyIdx].type = SDL_JOYHATMOTION;
                    keyMaps[keyIdx].jID = e.jhat.which;
                    keyMaps[keyIdx].partID = e.jhat.hat;
                    keyMaps[keyIdx].direction = e.jhat.value;
                    waiting = false;
                }
                break;

            case SDL_JOYBUTTONDOWN:
                keyMaps[keyIdx].type = SDL_JOYBUTTONDOWN;
                keyMaps[keyIdx].jID = e.jbutton.which;
                keyMaps[keyIdx].partID = e.jbutton.button;
                waiting = false;
                break;
            }
        }
    }
}


string input::inputName(keyMap km){
    string kname;
    switch(km.type){
    case SDL_USEREVENT:
        kname = "------";
        break;
    case SDL_KEYDOWN:
        kname = "Key " + string(SDL_GetKeyName(km.keyCode)) ;
        break;
    case SDL_JOYAXISMOTION:
        kname = "Axis " + intToString(km.jID) + "-" + intToString(km.partID) + " " + (km.direction == KEY_MAP_DIR_AXIS_POSITIVE ? "+" : "-");
        break;
    case SDL_JOYHATMOTION:
        kname = "Hat " + intToString(km.jID) + "-" + intToString(km.partID);
        switch(km.direction){
        case SDL_HAT_UP:
            kname = kname + " Up";
            break;
        case SDL_HAT_RIGHTUP:
            kname = kname + " Right Up";
            break;
        case SDL_HAT_RIGHT:
            kname = kname + " Right";
            break;
        case SDL_HAT_RIGHTDOWN:
            kname = kname + " Right Down";
            break;
        case SDL_HAT_DOWN:
            kname = kname + " Down";
            break;
        case SDL_HAT_LEFTDOWN:
            kname = kname + " Left Down";
            break;
        case SDL_HAT_LEFT:
            kname = kname + " Left";
            break;
        case SDL_HAT_LEFTUP:
            kname = kname + " Left Up";
            break;
        }

        break;
    case SDL_JOYBUTTONDOWN:
        kname = "Button " + intToString(km.jID) + "-" + intToString(km.partID);
        break;
    }
    return kname;
}

string input::inputNameForKeyIdx(int keyIdx){
    return inputName(keyMaps[keyIdx]);
}

string input::inputMapToConfigStr(keyMap km){
    string kname;
    switch(km.type){
    case SDL_USEREVENT:
        kname = "NONE";
        break;
    case SDL_KEYDOWN:
        kname = "KEY " + intToString(km.keyCode) ;
        break;
    case SDL_JOYAXISMOTION:
        kname = "AXIS " + joystickGUIDStrFromID(km.jID) + " " + intToString(km.partID) + " " + intToString(km.direction);
        break;
    case SDL_JOYHATMOTION:
        kname = "HAT " + joystickGUIDStrFromID(km.jID) + " " + intToString(km.partID) + " " + intToString(km.direction);
        break;
    case SDL_JOYBUTTONDOWN:
        kname = "BUTTON " + joystickGUIDStrFromID(km.jID) + " " + intToString(km.partID);
        break;
    }
    return kname;
}

keyMap input::inputConfigStrToMap(const string& value){
    keyMap m;
    vector<string> elems;
    split(value, " ", elems);

    if(elems[0].compare("NONE") == 0){
        m.type = SDL_USEREVENT;
    }
    else if(elems[0].compare("KEY") == 0){
        m.type = SDL_KEYDOWN;
        m.partID = stringToInt(elems[1]);
    }
    else if(elems[0].compare("AXIS") == 0){
        m.type = SDL_JOYAXISMOTION;
        m.jID = joystickIDFromGUIDStr(elems[1]);
        m.partID = stringToInt(elems[2]);
        m.direction = stringToInt(elems[3]);
    }
    else if(elems[0].compare("HAT") == 0){
        m.type = SDL_JOYHATMOTION;
        m.jID = joystickIDFromGUIDStr(elems[1]);
        m.partID = stringToInt(elems[2]);
        m.direction = stringToInt(elems[3]);
   }
    else if(elems[0].compare("BUTTON") == 0){
        m.type = SDL_JOYBUTTONDOWN;
        m.jID = joystickIDFromGUIDStr(elems[1]);
        m.partID = stringToInt(elems[2]);
    }
    return m;
}

string input::joystickGUIDStrFromID(SDL_JoystickID id){
    char buffer[33];

    for (vector<SDL_Joystick*>::iterator it = joysticks.begin(); it != joysticks.end(); ++it){
        if (SDL_JoystickInstanceID(*it) == id){
            SDL_JoystickGetGUIDString(SDL_JoystickGetGUID(*it) , buffer, 33);
        }
    }
    string result = string(buffer);
    return result;
}

SDL_JoystickID input::joystickIDFromGUIDStr(const string& guidStr){
    for (vector<SDL_Joystick*>::iterator it = joysticks.begin(); it != joysticks.end(); ++it){
        if (joystickGUIDStrFromID(SDL_JoystickInstanceID(*it)).compare(guidStr) == 0){
            return SDL_JoystickInstanceID(*it);
        }
    }
    return 0;
}

void input::handleUserInput(){
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch(e.type){
        case SDL_KEYDOWN:
            if(e.key.keysym.sym == SDLK_ESCAPE){
                gameManager::gm->functionKeyPressed(KEY_IDX_F0_STOP);
            }
            else{

            }
            break;

        }
    }
}
