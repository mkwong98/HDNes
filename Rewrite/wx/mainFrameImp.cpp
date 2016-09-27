#include "mainFrameImp.h"

mainFrameImp::mainFrameImp( wxWindow* parent )
:
mainFrame( parent )
{

}

void mainFrameImp::startGame( wxCommandEvent& event )
{
// TODO: Implement startGame
    gm->run_game();
}
