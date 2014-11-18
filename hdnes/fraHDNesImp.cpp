#include "StdAfx.h"
#include "fraHDNesImp.h"
#include "batchMapImp.h"
#include "paletteDialogImp.h"
#include "sysState.h"
#include <wx/rawbmp.h>
#include <Shlwapi.h>

fraHDNesImp::fraHDNesImp():fraHDNes(NULL){
	char tmpStr[3];

	fraHDNes(NULL);
	wxInitAllImageHandlers();
	screenTileCache = NULL;

	for(int i = SDLK_FIRST; i < SDLK_LAST; i++){
		keycodes[i] = i;
	}

	addKeyCode(cbo1UP);
	addKeyCode(cbo1DOWN);
	addKeyCode(cbo1LEFT);
	addKeyCode(cbo1RIGHT);
	addKeyCode(cbo1A);
	addKeyCode(cbo1B);
	addKeyCode(cbo1SELECT);
	addKeyCode(cbo1START);

	addKeyCode(cbo2UP);
	addKeyCode(cbo2DOWN);
	addKeyCode(cbo2LEFT);
	addKeyCode(cbo2RIGHT);
	addKeyCode(cbo2A);
	addKeyCode(cbo2B);
	addKeyCode(cbo2SELECT);
	addKeyCode(cbo2START);

	addKeyCode(cboEndGame);
	addKeyCode(cboSaveState);
	addKeyCode(cboLoadState);
	addKeyCode(cboScreenCap);

	addKeyCode(cboDataCap);
	addKeyCode(cboPause);
	addKeyCode(cboRunFrame);
	addKeyCode(cboContCap);

	editingMusic = -1;
	lstMusic->InsertColumn(0, wxT("Goto Next"), wxLIST_FORMAT_LEFT, 200);
	lstMusic->InsertColumn(0, wxT("Audio File"), wxLIST_FORMAT_LEFT, 200);
	lstMusic->InsertColumn(0, wxT("Play Type"), wxLIST_FORMAT_LEFT, 100);
	lstMusic->InsertColumn(0, wxT("Additional Conditions"), wxLIST_FORMAT_LEFT, 200);
	lstMusic->InsertColumn(0, wxT("Replace Value"), wxLIST_FORMAT_LEFT, 80);
	lstMusic->InsertColumn(0, wxT("Check Value"), wxLIST_FORMAT_LEFT, 80);
	lstMusic->InsertColumn(0, wxT("RAM Address"), wxLIST_FORMAT_LEFT, 80);
	lstMusic->InsertColumn(0, wxT("Priority"), wxLIST_FORMAT_LEFT, 50);

	for(int i = 0xF; i >= 0; i--){
		sprintf_s(tmpStr,"%x",i);
		lstMemory->InsertColumn(0, wxString(tmpStr, wxConvUTF8), wxLIST_FORMAT_LEFT, 35);		
	}
	lstMemory->InsertColumn(0, wxT(""), wxLIST_FORMAT_LEFT, 35);		

	for(int i = 0; i < 0x80; i++){
		sprintf_s(tmpStr,"%x",i);
		lstMemory->InsertItem(i, wxString(tmpStr, wxConvUTF8));
	}
	refreshGUI();
}


fraHDNesImp::~fraHDNesImp(){
	if(gm != NULL){
		delete gm;
	}
	if(screenTileCache){
		free(screenTileCache);
	}
}

void fraHDNesImp::refreshGUI(){
    m_filePicker1->SetPath(wxString(setting->gamePath.c_str(), wxConvUTF8));
	refreshInputGUI();
	refreshVideoGUI();
	refreshAudioGUI();
}

void fraHDNesImp::addKeyCode(wxChoice* cbobox){
	string keyname;
	for(int i = SDLK_FIRST; i < SDLK_LAST; i++){
		keyname = string(SDL_GetKeyName((SDLKey)i));
		if(keyname.compare("unknown key") != 0){
			cbobox->Append(wxString(keyname.c_str(), wxConvUTF8), &(keycodes[i]));
		}
	}
}

void fraHDNesImp::showKeyCode(wxChoice* cbobox, SDLKey key){
	cbobox->SetSelection(cbobox->FindString(wxString(SDL_GetKeyName(key), wxConvUTF8)));
}


void fraHDNesImp::refreshInputGUI(){
	showKeyCode(cbo1UP, inputCore->controller[0][BUTTON_UP].assignedKey);
	showKeyCode(cbo1DOWN, inputCore->controller[0][BUTTON_DOWN].assignedKey);
	showKeyCode(cbo1LEFT, inputCore->controller[0][BUTTON_LEFT].assignedKey);
	showKeyCode(cbo1RIGHT, inputCore->controller[0][BUTTON_RIGHT].assignedKey);
	showKeyCode(cbo1A, inputCore->controller[0][BUTTON_A].assignedKey);
	showKeyCode(cbo1B, inputCore->controller[0][BUTTON_B].assignedKey);
	showKeyCode(cbo1SELECT, inputCore->controller[0][BUTTON_SELECT].assignedKey);
	showKeyCode(cbo1START, inputCore->controller[0][BUTTON_START].assignedKey);

	showKeyCode(cbo2UP, inputCore->controller[1][BUTTON_UP].assignedKey);
	showKeyCode(cbo2DOWN, inputCore->controller[1][BUTTON_DOWN].assignedKey);
	showKeyCode(cbo2LEFT, inputCore->controller[1][BUTTON_LEFT].assignedKey);
	showKeyCode(cbo2RIGHT, inputCore->controller[1][BUTTON_RIGHT].assignedKey);
	showKeyCode(cbo2A, inputCore->controller[1][BUTTON_A].assignedKey);
	showKeyCode(cbo2B, inputCore->controller[1][BUTTON_B].assignedKey);
	showKeyCode(cbo2SELECT, inputCore->controller[1][BUTTON_SELECT].assignedKey);
	showKeyCode(cbo2START, inputCore->controller[1][BUTTON_START].assignedKey);

	showKeyCode(cboEndGame, inputCore->setting[SETTING_END_EMU].assignedKey);
	showKeyCode(cboSaveState, inputCore->setting[SETTING_SAVE_STATE].assignedKey);
	showKeyCode(cboLoadState, inputCore->setting[SETTING_LOAD_STATE].assignedKey);
	showKeyCode(cboScreenCap, inputCore->setting[SETTING_SCREENCAP].assignedKey);
	showKeyCode(cboDataCap, inputCore->setting[SETTING_CAP_DATA].assignedKey);
	showKeyCode(cboPause, inputCore->setting[SETTING_PAUSE].assignedKey);
	showKeyCode(cboRunFrame, inputCore->setting[SETTING_RUN_FRAME].assignedKey);
	showKeyCode(cboContCap, inputCore->setting[SETTING_CONT_CAP].assignedKey);

}

void fraHDNesImp::refreshVideoGUI(){
    switch (vid->screenSizeOption) {
        case SCREEN_SIZE_1X:
            m_radioBtn1->SetValue(true);
            break;
        case SCREEN_SIZE_2X:
            m_radioBtn2->SetValue(true);
            break;
        case SCREEN_SIZE_4X:
            m_radioBtn3->SetValue(true);
            break;
        default:
            m_radioBtn4->SetValue(true);
            txtwidth->SetValue(wxString(to_string((long double)(vid->screenSizeWidth)).c_str(), wxConvUTF8));
            txtheight->SetValue(wxString(to_string((long double)(vid->screenSizeHeight)).c_str(), wxConvUTF8));
            break;            
    }
	chkUsePack->SetValue(vid->usePack);
	rbxGenerateData->SetSelection(vid->editRecordingType);
	chkNearEdge->SetValue(vid->cutEdgeTiles);
	chkCHRRamEdit->SetValue(!vid->chrRamMatch);
	spnCapRate->SetValue(vid->capRate);
}

void fraHDNesImp::refreshGraphicsPackGUI(){
	cboScreen->Clear();
	for(unsigned int i = 0; i < vid->screenFileNameList.size(); i++){
		if(vid->screenNameList[i].compare("/") == 0){
			cboScreen->Append(wxString(vid->screenFileNameList[i].c_str(), wxConvUTF8));
		}
		else{
			cboScreen->Append(wxString(vid->screenNameList[i].c_str(), wxConvUTF8));
		}
	}
	cboScreen->Append(wxString("All", wxConvUTF8));
	cboScreen->SetSelection(0);
	loadScreen();
	loadScreenTiles();

	switch(vid->packScale){
	case 1:
		optPackScale1->SetValue(true);
		break;
	case 2:
		optPackScale2->SetValue(true);
		break;
	case 4:
		optPackScale4->SetValue(true);
		break;
	}

	cboImage->Clear();
	for(unsigned int i = 0; i < vid->bmpInfos.size(); i++){
		cboImage->Append(wxString(vid->bmpInfos[i].filename.c_str(), wxConvUTF8));
	}
}

