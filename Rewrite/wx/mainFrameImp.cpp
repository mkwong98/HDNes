#include "mainFrameImp.h"

mainFrameImp::mainFrameImp( wxWindow* parent )
:
mainFrame( parent )
{

}

void mainFrameImp::startGame( wxCommandEvent& event )
{
    gm->runGame();
}
