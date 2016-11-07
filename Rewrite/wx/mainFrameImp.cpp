#include "mainFrameImp.h"
#include "../gameManager.h"
#include "../emu/gameFile.h"
#include "../emu/input.h"

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

void mainFrameImp::p1UpClicked( wxCommandEvent& event ){
    gameManager::gm->setInputForKey(KEY_IDX_P1_UP);
    updateDisplay();
}

void mainFrameImp::updateDisplay(){
    fslROMPicker->SetPath(wxString(gameManager::gm->romF->romPath));
    rbnCurrentSlot->SetSelection(gameManager::gm->romF->currentStateSlot);
    chkRotateSlot->SetValue(gameManager::gm->romF->rotateState);
    chkOverwriteBat->SetValue(gameManager::gm->romF->overwriteBat);

    btnP1Up->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P1_UP)));
}