void fraHDNesImp::refreshAudioGUI(){
	chkUseAudioPack->SetValue(mixer->usePack);
}
void fraHDNesImp::refreshAudioPackGUI(){
	lstMusic->DeleteAllItems();
	for(unsigned int i = 0; i < mixer->musicList.size(); i++){
		musicPiece b = mixer->musicList[i];
		lstMusic->InsertItem(i, wxString(to_string((long double)b.priority).c_str(), wxConvUTF8));

		lstMusic->SetItem(i, 1, wxString(int_to_hex(b.ramAddress).c_str(), wxConvUTF8));
		if(b.hasCheck){
			lstMusic->SetItem(i, 2, wxString(int_to_hex(b.checkValue).c_str(), wxConvUTF8));
		}
		if(b.hasReplace){
			lstMusic->SetItem(i, 3, wxString(int_to_hex(b.replaceValue).c_str(), wxConvUTF8));
		}
		lstMusic->SetItem(i, 4, wxString(b.conditions.c_str(), wxConvUTF8));
		switch(b.playType){
		case 0:
			lstMusic->SetItem(i, 5, L"Repeat");
			break;
		case 1:
			lstMusic->SetItem(i, 5, L"Once and return");
			break;
		case 2:
			lstMusic->SetItem(i, 5, L"Once and stop");
			break;
		case 3:
			lstMusic->SetItem(i, 5, L"Once separately");
			break;
		}

		if(b.mp3Idx >= 0){
			lstMusic->SetItem(i, 6, wxString(mixer->mp3List[b.mp3Idx].c_str(), wxConvUTF8));
		}
		else if(b.mp3Idx == -1){
			lstMusic->SetItem(i, 6, wxString("(Silence)", wxConvUTF8));
		}
		else if(b.mp3Idx == -2){
			lstMusic->SetItem(i, 6, wxString("(No change)", wxConvUTF8));
		}
		lstMusic->SetItem(i, 7, wxString((b.gotoNext ? "Y" : "N"), wxConvUTF8));
	}
	cboMP3file->Clear();
	cboMP3file->Append(wxString("(No change)", wxConvUTF8));
	cboMP3file->Append(wxString("(Silence)", wxConvUTF8));
	for(unsigned int i = 0; i < mixer->mp3List.size(); i++){
		cboMP3file->Append(wxString(mixer->mp3List[i].c_str(), wxConvUTF8));
	}
	if(editingMusic >= 0){
		refreshMP3GUI();
	}
}



void fraHDNesImp::powerButtonClicked( wxCommandEvent& event ) { 
	if(gm == NULL){
		romDat->loadRom(string(m_filePicker1->GetPath().char_str()));
		gm = new gameManager();
		gm->start();
	}
	else{
		gm->continuePlay = false;
	}
}

void fraHDNesImp::input1UP( wxCommandEvent& event ){
	inputCore->controller[0][BUTTON_UP].assignedKey = (*(SDLKey*)(cbo1UP->GetClientData(cbo1UP->GetCurrentSelection())));
}

void fraHDNesImp::input1DOWN( wxCommandEvent& event ){
	inputCore->controller[0][BUTTON_DOWN].assignedKey = (*(SDLKey*)(cbo1DOWN->GetClientData(cbo1DOWN->GetCurrentSelection())));
}

void fraHDNesImp::input1LEFT( wxCommandEvent& event ){
	inputCore->controller[0][BUTTON_LEFT].assignedKey = (*(SDLKey*)(cbo1LEFT->GetClientData(cbo1LEFT->GetCurrentSelection())));
}

void fraHDNesImp::input1RIGHT( wxCommandEvent& event ){
	inputCore->controller[0][BUTTON_RIGHT].assignedKey = (*(SDLKey*)(cbo1RIGHT->GetClientData(cbo1RIGHT->GetCurrentSelection())));
}

void fraHDNesImp::input1A( wxCommandEvent& event ){
	inputCore->controller[0][BUTTON_A].assignedKey = (*(SDLKey*)(cbo1A->GetClientData(cbo1A->GetCurrentSelection())));
}

void fraHDNesImp::input1B( wxCommandEvent& event ){
	inputCore->controller[0][BUTTON_B].assignedKey = (*(SDLKey*)(cbo1B->GetClientData(cbo1B->GetCurrentSelection())));
}

void fraHDNesImp::input1SELECT( wxCommandEvent& event ){
	inputCore->controller[0][BUTTON_SELECT].assignedKey = (*(SDLKey*)(cbo1SELECT->GetClientData(cbo1SELECT->GetCurrentSelection())));
}

void fraHDNesImp::input1START( wxCommandEvent& event ){
	inputCore->controller[0][BUTTON_START].assignedKey = (*(SDLKey*)(cbo1START->GetClientData(cbo1START->GetCurrentSelection())));
}

void fraHDNesImp::input2UP( wxCommandEvent& event ){
	inputCore->controller[1][BUTTON_UP].assignedKey = (*(SDLKey*)(cbo2UP->GetClientData(cbo2UP->GetCurrentSelection())));
}

void fraHDNesImp::input2DOWN( wxCommandEvent& event ){
	inputCore->controller[1][BUTTON_DOWN].assignedKey = (*(SDLKey*)(cbo2DOWN->GetClientData(cbo2DOWN->GetCurrentSelection())));
}

void fraHDNesImp::input2LEFT( wxCommandEvent& event ){
	inputCore->controller[1][BUTTON_LEFT].assignedKey = (*(SDLKey*)(cbo2LEFT->GetClientData(cbo2LEFT->GetCurrentSelection())));
}

void fraHDNesImp::input2RIGHT( wxCommandEvent& event ){
	inputCore->controller[1][BUTTON_RIGHT].assignedKey = (*(SDLKey*)(cbo2RIGHT->GetClientData(cbo2RIGHT->GetCurrentSelection())));
}

void fraHDNesImp::input2A( wxCommandEvent& event ){
	inputCore->controller[1][BUTTON_A].assignedKey = (*(SDLKey*)(cbo2A->GetClientData(cbo2A->GetCurrentSelection())));
}

void fraHDNesImp::input2B( wxCommandEvent& event ){
	inputCore->controller[1][BUTTON_B].assignedKey = (*(SDLKey*)(cbo2B->GetClientData(cbo2B->GetCurrentSelection())));
}

void fraHDNesImp::input2SELECT( wxCommandEvent& event ){
	inputCore->controller[1][BUTTON_SELECT].assignedKey = (*(SDLKey*)(cbo2SELECT->GetClientData(cbo2SELECT->GetCurrentSelection())));
}

void fraHDNesImp::input2START( wxCommandEvent& event ){
	inputCore->controller[1][BUTTON_START].assignedKey = (*(SDLKey*)(cbo2START->GetClientData(cbo2START->GetCurrentSelection())));
}

void fraHDNesImp::inputEndGame( wxCommandEvent& event ){
	inputCore->setting[SETTING_END_EMU].assignedKey = (*(SDLKey*)(cboEndGame->GetClientData(cboEndGame->GetCurrentSelection())));
}

void fraHDNesImp::inputSaveState( wxCommandEvent& event ){
	inputCore->setting[SETTING_SAVE_STATE].assignedKey = (*(SDLKey*)(cboSaveState->GetClientData(cboSaveState->GetCurrentSelection())));
}

void fraHDNesImp::inputLoadState( wxCommandEvent& event ){
	inputCore->setting[SETTING_LOAD_STATE].assignedKey = (*(SDLKey*)(cboLoadState->GetClientData(cboLoadState->GetCurrentSelection())));
}

void fraHDNesImp::inputScreenCap( wxCommandEvent& event ){
	inputCore->setting[SETTING_SCREENCAP].assignedKey = (*(SDLKey*)(cboScreenCap->GetClientData(cboScreenCap->GetCurrentSelection())));
}

void fraHDNesImp::inputDataCap( wxCommandEvent& event ){
	inputCore->setting[SETTING_CAP_DATA].assignedKey = (*(SDLKey*)(cboDataCap->GetClientData(cboDataCap->GetCurrentSelection())));
}

void fraHDNesImp::inputPause( wxCommandEvent& event ){
	inputCore->setting[SETTING_PAUSE].assignedKey = (*(SDLKey*)(cboPause->GetClientData(cboPause->GetCurrentSelection())));
}

void fraHDNesImp::inputRunFrame( wxCommandEvent& event ){
	inputCore->setting[SETTING_RUN_FRAME].assignedKey = (*(SDLKey*)(cboRunFrame->GetClientData(cboRunFrame->GetCurrentSelection())));
}

void fraHDNesImp::inputContCap( wxCommandEvent& event ){
	inputCore->setting[SETTING_CONT_CAP].assignedKey = (*(SDLKey*)(cboContCap->GetClientData(cboContCap->GetCurrentSelection())));
}

void fraHDNesImp::capRateChange( wxSpinEvent& event ) { 
	vid->capRate = spnCapRate->GetValue();
}


void fraHDNesImp::screen1x( wxCommandEvent& event ){
	if(m_radioBtn1->GetValue()) vid->screenSizeOption = SCREEN_SIZE_1X;
}

