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
