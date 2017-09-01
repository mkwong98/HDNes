#define SDL_MAIN_HANDLED
#include <SDL2\SDL.h>
#include "hdnesPackEditormainForm.h"
#include "main.h"

using namespace std;
IMPLEMENT_APP(main)

hdnesPackEditormainForm* main::mForm;

main::main(void){
    SDL_SetMainReady();
	SDL_Init(0);
}

main::~main(void){
    SDL_Quit();
}

bool main::OnInit(){
	mForm = new hdnesPackEditormainForm(NULL);
	mForm->Show(true);
	return true;
}
