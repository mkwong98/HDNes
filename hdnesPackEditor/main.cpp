#define SDL_MAIN_HANDLED
#include <SDL2\SDL.h>
#include "hdnesPackEditormainForm.h"
#include "main.h"

using namespace std;
IMPLEMENT_APP(main)

main::main(void){
    SDL_SetMainReady();
	SDL_Init(0);
}

main::~main(void){
    SDL_Quit();
}

bool main::OnInit(){
	hdnesPackEditormainForm* ui = new hdnesPackEditormainForm(NULL);
	ui->Show(true);
	return true;
}
