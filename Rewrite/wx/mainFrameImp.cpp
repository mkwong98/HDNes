#include "mainFrameImp.h"
#include "../gameManager.h"
#include "../emu/gameFile.h"
#include "../emu/input.h"
#include "../emu/video.h"
#include "../emu/audio.h"

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
    gameManager::gm->changeSaveStateSlot(event.GetSelection());
}

void mainFrameImp::rotateSlotSelected( wxCommandEvent& event ){
    gameManager::gm->changeUseRotateState(event.IsChecked());
}

void mainFrameImp::overwriteBatSelected( wxCommandEvent& event ){
    gameManager::gm->changeOverwriteBat(event.IsChecked());
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

    if(event.GetEventObject() == btnKeyPause){
        keyID = KEY_IDX_F1_PAUSE;
    }
    else if(event.GetEventObject() == btnKeyAdvanceFrame){
        keyID = KEY_IDX_F1_ADVANCE_FRAME;
    }
    else if(event.GetEventObject() == btnKeyCaptureScreen){
        keyID = KEY_IDX_F1_CAPTURE_SCREEN;
    }
    else if(event.GetEventObject() == btnKeyToggleContScrCap){
        keyID = KEY_IDX_F1_TOOGLE_CONT_SCR_CAP;
    }
    else if(event.GetEventObject() == btnKeyReset){
        keyID = KEY_IDX_F1_RESET;
    }

    if(event.GetEventObject() == btnKeySaveState){
        keyID = KEY_IDX_F2_SAVE_STATE;
    }
    else if(event.GetEventObject() == btnKeyLoadState){
        keyID = KEY_IDX_F2_LOAD_STATE;
    }
    else if(event.GetEventObject() == btnKeyLoadLastState){
        keyID = KEY_IDX_F2_LOAD_LAST_STATE;
    }
    else if(event.GetEventObject() == btnKeyRotateState){
        keyID = KEY_IDX_F2_ROTATE_STATE;
    }

    if(event.GetEventObject() == btnKeySlot1){
        keyID = KEY_IDX_F3_SLOT1;
    }
    else if(event.GetEventObject() == btnKeySlot2){
        keyID = KEY_IDX_F3_SLOT2;
    }
    else if(event.GetEventObject() == btnKeySlot3){
        keyID = KEY_IDX_F3_SLOT3;
    }
    else if(event.GetEventObject() == btnKeySlot4){
        keyID = KEY_IDX_F3_SLOT4;
    }
    else if(event.GetEventObject() == btnKeySlot5){
        keyID = KEY_IDX_F3_SLOT5;
    }
    else if(event.GetEventObject() == btnKeySlot6){
        keyID = KEY_IDX_F3_SLOT6;
    }
    else if(event.GetEventObject() == btnKeySlot7){
        keyID = KEY_IDX_F3_SLOT7;
    }
    else if(event.GetEventObject() == btnKeySlot8){
        keyID = KEY_IDX_F3_SLOT8;
    }
    else if(event.GetEventObject() == btnKeySlot9){
        keyID = KEY_IDX_F3_SLOT9;
    }
    else if(event.GetEventObject() == btnKeySlot10){
        keyID = KEY_IDX_F3_SLOT10;
    }

    if(event.GetEventObject() == btnKeyHDCapFrame){
        keyID = KEY_IDX_F4_HD_CAP_FRAME;
    }
    else if(event.GetEventObject() == btnKeyToogleAutoHDCap){
        keyID = KEY_IDX_F4_TOOGLE_AUTO_HD_CAP;
    }
    else if(event.GetEventObject() == btnKeyToogleIgnoreEdge){
        keyID = KEY_IDX_F4_TOOGLE_IGNORE_EDGE;
    }

    gameManager::gm->setInputForKey(keyID);
    updateDisplay();
}

void mainFrameImp::updateDisplay(){
    fslROMPicker->SetPath(wxString(gameManager::gm->romF->romPath));
    rbnCurrentSlot->SetSelection(gameManager::gm->romF->currentStateSlot);
    chkRotateSlot->SetValue(gameManager::gm->romF->rotateState);
    chkOverwriteBat->SetValue(gameManager::gm->romF->overwriteBat);

    rbnScreenSize->SetSelection(gameManager::gm->vid->screenSize);
    spnContCapRate->SetValue(gameManager::gm->vid->conCapRate);
    chkUseHDGraphicsPack->SetValue(gameManager::gm->vid->useHDPack);
    chkGenHDData->SetValue(gameManager::gm->vid->autoCaptureForHD);
    chkIgnoreEdge->SetValue(gameManager::gm->vid->ignoreEdge);

    sldVolume->SetValue(gameManager::gm->aud->volume);
    chkUseHDMusicPack->SetValue(gameManager::gm->aud->useHDPack);

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

    btnKeyPause->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F1_PAUSE)));
    btnKeyAdvanceFrame->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F1_ADVANCE_FRAME)));
    btnKeyCaptureScreen->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F1_CAPTURE_SCREEN)));
    btnKeyToggleContScrCap->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F1_TOOGLE_CONT_SCR_CAP)));
    btnKeyReset->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F1_RESET)));

    btnKeySaveState->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F2_SAVE_STATE)));
    btnKeyLoadState->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F2_LOAD_STATE)));
    btnKeyLoadLastState->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F2_LOAD_LAST_STATE)));
    btnKeyRotateState->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F2_ROTATE_STATE)));

    btnKeySlot1->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F3_SLOT1)));
    btnKeySlot2->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F3_SLOT2)));
    btnKeySlot3->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F3_SLOT3)));
    btnKeySlot4->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F3_SLOT4)));
    btnKeySlot5->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F3_SLOT5)));
    btnKeySlot6->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F3_SLOT6)));
    btnKeySlot7->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F3_SLOT7)));
    btnKeySlot8->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F3_SLOT8)));
    btnKeySlot9->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F3_SLOT9)));
    btnKeySlot10->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F3_SLOT10)));

    btnKeyHDCapFrame->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F4_HD_CAP_FRAME)));
    btnKeyToogleAutoHDCap->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F4_TOOGLE_AUTO_HD_CAP)));
    btnKeyToogleIgnoreEdge->SetLabel(wxString(gameManager::gm->inp->inputNameForKeyIdx(KEY_IDX_F4_TOOGLE_IGNORE_EDGE)));
}

void mainFrameImp::screenSizeSelected( wxCommandEvent& event ){
    gameManager::gm->setScreenSize(event.GetSelection());
}

void mainFrameImp::contCapRateSelected( wxSpinEvent& event ){
    gameManager::gm->setconCapRate(event.GetValue());
}

void mainFrameImp::useGPackSelected( wxCommandEvent& event ){
    gameManager::gm->setUseHDPack(event.IsChecked());
}

void mainFrameImp::autoCaptureForHDSelected( wxCommandEvent& event ){
    gameManager::gm->setGenHDData(event.IsChecked());
}

void mainFrameImp::ignoreEdgeSelected( wxCommandEvent& event ){
    gameManager::gm->setIgnoreEdge(event.IsChecked());
}

void mainFrameImp::volumeChanged( wxScrollEvent& event ){
    gameManager::gm->setVolume(event.GetInt());
}

void mainFrameImp::useMPackSelected( wxCommandEvent& event ){
    gameManager::gm->setUseMusicHDPack(event.IsChecked());
}