void fraHDNesImp::screen2x( wxCommandEvent& event ){
	if(m_radioBtn2->GetValue()) vid->screenSizeOption = SCREEN_SIZE_2X;
}

void fraHDNesImp::screen4x( wxCommandEvent& event ){
	if(m_radioBtn3->GetValue()) vid->screenSizeOption = SCREEN_SIZE_4X;
}

void fraHDNesImp::screenxx( wxCommandEvent& event ){
	if(m_radioBtn4->GetValue()){
		long tmpVal;
		vid->screenSizeOption = SCREEN_SIZE_XX;
		txtwidth->GetValue().ToLong(&tmpVal);
		vid->screenSizeWidth = tmpVal;
		txtheight->GetValue().ToLong(&tmpVal);
		vid->screenSizeHeight = tmpVal;
	}
}

void fraHDNesImp::screenWidth( wxKeyEvent& event ){
	if(vid->screenSizeOption == SCREEN_SIZE_XX){
		long tmpVal;
		txtwidth->GetValue().ToLong(&tmpVal);
		vid->screenSizeWidth = tmpVal;
	}
}

void fraHDNesImp::screenHeight( wxKeyEvent& event ){
	if(vid->screenSizeOption == SCREEN_SIZE_XX){
		long tmpVal;
		txtheight->GetValue().ToLong(&tmpVal);
		vid->screenSizeHeight = tmpVal;
	}
}

void fraHDNesImp::toggleGraphicsPack( wxCommandEvent& event ){
	vid->usePack = chkUsePack->GetValue();
}

void fraHDNesImp::toggleEditPack( wxCommandEvent& event ){
	vid->editRecordingType = rbxGenerateData->GetSelection();
}

void fraHDNesImp::toggleEdgeData( wxCommandEvent& event ){
	vid->cutEdgeTiles = chkNearEdge->GetValue();
}

void fraHDNesImp::toggleCHRRamEdit( wxCommandEvent& event ){
	vid->chrRamMatch = !chkCHRRamEdit->GetValue();
}


void fraHDNesImp::loadPackData( wxCommandEvent& event ){
	romDat->loadRom(string(m_filePicker1->GetPath().char_str()));
    if (romDat->romLoaded) {
        vid->RefreshPackSize();
		vid->CleanHiResPack();
		vid->CleanPackEdit();
		vid->ReadHiResPack();
		vid->ReadPackEdit();
    }
	refreshGraphicsPackGUI();
}

void fraHDNesImp::savePackData( wxCommandEvent& event ){
	vid->SaveHiResPack();
}

void fraHDNesImp::setPackScale( wxCommandEvent& event ){
	if(optPackScale1->GetValue() == true){
		vid->packScale = 1;
	}
	if(optPackScale2->GetValue() == true){
		vid->packScale = 2;
	}
	if(optPackScale4->GetValue() == true){
		vid->packScale = 4;
	}
	
}

void fraHDNesImp::showScreenShot( wxCommandEvent& event ){
	loadScreen();
	loadScreenTiles();
}

void fraHDNesImp::showCustomImage( wxCommandEvent& event ){
	loadImage();
}

void fraHDNesImp::loadScreen(){
	wxClientDC* objDC;
	string filename;
	
	if(cboScreen->GetSelection() < cboScreen->GetCount() - 1){
		filename = getEditPackPath() + vid->screenFileNameList[cboScreen->GetSelection()];
	}
	else{
		int selCount;
		wxArrayInt selections;
		bitmapE* b;
		selCount = lstScreenTiles->GetSelections(selections);
		if(selCount > 0){
			b = (bitmapE*)lstScreenTiles->GetClientData(selections[0]);
			filename = getEditPackPath() + vid->screenFileNameList[b->bitmapID];
		}
		else{
			return;
		}
	}
	objScreenImg = wxImage(wxString((filename + ".png").c_str(), wxConvUTF8));
	refreshScreenBitmap();

	objDC = new wxClientDC(pnlScreen);
	objDC->DrawBitmap(objScreenBmp, 0, 0);
	delete objDC;
	
	
}

void fraHDNesImp::loadImage(){
	wxClientDC* objDC;
	
	string filename = getHDPackPath() + "\\" + vid->bmpInfos[cboImage->GetSelection()].filename;
	objImageImg = wxImage(wxString(filename.c_str(), wxConvUTF8));

	refreshImageBitmap();
	pnlImage->ClearBackground();
	objDC = new wxClientDC(pnlImage);
	objDC->DrawBitmap(objImageBmp, 0, 0);
	delete objDC;
}

void fraHDNesImp::toggleShowAllTiles( wxCommandEvent& event ){
	loadScreenTiles();
}


void fraHDNesImp::loadScreenTiles(){
	bitmapE b;
	bitmapF c;
	string tiledisplay;
	vector<bitmapE> v;
	bool patternMatch;
	
	//load tiles
	lstScreenTiles->Clear();
	if(screenTileCache){
		free(screenTileCache);
	}
	
	for(unsigned int i = 0; i < vid->packSize; i++){
		if(chkShowAllTiles->GetValue() && (cboScreen->GetSelection() != (cboScreen->GetCount() - 1))){
			if(vid->allEditData[i] != BAD_ADDRESS){
				for(unsigned int j = 0; j < vid->allEtiledata[vid->allEditData[i]].bitmapP.size(); j++){
					if(vid->allEtiledata[vid->allEditData[i]].bitmapP[j].bitmapID == cboScreen->GetSelection()){
						c = vid->allEtiledata[vid->allEditData[i]].bitmapP[j];
						b.bitmapID = c.bitmapID;
						b.colors = c.colors;
						b.rawDat = c.rawDat;
						b.patternAddress = vid->allEtiledata[vid->allEditData[i]].patternAddress;
						b.x = c.x;
						b.y = c.y;
						b.brightness = c.brightness;
						v.push_back(b);
					}
				}
			}
		}
		else{
			if(vid->editData[i] != BAD_ADDRESS){
				for(unsigned int j = 0; j < vid->etiledata[vid->editData[i]].bitmapP.size(); j++){
					if((vid->etiledata[vid->editData[i]].bitmapP[j].bitmapID == cboScreen->GetSelection()) || (cboScreen->GetSelection() == (cboScreen->GetCount() - 1))){
						c = vid->etiledata[vid->editData[i]].bitmapP[j];
						b.bitmapID = c.bitmapID;
						b.colors = c.colors;
						b.rawDat = c.rawDat;
						b.patternAddress = vid->etiledata[vid->editData[i]].patternAddress;
						b.x = c.x;
						b.y = c.y;
						b.brightness = c.brightness;
						v.push_back(b);
					}
				}
			}
		}
	}

	if(v.size() > 0){
		screenTileCache = (bitmapE*)malloc(v.size() * sizeof(bitmapE));
		for(unsigned int i = 0; i < v.size(); i++){
			bool tileFound = false;
			screenTileCache[i] = v[i];
			tiledisplay = to_string((long double)(screenTileCache[i].patternAddress)) + "," + vid->GetPaletteString(screenTileCache[i].colors); 
			//check for custom tile
			if(vid->packData[v[i].patternAddress] != BAD_ADDRESS){
				TileData t = vid->tdata[vid->packData[v[i].patternAddress]];
				for(unsigned int j = 0; j < t.bitmapP.size(); j++){
					if(t.bitmapP[j].colors.colorValues == v[i].colors.colorValues){
						if(romDat->chrPageCount > 0){
							patternMatch = true;
						}
						else{
							patternMatch = (t.bitmapP[j].rawDat.pixStrip1 == v[i].rawDat.pixStrip1
										&& t.bitmapP[j].rawDat.pixStrip2 == v[i].rawDat.pixStrip2
										&& t.bitmapP[j].rawDat.pixStrip3 == v[i].rawDat.pixStrip3
										&& t.bitmapP[j].rawDat.pixStrip4 == v[i].rawDat.pixStrip4);
						}
						if(patternMatch){
							tiledisplay = tiledisplay + "->" + vid->bmpInfos[t.bitmapP[j].bitmapID].filename + "," + to_string((long double)(t.bitmapP[j].x)) + "," + to_string((long double)(t.bitmapP[j].y)) + "," + to_string((long double)(t.bitmapP[j].brightness * 100)) + "%"; 
							tileFound = true;
						}
					}
				}
				if(!tileFound){
					if(t.defaultID != -1){
						tiledisplay = tiledisplay + "-> Using default";
						tileFound = true;
					}
				}
			}
			if(!tileFound && cboScreen->GetSelection() == (cboScreen->GetCount() - 1)){
				tiledisplay = tiledisplay + " @ " + vid->screenFileNameList[v[i].bitmapID];
			}
			lstScreenTiles->Append(wxString(tiledisplay.c_str(), wxConvUTF8), &screenTileCache[i]);
		}
	}
}

