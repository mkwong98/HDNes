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

void mainFrameImp::configKeyClicked( wxCommandEvent& event ){
    int keyID;
    if(event.GetEventObject() == btnP1Up){
        keyID = KEY_IDX_P1_UP;
    }
    else if(event.GetEventObject() == btnP1Left){
        keyID = KEY_IDX_P1_LEFT;
    }
    else if(event.GetEventObject() == btnP1Right){
        keyID = KEY_IDX_P1_RIGHT;
    }
    else if(event.GetEventObject() == btnP1Down){
        keyID = KEY_IDX_P1_DOWN;
    }
    else if(event.GetEventObject() == btnP1Select){
        keyID = KEY_IDX_P1_SELECT;
    }
    else if(event.GetEventObject() == btnP1Start){
        keyID = KEY_IDX_P1_START;
    }
    else if(event.GetEventObject() == btnP1B){
        keyID = KEY_IDX_P1_B;
    }
    else if(event.GetEventObject() == btnP1A){
        keyID = KEY_IDX_P1_A;
    }

    if(event.GetEventObject() == btnP2Up){
        keyID = KEY_IDX_P2_UP;
    }
    else if(event.GetEventObject() == btnP2Left){
        keyID = KEY_IDX_P2_LEFT;
    }
    else if(event.GetEventObject() == btnP2Right){
        keyID = KEY_IDX_P2_RIGHT;
    }
    else if(event.GetEventObject() == btnP2Down){
        keyID = KEY_IDX_P2_DOWN;
    }
    else if(event.GetEventObject() == btnP2Select){
        keyID = KEY_IDX_P2_SELECT;
    }
    else if(event.GetEventObject() == btnP2Start){
        keyID = KEY_IDX_P2_START;
    }
    else if(event.GetEventObject() == btnP2B){
        keyID = KEY_IDX_P2_B;
    }
    else if(event.GetEventObject() == btnP2A){
        keyID = KEY_IDX_P2_A;
    }

    gameManager::gm->setInputForKey(keyID);
    updateDisplay();
}

void mainFrameImp::updateDisplay(){
    fslROMPicker->SetPath(wxString(gameManager::gm->romF->romPath));
    rbnCurrentSlot->SetSelection(gameManager::gm->romF->currentStateSlot);
    chkRotateSlot->SetValue(gameManager::gm->romF->rotateState);
    chkOverwriteBat->SetValue(gameManager::gm->romF->overwriteBat);

    btnP1Up->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P1_UP)));
    btnP1Left->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P1_LEFT)));
    btnP1Right->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P1_RIGHT)));
    btnP1Down->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P1_DOWN)));
    btnP1Select->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P1_SELECT)));
    btnP1Start->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P1_START)));
    btnP1B->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P1_B)));
    btnP1A->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P1_A)));

    btnP2Up->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P2_UP)));
    btnP2Left->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P2_LEFT)));
    btnP2Right->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P2_RIGHT)));
    btnP2Down->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P2_DOWN)));
    btnP2Select->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P2_SELECT)));
    btnP2Start->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P2_START)));
    btnP2B->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P2_B)));
    btnP2A->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_P2_A)));

}
