#include "mainFrameImp.h"
#include "../gameManager.h"

mainFrameImp::mainFrameImp( wxWindow* parent )
:
mainFrame( parent ){

}

void mainFrameImp::startGame( wxCommandEvent& event ){
    gameManager::gm->runGame();
}

void mainFrameImp::romSelected( wxFileDirPickerEvent& event ){
    gameManager::gm->romSelected(event.GetPath().ToStdString());
}

void mainFrameImp::stateSlotSelected( wxCommandEvent& event ){
    gameManager::gm->romF->currentStateSlot = event.GetSelection();
}

void mainFrameImp::rotateSlotSelected( wxCommandEvent& event ){
    gameManager::gm->romF->rotateState = event.IsChecked();
}

void mainFrameImp::overwriteBatSelected( wxCommandEvent& event ){
    gameManager::gm->romF->overwriteBat = event.IsChecked();
}

void mainFrameImp::updateDisplay(){
    this->fslROMPicker->SetPath(wxString(gameManager::gm->romF->romPath));
    this->rbnCurrentSlot->SetSelection(gameManager::gm->romF->currentStateSlot);
    this->chkRotateSlot->SetValue(gameManager::gm->romF->rotateState);
    this->chkOverwriteBat->SetValue(gameManager::gm->romF->overwriteBat);
}