void fraHDNesImp::refreshScreenBitmap(){
	int neww, newh;
	if(objScreenImg.GetWidth() / objScreenImg.GetHeight() > pnlScreen->GetSize().GetWidth() / pnlScreen->GetSize().GetHeight()){
		neww = pnlScreen->GetSize().GetWidth();
		newh = objScreenImg.GetHeight() * pnlScreen->GetSize().GetWidth() / objScreenImg.GetWidth();
	}
	else{
		newh = pnlScreen->GetSize().GetHeight();	
		neww = objScreenImg.GetWidth() * pnlScreen->GetSize().GetHeight() / objScreenImg.GetHeight();
	}
	objScreenBmp = wxBitmap(objScreenImg.Scale(neww, newh) );
}

void fraHDNesImp::refreshImageBitmap(){
	int neww, newh;

	wxImage objimg;
	int offsetx;
	int offsety;
	int drawW;
	int drawH;

	int selCount;
	wxArrayInt selections;
	bitmapE* b;

	int screentileX;
	int screentileY;
	int imagetileX;
	int imagetileY;

	if(objImageImg.GetWidth() / objImageImg.GetHeight() > pnlImage->GetSize().GetWidth() / pnlImage->GetSize().GetHeight()){
		neww = pnlImage->GetSize().GetWidth();
		newh = objImageImg.GetHeight() * pnlImage->GetSize().GetWidth() / objImageImg.GetWidth();
	}
	else{
		newh = pnlImage->GetSize().GetHeight();	
		neww = objImageImg.GetWidth() * pnlImage->GetSize().GetHeight() / objImageImg.GetHeight();
	}
	objimg = objImageImg.Scale(neww, newh);
	if(!objimg.HasAlpha()) objimg.InitAlpha(); 
	if(string(txtMapX->GetValue().char_str()).compare("") != 0 
		&& string(txtMapY->GetValue().char_str()).compare("") != 0){

		imagetileX = stoi(string(txtMapX->GetValue().char_str()));
		imagetileY = stoi(string(txtMapY->GetValue().char_str()));
		
		selCount = lstScreenTiles->GetSelections(selections);

		if(selCount > 0){
			b = (bitmapE*)lstScreenTiles->GetClientData(selections[0]);
			screentileX = b->x;
			screentileY = b->y;
			for(int seli = 0; seli < selCount; seli++){
				b = (bitmapE*)lstScreenTiles->GetClientData(selections[seli]);

				offsetx = (imagetileX + ((b->x - screentileX) * vid->packScale)) * neww / objImageImg.GetWidth();
				offsety = (imagetileY + ((b->y - screentileY) * vid->packScale)) * newh / objImageImg.GetHeight();
				drawW = 8 * vid->packScale * neww / objImageImg.GetWidth();
				drawH = 8 * vid->packScale * newh / objImageImg.GetHeight();

				if(offsety + drawH < objimg.GetHeight() && offsetx + drawW < objimg.GetWidth()
					&& offsety >= 0 && offsetx >= 0){
					for(int i = offsetx; i < offsetx + drawW; i++){
						objimg.SetRGB(i, offsety + 1, 0, (seli == 0 ? 127 : 0), (seli == 0 ? 255 : 0));
						objimg.SetAlpha(i, offsety + 1, 255);
						if(offsety + 1 + drawH < objimg.GetHeight()){
							objimg.SetRGB(i, offsety + 1 + drawH, 0, (seli == 0 ? 127 : 0), (seli == 0 ? 255 : 0));
							objimg.SetAlpha(i, offsety + 1 + drawH, 255);
						}
					}
					for(int j = offsety; j < offsety + drawH; j++){
						objimg.SetRGB(offsetx + 1, j, 0, (seli == 0 ? 127 : 0), (seli == 0 ? 255 : 0));
						objimg.SetAlpha(offsetx + 1, j, 255);
						if(offsetx + 1 + drawW < objimg.GetWidth()){
							objimg.SetRGB(offsetx + 1 + drawW, j, 0, (seli == 0 ? 127 : 0), (seli == 0 ? 255 : 0));
							objimg.SetAlpha(offsetx + 1 + drawW, j, 255);
						}
					}
					for(int i = offsetx; i < offsetx + drawW; i++){
						objimg.SetRGB(i, offsety, 255, (seli == 0 ? 127 : 255), (seli == 0 ? 0 : 255));
						objimg.SetAlpha(i, offsety, 255);
						if(offsety + drawH < objimg.GetHeight()){
							objimg.SetRGB(i, offsety + drawH, 255, (seli == 0 ? 127 : 255), (seli == 0 ? 0 : 255));
							objimg.SetAlpha(i, offsety + drawH, 255);
						}
					}
					for(int j = offsety; j < offsety + drawH; j++){
						objimg.SetRGB(offsetx, j, 255, (seli == 0 ? 127 : 255), (seli == 0 ? 0 : 255));
						objimg.SetAlpha(offsetx, j, 255);
						if(offsetx + drawW< objimg.GetWidth()){
							objimg.SetRGB(offsetx + drawW, j, 255, (seli == 0 ? 127 : 255), (seli == 0 ? 0 : 255));
							objimg.SetAlpha(offsetx + drawW, j, 255);
						}
					}			
				}
			}		
		}
	}
	objImageBmp = wxBitmap(objimg);
}


void fraHDNesImp::screenTileSelected( wxCommandEvent& event ){
	wxImage objimg;
	int offsetx;
	int offsety;
	int drawW;
	int drawH;
	int selCount;
	Uint8 byte1;
	Uint8 byte2;
	wxArrayInt selections;
	bitmapE* b;
	wxClientDC* objDC;

	loadScreen();
	objimg = objScreenBmp.ConvertToImage();

	selCount = lstScreenTiles->GetSelections(selections);

	if(selCount > 1 && (cboScreen->GetSelection() == cboScreen->GetCount() - 1)){
		for(int seli = 1; seli < selCount; seli++){
			lstScreenTiles->Deselect(selections[seli]);
		}
		selCount = 1;
	}

	for(int seli = 0; seli < selCount; seli++){
		b = (bitmapE*)lstScreenTiles->GetClientData(selections[seli]);

		//draw a box in the screenshot
		offsetx = b->x * objimg.GetWidth() / DISPLAY_WIDTH;
		offsety = b->y * objimg.GetHeight() / DISPLAY_HEIGHT;
		drawW = 8 * objimg.GetWidth() / DISPLAY_WIDTH;
		drawH = 8 * objimg.GetHeight() / DISPLAY_HEIGHT;

		for(int i = offsetx; i < offsetx + drawW; i++){
			if(i < objimg.GetWidth() && (offsety + 1) < objimg.GetHeight() && i >= 0 && (offsety + 1) >= 0)
				objimg.SetRGB(i, offsety + 1, 0, (seli == 0 ? 127 : 0), (seli == 0 ? 255 : 0));
			if(i < objimg.GetWidth() && (offsety + 1 + drawH) < objimg.GetHeight() && i >= 0 && (offsety + 1 + drawH) >= 0)
				objimg.SetRGB(i, offsety + 1 + drawH, 0, (seli == 0 ? 127 : 0), (seli == 0 ? 255 : 0));
		}
		for(int j = offsety; j < offsety + drawH; j++){
			if((offsetx + 1) < objimg.GetWidth() && j < objimg.GetHeight() && (offsetx + 1) >= 0 && j >= 0)
				objimg.SetRGB(offsetx + 1, j, 0, (seli == 0 ? 127 : 0), (seli == 0 ? 255 : 0));
			if((offsetx + 1 + drawW) < objimg.GetWidth() && j < objimg.GetHeight() && (offsetx + 1 + drawW) >= 0 && j >= 0)
				objimg.SetRGB(offsetx + 1 + drawW, j, 0, (seli == 0 ? 127 : 0), (seli == 0 ? 255 : 0));
		}
		for(int i = offsetx; i < offsetx + drawW; i++){
			if(i < objimg.GetWidth() && offsety < objimg.GetHeight() && i >= 0 && offsety >= 0)
				objimg.SetRGB(i, offsety, 255, (seli == 0 ? 127 : 255), (seli == 0 ? 0 : 255));
			if(i < objimg.GetWidth() && (offsety + drawH) < objimg.GetHeight() && i >= 0 && (offsety + drawH) >= 0)
				objimg.SetRGB(i, offsety + drawH, 255, (seli == 0 ? 127 : 255), (seli == 0 ? 0 : 255));
		}
		for(int j = offsety; j < offsety + drawH; j++){
			if(offsetx < objimg.GetWidth() && j < objimg.GetHeight() && offsetx >= 0 && j >= 0)
				objimg.SetRGB(offsetx, j, 255, (seli == 0 ? 127 : 255), (seli == 0 ? 0 : 255));
			if((offsetx + drawW) < objimg.GetWidth() && j < objimg.GetHeight() && (offsetx + drawW) >= 0 && j >= 0)
				objimg.SetRGB(offsetx + drawW, j, 255, (seli == 0 ? 127 : 255), (seli == 0 ? 0 : 255));
		}	
	}

	objScreenBmp = wxBitmap(objimg);
	displayScreenBitmap();

	if(selCount > 0){
		//display the first selected in a seperate panel
		b = (bitmapE*)lstScreenTiles->GetClientData(selections[0]);
		objimg = wxImage(8, 8, true);
		objimg.InitAlpha();
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				objimg.SetAlpha(0);
			}
		}

		for(int r = 0; r < 8; r++){
			//compose the tile
			if(romDat->chrPageCount > 0){
				byte1 = romDat->chrROM[(b->patternAddress << 4) + r];
				byte2 = romDat->chrROM[(b->patternAddress << 4) + 8 + r];
			}
			else{
				byte1 = *(((Uint8*)(&(b->rawDat))) + r);
				byte2 = *(((Uint8*)(&(b->rawDat))) + 8 + r);											
			}
			for(int c = 0; c < 8; c++){
				int pix = ((byte1 >> (7 - c)) & 0x01) | (((byte2 >> (7 - c)) & 0x01) << 1);
				switch(pix){
				case 0:
					objimg.SetAlpha(c, r, 0);
					objimg.SetRGB(c, r, 0, 0, 0);
					break;
				case 1:
					objimg.SetAlpha(c, r, 255);
					objimg.SetRGB(c, r, 
						(vid->colourList[b->colors.color1 & 0x3F] & 0xFF000000) >> 24, 
						(vid->colourList[b->colors.color1 & 0x3F] & 0x00FF0000) >> 16, 
						(vid->colourList[b->colors.color1 & 0x3F] & 0x0000FF00) >> 8);
					break;
				case 2:
					objimg.SetAlpha(c, r, 255);
					objimg.SetRGB(c, r, 
						(vid->colourList[b->colors.color2 & 0x3F] & 0xFF000000) >> 24, 
						(vid->colourList[b->colors.color2 & 0x3F] & 0x00FF0000) >> 16, 
						(vid->colourList[b->colors.color2 & 0x3F] & 0x0000FF00) >> 8);
					break;
				case 3:
					objimg.SetAlpha(c, r, 255);
					objimg.SetRGB(c, r, 
						(vid->colourList[b->colors.color3 & 0x3F] & 0xFF000000) >> 24, 
						(vid->colourList[b->colors.color3 & 0x3F] & 0x00FF0000) >> 16, 
						(vid->colourList[b->colors.color3 & 0x3F] & 0x0000FF00) >> 8);
					break;
				}
			}
		}
		pnlScreenTile->ClearBackground();
		objDC = new wxClientDC(pnlScreenTile);
		objDC->DrawBitmap(wxBitmap(objimg.Scale(pnlScreenTile->GetSize().GetWidth(), pnlScreenTile->GetSize().GetWidth() ) ), 0, 0);
		delete objDC;
	}

	
	pnlImage->ClearBackground();
	cboImage->SetSelection(-1);
	chkDefaultTile->SetValue(false);
	//check if the tile has a custom tile

	if(selCount > 0){
		b = (bitmapE*)lstScreenTiles->GetClientData(selections[0]);
		if(vid->packData[b->patternAddress] != BAD_ADDRESS){
			TileData t = vid->tdata[vid->packData[b->patternAddress]];
			txtMapX->SetValue(wxString("", wxConvUTF8)); 
			txtMapY->SetValue(wxString("", wxConvUTF8)); 
			for(unsigned int i = 0; i < t.bitmapP.size(); i++){
				if(t.bitmapP[i].colors.colorValues == b->colors.colorValues){
					cboImage->SetSelection(t.bitmapP[i].bitmapID);
					txtMapX->SetValue(wxString(to_string((long double)(t.bitmapP[i].x)).c_str(), wxConvUTF8)); 
					txtMapY->SetValue(wxString(to_string((long double)(t.bitmapP[i].y)).c_str(), wxConvUTF8));
					txtBrightness->SetValue(wxString(to_string((long double)(t.bitmapP[i].brightness * 100)).c_str(), wxConvUTF8));
					chkDefaultTile->SetValue(t.defaultID == i);
					loadImage();
					refreshImageBitmap();
					displayImageBitmap();
				}
			}
		}	
	}
}

