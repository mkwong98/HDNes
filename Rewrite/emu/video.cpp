#include <GL/glew.h>
#include "video.h"
#include "../gameManager.h"

using namespace std;

video::video(){
    screenSize = 0;
    conCapRate = 15;
    useHDPack = true;
    autoCaptureForHD = false;
    ignoreEdge = false;
}

video::~video(){
    //dtor
}

void video::initGameConfig(){
}


string video::partName(){
    return string("video");
}


void video::saveConfigLines(fstream* fs){
    saveConfigLine(fs, "screenSize", intToString(screenSize));
    saveConfigLine(fs, "conCapRate", intToString(conCapRate));
    saveConfigLine(fs, "useHDPack", (useHDPack ? "Y" : "N"));
    saveConfigLine(fs, "genHDData", (autoCaptureForHD ? "Y" : "N"));
    saveConfigLine(fs, "ignoreEdge", (ignoreEdge ? "Y" : "N"));
}

void video::saveGameConfigLines(fstream* fs){
}

void video::loadConfigVal(const string& hdr, const string& value){
    if(hdr.compare("screenSize") == 0){
        screenSize = stringToInt(value);
    }
    else if(hdr.compare("conCapRate") == 0){
        conCapRate = stringToInt(value);
    }
    else if(hdr.compare("useHDPack") == 0){
        useHDPack = (value.compare("Y") == 0);
    }
    else if(hdr.compare("genHDData") == 0){
        autoCaptureForHD = (value.compare("Y") == 0);
    }
    else if(hdr.compare("ignoreEdge") == 0){
        ignoreEdge = (value.compare("Y") == 0);
    }
}

void video::startGame(){
    int screenScale;
    switch(screenSize){
    case 0:
        screenScale = 1;
        break;
    case 1:
        screenScale = 2;
        break;
    case 2:
        screenScale = 4;
        break;
    }

    if((displayWindow = SDL_CreateWindow("HDNes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenScale * 256, screenScale * 240, SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL)) == NULL) {
        return;
    }
    glcontext = SDL_GL_CreateContext(displayWindow);
    GLenum err = glewInit();
    glShadeModel(GL_SMOOTH);
	glEnable (GL_BLEND);
	glEnable (GL_DEPTH_TEST);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_GL_SwapWindow(displayWindow);


}

void video::endGame(){
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(displayWindow);

}

void video::setScreenSize(Uint8 sizeIdx){
    screenSize = sizeIdx;
    if(gameManager::gm->gameState != GAME_STATE_STOPPED){
        endGame();
        startGame();
    }
}

void video::setconCapRate(Uint16 rate){
    conCapRate = rate;
}

void video::setUseHDPack(bool use){
    useHDPack = use;
}

void video::setGenHDData(bool use){
    autoCaptureForHD = use;
}

void video::setIgnoreEdge(bool use){
    ignoreEdge = use;
}



