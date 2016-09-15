#include <iostream>
#include "common.h"

using namespace std;

int main(int argc, char* argv[]){
    if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK) < 0){
        cout << "SDL2 init failed " << SDL_GetError() << endl;
        return 1;
    }
    atexit(SDL_Quit);


    return 0;
}