void fraHDNesImp::ImageTileSelected( wxMouseEvent& event ){	
	int selectX;
	int selectY;
	float scale;

	if(!objImageImg.IsOk()) return;

	if(objImageImg.GetWidth() / objImageImg.GetHeight() > pnlImage->GetSize().GetWidth() / pnlImage->GetSize().GetHeight()){
		scale = (float)objImageImg.GetWidth() / (float)pnlImage->GetSize().GetWidth();
	}
	else{
		scale = (float)objImageImg.GetHeight() / (float)pnlImage->GetSize().GetHeight();
	}

	selectX = event.GetPosition().x * scale;
	selectX = selectX - (selectX % (8 * vid->packScale));
	selectY = event.GetPosition().y * scale;
	selectY = selectY - (selectY % (8 * vid->packScale));

	if(selectX < objImageImg.GetWidth() && selectY < objImageImg.GetHeight()){
		txtMapX->SetValue(wxString(to_string((long double)(selectX)).c_str(), wxConvUTF8)); 
		txtMapY->SetValue(wxString(to_string((long double)(selectY)).c_str(), wxConvUTF8));
		refreshImageBitmap();
		displayImageBitmap();
	}
}

void fraHDNesImp::displayScreenBitmap(){
	if(objScreenBmp.IsOk()){
		wxClientDC* objDC;
		objDC = new wxClientDC(pnlScreen);
		objDC->DrawBitmap(objScreenBmp, 0, 0);
		delete objDC;
	}
}

void fraHDNesImp::displayImageBitmap(){
	if(objImageBmp.IsOk()){
		pnlImage->ClearBackground();
		wxClientDC* objDC;
		objDC = new wxClientDC(pnlImage);
		objDC->DrawBitmap(objImageBmp, 0, 0);
		delete objDC;
	}
}

void fraHDNesImp::removeImageFromPack( wxCommandEvent& event ){
	bool hasWork;
	if(cboImage->GetSelection() == -1) return;
	//remove any mapping which uses that image
	for(unsigned int j = 0; j < vid->tdata.size(); j++){
		hasWork = true;
		while(hasWork){ 
			hasWork = false;
			for(unsigned int i = 0; i < vid->tdata[j].bitmapP.size(); i++){
				if(vid->tdata[j].bitmapP[i].bitmapID == cboImage->GetSelection()){
					//cancel default
					if(vid->tdata[j].defaultID == i){
						vid->tdata[j].defaultID = -1;
					}
					vid->tdata[j].bitmapP.erase(vid->tdata[j].bitmapP.begin() + i);
					hasWork = true;
				}
			}
		}
	}
	//remove the bitmap image
	vid->RemoveHiResImg(cboImage->GetSelection());

	//shift up all mappings using images after the deleted one
	for(unsigned int j = 0; j < vid->tdata.size(); j++){
		for(unsigned int i = 0; i < vid->tdata[j].bitmapP.size(); i++){
			if(vid->tdata[j].bitmapP[i].bitmapID > cboImage->GetSelection()){
				vid->tdata[j].bitmapP[i].bitmapID--;
			}
		}
	}

	refreshGraphicsPackGUI();
}

void fraHDNesImp::addImageToPack( wxFileDirPickerEvent& event ){
	string filename = string(m_filePicker2->GetPath().char_str());
	wxImage objImg;
	//load image for image size
	objImg = wxImage(wxString(filename.c_str(), wxConvUTF8));

	//create hd pack dir
	string packdir = getHDPackPath() + "\\";
    _mkdir(packdir.c_str());

	//get file name
	CHAR szPath[MAX_PATH];
	filename.copy(szPath, MAX_PATH, 0);
	szPath[filename.length()] = NULL;
	PathStripPathA(szPath);

	objImg.SaveFile(wxString((packdir + string(szPath)).c_str(), wxConvUTF8));

	vid->AddHiResImg(string(szPath));
	cboImage->Append(wxString(szPath, wxConvUTF8));
	cboImage->SetSelection(vid->bmpInfos.size() - 1);

	loadImage();
	displayImageBitmap();
}

