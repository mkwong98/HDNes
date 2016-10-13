#include "mainFrameImp.h"

mainFrameImp::mainFrameImp( wxWindow* parent )
:
mainFrame( parent ){

}

void mainFrameImp::startGame( wxCommandEvent& event ){
    gm->runGame();
}

void mainFrameImp::romSelected( wxFileDirPickerEvent& event ){
    gm->romSelected(event.GetPath().ToStdString());
}

void mainFrameImp::stateSlotSelected( wxCommandEvent& event ){
    gm->romF->currentStateSlot = event.GetSelection();
}

void mainFrameImp::rotateSlotSelected( wxCommandEvent& event ){
    gm->romF->rotateState = event.IsChecked();
}

void mainFrameImp::updateDisplay(){
    this->fslROMPicker->SetPath(wxString(gm->romF->romPath));
    this->rbnCurrentSlot->SetSelection(gm->romF->currentStateSlot);
    this->chkRotateSlot->SetValue(gm->romF->rotateState);
}
