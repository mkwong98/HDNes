#include <GL/glew.h>
#include "video.h"

using namespace std;

video::video(){
}

video::~video(){
    //dtor
}

string video::partName(){
    return string("video");
}


void video::saveConfigLines(fstream* fs){
    saveConfigLine(fs, string("a"), string("b"));
}

void video::loadConfigVal(string hdr, string value){
    if(hdr.compare("a") == 0){

    }
}

void video::startGame(){
    if((displayWindow = SDL_CreateWindow("HDNes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL)) == NULL) {
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

    SDL_Delay(3000);
}

void video::endGame(){
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(displayWindow);

}