void fraHDNesImp::confirmImgSelection( wxCommandEvent& event ){
	if(cboImage->GetSelection() == -1) return;
		
	int selCount;
	wxArrayInt selections;
	bitmapE* b;
	bitmapF c;

	int screentileX;
	int screentileY;
	int imagetileX;
	int imagetileY;
	int offsetx;
	int offsety;

	TileData t;
	int tid;
	bool bmpFound;
	int bid;
	bool patternMatch;

	if(string(txtMapX->GetValue().char_str()).compare("") != 0 
		&& string(txtMapY->GetValue().char_str()).compare("") != 0){

		imagetileX = stoi(string(txtMapX->GetValue().char_str()));
		imagetileY = stoi(string(txtMapY->GetValue().char_str()));
		
		selCount = lstScreenTiles->GetSelections(selections);
		if(selCount > 0){
			b = (bitmapE*)lstScreenTiles->GetClientData(selections[0]);
			screentileX = b->x;
			screentileY = b->y;
			for(int seli = 0; seli < selCount; seli++){
				b = (bitmapE*)lstScreenTiles->GetClientData(selections[seli]);
				c.bitmapID = b->bitmapID;
				c.colors = b->colors;
				c.rawDat = b->rawDat;
				c.x = b->x;
				c.y = b->y;
				c.brightness = b->brightness;

				offsetx = imagetileX + ((b->x - screentileX) * vid->packScale);
				offsety = imagetileY + ((b->y - screentileY) * vid->packScale);

				if(offsety + (8 * vid->packScale) <= objImageImg.GetHeight() && offsetx + (8 * vid->packScale) <= objImageImg.GetWidth()
					&& offsety >= 0 && offsetx >= 0){
					//check if the tile has a custom tile
					if(vid->packData[b->patternAddress] == BAD_ADDRESS){
						vid->packData[b->patternAddress] = vid->tdata.size();
						t.defaultID = -1;
						vid->tdata.push_back(t);
					}
					tid = vid->packData[b->patternAddress];

					//check existing mapping
					bmpFound = false;
					for(unsigned int i = 0; i < vid->tdata[tid].bitmapP.size(); i++){
						if(vid->tdata[tid].bitmapP[i].colors.colorValues == b->colors.colorValues){
							if(romDat->chrPageCount > 0){
								patternMatch = true;
							}
							else{
								patternMatch = (vid->tdata[tid].bitmapP[i].rawDat.pixStrip1 == b->rawDat.pixStrip1
											&& vid->tdata[tid].bitmapP[i].rawDat.pixStrip2 == b->rawDat.pixStrip2
											&& vid->tdata[tid].bitmapP[i].rawDat.pixStrip3 == b->rawDat.pixStrip3
											&& vid->tdata[tid].bitmapP[i].rawDat.pixStrip4 == b->rawDat.pixStrip4);
							}
							if(patternMatch){
								bid = i;
								bmpFound = true;
							}
						}
					}
					if(!bmpFound){
						//add new mapping
						bid = vid->tdata[tid].bitmapP.size();
						vid->tdata[tid].bitmapP.push_back(c);
					}
					vid->tdata[tid].bitmapP[bid].bitmapID = cboImage->GetSelection();
					if(string(txtMapX->GetValue().char_str()).compare("") != 0 
						&& string(txtMapY->GetValue().char_str()).compare("") != 0){
						vid->tdata[tid].bitmapP[bid].x = offsetx;
						vid->tdata[tid].bitmapP[bid].y = offsety;
					}
					if(string(txtBrightness->GetValue().char_str()).compare("") != 0){
						vid->tdata[tid].bitmapP[bid].brightness = 0.01f * stof(string(txtBrightness->GetValue().char_str()));
					}
					//set default value
					if(chkDefaultTile->GetValue()){
						vid->tdata[tid].defaultID = bid;	
					}
					else if(vid->tdata[tid].defaultID == bid){
						vid->tdata[tid].defaultID = -1;
					}
					//refresh screen tile list
					string tiledisplay = to_string((long double)(b->patternAddress)) + "," + vid->GetPaletteString(b->colors); 
					tiledisplay = tiledisplay + "->" + vid->bmpInfos[vid->tdata[tid].bitmapP[bid].bitmapID].filename + "," + to_string((long double)(vid->tdata[tid].bitmapP[bid].x)) + "," + to_string((long double)(vid->tdata[tid].bitmapP[bid].y)) + "," + to_string((long double)(vid->tdata[tid].bitmapP[bid].brightness * 100)) + "%"; 

					lstScreenTiles->SetString(selections[seli], wxString(tiledisplay.c_str(), wxConvUTF8));
				}
			}
		}
	}
}

void fraHDNesImp::cancelSelection( wxCommandEvent& event ){
	bool patternMatch;
	int selCount;
	int tid;
	wxArrayInt selections;
	bitmapE* b;

	selCount = lstScreenTiles->GetSelections(selections);
	if(selCount > 0){
		for(int seli = 0; seli < selCount; seli++){
			b = (bitmapE*)lstScreenTiles->GetClientData(selections[seli]);


			//check if the tile has a custom tile
			if(vid->packData[b->patternAddress] != BAD_ADDRESS){
				tid = vid->packData[b->patternAddress];

				//check existing mapping
				for(unsigned int i = 0; i < vid->tdata[tid].bitmapP.size(); i++){
					if(vid->tdata[tid].bitmapP[i].colors.colorValues == b->colors.colorValues){
						if(romDat->chrPageCount > 0){
							patternMatch = true;
						}
						else{
							patternMatch = (vid->tdata[tid].bitmapP[i].rawDat.pixStrip1 == b->rawDat.pixStrip1
										&& vid->tdata[tid].bitmapP[i].rawDat.pixStrip2 == b->rawDat.pixStrip2
										&& vid->tdata[tid].bitmapP[i].rawDat.pixStrip3 == b->rawDat.pixStrip3
										&& vid->tdata[tid].bitmapP[i].rawDat.pixStrip4 == b->rawDat.pixStrip4);
						}
						if(patternMatch){

							//cancel default
							if(vid->tdata[tid].defaultID == i){
								vid->tdata[tid].defaultID = -1;
							}
							vid->tdata[tid].bitmapP.erase(vid->tdata[tid].bitmapP.begin() + i);

							//refresh list
							string tiledisplay = to_string((long double)(b->patternAddress)) + "," + vid->GetPaletteString(b->colors); 
							if(vid->tdata[tid].defaultID != -1){
								tiledisplay = tiledisplay + "-> Using default";
							}
							lstScreenTiles->SetString(selections[seli], wxString(tiledisplay.c_str(), wxConvUTF8));
						}
					}
				}
			}
		}
	}
}

