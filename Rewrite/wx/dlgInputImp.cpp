#include "dlgInputImp.h"
#include "../emu/input.h"

dlgInputImp::dlgInputImp( wxWindow* parent )
:
dlgInput( parent )
{

}

void dlgInputImp::showInputDialog( wxActivateEvent& event ){
    bool waiting = true;
/*
    SDL_Event e;
    while(waiting){
        while (SDL_PollEvent(&e)) {
            switch(e.type){
            case SDL_KEYDOWN:
                waiting = false;
                break;
            }
        }
    }

    close(0);
    */
}