void fraHDNesImp::genHDPack( wxCommandEvent& event ){
	bool hasMap;
	bool hasAddress;
	Uint32 tileAddress;
	TileData t;

	wxImage objimg;
	wxImage objFimg;
	int fillx = 0;
	int filly = 0;
	bool newImgReq = true;
	Uint8 byte1;
	Uint8 byte2;
	bitmapF b;
	int fileID = 0;
	string filename;
	bmpInfo f;
	bool patternMatch;


	string dirpath = getHDPackPath();
	_mkdir(dirpath.c_str());

	if(cboScreen->GetSelection() < cboScreen->GetCount() - 1){
		//init image
		objimg = wxImage(DISPLAY_WIDTH, DISPLAY_HEIGHT, true);
		objimg.InitAlpha();
		for(int i = 0; i < DISPLAY_WIDTH; i++){
			for(int j = 0; j < DISPLAY_HEIGHT; j++){
				objimg.SetAlpha(0);
			}
		}

		for(unsigned int i = 0; i < vid->packSize; i++){
			if(vid->editData[i] != BAD_ADDRESS){
				//currently for bg only
				if(vid->etiledata[vid->editData[i]].defaultID == 0){
					for(unsigned int j = 0; j < vid->etiledata[vid->editData[i]].bitmapP.size(); j++){
						//check match current screen
						if((vid->etiledata[vid->editData[i]].bitmapP[j].bitmapID == cboScreen->GetSelection()) || (cboScreen->GetSelection() == (cboScreen->GetCount() - 1))){
							hasMap = false;
							hasAddress = false;
							tileAddress = vid->etiledata[vid->editData[i]].patternAddress;
							//pack data for default
							if(vid->packData[tileAddress] != BAD_ADDRESS){
								hasAddress = true;
								t = vid->tdata[vid->packData[tileAddress]];
								if(t.defaultID != -1){
									//no need to work if has default
									hasMap = true;
								}
							}
							else{
								//add tile to pack if none existed
								vid->packData[tileAddress] = vid->tdata.size();
								t.patternAddress = tileAddress;
								t.defaultID = -1;
								t.bitmapP.clear();
								vid->tdata.push_back(t);
							}


							if(!hasMap){
								hasMap = false;
								if(hasAddress){
									//check has matching tile in pack
									for(unsigned int k = 0; k < t.bitmapP.size(); k++){
										if(t.bitmapP[k].colors.colorValues == vid->etiledata[vid->editData[i]].bitmapP[j].colors.colorValues){
											if(romDat->chrPageCount > 0){
												patternMatch = true;
											}
											else{
												patternMatch = (t.bitmapP[k].rawDat.pixStrip1 == vid->etiledata[vid->editData[i]].bitmapP[j].rawDat.pixStrip1
															&& t.bitmapP[k].rawDat.pixStrip2 == vid->etiledata[vid->editData[i]].bitmapP[j].rawDat.pixStrip2
															&& t.bitmapP[k].rawDat.pixStrip3 == vid->etiledata[vid->editData[i]].bitmapP[j].rawDat.pixStrip3
															&& t.bitmapP[k].rawDat.pixStrip4 == vid->etiledata[vid->editData[i]].bitmapP[j].rawDat.pixStrip4);
											}
											if(patternMatch){
												hasMap = true;
											}
										}
									}
								}
								if(!hasMap){

									//add hd record
									b = vid->etiledata[vid->editData[i]].bitmapP[j];
									b.bitmapID = vid->bmpInfos.size();
									fillx = vid->etiledata[vid->editData[i]].bitmapP[j].x;
									filly = vid->etiledata[vid->editData[i]].bitmapP[j].y;
									b.x = fillx * vid->packScale;
									b.y = filly * vid->packScale;
									b.brightness = 1.0f;
									vid->tdata[vid->packData[tileAddress]].bitmapP.push_back(b);

									for(int r = 0; r < 8; r++){
										//compose the tile
										if(romDat->chrPageCount > 0){
											byte1 = romDat->chrROM[(tileAddress << 4) + r];
											byte2 = romDat->chrROM[(tileAddress << 4) + 8 + r];
										}
										else{
											byte1 = *(((Uint8*)(&b.rawDat)) + r);
											byte2 = *(((Uint8*)(&b.rawDat)) + 8 + r);											
										}
										for(int c = 0; c < 8; c++){
											int pix = ((byte1 >> (7 - c)) & 0x01) | (((byte2 >> (7 - c)) & 0x01) << 1);
											switch(pix){
											case 0:
												objimg.SetAlpha(fillx + c, filly + r, 0);
												objimg.SetRGB(fillx + c, filly + r, 0, 0, 0);
												break;
											case 1:
												objimg.SetAlpha(fillx + c, filly + r, 255);
												objimg.SetRGB(fillx + c, filly + r, 
													(vid->colourList[b.colors.color1 & 0x3F] & 0xFF000000) >> 24, 
													(vid->colourList[b.colors.color1 & 0x3F] & 0x00FF0000) >> 16, 
													(vid->colourList[b.colors.color1 & 0x3F] & 0x0000FF00) >> 8);
												break;
											case 2:
												objimg.SetAlpha(fillx + c, filly + r, 255);
												objimg.SetRGB(fillx + c, filly + r, 
													(vid->colourList[b.colors.color2 & 0x3F] & 0xFF000000) >> 24, 
													(vid->colourList[b.colors.color2 & 0x3F] & 0x00FF0000) >> 16, 
													(vid->colourList[b.colors.color2 & 0x3F] & 0x0000FF00) >> 8);
												break;
											case 3:
												objimg.SetAlpha(fillx + c, filly + r, 255);
												objimg.SetRGB(fillx + c, filly + r, 
													(vid->colourList[b.colors.color3 & 0x3F] & 0xFF000000) >> 24, 
													(vid->colourList[b.colors.color3 & 0x3F] & 0x00FF0000) >> 16, 
													(vid->colourList[b.colors.color3 & 0x3F] & 0x0000FF00) >> 8);
												break;
											}
										}
									}
								}
							}

						}
					}
				}
			}
		}

		objFimg = objimg.Scale(DISPLAY_WIDTH * vid->packScale, DISPLAY_HEIGHT * vid->packScale);
						
		CHAR szPath[MAX_PATH];
		filename = dirpath + "\\" + vid->screenFileNameList[cboScreen->GetSelection()] + ".png";
		filename.copy(szPath, MAX_PATH, 0);
		szPath[filename.length()] = NULL;

		objFimg.SaveFile(wxString(filename.c_str(), wxConvUTF8));
		f.filename = vid->screenFileNameList[cboScreen->GetSelection()] + ".png";
		f.width = DISPLAY_WIDTH * vid->packScale;
		f.height = DISPLAY_HEIGHT * vid->packScale;
		vid->bmpInfos.push_back(f);

	}
	else{
		//go though all unassigned tile and export to a png file
		for(unsigned int i = 0; i < vid->packSize; i++){
			if(vid->editData[i] != BAD_ADDRESS){
				hasMap = false;
				hasAddress = false;
				tileAddress = vid->etiledata[vid->editData[i]].patternAddress;
				if(vid->packData[tileAddress] != BAD_ADDRESS){
					hasAddress = true;
					t = vid->tdata[vid->packData[tileAddress]];
					if(t.defaultID != -1){
						//no need to work if has default
						hasMap = true;
					}
				}
				else{
					vid->packData[tileAddress] = vid->tdata.size();
					t.patternAddress = tileAddress;
					t.defaultID = -1;
					t.bitmapP.clear();
					vid->tdata.push_back(t);
				}
				if(!hasMap){
					for(unsigned int j = 0; j < vid->etiledata[vid->editData[i]].bitmapP.size(); j++){
						//check individual tile
						hasMap = false;
						if(hasAddress){
							for(unsigned int k = 0; k < t.bitmapP.size(); k++){
								if(t.bitmapP[k].colors.colorValues == vid->etiledata[vid->editData[i]].bitmapP[j].colors.colorValues){
									if(romDat->chrPageCount > 0){
										patternMatch = true;
									}
									else{
										patternMatch = (t.bitmapP[k].rawDat.pixStrip1 == vid->etiledata[vid->editData[i]].bitmapP[j].rawDat.pixStrip1
													&& t.bitmapP[k].rawDat.pixStrip2 == vid->etiledata[vid->editData[i]].bitmapP[j].rawDat.pixStrip2
													&& t.bitmapP[k].rawDat.pixStrip3 == vid->etiledata[vid->editData[i]].bitmapP[j].rawDat.pixStrip3
													&& t.bitmapP[k].rawDat.pixStrip4 == vid->etiledata[vid->editData[i]].bitmapP[j].rawDat.pixStrip4);
									}
									if(patternMatch){
										hasMap = true;
									}
								}
							}
						}
						if(!hasMap){
							//generate image
							if(newImgReq){
								fillx = 0;
								filly = 0;
								objimg = wxImage(GEN_HD_WIDTH, GEN_HD_HEIGHT, true);
								objimg.InitAlpha();
								newImgReq = false;
							}

							//add hd record
							b = vid->etiledata[vid->editData[i]].bitmapP[j];
							b.bitmapID = vid->bmpInfos.size();
							b.x = fillx * vid->packScale;
							b.y = filly * vid->packScale;
							b.brightness = 1.0f;
							vid->tdata[vid->packData[tileAddress]].bitmapP.push_back(b);

							for(int r = 0; r < 8; r++){
								//compose the tile
								if(romDat->chrPageCount > 0){
									byte1 = romDat->chrROM[(tileAddress << 4) + r];
									byte2 = romDat->chrROM[(tileAddress << 4) + 8 + r];
								}
								else{
									byte1 = *(((Uint8*)(&b.rawDat)) + r);
									byte2 = *(((Uint8*)(&b.rawDat)) + 8 + r);											
								}
								for(int c = 0; c < 8; c++){
									int pix = ((byte1 >> (7 - c)) & 0x01) | (((byte2 >> (7 - c)) & 0x01) << 1);
									switch(pix){
									case 0:
										objimg.SetAlpha(fillx + c, filly + r, 0);
										objimg.SetRGB(fillx + c, filly + r, 0, 0, 0);
										break;
									case 1:
										objimg.SetAlpha(fillx + c, filly + r, 255);
										objimg.SetRGB(fillx + c, filly + r, 
											(vid->colourList[b.colors.color1 & 0x3F] & 0xFF000000) >> 24, 
											(vid->colourList[b.colors.color1 & 0x3F] & 0x00FF0000) >> 16, 
											(vid->colourList[b.colors.color1 & 0x3F] & 0x0000FF00) >> 8);
										break;
									case 2:
										objimg.SetAlpha(fillx + c, filly + r, 255);
										objimg.SetRGB(fillx + c, filly + r, 
											(vid->colourList[b.colors.color2 & 0x3F] & 0xFF000000) >> 24, 
											(vid->colourList[b.colors.color2 & 0x3F] & 0x00FF0000) >> 16, 
											(vid->colourList[b.colors.color2 & 0x3F] & 0x0000FF00) >> 8);
										break;
									case 3:
										objimg.SetAlpha(fillx + c, filly + r, 255);
										objimg.SetRGB(fillx + c, filly + r, 
											(vid->colourList[b.colors.color3 & 0x3F] & 0xFF000000) >> 24, 
											(vid->colourList[b.colors.color3 & 0x3F] & 0x00FF0000) >> 16, 
											(vid->colourList[b.colors.color3 & 0x3F] & 0x0000FF00) >> 8);
										break;
									}
								}
							}
							fillx += 8;
							if(fillx == GEN_HD_WIDTH){
								fillx = 0;
								filly += 8;
							}
							if(filly == GEN_HD_HEIGHT){
								newImgReq = true;
								objFimg = objimg.Scale(GEN_HD_WIDTH * vid->packScale, GEN_HD_HEIGHT * vid->packScale);
						
								CHAR szPath[MAX_PATH];
								do{
									fileID++;
									filename = dirpath + "\\" + to_string((long double)fileID) + ".png";
									filename.copy(szPath, MAX_PATH, 0);
									szPath[filename.length()] = NULL;
								}
								while(PathFileExistsA(szPath) == 1);

								objFimg.SaveFile(wxString(filename.c_str(), wxConvUTF8));
								filly = 0;
								f.filename = to_string((long double)fileID) + ".png";
								f.width = GEN_HD_WIDTH * vid->packScale;
								f.height = GEN_HD_HEIGHT * vid->packScale;
								vid->bmpInfos.push_back(f);
							}
						}
					}
				}
			}
		}

		if(fillx != 0 || filly != 0){
			objFimg = objimg.Scale(GEN_HD_WIDTH * vid->packScale, GEN_HD_HEIGHT * vid->packScale);
						
			CHAR szPath[MAX_PATH];
			do{
				fileID++;
				filename = dirpath + "\\" + to_string((long double)fileID) + ".png";
				filename.copy(szPath, MAX_PATH, 0);
				szPath[filename.length()] = NULL;
			}
			while(PathFileExistsA(szPath) == 1);

			objFimg.SaveFile(wxString(filename.c_str(), wxConvUTF8));
			filly = 0;
			f.filename = to_string((long double)fileID) + ".png";
			f.width = GEN_HD_WIDTH * vid->packScale;
			f.height = GEN_HD_HEIGHT * vid->packScale;
			vid->bmpInfos.push_back(f);
		}
	}
	refreshGraphicsPackGUI();
}

void fraHDNesImp::addBatchMapping( wxCommandEvent& event ) { 
	bmDialog = new batchMapImp();
	if(bmDialog->ShowModal()){
/*		vid->SaveHiResPack();
		vid->CleanHiResPack();
		vid->ReadHiResPack();
 */
		refreshGraphicsPackGUI();
	}
	delete bmDialog;
}

void fraHDNesImp::loadAudioPack( wxCommandEvent& event ) { 
	romDat->loadRom(string(m_filePicker1->GetPath().char_str()));
	mixer->ReadAudioPack();
	refreshAudioPackGUI();
}

void fraHDNesImp::saveAudioPack( wxCommandEvent& event ) {
	mixer->SaveAudioPack();
}

void fraHDNesImp::addMP3ToPack( wxFileDirPickerEvent& event ) {
	string filename = string(m_filePicker4->GetPath().char_str());
	//create hd pack dir
	string packdir = getHDPackPath() + "\\";
    _mkdir(packdir.c_str());
    
	//get file name
	CHAR szPath[MAX_PATH];
	filename.copy(szPath, MAX_PATH, 0);
	szPath[filename.length()] = NULL;
	PathStripPathA(szPath);
	string newPath = packdir + string(szPath);
    
	if(filename.compare(newPath) != 0){
	    ifstream src(filename, std::ios::binary);
		ofstream dst(newPath, std::ios::binary);
	    dst << src.rdbuf();
	}
    mixer->mp3List.push_back(szPath);
	cboMP3file->Append(wxString(szPath, wxConvUTF8));
}

void fraHDNesImp::musicSelected( wxListEvent& event ){
	editingMusic = event.GetIndex();
	refreshMP3GUI();
}


void fraHDNesImp::addMP3( wxCommandEvent& event ){
	addMP3Field();
}

void fraHDNesImp::changeMP3( wxCommandEvent& event ){
	if(editingMusic >= 0){
		lstMusic->DeleteItem(editingMusic);
		mixer->musicList.erase(mixer->musicList.begin() + editingMusic);
		addMP3Field();
	}
}

void fraHDNesImp::deleteMP3( wxCommandEvent& event ){
	if(editingMusic >= 0){
		lstMusic->DeleteItem(editingMusic);
		mixer->musicList.erase(mixer->musicList.begin() + editingMusic);
		if(editingMusic >= mixer->musicList.size()){
			editingMusic = mixer->musicList.size() - 1;
		}
	}
}

void fraHDNesImp::addMP3Field(){
	musicPiece b;
	b.priority = spinMusicPriority->GetValue();
	if(string(txtMusicRAMAddress->GetValue().char_str()).compare("") == 0){
		return;
	}
	b.ramAddress = stoi(string(txtMusicRAMAddress->GetValue().char_str()), nullptr, 16);
	if(string(txtMusicRAMValue->GetValue().char_str()).compare("") == 0){
		b.hasCheck = false;
	}
	else{
		b.hasCheck = true;
		b.checkValue = stoi(string(txtMusicRAMValue->GetValue().char_str()), nullptr, 16);
	}

	if(string(txtMusicRAMNewValue->GetValue().char_str()).compare("") == 0){
		b.hasReplace = false;
	}
	else{
		b.hasReplace = true;
		b.replaceValue = stoi(string(txtMusicRAMNewValue->GetValue().char_str()), nullptr, 16);
	}

	b.playType = rbxMusciPlayType->GetSelection();
	b.mp3Idx = cboMP3file->GetSelection() - 2;
	b.conditions = txtConditions->GetValue().char_str();
	mixer->compileCondition(b);
	b.gotoNext = chkGotoNext->GetValue();

    //check for replicate priority
    bool hasMatch = false;
    int insertIdx = -1;
    for(unsigned int i = 0; i < mixer->musicList.size(); i++){
        if (mixer->musicList[i].priority == b.priority) {
            hasMatch = true;
        }
        if (hasMatch) {
            mixer->musicList[i].priority += 10;
        }
        if (mixer->musicList[i].priority > b.priority && insertIdx == -1) {
            insertIdx = i;
        }
    }
    if (insertIdx == -1) {
        mixer->musicList.push_back(b);
		editingMusic = mixer->musicList.size() - 1;
    }
    else{
		vector<musicPiece>::iterator it;
		it = mixer->musicList.begin() + insertIdx;
		mixer->musicList.insert(it, b);
		editingMusic = insertIdx;
    }
    refreshAudioPackGUI();
}

void fraHDNesImp::refreshMP3GUI(){
	char tmpStr[20];

	musicPiece b = mixer->musicList[editingMusic];
	spinMusicPriority->SetValue(b.priority);

	sprintf_s(tmpStr, "%x", b.ramAddress);
	txtMusicRAMAddress->SetValue(wxString(tmpStr, wxConvUTF8));

	if(b.hasCheck){
		sprintf_s(tmpStr, "%x", b.checkValue);
		txtMusicRAMValue->SetValue(wxString(tmpStr, wxConvUTF8));
	}
	else{
		txtMusicRAMValue->SetValue(wxString("", wxConvUTF8));
	}

	if(b.hasReplace){
		sprintf_s(tmpStr, "%x", b.replaceValue);
		txtMusicRAMNewValue->SetValue(wxString(tmpStr, wxConvUTF8));
	}
	else{
		txtMusicRAMNewValue->SetValue(wxString("", wxConvUTF8));
	}
	txtConditions->SetValue(wxString(b.conditions.c_str(), wxConvUTF8));
	rbxMusciPlayType->SetSelection(b.playType);
	cboMP3file->SetSelection(b.mp3Idx + 2);
	chkGotoNext->SetValue(b.gotoNext);
}

void fraHDNesImp::toggleAudioPack( wxCommandEvent& event ) {
	mixer->usePack = chkUseAudioPack->GetValue();
}

void fraHDNesImp::refreshRAMGUI(){
	char tmpStr[3];
	string lastStr;
	for(int i = 0; i < 0x80; i++){
		for(int j = 0; j < 16; j++){
			sprintf_s(tmpStr,"%x", memDat->cpuRAM[(i << 4) + j] );
			lastStr = string(GetCellContentsString(lstMemory, i, j + 1).char_str());
			if(lastStr.find("(") > 0){
				lastStr = lastStr.substr(0, lastStr.find("("));
			}
			if(lastStr.compare("") == 0){
				lstMemory->SetItem(i, j + 1, wxString(tmpStr, wxConvUTF8));
			}
			else if(lastStr.compare(tmpStr) != 0){
				lstMemory->SetItem(i, j + 1, wxString((string(tmpStr) + "(" + lastStr + ")").c_str(), wxConvUTF8));
			}
		}
	}
}

string fraHDNesImp::GetTileDisplayString(bitmapE* b){
	return to_string((long double)(b->patternAddress)) + "," + vid->GetPaletteString(b->colors);
}


wxString fraHDNesImp::GetCellContentsString(wxListCtrl* wxc, long row_number, int column)
{
	wxListItem row_info;
	wxString cell_contents_string;

	// Set what row it is (m_itemId is a member of the regular wxListCtrl class)
	row_info.m_itemId = row_number;
	// Set what column of that row we want to query for information.
	row_info.m_col = column;
	// Set text mask
	row_info.m_mask = wxLIST_MASK_TEXT;

	// Get the info and store it in row_info variable.
	wxc->GetItem( row_info );

	// Extract the text out that cell
	cell_contents_string = row_info.m_text;

	return cell_contents_string;
}

void fraHDNesImp::optimizeScreenEdit( wxCommandEvent& event ){
	vid->OptimizePackEdit();
	vid->RewritePackEdit();
	refreshGraphicsPackGUI();
}

void fraHDNesImp::AddDarkMapping( wxCommandEvent& event ){
	vid->AddDarkMapping();
	refreshGraphicsPackGUI();
}

void fraHDNesImp::customizePaletteClicked( wxCommandEvent& event ) {
	pDialog = new paletteDialogImp();
	if(pDialog->ShowModal()){
		refreshGraphicsPackGUI();
	}
	delete pDialog;
}
