#include "hdnesPackEditormainForm.h"
#include "hdnesPackEditornewProjectDialog.h"
#include "hdnesPackEditorcolourSelectDialog.h"
#include "hdnesPackEditorreplacementDialog.h"
#include "coreData.h"
#include "main.h"
#include "common.h"
#include <wx/wx.h>
#include <wx/clipbrd.h>
#include "gameObjNode.h"
#include "image.h"
#include "paletteSwap.h"

hdnesPackEditormainForm::hdnesPackEditormainForm( wxWindow* parent )
:
mainForm( parent )
{
    initROMView();
    initGameObjs();
    initGeneral();
    initHDImg();

    //load config
    string configPath;
    configPath = main::exeDir + string("\\config.txt");

    fstream fs;
    string line;
    string lineHdr;
    string lineTail;
    fs.open(configPath, fstream::in);
    if(fs.is_open()){
        while(getline(fs, line)){
            size_t found = line.find_first_of(">");
            if(found!=string::npos){
                lineHdr = line.substr(0, found + 1);
                lineTail = line.substr(found + 1);
                configGeneral(lineHdr, lineTail);
                configROMView(lineHdr, lineTail);
                configGameObjs(lineHdr, lineTail);
            }
        }
        fs.close();
    }
    tItmGameObjMenu = NULL;
}

void hdnesPackEditormainForm::closeWindow( wxCloseEvent& event ){
	fstream inifile;
	inifile.open(main::exeDir + "\\config.txt", ios::out);

    saveCfgGeneral(inifile);
	saveCfgROMView(inifile);
	saveCfgGameObjs(inifile);

	inifile.close();

    if ( event.CanVeto() && notSaved ){
        if ( wxMessageBox("The file has not been saved... continue closing?",
                          "Please confirm",
                          wxICON_QUESTION | wxYES_NO) != wxYES ){
            event.Veto();
            return;
        }
    }

	Show(false);
	Destroy();
}

void hdnesPackEditormainForm::romChanged(){
    romViewROMChanged();
    gameObjsROMChanged();
}

void hdnesPackEditormainForm::initGeneral(){
    lastDir = "";
    romDir = "";
    packDir = "";
    m_menu3->FindItem(m_menu3->FindItem(wxString("Save Project")))->Enable(false);
    m_menu3->FindItem(m_menu3->FindItem(wxString("Save Project As...")))->Enable(false);
    m_menu3->FindItem(m_menu3->FindItem(wxString("Generate Pack Data")))->Enable(false);
}

void hdnesPackEditormainForm::configGeneral(string lineHdr, string lineTail){
    if(lineHdr == "<lastDir>"){
        lastDir = lineTail;
    }
    else if(lineHdr == "<romDir>" ){
        romDir = lineTail;
    }
    else if(lineHdr == "<packDir>"){
        packDir = lineTail;
    }
}

void hdnesPackEditormainForm::saveCfgGeneral(fstream& inifile){
	inifile << "<lastDir>" + lastDir + "\n";
	inifile << "<romDir>" + romDir + "\n";
	inifile << "<packDir>" + packDir + "\n";
}

void hdnesPackEditormainForm::MenuFileNew( wxCommandEvent& event ){
    if(coreData::cData){
        delete(coreData::cData);
    }
    coreData::cData = new coreData();
    hdnesPackEditornewProjectDialog* fp = new hdnesPackEditornewProjectDialog(this);
    fp->Show(true);
}

void hdnesPackEditormainForm::MenuFileOpen( wxCommandEvent& event ){
    wxFileDialog dialog(this, wxString("Open project"), lastDir, lastDir, wxString("*.hnp"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if(dialog.ShowModal() == wxID_OK){
        if(coreData::cData){
            delete(coreData::cData);
        }
        coreData::cData = new coreData();
        coreData::cData->load(dialog.GetPath().ToStdString());
    }
}

void hdnesPackEditormainForm::MenuFileSave( wxCommandEvent& event ){
    if(coreData::cData->projectPath == ""){
        string romName = coreData::cData->romPath.substr(coreData::cData->romPath.find_last_of("\\/") + 1);
        romName = romName.substr(0, romName.find_last_of("."));
        wxFileDialog dialog(this, wxString("Save As"), lastDir, wxString(string(romName + ".hnp")), wxString("*.hnp"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if(dialog.ShowModal() == wxID_OK){
            coreData::cData->saveAs(dialog.GetPath().ToStdString());
        }
    }
    else{
        coreData::cData->save();
    }
}

void hdnesPackEditormainForm::MenuFileSaveAs( wxCommandEvent& event ){
    string romName = coreData::cData->projectPath.substr(coreData::cData->projectPath.find_last_of("\\/") + 1);
    romName = romName.substr(0, romName.find_last_of("."));
    wxFileDialog dialog(this, wxString("Save As"), coreData::cData->projectPath, wxString(string(romName + ".hnp")), wxString("*.hnp"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if(dialog.ShowModal() == wxID_OK){
        coreData::cData->saveAs(dialog.GetPath().ToStdString());
    }
}

void hdnesPackEditormainForm::MenuFileGen( wxCommandEvent& event ){
    coreData::cData->genPackData();
}

void hdnesPackEditormainForm::MenuFileExit( wxCommandEvent& event ){
// TODO: Implement MenuFileExit
}

void hdnesPackEditormainForm::colourSelected(Uint8 selectedColour){
    wxTreeItemId tID;
    gameObjNode* data;

    switch(colourSelectSource){
    case COLOUR_CLIENT_ROM_VIEW_BG:
        romViewColours[0] = selectedColour;
        romViewPaletteToText();
        refreshROMView();
        break;
    case COLOUR_CLIENT_ROM_VIEW_1:
        romViewColours[1] = selectedColour;
        romViewPaletteToText();
        refreshROMView();
        break;
    case COLOUR_CLIENT_ROM_VIEW_2:
        romViewColours[2] = selectedColour;
        romViewPaletteToText();
        refreshROMView();
        break;
    case COLOUR_CLIENT_ROM_VIEW_3:
        romViewColours[3] = selectedColour;
        romViewPaletteToText();
        refreshROMView();
        break;
    case COLOUR_CLIENT_GAME_OBJ_BG:
        tID = treeGameObjs->GetFocusedItem();
        data = (gameObjNode*)(treeGameObjs->GetItemData(tID));
        data->bgColour = selectedColour;
        refreshGameObj();
        coreData::cData->dataChanged();
        break;
    case COLOUR_CLIENT_NEW_SWAP_BG:
        swapNewColours[0] = selectedColour;
        updateNewSwapText();
        break;
    case COLOUR_CLIENT_NEW_SWAP_1:
        swapNewColours[1] = selectedColour;
        updateNewSwapText();
        break;
    case COLOUR_CLIENT_NEW_SWAP_2:
        swapNewColours[2] = selectedColour;
        updateNewSwapText();
        break;
    case COLOUR_CLIENT_NEW_SWAP_3:
        swapNewColours[3] = selectedColour;
        updateNewSwapText();
        break;
    }
}

void hdnesPackEditormainForm::openColourDialog(Uint16 clientID){
    if(coreData::cData){
        colourSelectSource = clientID;
        hdnesPackEditorcolourSelectDialog* fp = new hdnesPackEditorcolourSelectDialog(this);
        fp->setClientObj(this);
        fp->Show(true);
    }
}

void hdnesPackEditormainForm::paintTile(wxImage &img, Uint8* tileData, int x, int y, bool hFlip, bool vFlip, wxColour c1, wxColour c2, wxColour c3){
    wxColour useColour[4];
    useColour[1] = c1;
    useColour[2] = c2;
    useColour[3] = c3;
    Uint8 decodeByte1;
    Uint8 decodeByte2;
    Uint8 decodedVal;
    int drawX;
    int drawY;
    for(Uint8 dy = 0; dy < 8; ++dy){
        if(!vFlip){
            decodeByte1 = tileData[dy];
            decodeByte2 = tileData[dy + 8];
        }
        else{
            decodeByte1 = tileData[7 - dy];
            decodeByte2 = tileData[15 - dy];
        }
        for(Uint8 dx = 0; dx < 8; ++dx){
            if(!hFlip){
                decodedVal = ((decodeByte1 >> dx) & 0x01) | (((decodeByte2 >> dx) << 1) & 0x02);
            }
            else{
                decodedVal = ((decodeByte1 >> (7 - dx)) & 0x01) | (((decodeByte2 >> (7 - dx)) << 1) & 0x02);
            }
            drawX = x + 7 - dx;
            drawY = y + dy;
            if(drawX >= 0 && drawX < img.GetWidth() && drawY >= 0 && drawY < img.GetHeight() && decodedVal > 0){
                img.SetRGB(drawX, drawY, useColour[decodedVal].Red(), useColour[decodedVal].Green(), useColour[decodedVal].Blue());
                if(img.HasAlpha()) img.SetAlpha(drawX, drawY, 255);
            }
        }
    }
}

void hdnesPackEditormainForm::dataChanged(){
    refreshCoreDataDisplay();
    romDir = coreData::cData->romPath;
    packDir = coreData::cData->packPath;
    m_menu3->FindItem(m_menu3->FindItem(wxString("Save Project As...")))->Enable(true);
    m_menu3->FindItem(m_menu3->FindItem(wxString("Generate Pack Data")))->Enable(true);
    m_menu3->FindItem(m_menu3->FindItem(wxString("Save Project")))->Enable(true);
}

void hdnesPackEditormainForm::dataSaved(){
    lastDir = coreData::cData->projectPath;
    m_menu3->FindItem(m_menu3->FindItem(wxString("Save Project")))->Enable(false);
}

void hdnesPackEditormainForm::initROMView(){
    romViewColours[0] = 13;
    romViewColours[1] = 18;
    romViewColours[2] = 22;
    romViewColours[3] = 26;
    romViewClicked = false;
    romViewPaletteToText();
    romHScroll->SetRange(1);
    romHScroll->SetThumbSize(1);
    romVScroll->SetRange(1);
    romVScroll->SetThumbSize(1);
    zoomRom->SetValue(4);
}

void hdnesPackEditormainForm::romViewROMChanged(){
    romHScroll->SetThumbPosition(0);
    romVScroll->SetThumbPosition(0);
    romViewClicked = false;
}

void hdnesPackEditormainForm::configROMView(string lineHdr, string lineTail){
    if(lineHdr == "<romViewColour0>" ){
        romViewColours[0] = atoi(lineTail.c_str());
        romViewPaletteToText();
    }
    else if(lineHdr == "<romViewColour1>" ){
        romViewColours[1] = atoi(lineTail.c_str());
        romViewPaletteToText();
    }
    else if(lineHdr == "<romViewColour2>" ){
        romViewColours[2] = atoi(lineTail.c_str());
        romViewPaletteToText();
    }
    else if(lineHdr == "<romViewColour3>" ){
        romViewColours[3] = atoi(lineTail.c_str());
        romViewPaletteToText();
    }
}

void hdnesPackEditormainForm::saveCfgROMView(fstream& inifile){
	inifile << "<romViewColour0>" + main::intToStr(romViewColours[0]) + "\n";
	inifile << "<romViewColour1>" + main::intToStr(romViewColours[1]) + "\n";
	inifile << "<romViewColour2>" + main::intToStr(romViewColours[2]) + "\n";
	inifile << "<romViewColour3>" + main::intToStr(romViewColours[3]) + "\n";
}

void hdnesPackEditormainForm::zoomRomChanged( wxSpinEvent& event ){
    if(coreData::cData){
        refreshROMView();
    }
}

void hdnesPackEditormainForm::romBGColour( wxCommandEvent& event ){
    openColourDialog(COLOUR_CLIENT_ROM_VIEW_BG);
}

void hdnesPackEditormainForm::romViewPaletteHexChanged( wxCommandEvent& event ){
    string v = txtRomViewPalette->GetValue().ToStdString();
    main::hexToByteArray(v, (Uint8*)romViewColours);
    if(coreData::cData){
        refreshROMView();
    }
}

void hdnesPackEditormainForm::romColour1( wxCommandEvent& event ){
    openColourDialog(COLOUR_CLIENT_ROM_VIEW_1);
}

void hdnesPackEditormainForm::romColour2( wxCommandEvent& event ){
    openColourDialog(COLOUR_CLIENT_ROM_VIEW_2);
}

void hdnesPackEditormainForm::romColour3( wxCommandEvent& event ){
    openColourDialog(COLOUR_CLIENT_ROM_VIEW_3);
}

void hdnesPackEditormainForm::romViewSizeChanged( wxSizeEvent& event ){
    if(coreData::cData){
        refreshROMView();
    }
}

void hdnesPackEditormainForm::romViewVScrolled( wxScrollEvent& event ){
    if(coreData::cData){
        drawROMView();
    }
}

void hdnesPackEditormainForm::romViewHScrolled( wxScrollEvent& event ){
    if(coreData::cData){
        drawROMView();
    }
}

void hdnesPackEditormainForm::refreshCoreDataDisplay(){
    refreshROMView();
    listOutHDImgImages();
}

void hdnesPackEditormainForm::refreshROMView(){
    btnRomViewBGColour->SetBackgroundColour(coreData::cData->palette[romViewColours[0]]);
    if(coreData::cData->palette[romViewColours[0]].Red() + coreData::cData->palette[romViewColours[0]].Green() + coreData::cData->palette[romViewColours[0]].Blue() > 256){
        btnRomViewBGColour->SetForegroundColour(wxColour(0,0,0));
    }
    else{
        btnRomViewBGColour->SetForegroundColour(wxColour(255,255,255));
    }

    btnRomViewColour1->SetBackgroundColour(coreData::cData->palette[romViewColours[1]]);
    if(coreData::cData->palette[romViewColours[1]].Red() + coreData::cData->palette[romViewColours[1]].Green() + coreData::cData->palette[romViewColours[1]].Blue() > 256){
        btnRomViewColour1->SetForegroundColour(wxColour(0,0,0));
    }
    else{
        btnRomViewColour1->SetForegroundColour(wxColour(255,255,255));
    }

    btnRomViewColour2->SetBackgroundColour(coreData::cData->palette[romViewColours[2]]);
    if(coreData::cData->palette[romViewColours[2]].Red() + coreData::cData->palette[romViewColours[2]].Green() + coreData::cData->palette[romViewColours[2]].Blue() > 256){
        btnRomViewColour2->SetForegroundColour(wxColour(0,0,0));
    }
    else{
        btnRomViewColour2->SetForegroundColour(wxColour(255,255,255));
    }

    btnRomViewColour3->SetBackgroundColour(coreData::cData->palette[romViewColours[3]]);
    if(coreData::cData->palette[romViewColours[3]].Red() + coreData::cData->palette[romViewColours[3]].Green() + coreData::cData->palette[romViewColours[3]].Blue() > 256){
        btnRomViewColour3->SetForegroundColour(wxColour(0,0,0));
    }
    else{
        btnRomViewColour3->SetForegroundColour(wxColour(255,255,255));
    }

    romViewTileSize = 8 * zoomRom->GetValue();
    romViewCurrentRow = -1;

    tileCnt = coreData::cData->romSize / 16;
    romViewDisplayRows = ((tileCnt / 16) + (tileCnt % 16 ? 1 : 0));
    //display 16 tiles across
    romViewDisplayWidth = 16 * romViewTileSize;
    romViewDisplayHeight = romViewDisplayRows * romViewTileSize;

    romHScroll->SetRange(romViewDisplayWidth);
    romVScroll->SetRange(romViewDisplayHeight);
    romHScroll->SetThumbSize(pnlRom->GetSize().GetWidth());
    romVScroll->SetThumbSize(pnlRom->GetSize().GetHeight());

    romViewImageDisplay = wxImage(pnlRom->GetSize().x, pnlRom->GetSize().y);

    drawROMView();
}

void hdnesPackEditormainForm::drawROMView(){
    int newRowStart = romVScroll->GetThumbPosition() / romViewTileSize;
    int bufferRows = newRowStart % 3;
    newRowStart -= bufferRows;
    if(romViewCurrentRow != newRowStart){
        romViewCurrentRow = newRowStart;
        Uint16 visibleRows = (romVScroll->GetThumbSize() / romViewTileSize) + (romVScroll->GetThumbSize() % romViewTileSize ? 1 : 0) + 2;
        romViewImage = wxImage(16 * 8, visibleRows * 8, true);

        Uint32 memAddress;
        Uint16 drawX;
        Uint16 drawY;
        for(Uint16 j = 0; j < visibleRows; ++j){
            for(Uint16 i = 0; i < 16; ++i){
                if(romViewCurrentRow + j < romViewDisplayRows){
                    memAddress = ((romViewCurrentRow + j) * 16 + i) * 16;
                    if(memAddress < coreData::cData->romSize){
                        drawX = i * 8;
                        drawY = j * 8;
                        romViewImage.SetRGB(wxRect(drawX, drawY, 8, 8), coreData::cData->palette[romViewColours[0]].Red(), coreData::cData->palette[romViewColours[0]].Green(), coreData::cData->palette[romViewColours[0]].Blue());

                        paintTile(romViewImage, coreData::cData->romData + memAddress, drawX, drawY, false, false,
                                coreData::cData->palette[romViewColours[1]],
                                coreData::cData->palette[romViewColours[2]],
                                coreData::cData->palette[romViewColours[3]]);
                    }
                }
            }
        }
        drawROMViewSelection();
    }
    else{
        showROMView();
    }
}

void hdnesPackEditormainForm::drawROMViewSelection(){
    romViewImageWithSelection = romViewImage.Scale(romViewImage.GetWidth() * zoomRom->GetValue(), romViewImage.GetHeight() * zoomRom->GetValue());
    int rowY = romViewCurrentRow * romViewTileSize;

    wxPoint pt;
    wxPoint pt2;
    wxPoint tileBoxSize;
    tileBoxSize.x = romViewTileSize - 1;
    tileBoxSize.y = romViewTileSize - 1;
    for (vector<Uint32>::iterator it = romViewSelectedTiles.begin() ; it != romViewSelectedTiles.end(); ++it){
        pt.x = ((*it) % 16) * romViewTileSize;
        pt.y = ((*it) / 16) * romViewTileSize - rowY;
        pt2 = pt;
        ++(pt2.x);
        ++(pt2.y);
        main::drawRect(romViewImageWithSelection, pt2, tileBoxSize, wxColour(0, 0, 0));
        main::drawRect(romViewImageWithSelection, pt, tileBoxSize, wxColour(255, 255, 255));
    }
    showROMView();
}

void hdnesPackEditormainForm::showROMView(){
    int rowY = romViewCurrentRow * romViewTileSize;
    romViewImageDisplay.Clear();
    romViewImageDisplay.Paste(romViewImageWithSelection, -romHScroll->GetThumbPosition(), rowY - romVScroll->GetThumbPosition());

    if(romViewClicked){
        wxPoint p1;
        p1.x = min(romViewLDownPos.x, romViewLCurrPos.x);
        p1.y = min(romViewLDownPos.y, romViewLCurrPos.y);

        wxPoint p2;
        p2.x = max(romViewLDownPos.x, romViewLCurrPos.x);
        p2.y = max(romViewLDownPos.y, romViewLCurrPos.y);

        wxPoint rectSize;
        rectSize.x = p2.x - p1.x;
        rectSize.y = p2.y - p1.y;

        wxPoint p3 = p1;
        ++(p3.x);
        ++(p3.y);


        main::drawRect(romViewImageDisplay, p3, rectSize, wxColour(0, 0, 0));
        main::drawRect(romViewImageDisplay, p1, rectSize, wxColour(255, 255, 255));
    }

    wxBitmap bmp = wxBitmap(romViewImageDisplay);
	if(bmp.IsOk()){
		wxClientDC* objDC;
		objDC = new wxClientDC(pnlRom);
		objDC->DrawBitmap(bmp, 0, 0);
		delete objDC;
	}
}

void hdnesPackEditormainForm::romViewPaletteToText(){
    wxString v;
    v = wxString((main::intToHex(romViewColours[0])
                + main::intToHex(romViewColours[1])
                + main::intToHex(romViewColours[2])
                + main::intToHex(romViewColours[3])).c_str());
    txtRomViewPalette->ChangeValue(v);

}

void hdnesPackEditormainForm::romViewLDown( wxMouseEvent& event ){
    if(coreData::cData){
        if(event.GetModifiers() != wxMOD_CONTROL){
            //clear currently selected
            romViewSelectedTiles.clear();
        }
        romViewLDownPos = event.GetPosition();
        romViewLCurrPos = romViewLDownPos;
        romViewClicked = true;
        drawROMViewSelection();
    }
}

void hdnesPackEditormainForm::romViewLUp( wxMouseEvent& event ){
    if(coreData::cData){
        if(romViewClicked){
            wxPoint p = event.GetPosition();
            int x1 = min(p.x, romViewLDownPos.x);
            int x2 = max(p.x, romViewLDownPos.x);
            int y1 = min(p.y, romViewLDownPos.y);
            int y2 = max(p.y, romViewLDownPos.y);

            int tileX1 = (romHScroll->GetThumbPosition() + x1) / romViewTileSize;
            int tileY1 = (romVScroll->GetThumbPosition() + y1) / romViewTileSize;
            int tileX2 = (romHScroll->GetThumbPosition() + x2) / romViewTileSize;
            int tileY2 = (romVScroll->GetThumbPosition() + y2) / romViewTileSize;

            Uint32 tileID;
            for(int j = tileY1; j <= tileY2; ++j){
                for(int i = tileX1; i <= tileX2; ++i){
                    if(i < 16){
                        tileID = j * 16 + i;
                        if(tileID < tileCnt){
                            //look for that id in vector
                            bool tileFound = false;
                            for(Uint32 k = 0; k < romViewSelectedTiles.size(); ++k){
                                if(romViewSelectedTiles[k] == tileID){
                                    romViewSelectedTiles.erase(romViewSelectedTiles.begin() + k);
                                    tileFound = true;
                                }
                            }
                            if(!tileFound){
                                romViewSelectedTiles.push_back(tileID);
                            }
                        }
                    }
                }
            }

            romViewClicked = false;
            drawROMViewSelection();
        }
    }
}

void hdnesPackEditormainForm::romViewRUp( wxMouseEvent& event ){
    //check right click on a selected tile
    if(coreData::cData){
        wxPoint p = event.GetPosition();
        int tileX1 = (romHScroll->GetThumbPosition() + p.x) / romViewTileSize;
        int tileY1 = (romVScroll->GetThumbPosition() + p.y) / romViewTileSize;
        if(tileX1 < 16){
            Uint32 tileID = tileY1 * 16 + tileX1;
            if(tileID < tileCnt){
                //look for that id in vector
                bool tileFound = false;
                for(Uint32 k = 0; k < romViewSelectedTiles.size(); ++k){
                    if(romViewSelectedTiles[k] == tileID){
                        tileFound = true;
                        rightClickedID = tileID;
                        rightClickedTileX = tileX1;
                        rightClickedTileY = tileY1;
                    }
                }
                if(tileFound){
                    wxMenu menu(wxT(""));
                    menu.Append(wxID_ANY, wxT("Copy"));
                    menu.Connect( wxEVT_MENU, wxCommandEventHandler(hdnesPackEditormainForm::romViewMenu), NULL, this );
                    pnlRom->PopupMenu(&menu, p);
                }
                else{
                    romViewSelectedTiles.clear();
                    drawROMViewSelection();
                }
            }
        }
    }
}

void hdnesPackEditormainForm::romViewMenu( wxCommandEvent& event ){
    string copyContent = "";
    int tileX;
    int tileY;
    for(Uint32 k = 0; k < romViewSelectedTiles.size(); ++k){
        tileX = romViewSelectedTiles[k] % 16;
        tileY = romViewSelectedTiles[k] / 16;
        if(copyContent != ""){
            copyContent = copyContent + "\n";
        }
        copyContent = copyContent + coreData::cData->getTileID(romViewSelectedTiles[k])
                        + "," + txtRomViewPalette->GetValue().ToStdString()
                        + "," + main::intToStr((tileX - rightClickedTileX) * 8)
                        + "," + main::intToStr((tileY - rightClickedTileY) * 8);

    }

    if (wxTheClipboard->Open()){
        wxTheClipboard->SetData( new wxTextDataObject(copyContent.c_str()) );
        wxTheClipboard->Close();
    }
}

void hdnesPackEditormainForm::romViewMove( wxMouseEvent& event ){
    if(coreData::cData){
        wxPoint p = event.GetPosition();
        int tileX1 = (romHScroll->GetThumbPosition() + p.x) / romViewTileSize;
        int tileY1 = (romVScroll->GetThumbPosition() + p.y) / romViewTileSize;
        if(tileX1 < 16){
            int tileIndex = tileY1 * 16 + tileX1;
            if(tileIndex < tileCnt){
                m_statusBar->SetLabel(wxString(coreData::cData->getTileID(tileIndex)));
            }
        }

        if(romViewClicked){
            romViewLCurrPos = p;
            showROMView();
        }
    }
}

void hdnesPackEditormainForm::romViewEnter( wxMouseEvent& event ){
    if(coreData::cData && !event.LeftIsDown()){
        romViewClicked = false;
        showROMView();
    }
}


void hdnesPackEditormainForm::initGameObjs(){
    zoomGameObjs->SetValue(4);
    gameObjZoom = 4;
    gameObjTileSize = 8 * gameObjZoom;
    scrGameObjRawH->SetRange(1);
    scrGameObjRawH->SetThumbSize(1);
    scrGameObjRawV->SetRange(1);
    scrGameObjRawV->SetThumbSize(1);
    scrGameObjNewH->SetRange(1);
    scrGameObjNewH->SetThumbSize(1);
    scrGameObjNewV->SetRange(1);
    scrGameObjNewV->SetThumbSize(1);
    clearGameObj();
    gameObjClicked = false;
    editCondition = false;
    conditionCounter = 0;
    gameObjRawImageDisplay = wxImage(pnlGameObjRaw->GetSize().x, pnlGameObjRaw->GetSize().y);
    gameObjNewImageDisplay = wxImage(pnlGameObjNew->GetSize().x, pnlGameObjNew->GetSize().y);
    gameObjBaseTile = wxImage(8, 8);

    lstSwaps->AppendColumn(wxString("Name"));
    lstSwaps->AppendColumn(wxString("New palettes"));
    lstSwaps->AppendColumn(wxString("New brightness %"));
    lstSwaps->AppendColumn(wxString("Rotate hue degrees"));
    lstSwaps->AppendColumn(wxString("New saturation %"));

    lstPalettes->AppendColumn(wxString("Original palette"));
    lstPalettes->AppendColumn(wxString("New Palette"));

    lstConditions->AppendColumn(wxString(" "));
    lstConditions->AppendColumn(wxString("Name"));
    lstConditions->AppendColumn(wxString("Type"));
    lstConditions->AppendColumn(wxString("Condition"));
    lstConditions->SetColumnWidth(0, 20);
    lstConditions->SetColumnWidth(3, 500);

    cboConditionType->Append(wxString("hmirror"));
    cboConditionType->Append(wxString("vmirror"));
    cboConditionType->Append(wxString("bgpriority"));
    cboConditionType->Append(wxString("tileAtPosition"));
    cboConditionType->Append(wxString("spriteAtPosition"));
    cboConditionType->Append(wxString("memoryCheck"));
    cboConditionType->Append(wxString("ppuMemoryCheck"));
    cboConditionType->Append(wxString("memoryCheckConstant"));
    cboConditionType->Append(wxString("ppuMemoryCheckConstant"));
    showConditionPanel();

    cboConditionOp->Append(wxString("=="));
    cboConditionOp->Append(wxString("!="));
    cboConditionOp->Append(wxString(">"));
    cboConditionOp->Append(wxString("<"));
    cboConditionOp->Append(wxString("<="));
    cboConditionOp->Append(wxString("<="));

    cboConditionOp2->Append(wxString("=="));
    cboConditionOp2->Append(wxString("!="));
    cboConditionOp2->Append(wxString(">"));
    cboConditionOp2->Append(wxString("<"));
    cboConditionOp2->Append(wxString("<="));
    cboConditionOp2->Append(wxString("<="));

    loadingTab = false;
}

void hdnesPackEditormainForm::gameObjsROMChanged(){
    treeGameObjs->DeleteAllItems();
    gameObjNode* node = new gameObjNode();
    node->nodeType = GAME_OBJ_NODE_TYPE_ROOT;
    node->nodeName = "";
    tItmGameObjRoot = treeGameObjs->AddRoot(wxString("\\"), -1, -1, node);
    tItmGameObjMenu = tItmGameObjRoot;
    gameObjectTreeWillMove = false;
    clearGameObj();
    gameObjClicked = false;
    editCondition = false;
    gameObjBaseTileNew = wxImage(8 * coreData::cData->scale, 8 * coreData::cData->scale);

}

gameObjNode* hdnesPackEditormainForm::getGameObjsSelectedObjectTreeNode(){
    if(coreData::cData && tItmGameObjMenu){
        gameObjNode* ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));
        if(ndata->nodeType == GAME_OBJ_NODE_TYPE_OBJECT || ndata->nodeType == GAME_OBJ_NODE_TYPE_BGIMAGE) return ndata;
    }
    return NULL;
}

void hdnesPackEditormainForm::gameObjTItemBeginEdit( wxTreeEvent& event ){
    wxTreeItemId tID = event.GetItem();
    gameObjNode* data = (gameObjNode*)(treeGameObjs->GetItemData(tID));
    switch(data->nodeType){
    case GAME_OBJ_NODE_TYPE_ROOT:
        event.Veto();
        break;
    case GAME_OBJ_NODE_TYPE_GROUP:
        treeGameObjs->SetItemText(tID, wxString(data->nodeName));
        break;
    }
}

void hdnesPackEditormainForm::gameObjTItemChangeName( wxTreeEvent& event ){
    wxTreeItemId tID = event.GetItem();
    gameObjNode* data = (gameObjNode*)(treeGameObjs->GetItemData(tID));
    switch(data->nodeType){
    case GAME_OBJ_NODE_TYPE_GROUP:
        if(!event.IsEditCancelled()){
            data->nodeName = event.GetLabel();
            event.Veto();
        }
        treeGameObjs->SetItemText(tID, wxString(data->nodeName + "\\"));
        break;
    case GAME_OBJ_NODE_TYPE_OBJECT:
    case GAME_OBJ_NODE_TYPE_BGIMAGE:
        if(!event.IsEditCancelled()){
            data->nodeName = event.GetLabel();
        }
        break;
    }
    coreData::cData->dataChanged();
}

void hdnesPackEditormainForm::gameObjTItemOpenMenu( wxTreeEvent& event ){
    tItmGameObjMenu = event.GetItem();
    gameObjNode* data = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));
    wxMenu menu(wxT(""));
    if(data->nodeType != GAME_OBJ_NODE_TYPE_OBJECT && data->nodeType != GAME_OBJ_NODE_TYPE_BGIMAGE){
        menu.Append(GAME_OBJ_NODE_MENU_ADD_FOLDER, wxT("Add folder"));
        menu.Append(GAME_OBJ_NODE_MENU_ADD_OBJECT, wxT("Add object"));
        menu.Append(GAME_OBJ_NODE_MENU_ADD_BGIMAGE, wxT("Add background"));
        if(gameObjectTreeWillMove && !(data->effectedByMove)){
            menu.Append(GAME_OBJ_NODE_MENU_MOVE_HERE, wxT("Move here"));
        }
    }
    if(data->nodeType != GAME_OBJ_NODE_TYPE_ROOT){
        menu.Append(GAME_OBJ_NODE_MENU_DEL, wxT("Delete"));
        if(treeGameObjs->GetPrevSibling(tItmGameObjMenu).IsOk()){
            menu.Append(GAME_OBJ_NODE_MENU_MOVE_UP, wxT("Move up"));
        }
        if(treeGameObjs->GetNextSibling(tItmGameObjMenu).IsOk()){
            menu.Append(GAME_OBJ_NODE_MENU_MOVE_DOWN, wxT("Move down"));
        }
        menu.Append(GAME_OBJ_NODE_MENU_MOVE_TO_FOLDER, wxT("Move to folder"));
    }

    menu.Connect( wxEVT_MENU, wxCommandEventHandler(hdnesPackEditormainForm::gameObjsTreeMenu), NULL, this );
    treeGameObjs->PopupMenu(&menu, event.GetPoint());
}

void hdnesPackEditormainForm::gameObjTItemSelected( wxTreeEvent& event ){
    tItmGameObjMenu = event.GetItem();
    gameObjViewCentreX = 0;
    gameObjViewCentreY = 0;
    gameObjSelectedTiles.clear();
    gameObjconditionTiles.clear();
    editCondition = false;
    refreshNode();
}

void hdnesPackEditormainForm::gameObjsTreeMenu( wxCommandEvent& event ){
    gameObjNode* node;
    wxTreeItemId newItm;
    switch(event.GetId()){
    case GAME_OBJ_NODE_MENU_ADD_FOLDER:
        node = new gameObjNode();
        node->nodeType = GAME_OBJ_NODE_TYPE_GROUP;
        node->nodeName = "Folder";
        newItm = treeGameObjs->AppendItem(tItmGameObjMenu, wxString("Folder\\"), -1, -1, node);
        treeGameObjs->Expand(tItmGameObjMenu);
        treeGameObjs->EditLabel(newItm);
        coreData::cData->dataChanged();
        break;
    case GAME_OBJ_NODE_MENU_ADD_OBJECT:
    case GAME_OBJ_NODE_MENU_ADD_BGIMAGE:
        node = new gameObjNode();
        if(event.GetId() == GAME_OBJ_NODE_MENU_ADD_OBJECT){
            node->nodeType = GAME_OBJ_NODE_TYPE_OBJECT;
            node->nodeName = "Object";
            newItm = treeGameObjs->AppendItem(tItmGameObjMenu, wxString("Object"), -1, -1, node);
        }
        else{
            node->nodeType = GAME_OBJ_NODE_TYPE_BGIMAGE;
            node->nodeName = "Background";
            newItm = treeGameObjs->AppendItem(tItmGameObjMenu, wxString("Background"), -1, -1, node);
        }
        treeGameObjs->Expand(tItmGameObjMenu);
        treeGameObjs->EditLabel(newItm);
        treeGameObjs->SetFocusedItem(newItm);
        tItmGameObjMenu = newItm;
        gameObjSelectedTiles.clear();
        refreshNode();
        coreData::cData->dataChanged();
        break;
    case GAME_OBJ_NODE_MENU_DEL:
        treeGameObjs->Delete(tItmGameObjMenu);
        coreData::cData->dataChanged();
        break;
    case GAME_OBJ_NODE_MENU_MOVE_UP:
        gameObjectTreeWillMove = false;
        gameObjsMoveTreeItem(tItmGameObjMenu, treeGameObjs->GetItemParent(tItmGameObjMenu), treeGameObjs->GetPrevSibling(treeGameObjs->GetPrevSibling(tItmGameObjMenu)));
        coreData::cData->dataChanged();
        break;
    case GAME_OBJ_NODE_MENU_MOVE_DOWN:
        gameObjectTreeWillMove = false;
        gameObjsMoveTreeItem(tItmGameObjMenu, treeGameObjs->GetItemParent(tItmGameObjMenu), treeGameObjs->GetNextSibling(tItmGameObjMenu));
        coreData::cData->dataChanged();
        break;
    case GAME_OBJ_NODE_MENU_MOVE_TO_FOLDER:
        gameObjectTreeWillMove = true;
        gameObjsCancelWillMove(tItmGameObjRoot);
        gameObjsSetWillMove(tItmGameObjMenu);
        tItmGameObjMove = tItmGameObjMenu;
        coreData::cData->dataChanged();
        break;
    case GAME_OBJ_NODE_MENU_MOVE_HERE:
        gameObjectTreeWillMove = false;
        gameObjsMoveTreeItem(tItmGameObjMove, tItmGameObjMenu, treeGameObjs->GetLastChild(tItmGameObjMenu));
        gameObjsCancelWillMove(tItmGameObjRoot);
        coreData::cData->dataChanged();
        break;
    }
}

void hdnesPackEditormainForm::gameObjsMoveTreeItem(wxTreeItemId item, wxTreeItemId newParent, wxTreeItemId previousItem){
    gameObjNode* node = (gameObjNode*)(treeGameObjs->GetItemData(item));
    treeGameObjs->SetItemData(item, NULL);
    wxTreeItemId newItm = treeGameObjs->InsertItem(newParent, previousItem, treeGameObjs->GetItemText(item), -1, -1, node);

    wxTreeItemIdValue cookie = 0;
    wxTreeItemId child = treeGameObjs->GetFirstChild(item, cookie);
    while(child.IsOk()){
        gameObjsMoveTreeItem(child, newItm, treeGameObjs->GetLastChild(newItm));
        child = treeGameObjs->GetFirstChild(item, cookie);
    }
    treeGameObjs->Delete(item);
}

void hdnesPackEditormainForm::gameObjsCancelWillMove(wxTreeItemId item){
    gameObjNode* node = (gameObjNode*)(treeGameObjs->GetItemData(item));
    node->effectedByMove = false;
    wxTreeItemIdValue cookie = 0;
    wxTreeItemId child = treeGameObjs->GetFirstChild(item, cookie);
    while(child.IsOk()){
        gameObjsCancelWillMove(child);
        child = treeGameObjs->GetNextSibling(child);
    }
}

void hdnesPackEditormainForm::gameObjsSetWillMove(wxTreeItemId item){
    gameObjNode* node = (gameObjNode*)(treeGameObjs->GetItemData(item));
    node->effectedByMove = true;
    wxTreeItemIdValue cookie = 0;
    wxTreeItemId child = treeGameObjs->GetFirstChild(item, cookie);
    while(child.IsOk()){
        gameObjsSetWillMove(child);
        child = treeGameObjs->GetNextSibling(child);
    }
}

void hdnesPackEditormainForm::gameObjsRawRUp( wxMouseEvent& event ){
    gameObjNode* data = getGameObjsSelectedObjectTreeNode();
    if(data){
        wxPoint p = event.GetPosition();
        gameObjRawCurrPos = convertGameObjRawPosition(p);
        wxMenu menu(wxT(""));

        //show paste when context valid
        if(gameObjPasteData.tiles.size() > 0){
            menu.Append(GAME_OBJ_PNL_CONFIRM_PASTE, wxT("Confirm paste location"));
            menu.Append(GAME_OBJ_PNL_CANCEL_PASTE, wxT("Cancel paste"));
        }
        else if(editCondition){
            menu.Append(GAME_OBJ_PNL_CONFIRM_CONDITION, wxT("Confirm changes"));
            menu.Append(GAME_OBJ_PNL_CANCEL_CONDITION, wxT("Cancel changes"));
        }
        else{
            if (wxTheClipboard->IsSupported( wxDF_TEXT )){
                wxTextDataObject txt;
                wxTheClipboard->GetData( txt );
                if(checkPasteValid(txt.GetText().ToStdString())){
                    menu.Append(GAME_OBJ_PNL_PASTE, wxT("Paste"));
                }
            }
            menu.Append(GAME_OBJ_PNL_SHOW_NOT_UNIQUE, wxT("Select untreated tiles"));
            menu.Append(GAME_OBJ_PNL_AUTO_CONDITION, wxT("Add condition to untreated tiles"));

            if(data->palettes.size() > 0){
                wxMenu submenu(wxT(""));
                stringstream s;
                for(int i = 0; i < data->palettes.size(); ++i){
                    s.str(std::string());
                    s.clear();
                    s << main::intToHex(data->palettes[i][0]);
                    s << main::intToHex(data->palettes[i][1]);
                    s << main::intToHex(data->palettes[i][2]);
                    s << main::intToHex(data->palettes[i][3]);

                    submenu.Append(i + GAME_OBJ_PNL_PALETTE_SELECT_OFFSET, wxString(s.str().c_str()));
                }
                menu.AppendSubMenu(&submenu, wxT("Select tiles with palette"));
            }

            //check right click on a selected tile
            bool tileFound = false;
            for(Uint32 k = 0; k < gameObjSelectedTiles.size(); ++k){
                if(gameObjRawCurrPos.x <= data->tiles[gameObjSelectedTiles[k]].objCoordX + 8
                    && gameObjRawCurrPos.x >= data->tiles[gameObjSelectedTiles[k]].objCoordX
                    && gameObjRawCurrPos.y <= data->tiles[gameObjSelectedTiles[k]].objCoordY + 8
                    && gameObjRawCurrPos.y >= data->tiles[gameObjSelectedTiles[k]].objCoordY){
                    tileFound = true;
                    rightClickedgameObjID = gameObjSelectedTiles[k];
                    rightClickedGameObjTileX = gameObjRawCurrPos.x;
                    rightClickedGameObjTileY = gameObjRawCurrPos.y;
                }
            }
            if(tileFound){
                menu.Append(GAME_OBJ_PNL_COPY, wxT("Copy"));
                menu.Append(GAME_OBJ_PNL_DELETE, wxT("Delete"));
                menu.Append(GAME_OBJ_PNL_REPLACE, wxT("Set replacement"));
                if(gameObjSelectedTiles.size() == 1){
                    menu.Append(GAME_OBJ_PNL_CONDITION, wxT("Set conditions"));
                }
                else{
                    menu.Append(GAME_OBJ_PNL_GROUP_CONDITION, wxT("Set conditions for tiles"));
                }
                if(data->isSprite){
                    wxMenu submenu2(wxT(""));
                    submenu2.Append(GAME_OBJ_PNL_HFLIP, wxT("Flip direction horizontally"));
                    submenu2.Append(GAME_OBJ_PNL_VFLIP, wxT("Flip direction vertically"));
                    if(gameObjSelectedTiles.size() > 1){
                        submenu2.Append(GAME_OBJ_PNL_HFLIP2, wxT("Flip direction and location horizontally"));
                        submenu2.Append(GAME_OBJ_PNL_VFLIP2, wxT("Flip direction and location vertically"));
                    }
                    menu.AppendSubMenu(&submenu2, wxT("Flip tiles"));
                }
            }
            else{
                gameObjSelectedTiles.clear();
                drawGameObjEdits();
            }
        }

        menu.Connect( wxEVT_MENU, wxCommandEventHandler(hdnesPackEditormainForm::gameObjsRawMenu), NULL, this );
        pnlGameObjRaw->PopupMenu(&menu, p);
    }
}

void hdnesPackEditormainForm::gameObjsRawMenu( wxCommandEvent& event ){
    string copyContent = "";
    gameObjNode* ndata;
    gameTile t;
    condition c;
    int clickedX;
    int clickedY;
    hdnesPackEditorreplacementDialog* fp;
    vector<gameTile> selectedTiles;
    int offset;
    int uniqueTileID;

    switch(event.GetId()){
    case GAME_OBJ_PNL_PASTE:
        if (wxTheClipboard->IsSupported( wxDF_TEXT )){
            wxTextDataObject txt;
            wxTheClipboard->GetData( txt );
            //read tile string into tiles and add to the current object
            vector<string> tileLines;
            vector<string> tileDetails;
            gameTile g;

            gameObjPasteData.clearAllTiles();
            main::split(txt.GetText().ToStdString(), '\n', tileLines);
            for(int i = 0; i < tileLines.size(); ++i){
                main::split(tileLines[i], ',', tileDetails);
                if(tileDetails.size() == 4 || tileDetails.size() == 6){
                    if(coreData::cData->isCHRROM){
                        g.id.id = atoi(tileDetails[0].c_str());
                    }
                    else{
                        main::hexToByteArray(tileDetails[0], g.id.rawData);
                    }
                    main::hexToByteArray(tileDetails[1], g.id.palette);
                    g.objCoordX = atoi(tileDetails[2].c_str());
                    g.objCoordY = atoi(tileDetails[3].c_str());
                    if(tileDetails.size() == 6){
                        g.hFlip = (tileDetails[4] == "Y");
                        g.vFlip = (tileDetails[5] == "Y");
                    }
                    else{
                        g.hFlip = false;
                        g.vFlip = false;
                    }
                    g.markForDelete = false;
                    gameObjPasteData.addTile(g);
                }
            }
            drawGameObjPasteTiles();
        }
        break;
    case GAME_OBJ_PNL_CONFIRM_PASTE:
        ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));
        //set bg colour this is the first tiles to be added
        if(ndata->tiles.size() == 0 && gameObjPasteData.tiles[0].id.palette[0] < 64 && !ndata->isSprite){
            ndata->bgColour = gameObjPasteData.tiles[0].id.palette[0];
        }
        for(int i = 0; i < gameObjPasteData.tiles.size(); ++i){
            gameObjPasteData.tiles[i].objCoordX += gameObjRawCurrPos.x;
            gameObjPasteData.tiles[i].objCoordY += gameObjRawCurrPos.y;
            ndata->addTile(gameObjPasteData.tiles[i]);
        }
        ndata->updatePalettes();
        gameObjPasteData.clearAllTiles();
        refreshGameObj();
        coreData::cData->dataChanged();
        break;
    case GAME_OBJ_PNL_CANCEL_PASTE:
        gameObjPasteData.clearAllTiles();
        drawGameObjEdits();
        break;
    case GAME_OBJ_PNL_COPY:
        ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));

        for(int k = 0; k < gameObjSelectedTiles.size(); ++k){
            if(copyContent != ""){
                copyContent = copyContent + "\n";
            }
            if(coreData::cData->isCHRROM){
                copyContent = copyContent + main::intToStr(ndata->tiles[gameObjSelectedTiles[k]].id.id);
            }
            else{
                string tmpVal = "";
                for(Uint8 i = 0; i < 16; ++i){
                    tmpVal = tmpVal + main::intToHex(ndata->tiles[gameObjSelectedTiles[k]].id.rawData[i]);
                }
                copyContent = copyContent + tmpVal;
            }
            copyContent = copyContent + "," + wxString(main::intToHex(ndata->bgColour).c_str())
                        + wxString(main::intToHex(ndata->tiles[gameObjSelectedTiles[k]].id.palette[1]).c_str())
                        + wxString(main::intToHex(ndata->tiles[gameObjSelectedTiles[k]].id.palette[2]).c_str())
                        + wxString(main::intToHex(ndata->tiles[gameObjSelectedTiles[k]].id.palette[3]).c_str())
                        + "," + main::intToStr(ndata->tiles[gameObjSelectedTiles[k]].objCoordX - rightClickedGameObjTileX)
                        + "," + main::intToStr(ndata->tiles[gameObjSelectedTiles[k]].objCoordY - rightClickedGameObjTileY)
                        + "," +(ndata->tiles[gameObjSelectedTiles[k]].hFlip ? "Y" : "N")
                        + "," +(ndata->tiles[gameObjSelectedTiles[k]].vFlip ? "Y" : "N");
        }
        if (wxTheClipboard->Open()){
            wxTheClipboard->SetData( new wxTextDataObject(copyContent.c_str()) );
            wxTheClipboard->Close();
        }
        break;
    case GAME_OBJ_PNL_DELETE:
        ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));
        for(int k = 0; k < gameObjSelectedTiles.size(); ++k){
            ndata->tiles[gameObjSelectedTiles[k]].markForDelete = true;
        }
        int i;
        i = 0;
        while(i < ndata->tiles.size()){
            if(ndata->tiles[i].markForDelete){
                ndata->tiles.erase(ndata->tiles.begin() + i);
            }
            else{
                ++i;
            }
        }
        ndata->updatePalettes();
        gameObjSelectedTiles.clear();
        refreshGameObj();
        coreData::cData->dataChanged();
        break;
    case GAME_OBJ_PNL_HFLIP:
        ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));

        for(int k = 0; k < gameObjSelectedTiles.size(); ++k){
            ndata->tiles[gameObjSelectedTiles[k]].hFlip = !ndata->tiles[gameObjSelectedTiles[k]].hFlip;
        }
        refreshGameObj();
        coreData::cData->dataChanged();
        break;

    case GAME_OBJ_PNL_HFLIP2:
        ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));

        int minX, maxX;
        minX = ndata->tiles[gameObjSelectedTiles[0]].objCoordX;
        maxX = ndata->tiles[gameObjSelectedTiles[0]].objCoordX;

        for(int k = 0; k < gameObjSelectedTiles.size(); ++k){
            ndata->tiles[gameObjSelectedTiles[k]].hFlip = !ndata->tiles[gameObjSelectedTiles[k]].hFlip;
            if(ndata->tiles[gameObjSelectedTiles[k]].objCoordX < minX) minX = ndata->tiles[gameObjSelectedTiles[k]].objCoordX;
            if(ndata->tiles[gameObjSelectedTiles[k]].objCoordX > maxX) maxX = ndata->tiles[gameObjSelectedTiles[k]].objCoordX;
        }

        for(int k = 0; k < gameObjSelectedTiles.size(); ++k){
            ndata->tiles[gameObjSelectedTiles[k]].objCoordX = minX + (maxX - ndata->tiles[gameObjSelectedTiles[k]].objCoordX);
        }

        refreshGameObj();
        coreData::cData->dataChanged();
        break;

    case GAME_OBJ_PNL_VFLIP:
        ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));

        for(int k = 0; k < gameObjSelectedTiles.size(); ++k){
            ndata->tiles[gameObjSelectedTiles[k]].vFlip = !ndata->tiles[gameObjSelectedTiles[k]].vFlip;
        }
        refreshGameObj();
        coreData::cData->dataChanged();
        break;

    case GAME_OBJ_PNL_VFLIP2:
        ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));

        int minY, maxY;
        minY = ndata->tiles[gameObjSelectedTiles[0]].objCoordY;
        maxY = ndata->tiles[gameObjSelectedTiles[0]].objCoordY;

        for(int k = 0; k < gameObjSelectedTiles.size(); ++k){
            ndata->tiles[gameObjSelectedTiles[k]].vFlip = !ndata->tiles[gameObjSelectedTiles[k]].vFlip;
            if(ndata->tiles[gameObjSelectedTiles[k]].objCoordY < minY) minY = ndata->tiles[gameObjSelectedTiles[k]].objCoordY;
            if(ndata->tiles[gameObjSelectedTiles[k]].objCoordY > maxY) maxY = ndata->tiles[gameObjSelectedTiles[k]].objCoordY;
        }

        for(int k = 0; k < gameObjSelectedTiles.size(); ++k){
            ndata->tiles[gameObjSelectedTiles[k]].objCoordY = minY + (maxY - ndata->tiles[gameObjSelectedTiles[k]].objCoordY);
        }
        refreshGameObj();
        coreData::cData->dataChanged();
        break;

    case GAME_OBJ_PNL_REPLACE:

        ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));
        clickedX = 0;
        clickedY = 0;
        for(int k = 0; k < gameObjSelectedTiles.size(); ++k){
            selectedTiles.push_back(ndata->tiles[gameObjSelectedTiles[k]]);
        }
        t = ndata->tiles[rightClickedgameObjID];
        fp = new hdnesPackEditorreplacementDialog(this);
        fp->setSelectedTiles(selectedTiles, t.objCoordX, t.objCoordY, rightClickedGameObjTileX - t.objCoordX, rightClickedGameObjTileY - t.objCoordY);
        fp->Show(true);
        break;
    case GAME_OBJ_PNL_CONDITION:
        editCondition = true;
        gameObjconditionTiles.clear();
        gameObjconditionTiles.push_back(rightClickedgameObjID);
        //set condition tiles to selected tiles
        ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));
        t = ndata->tiles[rightClickedgameObjID];
        gameObjSelectedTiles.clear();
        for(int k = 0; k < t.conditions.size(); ++k){
            for(int i = 0; i < ndata->tiles.size(); ++i){
                if(t.conditions[k].isMatch(t, ndata->tiles[i])){
                    gameObjSelectedTiles.push_back(i);
                }
            }
        }
        drawGameObjEdits();
        break;
    case GAME_OBJ_PNL_GROUP_CONDITION:
        editCondition = true;
        gameObjconditionTiles.clear();
        for(int k = 0; k < gameObjSelectedTiles.size(); ++k){
            gameObjconditionTiles.push_back(gameObjSelectedTiles[k]);
        }
        gameObjSelectedTiles.clear();
        drawGameObjEdits();
        break;
    case GAME_OBJ_PNL_CONFIRM_CONDITION:
        editCondition = false;
        ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));
        for(int i = 0; i < gameObjconditionTiles.size(); ++i){
            t = ndata->tiles[gameObjconditionTiles[i]];
            t.conditions.clear();
            t.conSigns.clear();
            //add selected tiles to condition
            for(int k = 0; k < gameObjSelectedTiles.size(); ++k){
                c.id = ndata->tiles[gameObjSelectedTiles[k]].id;
                c.objCoordX = ndata->tiles[gameObjSelectedTiles[k]].objCoordX - t.objCoordX;
                c.objCoordY = ndata->tiles[gameObjSelectedTiles[k]].objCoordY - t.objCoordY;
                c.hFlip = (ndata->tiles[gameObjSelectedTiles[k]].hFlip != t.hFlip);
                c.vFlip = (ndata->tiles[gameObjSelectedTiles[k]].vFlip != t.vFlip);
                c.name = main::intToStr(conditionCounter++);
                t.conditions.push_back(c);
                t.conSigns.push_back(false);
            }
            ndata->tiles[gameObjconditionTiles[i]] = t;
        }

        gameObjSelectedTiles.clear();
        drawGameObjEdits();
        coreData::cData->dataChanged();
        break;
    case GAME_OBJ_PNL_CANCEL_CONDITION:
        editCondition = false;
        gameObjSelectedTiles.clear();
        drawGameObjEdits();
        break;
    case GAME_OBJ_PNL_SHOW_NOT_UNIQUE:
        gameObjSelectedTiles.clear();
        findGameObjNotUniqueTile();
        ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));
        for(int i = 0; i < ndata->tiles.size(); ++i){
            if(ndata->tiles[i].conditions.size() == 0 && !ndata->tiles[i].isUnique){
                gameObjSelectedTiles.push_back(i);
            }
        }
        drawGameObjEdits();
        break;
    case GAME_OBJ_PNL_AUTO_CONDITION:
        findGameObjNotUniqueTile();
        ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));
        //find an unique tile
        uniqueTileID = -1;
        for(int i = 0; i < ndata->tiles.size(); ++i){
            if(ndata->tiles[i].isUnique){
                uniqueTileID = i;
            }
        }
        if(uniqueTileID != -1){
            t = ndata->tiles[uniqueTileID];
            for(int i = 0; i < ndata->tiles.size(); ++i){
                if(ndata->tiles[i].conditions.size() == 0 && !ndata->tiles[i].isUnique){
                    c.id = t.id;
                    c.objCoordX = t.objCoordX - ndata->tiles[i].objCoordX;
                    c.objCoordY = t.objCoordY - ndata->tiles[i].objCoordY;
                    c.hFlip = (ndata->tiles[i].hFlip != t.hFlip);
                    c.vFlip = (ndata->tiles[i].vFlip != t.vFlip);
                    c.name = main::intToStr(conditionCounter++);
                    ndata->tiles[i].conditions.push_back(c);
                }
            }
        }
        coreData::cData->dataChanged();
        break;
    default:
        if(event.GetId() >= GAME_OBJ_PNL_PALETTE_SELECT_OFFSET){
            offset = event.GetId() - GAME_OBJ_PNL_PALETTE_SELECT_OFFSET;
            gameObjSelectedTiles.clear();
            ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));
            for(int i = 0; i < ndata->tiles.size(); ++i){
                if(ndata->tiles[i].id.palette[0] == ndata->palettes[offset][0]
                && ndata->tiles[i].id.palette[1] == ndata->palettes[offset][1]
                && ndata->tiles[i].id.palette[2] == ndata->palettes[offset][2]
                && ndata->tiles[i].id.palette[3] == ndata->palettes[offset][3]
                ){
                    gameObjSelectedTiles.push_back(i);
                }
            }
            drawGameObjEdits();
        }
        break;
    }
}

void hdnesPackEditormainForm::setReplacement(int imageID, int x, int y){
    gameObjNode* ndata;
    ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));
    gameTile t;
    gameTile t2;
    t2 = ndata->tiles[rightClickedgameObjID];
    for(int k = 0; k < gameObjSelectedTiles.size(); ++k){
        t = ndata->tiles[gameObjSelectedTiles[k]];
        t.hasReplacement = true;
        t.isDefault = false;
        t.aniFrames[0].img = imageID;
        t.aniFrames[0].x = x + ((t.objCoordX - t2.objCoordX) * coreData::cData->scale);
        t.aniFrames[0].y = y + ((t.objCoordY - t2.objCoordY) * coreData::cData->scale);
        t.aniFrames[0].brightness = 1;
        ndata->tiles[gameObjSelectedTiles[k]] = t;
    }
    refreshGameObj();
    coreData::cData->dataChanged();
}

bool hdnesPackEditormainForm::checkPasteValid(string content){
    vector<string> tileLines;
    main::split(content, '\n', tileLines);
    if(tileLines.size() > 0){
        bool allValid = true;
        vector<string> tileDetails;
        for(int i = 0; i < tileLines.size(); ++i){
            main::split(tileLines[i], ',', tileDetails);
            if(tileDetails.size() != 4 && tileDetails.size() != 6){
                allValid = false;
            }
        }
        return allValid;
    }
    return false;
}

void hdnesPackEditormainForm::refreshNode(){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;

    loadingTab = true;
    int i = nbkGameObject->GetPageCount();
    while (i-- > 0) {
        nbkGameObject->GetPage(i)->Show(false);
        nbkGameObject->RemovePage(i);
    }

    if(ndata->nodeType == GAME_OBJ_NODE_TYPE_OBJECT){
        pnlObj->Show(true);
        nbkGameObject->AddPage(pnlObj, wxString("Objection Information"));
        pnlSwaps->Show(true);
        nbkGameObject->AddPage(pnlSwaps, wxString("Palette swaps"));
        pnlConditions->Show(true);
        nbkGameObject->AddPage(pnlConditions, wxString("Conditions"));
    }
    else{
        pnlBGImage->Show(true);
        nbkGameObject->AddPage(pnlBGImage, wxString("Background"), false);
        pnlConditions->Show(true);
        nbkGameObject->AddPage(pnlConditions, wxString("Conditions"), false);
    }
    loadingTab = false;
    nbkGameObject->Refresh();
    nbkGameObject->Update();
    if(ndata->nodeType == GAME_OBJ_NODE_TYPE_OBJECT){
        refreshGameObj();
    }
    else{
        refreshBGImage();
    }
}

void hdnesPackEditormainForm::refreshBGImage(){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;

    spnBGBrightness->SetValue(ndata->brightness * 100);
    spnBGHScrollRate->SetValue(ndata->hScrollRate * 100);
    spnBGVScrollRate->SetValue(ndata->vScrollRate * 100);

    loadConditions();
    drawBGImage();
}

void hdnesPackEditormainForm::drawBGImage(){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(ndata && ndata->fileName > ""){
        wxImage imageData;
        imageData.LoadFile(wxString((coreData::cData->packPath + "\\" + ndata->fileName).c_str()));

        float bgImgScale = min(((float)pnlBGImageDisplay->GetSize().x) / ((float)imageData.GetWidth()), ((float)pnlBGImageDisplay->GetSize().y) / ((float)imageData.GetHeight()));

        wxImage scaledImg;
        scaledImg = imageData.Scale(imageData.GetWidth() * bgImgScale, imageData.GetHeight() * bgImgScale);

        wxImage displayImg;
        displayImg = wxImage(pnlBGImageDisplay->GetSize(), true);
        displayImg.SetRGB(displayImg.GetSize(), 128, 0, 128);
        scaledImg.ConvertAlphaToMask(64);
        displayImg.Paste(scaledImg, (pnlBGImageDisplay->GetSize().x - scaledImg.GetWidth()) / 2, (pnlBGImageDisplay->GetSize().y - scaledImg.GetHeight()) / 2);
        displayImg.ConvertAlphaToMask(64);
        displayImg.SetMask(false);

        wxBitmap bmp = wxBitmap(displayImg);
        if(bmp.IsOk()){
            wxClientDC* objDC;
            objDC = new wxClientDC(pnlBGImageDisplay);
            objDC->DrawBitmap(bmp, 0, 0);
            delete objDC;
        }
    }
}

void hdnesPackEditormainForm::refreshGameObj(){
    clearGameObj();
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;

    rbnObjectSprite->SetValue(ndata->isSprite);
    rbnObjectBG->SetValue(!ndata->isSprite);
    spnBrightness->SetValue(ndata->brightness * 100);
    chkGameObjIsDefault->SetValue(ndata->isDefault);

    //refresh bg colour button
    btnGameObjBGColour->SetBackgroundColour(coreData::cData->palette[ndata->bgColour]);
    if(coreData::cData->palette[ndata->bgColour].Red() + coreData::cData->palette[ndata->bgColour].Green() + coreData::cData->palette[ndata->bgColour].Blue() > 256){
        gameObjBlankColour = wxColour(0,0,0);
    }
    else{
        gameObjBlankColour = wxColour(255,255,255);
    }
    btnGameObjBGColour->SetForegroundColour(gameObjBlankColour);
    wxString v;
    v = wxString(main::intToHex(ndata->bgColour).c_str());
    btnGameObjBGColour->SetLabel(v);

    drawGameObj();
    adjustGameObjSize();
    drawGameObjEdits();

    loadSwaps();
    loadConditions();
}

void hdnesPackEditormainForm::loadSwaps(){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;

    //add palette swaps
    long j;
    lstSwaps->DeleteAllItems();
    for(int i = 0; i < ndata->swaps.size(); ++i){
        j = lstSwaps->InsertItem(i, wxString(ndata->swaps[i].name.c_str()), 0);
        lstSwaps->SetItem(j, 1, wxString(main::paletteToStr(ndata->swaps[i].newPalettes).c_str()));
        lstSwaps->SetItem(j, 2, wxString(main::intToStr(ndata->swaps[i].brightness * 100).c_str()));
        lstSwaps->SetItem(j, 3, wxString(main::intToStr(ndata->swaps[i].hueRotation * 360).c_str()));
        lstSwaps->SetItem(j, 4, wxString(main::intToStr(ndata->swaps[i].saturation * 100).c_str()));
    }
    selectedSwap = -1;
    showSwap();
}

void hdnesPackEditormainForm::loadConditions(){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;

    //add palette swaps
    long j;
    lstConditions->DeleteAllItems();
    for(int i = 0; i < ndata->conditions.size(); ++i){
        j = lstConditions->InsertItem(i, (ndata->conSigns[i] ? "!" : ""), 0);
        lstConditions->SetItem(j, 1, wxString(ndata->conditions[i].name.c_str()));
        lstConditions->SetItem(j, 2, wxString(ndata->conditions[i].conditionType.c_str()));
        lstConditions->SetItem(j, 3, wxString(ndata->conditions[i].writeLine().c_str()));
    }
    selectedCondition = -1;
    showCondition();
}

void hdnesPackEditormainForm::clearGameObj(){
    gameObjViewCentreX = 0;
    gameObjViewCentreY = 0;
    wxClientDC* objDC;
    objDC = new wxClientDC(pnlGameObjRaw);
    objDC->SetBackground(*wxBLACK_BRUSH);
    objDC->Clear();
    delete objDC;
    objDC = new wxClientDC(pnlGameObjNew);
    objDC->SetBackground(*wxBLACK_BRUSH);
    objDC->Clear();
    delete objDC;
}

void hdnesPackEditormainForm::drawGameObj(){
    gameObjNode* ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));
    gameObjRawImage = wxImage(max(ndata->objectWidth, 1), max(ndata->objectHeight, 1), true);
    gameObjNewImage = wxImage(max(ndata->objectWidth * coreData::cData->scale, 1), max(ndata->objectHeight * coreData::cData->scale, 1), true);
    //clear image with blank colour
    gameObjRawImage.SetRGB(wxRect(gameObjRawImage.GetSize()), gameObjBlankColour.Red(), gameObjBlankColour.Green(), gameObjBlankColour.Blue());
    gameObjNewImage.SetRGB(wxRect(gameObjNewImage.GetSize()), gameObjBlankColour.Red(), gameObjBlankColour.Green(), gameObjBlankColour.Blue());
    Uint32 memAddress;
    Uint16 drawX;
    Uint16 drawY;
    bool hasHD;
    gameTile* tile;
    int replaceSize = 8 * coreData::cData->scale;

    //fill background first
    for(int i = 0; i < ndata->tiles.size(); ++i){
        drawX = ndata->tiles[i].objCoordX - ndata->x1;
        drawY = ndata->tiles[i].objCoordY - ndata->y1;
        gameObjRawImage.SetRGB(wxRect(drawX, drawY, 8, 8), coreData::cData->palette[ndata->bgColour].Red(), coreData::cData->palette[ndata->bgColour].Green(), coreData::cData->palette[ndata->bgColour].Blue());
        gameObjNewImage.SetRGB(wxRect(drawX * coreData::cData->scale, drawY * coreData::cData->scale, replaceSize, replaceSize), coreData::cData->palette[ndata->bgColour].Red(), coreData::cData->palette[ndata->bgColour].Green(), coreData::cData->palette[ndata->bgColour].Blue());
    }
    //draw tiles in reverse order
    for(int i = ndata->tiles.size() - 1; i >= 0; --i){
        drawX = ndata->tiles[i].objCoordX - ndata->x1;
        drawY = ndata->tiles[i].objCoordY - ndata->y1;
        gameObjBaseTile.InitAlpha();
        memset(gameObjBaseTile.GetAlpha(), 0, 64);
        if(coreData::cData->isCHRROM){
            memAddress = ndata->tiles[i].id.id * 16;
            paintTile(gameObjBaseTile, coreData::cData->romData + memAddress, 0, 0, ndata->tiles[i].hFlip, ndata->tiles[i].vFlip,
                    coreData::cData->palette[ndata->tiles[i].id.palette[1]],
                    coreData::cData->palette[ndata->tiles[i].id.palette[2]],
                    coreData::cData->palette[ndata->tiles[i].id.palette[3]]);
        }
        else{
            paintTile(gameObjBaseTile, ndata->tiles[i].id.rawData, 0, 0, ndata->tiles[i].hFlip, ndata->tiles[i].vFlip,
                    coreData::cData->palette[ndata->tiles[i].id.palette[1]],
                    coreData::cData->palette[ndata->tiles[i].id.palette[2]],
                    coreData::cData->palette[ndata->tiles[i].id.palette[3]]);
        }
        gameObjBaseTile.ConvertAlphaToMask(64);
        gameObjRawImage.Paste(gameObjBaseTile, drawX, drawY);
        if(ndata->tiles[i].hasReplacement){
            gameObjBaseTileNew = coreData::cData->images[ndata->tiles[i].aniFrames[0].img]->imageData.GetSubImage(wxRect(ndata->tiles[i].aniFrames[0].x, ndata->tiles[i].aniFrames[0].y, replaceSize, replaceSize));
            gameObjBaseTileNew.ConvertAlphaToMask(64);
            gameObjNewImage.Paste(gameObjBaseTileNew, drawX * coreData::cData->scale, drawY * coreData::cData->scale);
            gameObjNewImage.ConvertAlphaToMask(64);
            gameObjNewImage.SetMask(false);
        }
        else{
            //look for replacement tiles
            hasHD = false;
            for(int j = 0; j < coreData::cData->tiles.size(); ++j){
                tile = coreData::cData->tiles[j];
                if(tile->compareEqual(ndata->tiles[i])){
                    if(tile->hasReplacement ){
                        hasHD = true;
                        gameObjBaseTileNew = coreData::cData->images[tile->aniFrames[0].img]->imageData.GetSubImage(wxRect(tile->aniFrames[0].x, tile->aniFrames[0].y, replaceSize, replaceSize));
                        if(ndata->tiles[i].hFlip){
                            gameObjBaseTileNew = gameObjBaseTileNew.Mirror(true);
                        }
                        if(ndata->tiles[i].vFlip){
                            gameObjBaseTileNew = gameObjBaseTileNew.Mirror(false);
                        }
                    }
                }
            }
            if(!hasHD){
                gameObjBaseTileNew = gameObjBaseTile.Scale(replaceSize, replaceSize);
            }
            gameObjBaseTileNew.ConvertAlphaToMask(64);
            gameObjNewImage.Paste(gameObjBaseTileNew, drawX * coreData::cData->scale, drawY * coreData::cData->scale);
            gameObjNewImage.ConvertAlphaToMask(64);
            gameObjNewImage.SetMask(false);

        }
    }
}

void hdnesPackEditormainForm::drawGameObjEdits(){
    if(gameObjPasteData.tiles.size() == 0){
        drawGameObjSelection();
    }
    else{
        drawGameObjPasteTiles();
    }
    showGameObj(gameObjRawImage2, gameObjNewImage2, gameObjRawPasteX, gameObjRawPasteY);
}

void hdnesPackEditormainForm::drawGameObjPasteTiles(){
    gameObjNode* ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));
    //cal image size
    int pasteX1 = min(gameObjPasteData.x1 + gameObjRawCurrPos.x, ndata->x1);
    int pasteX2 = max(gameObjPasteData.x2 + gameObjRawCurrPos.x, ndata->x2);
    int pasteY1 = min(gameObjPasteData.y1 + gameObjRawCurrPos.y, ndata->y1);
    int pasteY2 = max(gameObjPasteData.y2 + gameObjRawCurrPos.y, ndata->y2);
    int pasteWidth = pasteX2 - pasteX1;
    int pasteHeight = pasteY2 - pasteY1;

    //create image
    gameObjRawImage2 = wxImage(pasteWidth, pasteHeight, true);
    gameObjNewImage2 = wxImage(pasteWidth * coreData::cData->scale, pasteHeight * coreData::cData->scale, true);
    //clear image with blank colour
    gameObjRawImage2.SetRGB(wxRect(gameObjRawImage2.GetSize()), gameObjBlankColour.Red(), gameObjBlankColour.Green(), gameObjBlankColour.Blue());
    gameObjNewImage2.SetRGB(wxRect(gameObjNewImage2.GetSize()), gameObjBlankColour.Red(), gameObjBlankColour.Green(), gameObjBlankColour.Blue());

    //copy raw image here
    if(ndata->tiles.size() > 0){
        gameObjRawImage2.Paste(gameObjRawImage, ndata->x1 - pasteX1, ndata->y1 - pasteY1);
        gameObjNewImage2.Paste(gameObjNewImage, (ndata->x1 - pasteX1) * coreData::cData->scale, (ndata->y1 - pasteY1) * coreData::cData->scale);
    }

    //draw paste tiles
    Uint32 memAddress;
    int drawX;
    int drawY;
    for(int i = 0; i < gameObjPasteData.tiles.size(); ++i){
        drawX = gameObjPasteData.tiles[i].objCoordX - pasteX1 + gameObjRawCurrPos.x;
        drawY = gameObjPasteData.tiles[i].objCoordY - pasteY1 + gameObjRawCurrPos.y;
        if(coreData::cData->isCHRROM){
            memAddress = gameObjPasteData.tiles[i].id.id * 16;
            paintTile(gameObjRawImage2, coreData::cData->romData + memAddress, drawX, drawY, gameObjPasteData.tiles[i].hFlip, gameObjPasteData.tiles[i].vFlip,
                    coreData::cData->palette[gameObjPasteData.tiles[i].id.palette[1]],
                    coreData::cData->palette[gameObjPasteData.tiles[i].id.palette[2]],
                    coreData::cData->palette[gameObjPasteData.tiles[i].id.palette[3]]);
        }
        else{
            paintTile(gameObjRawImage2, gameObjPasteData.tiles[i].id.rawData, drawX, drawY, gameObjPasteData.tiles[i].hFlip, gameObjPasteData.tiles[i].vFlip,
                    coreData::cData->palette[gameObjPasteData.tiles[i].id.palette[1]],
                    coreData::cData->palette[gameObjPasteData.tiles[i].id.palette[2]],
                    coreData::cData->palette[gameObjPasteData.tiles[i].id.palette[3]]);
        }
    }
    //scale up
    gameObjRawImage2 = gameObjRawImage2.Scale(pasteWidth * gameObjZoom, pasteHeight * gameObjZoom);
    gameObjNewImage2 = gameObjNewImage2.Scale(pasteWidth * gameObjZoom, pasteHeight * gameObjZoom);

    //draw outline of paste tiles
    wxPoint pt;
    wxPoint pt2;
    wxPoint tileBoxSize;
    tileBoxSize.x = gameObjTileSize - 1;
    tileBoxSize.y = gameObjTileSize - 1;
    for(int i = 0; i < gameObjPasteData.tiles.size(); ++i){
        pt.x = (gameObjPasteData.tiles[i].objCoordX - pasteX1 + gameObjRawCurrPos.x) * gameObjZoom;
        pt.y = (gameObjPasteData.tiles[i].objCoordY - pasteY1 + gameObjRawCurrPos.y) * gameObjZoom;
        pt2 = pt;
        ++(pt2.x);
        ++(pt2.y);
        main::drawRect(gameObjRawImage2, pt2, tileBoxSize, wxColour(0, 0, 0));
        main::drawRect(gameObjRawImage2, pt, tileBoxSize, wxColour(255, 255, 255));
    }

    gameObjRawPasteX = pasteX1 * gameObjZoom + (pnlGameObjRaw->GetSize().GetWidth() / 2) - gameObjViewCentreX;
    gameObjRawPasteY = pasteY1 * gameObjZoom + (pnlGameObjRaw->GetSize().GetHeight() / 2) - gameObjViewCentreY;

}

void hdnesPackEditormainForm::drawGameObjSelection(){
    gameObjNode* ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));
    gameObjRawImage2 = gameObjRawImage.Scale(gameObjRawImage.GetWidth() * gameObjZoom, gameObjRawImage.GetHeight() * gameObjZoom);
    gameObjNewImage2 = gameObjNewImage.Scale(gameObjRawImage.GetWidth() * gameObjZoom, gameObjRawImage.GetHeight() * gameObjZoom);

    //draw outline of selected tiles
    wxPoint pt;
    wxPoint pt2;
    wxPoint tileBoxSize;
    tileBoxSize.x = gameObjTileSize - 1;
    tileBoxSize.y = gameObjTileSize - 1;
    for(int i = 0; i < gameObjSelectedTiles.size(); ++i){
        pt.x = (ndata->tiles[gameObjSelectedTiles[i]].objCoordX - ndata->x1) * gameObjZoom;
        pt.y = (ndata->tiles[gameObjSelectedTiles[i]].objCoordY - ndata->y1) * gameObjZoom;
        pt2 = pt;
        ++(pt2.x);
        ++(pt2.y);
        main::drawRect(gameObjRawImage2, pt2, tileBoxSize, wxColour(0, 0, 0));
        main::drawRect(gameObjRawImage2, pt, tileBoxSize, wxColour(255, 255, 255));
        main::drawRect(gameObjNewImage2, pt2, tileBoxSize, wxColour(0, 0, 0));
        main::drawRect(gameObjNewImage2, pt, tileBoxSize, wxColour(255, 255, 255));
    }
    if(editCondition){
        for(int i = 0; i < gameObjconditionTiles.size(); ++i){
            pt.x = (ndata->tiles[gameObjconditionTiles[i]].objCoordX - ndata->x1) * gameObjZoom;
            pt.y = (ndata->tiles[gameObjconditionTiles[i]].objCoordY - ndata->y1) * gameObjZoom;
            pt2 = pt;
            ++(pt2.x);
            ++(pt2.y);
            main::drawRect(gameObjRawImage2, pt2, tileBoxSize, wxColour(0, 100, 100));
            main::drawRect(gameObjRawImage2, pt, tileBoxSize, wxColour(0, 255, 255));
            main::drawRect(gameObjNewImage2, pt2, tileBoxSize, wxColour(0, 100, 100));
            main::drawRect(gameObjNewImage2, pt, tileBoxSize, wxColour(0, 255, 255));
        }
    }

    gameObjRawPasteX = ndata->x1 * gameObjZoom + (pnlGameObjRaw->GetSize().GetWidth() / 2) - gameObjViewCentreX;
    gameObjRawPasteY = ndata->y1 * gameObjZoom + (pnlGameObjRaw->GetSize().GetHeight() / 2) - gameObjViewCentreY;
}

void hdnesPackEditormainForm::adjustGameObjSize(){
    gameObjNode* ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));
    //at least half panel left of centre
    gameObjScrollMinH = -pnlGameObjRaw->GetSize().GetWidth() / 2;
    //adjust for object left size
    gameObjScrollMinH = min(gameObjScrollMinH, (ndata->x1 - 16) * gameObjZoom);
    //repeat for right side
    gameObjScrollMaxH = pnlGameObjRaw->GetSize().GetWidth() / 2;
    gameObjScrollMaxH = max(gameObjScrollMaxH, (ndata->x2 + 16) * gameObjZoom);

    //repeat for vertical
    gameObjScrollMinV = -pnlGameObjRaw->GetSize().GetHeight() / 2;
    gameObjScrollMinV = min(gameObjScrollMinV, (ndata->y1 - 16) * gameObjZoom);
    gameObjScrollMaxV = pnlGameObjRaw->GetSize().GetHeight() / 2;
    gameObjScrollMaxV = max(gameObjScrollMaxV, (ndata->y2 + 16) * gameObjZoom);

    gameObjScrollSizeH = gameObjScrollMaxH - gameObjScrollMinH;
    gameObjScrollSizeV = gameObjScrollMaxV - gameObjScrollMinV;

    scrGameObjRawH->SetRange(gameObjScrollSizeH);
    scrGameObjRawV->SetRange(gameObjScrollSizeV);
    scrGameObjRawH->SetThumbSize(pnlGameObjRaw->GetSize().GetWidth());
    scrGameObjRawV->SetThumbSize(pnlGameObjRaw->GetSize().GetHeight());

    //check view centre is out of bound
    gameObjViewCentreX = min(gameObjViewCentreX, gameObjScrollMaxH - (pnlGameObjRaw->GetSize().GetWidth() / 2));
    gameObjViewCentreX = max(gameObjViewCentreX, gameObjScrollMinH + (pnlGameObjRaw->GetSize().GetWidth() / 2));
    gameObjViewCentreY = min(gameObjViewCentreY, gameObjScrollMaxV - (pnlGameObjRaw->GetSize().GetHeight() / 2));
    gameObjViewCentreY = max(gameObjViewCentreY, gameObjScrollMinV + (pnlGameObjRaw->GetSize().GetHeight() / 2));

    scrGameObjRawH->SetThumbPosition(gameObjViewCentreX - gameObjScrollMinH - (pnlGameObjRaw->GetSize().GetWidth() / 2));
    scrGameObjRawV->SetThumbPosition(gameObjViewCentreY - gameObjScrollMinV - (pnlGameObjRaw->GetSize().GetHeight() / 2));
}

void hdnesPackEditormainForm::showGameObj(wxImage& displayImg, wxImage& displayImg2, int x, int y){
    gameObjRawImageDisplay.SetRGB(wxRect(gameObjRawImageDisplay.GetSize()), gameObjBlankColour.Red(), gameObjBlankColour.Green(), gameObjBlankColour.Blue());
    gameObjRawImageDisplay.Paste(displayImg, x, y);
    gameObjNewImageDisplay.SetRGB(wxRect(gameObjNewImageDisplay.GetSize()), gameObjBlankColour.Red(), gameObjBlankColour.Green(), gameObjBlankColour.Blue());
    gameObjNewImageDisplay.Paste(displayImg2, x, y);

    if(gameObjClicked){
        wxPoint p1;
        p1.x = min(gameObjLDownPos.x, gameObjLCurrPos.x);
        p1.y = min(gameObjLDownPos.y, gameObjLCurrPos.y);

        wxPoint p2;
        p2.x = max(gameObjLDownPos.x, gameObjLCurrPos.x);
        p2.y = max(gameObjLDownPos.y, gameObjLCurrPos.y);

        wxPoint rectSize;
        rectSize.x = p2.x - p1.x;
        rectSize.y = p2.y - p1.y;

        wxPoint p3 = p1;
        ++(p3.x);
        ++(p3.y);

        main::drawRect(gameObjRawImageDisplay, p3, rectSize, wxColour(0, 0, 0));
        main::drawRect(gameObjRawImageDisplay, p1, rectSize, wxColour(255, 255, 255));
    }

    wxClientDC* objDC;
    wxBitmap bmp = wxBitmap(gameObjRawImageDisplay);
	if(bmp.IsOk()){
		objDC = new wxClientDC(pnlGameObjRaw);
		objDC->DrawBitmap(bmp, 0, 0);
		delete objDC;
	}
    bmp = wxBitmap(gameObjNewImageDisplay);
	if(bmp.IsOk()){
		objDC = new wxClientDC(pnlGameObjNew);
		objDC->DrawBitmap(bmp, 0, 0);
		delete objDC;
	}
}

void hdnesPackEditormainForm::gameObjSpriteClicked( wxCommandEvent& event ){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;

    ndata->isSprite = rbnObjectSprite->GetValue();
    coreData::cData->dataChanged();
}

void hdnesPackEditormainForm::gameObjBGClicked( wxCommandEvent& event ){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;

    ndata->isSprite = !rbnObjectBG->GetValue();
    coreData::cData->dataChanged();
}

void hdnesPackEditormainForm::gameObjBGColour( wxCommandEvent& event ){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;
    if(ndata->isSprite){
        openColourDialog(COLOUR_CLIENT_GAME_OBJ_BG);
    }
    else{
        wxMessageBox("Only background color of sprite objects can be changed.", "Action invalid", wxICON_ERROR);
    }
}

void hdnesPackEditormainForm::gameObjsRawMove( wxMouseEvent& event ){
    if(getGameObjsSelectedObjectTreeNode()){
        gameObjRawCurrPos = convertGameObjRawPosition(event.GetPosition());
        if(gameObjPasteData.tiles.size() > 0){
            drawGameObjEdits();
        }
        else if(gameObjClicked){
            gameObjLCurrPos = event.GetPosition();
            drawGameObjEdits();
        }
    }
}

wxPoint hdnesPackEditormainForm::convertGameObjRawPosition(wxPoint pos){
    wxPoint result;
    int pnlWidth = pnlGameObjRaw->GetSize().GetWidth();
    int pnlHeight = pnlGameObjRaw->GetSize().GetHeight();
    result.x = pos.x + gameObjViewCentreX - (pnlWidth / 2);
    result.y = pos.y + gameObjViewCentreY - (pnlHeight / 2);;
    //remove scale
    result.x = result.x / gameObjZoom;
    result.y = result.y / gameObjZoom;
    return result;
}

void hdnesPackEditormainForm::gameObjsRawEnter( wxMouseEvent& event ){
    if(getGameObjsSelectedObjectTreeNode() && !event.LeftIsDown()){
        gameObjClicked = false;
        drawGameObjSelection();
    }
}

void hdnesPackEditormainForm::gameObjsRawLDown( wxMouseEvent& event ){
    if(!getGameObjsSelectedObjectTreeNode()) return;
    if(event.GetModifiers() != wxMOD_CONTROL){
        //clear currently selected
        gameObjSelectedTiles.clear();
    }
    gameObjLDownPos = event.GetPosition();
    gameObjLCurrPos = gameObjLDownPos;
    gameObjClicked = true;
    drawGameObjSelection();
}

void hdnesPackEditormainForm::gameObjsRawLUp( wxMouseEvent& event ){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(ndata){
        if(gameObjClicked){
            wxPoint p = event.GetPosition();
            wxPoint corner1;
            wxPoint corner2;
            corner1.x = min(p.x, gameObjLDownPos.x);
            corner2.x = max(p.x, gameObjLDownPos.x);
            corner1.y = min(p.y, gameObjLDownPos.y);
            corner2.y = max(p.y, gameObjLDownPos.y);
            corner1 = convertGameObjRawPosition(corner1);
            corner2 = convertGameObjRawPosition(corner2);
            wxPoint ld = convertGameObjRawPosition(gameObjLDownPos);
            for(int i = 0; i < ndata->tiles.size(); i++){
                if(editCondition){
                    for(int j = 0; j < gameObjconditionTiles.size(); j++){
                        if(i == gameObjconditionTiles[j])
                            continue;
                    }
                }

                if(ld.x <= ndata->tiles[i].objCoordX + 8
                   && ld.x >= ndata->tiles[i].objCoordX
                   && ld.y <= ndata->tiles[i].objCoordY + 8
                   && ld.y >= ndata->tiles[i].objCoordY){
                    m_statusBar->SetLabel(wxString((ndata->tiles[i].id.writeID() + ", " + ndata->tiles[i].id.writePalette()).c_str()));
                }
                if(corner1.x <= ndata->tiles[i].objCoordX + 8
                   && corner2.x >= ndata->tiles[i].objCoordX
                   && corner1.y <= ndata->tiles[i].objCoordY + 8
                   && corner2.y >= ndata->tiles[i].objCoordY){

                    //look for that id in vector
                    bool tileFound = false;
                    for(Uint32 k = 0; k < gameObjSelectedTiles.size(); ++k){
                        if(gameObjSelectedTiles[k] == i){
                            gameObjSelectedTiles.erase(gameObjSelectedTiles.begin() + k);
                            tileFound = true;
                        }
                    }
                    if(!tileFound){
                        gameObjSelectedTiles.push_back(i);
                    }
                }
            }
            gameObjClicked = false;
            drawGameObjEdits();
        }
    }
}

void hdnesPackEditormainForm::gameObjsRawSizeChanged( wxSizeEvent& event ){
    if(coreData::cData && !loadingTab){
        gameObjRawImageDisplay = wxImage(pnlGameObjRaw->GetSize().x, pnlGameObjRaw->GetSize().y);
        gameObjNewImageDisplay = wxImage(pnlGameObjNew->GetSize().x, pnlGameObjNew->GetSize().y);

        if(!getGameObjsSelectedObjectTreeNode()) return;
        adjustGameObjSize();
        drawGameObjEdits();
    }
}

void hdnesPackEditormainForm::gameObjsRawHScrolled( wxScrollEvent& event ){
    if(getGameObjsSelectedObjectTreeNode()){
        gameObjViewCentreX = scrGameObjRawH->GetThumbPosition() + gameObjScrollMinH + (pnlGameObjRaw->GetSize().GetWidth() / 2);
        drawGameObjEdits();
    }
}

void hdnesPackEditormainForm::gameObjsRawVScrolled( wxScrollEvent& event ){
    if(getGameObjsSelectedObjectTreeNode()){
        gameObjViewCentreY = scrGameObjRawV->GetThumbPosition() + gameObjScrollMinV + (pnlGameObjRaw->GetSize().GetHeight() / 2);
        drawGameObjEdits();
    }
}

void hdnesPackEditormainForm::zoomGameObjsChanged( wxSpinEvent& event ){
    gameObjZoom = zoomGameObjs->GetValue();
    gameObjTileSize = 8 * gameObjZoom;
    if(getGameObjsSelectedObjectTreeNode()){
        gameObjViewCentreX = (gameObjViewCentreX * zoomGameObjs->GetValue()) / gameObjZoom;
        gameObjViewCentreY = (gameObjViewCentreY * zoomGameObjs->GetValue()) / gameObjZoom;
        adjustGameObjSize();
        drawGameObjEdits();
    }
}

void hdnesPackEditormainForm::replaceBrightnessChanged( wxScrollEvent& event ){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(ndata){
        ndata->brightness = (float)spnBrightness->GetValue() / 100.0;
        dataChanged();
    }
}

void hdnesPackEditormainForm::gameObjDefaultClicked( wxCommandEvent& event ){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(ndata){
        ndata->isDefault = chkGameObjIsDefault->GetValue();
        dataChanged();
    }
}

void hdnesPackEditormainForm::configGameObjs(string lineHdr, string lineTail){
}

void hdnesPackEditormainForm::saveCfgGameObjs(fstream& inifile){
}

void hdnesPackEditormainForm::loadGameObjs(fstream& file){
    loadGameObjItem(file, treeGameObjs->GetRootItem(), true);
    renameGameObjConditions();
}

void hdnesPackEditormainForm::loadGameObjItem(fstream& file, wxTreeItemId item, bool isRoot){
    gameObjNode* node = new gameObjNode();
    wxTreeItemId newItm;
    if(isRoot){
        newItm = item;
        node->nodeName = "\\";
    }
    else{
        newItm = treeGameObjs->InsertItem(item, treeGameObjs->GetLastChild(item), "");
    }
    node->load(file, newItm);
    treeGameObjs->SetItemData(newItm, node);
    if(node->nodeType == GAME_OBJ_NODE_TYPE_GROUP){
        treeGameObjs->SetItemText(newItm, wxString(node->nodeName + "\\"));
    }
    else{
        treeGameObjs->SetItemText(newItm, wxString(node->nodeName));
    }
}

void hdnesPackEditormainForm::loadChildGameObjs(fstream& file, wxTreeItemId item){
    string line;
    getline(file, line);
    while(line != "<endChildObjects>"){
        loadGameObjItem(file, item, false);
        getline(file, line);
    }
}

void hdnesPackEditormainForm::saveGameObjs(fstream& file){
    saveGameObjItem(file, tItmGameObjRoot);
}

void hdnesPackEditormainForm::saveGameObjItem(fstream& file, wxTreeItemId item){
    gameObjNode* node = (gameObjNode*)(treeGameObjs->GetItemData(item));
    node->save(file, item);
}

void hdnesPackEditormainForm::saveChildGameObjs(fstream& file, wxTreeItemId item){
    wxTreeItemIdValue cookie = 0;
    wxTreeItemId child = treeGameObjs->GetFirstChild(item, cookie);
    while(child.IsOk()){
        saveGameObjItem(file, child);
        child = treeGameObjs->GetNextSibling(child);
    }
}

void hdnesPackEditormainForm::renameGameObjConditions(){
    conditionCounter = 0;
    renameChildGameObjItemConditions(tItmGameObjRoot);
}

void hdnesPackEditormainForm::renameChildGameObjConditions(wxTreeItemId item){
    wxTreeItemIdValue cookie = 0;
    wxTreeItemId child = treeGameObjs->GetFirstChild(item, cookie);
    while(child.IsOk()){
        renameChildGameObjItemConditions(child);
        child = treeGameObjs->GetNextSibling(child);
    }
}

void hdnesPackEditormainForm::renameChildGameObjItemConditions(wxTreeItemId item){
    gameObjNode* node = (gameObjNode*)(treeGameObjs->GetItemData(item));
    for(int i = 0; i < node->tiles.size(); ++i){
        for(int j = 0; j <  node->tiles[i].conditions.size(); ++j){
            node->tiles[i].conditions[j].name = main::intToStr(conditionCounter++);
        }
    }
    renameChildGameObjConditions(item);
}

void hdnesPackEditormainForm::removeGameObjImage(int index){
    removeChildGameObjItemImage(tItmGameObjRoot, index);
}

void hdnesPackEditormainForm::removeChildGameObjImage(wxTreeItemId item, int index){
    wxTreeItemIdValue cookie = 0;
    wxTreeItemId child = treeGameObjs->GetFirstChild(item, cookie);
    while(child.IsOk()){
        removeChildGameObjItemImage(child, index);
        child = treeGameObjs->GetNextSibling(child);
    }
}

void hdnesPackEditormainForm::removeChildGameObjItemImage(wxTreeItemId item, int index){
    gameObjNode* node = (gameObjNode*)(treeGameObjs->GetItemData(item));
    for(int i = 0; i < node->tiles.size(); ++i){
        if(node->tiles[i].hasReplacement){
            if(node->tiles[i].aniFrames[0].img > index){
                node->tiles[i].aniFrames[0].img--;
            }
            else if(node->tiles[i].aniFrames[0].img == index){
                node->tiles[i].hasReplacement = false;
            }
        }
    }
    removeChildGameObjImage(item, index);
}

void hdnesPackEditormainForm::applySwap(Uint8* palette, paletteSwap& s){
    for(int i = 0; i < s.orgPalettes.size(); ++i){
        if(palette[0] == s.orgPalettes[i][0]
           && palette[1] == s.orgPalettes[i][1]
           && palette[2] == s.orgPalettes[i][2]
           && palette[3] == s.orgPalettes[i][3]){
            palette[0] = s.newPalettes[i][0];
            palette[1] = s.newPalettes[i][1];
            palette[2] = s.newPalettes[i][2];
            palette[3] = s.newPalettes[i][3];
        }
    }
}

void hdnesPackEditormainForm::genGameObjsConditionPack(fstream& file){
    genGameObjItemConditionPack(file, tItmGameObjRoot);
    gameObjectGenImageCnt = 0;
    gameObjectGenImageX = 0;
    gameObjectGenImageY = 0;
}

void hdnesPackEditormainForm::genChildGameObjsConditionPack(fstream& file, wxTreeItemId item){
    wxTreeItemIdValue cookie = 0;
    wxTreeItemId child = treeGameObjs->GetFirstChild(item, cookie);
    while(child.IsOk()){
        genGameObjItemConditionPack(file, child);
        child = treeGameObjs->GetNextSibling(child);
    }
}

void hdnesPackEditormainForm::genGameObjItemConditionPack(fstream& file, wxTreeItemId item){
    gameObjNode* node = (gameObjNode*)(treeGameObjs->GetItemData(item));
    for(int i = 0; i < node->conditions.size(); ++i){
        file << "<condition>" << node->nodeName << "_" << node->conditions[i].name << "," << node->conditions[i].conditionType << "," << node->conditions[i].writeLine() << "\n";
    }
    for(int i = 0; i < node->tiles.size(); ++i){
        for(int j = 0; j <  node->tiles[i].conditions.size(); ++j){
            node->tiles[i].conditions[j].conditionType = (node->isSprite ? "spriteNearby" : "tileNearby");
            file << "<condition>" << node->tiles[i].conditions[j].name << "," << node->tiles[i].conditions[j].conditionType << "," << node->tiles[i].conditions[j].writeLine() << "\n";
            for(int k = 0; k < node->swaps.size(); ++k){
                condition tmpC = node->tiles[i].conditions[j];
                applySwap(tmpC.id.palette, node->swaps[k]);
                tmpC.name = tmpC.name + "_" + main::intToStr(k);
                file << "<condition>" << tmpC.name << "," << tmpC.conditionType << "," << tmpC.writeLine() << "\n";
            }
        }
    }
    genChildGameObjsConditionPack(file, item);
}

void hdnesPackEditormainForm::genGameObjsTilePack(fstream& file, bool withCondition){
    genGameObjItemTilePack(file, tItmGameObjRoot, withCondition);
}

void hdnesPackEditormainForm::genChildGameObjsTilePack(fstream& file, wxTreeItemId item, bool withCondition){
    wxTreeItemIdValue cookie = 0;
    wxTreeItemId child = treeGameObjs->GetFirstChild(item, cookie);
    while(child.IsOk()){
        genGameObjItemTilePack(file, child, withCondition);
        child = treeGameObjs->GetNextSibling(child);
    }
}

void hdnesPackEditormainForm::genGameObjItemTilePack(fstream& file, wxTreeItemId item, bool withCondition){
    gameObjNode* node = (gameObjNode*)(treeGameObjs->GetItemData(item));

    if(node->nodeType == GAME_OBJ_NODE_TYPE_OBJECT){
        for(int i = 0; i < node->tiles.size(); ++i){
            if(node->tiles[i].hasReplacement && (withCondition == (node->tiles[i].conditions.size() > 0 || node->conditions.size() > 0))){
                paletteSwap s = paletteSwap();
                s.brightness = node->brightness;
                genCustomImage(file, node->tiles[i], s, node->isSprite, -1, node->isDefault, node);
                for(int j = 0; j < node->swaps.size(); ++j){
                    genCustomImage(file, node->tiles[i], node->swaps[j], node->isSprite, j, false, node);
                }
            }
        }
    }
    else if(node->nodeType == GAME_OBJ_NODE_TYPE_BGIMAGE && withCondition){
        if(node->conditions.size() > 0){
            file << "[";
            file << node->writeConditionNames();
            file << "]";
        }
        //write line
        file << "<background>" << node->writeLine() << "\n";
    }
    else{
        genChildGameObjsTilePack(file, item, withCondition);
    }
    if(gameObjectGenImageX != 0 || gameObjectGenImageY != 0){
        //save image file
        gameObjectGenImage.SaveFile(wxString((coreData::cData->packPath + "\\editorGenImage" + main::intToStr(gameObjectGenImageCnt) + ".png").c_str()));
    }
}

void hdnesPackEditormainForm::genCustomImage(fstream& file, gameTile t, paletteSwap s, bool isSprite, int swapID, bool isDefault, gameObjNode* gObj){
    int replaceSize = 8 * coreData::cData->scale;
    wxImage tmp;
    t.aniFrames[0].brightness = s.brightness;
    t.isDefault = isDefault;
    if(swapID >= 0){
        applySwap(t.id.palette, s);
        for(int i = 0; i < t.conditions.size(); ++i){
            t.conditions[i].name = t.conditions[i].name + "_" + main::intToStr(swapID);
        }
    }
    //adjust for sprite
    if(isSprite){
        t.id.palette[0] = 0xff;
    }
    if((isSprite && (t.hFlip || t.vFlip)) || (s.hueRotation != 0.0) || (s.saturation != 1.0)){
        //generate mirrored tile
        //create if not yet
        if(gameObjectGenImageX == 0 && gameObjectGenImageY == 0){
            gameObjectGenImage = wxImage(32 * replaceSize, 32 * replaceSize, true);
            gameObjectGenImage.InitAlpha();
            memset(gameObjectGenImage.GetAlpha(), 0, 32 * replaceSize * 32 * replaceSize);
            file << "<img>editorGenImage" + main::intToStr(gameObjectGenImageCnt) + ".png\n";
        }
        //add flipped tile to image
        tmp = coreData::cData->images[t.aniFrames[0].img]->imageData.GetSubImage(wxRect(t.aniFrames[0].x, t.aniFrames[0].y, replaceSize, replaceSize));
        if(t.hFlip){
            tmp = tmp.Mirror(true);
        }
        if(t.vFlip){
            tmp = tmp.Mirror(false);
        }
        if(s.hueRotation != 0.0){
            tmp.RotateHue(s.hueRotation);
        }
        if(s.saturation != 1.0){
            for(int dx = 0; dx < replaceSize; ++dx){
                for(int dy = 0; dy < replaceSize; ++dy){
                    wxImage::RGBValue rgbC = wxImage::RGBValue(tmp.GetRed(dx, dy), tmp.GetGreen(dx, dy), tmp.GetBlue(dx, dy));
                    wxImage::HSVValue hsvC = wxImage::RGBtoHSV(rgbC);
                    hsvC.saturation = hsvC.saturation * s.saturation;
                    rgbC = wxImage::HSVtoRGB(hsvC);
                    tmp.SetRGB(dx, dy, rgbC.red, rgbC.green, rgbC.blue);
                }
            }
        }

        //copy pixel data
        gameObjectGenImage.Paste(tmp, gameObjectGenImageX * replaceSize, gameObjectGenImageY * replaceSize);
        //copy alpha data
        for(int dx = 0; dx < replaceSize; ++dx){
            for(int dy = 0; dy < replaceSize; ++dy){
                gameObjectGenImage.SetAlpha(gameObjectGenImageX * replaceSize + dx, gameObjectGenImageY * replaceSize + dy, tmp.GetAlpha(dx, dy));
            }
        }
        //create tmp tile
        t.aniFrames[0].img = coreData::cData->images.size() + gameObjectGenImageCnt;
        t.aniFrames[0].x = gameObjectGenImageX * replaceSize;
        t.aniFrames[0].y = gameObjectGenImageY * replaceSize;

        //move position
        gameObjectGenImageX += 1;
        if(gameObjectGenImageX == 32){
            gameObjectGenImageY += 1;
            gameObjectGenImageX = 0;
            if(gameObjectGenImageY == 32){
                //save image file
                gameObjectGenImage.SaveFile(wxString((coreData::cData->packPath + "\\editorGenImage" + main::intToStr(gameObjectGenImageCnt) + ".png").c_str()));
                gameObjectGenImageCnt ++;
                gameObjectGenImageY = 0;
            }
        }
    }


    //write object condition
    if(t.conditions.size() > 0 || gObj->conditions.size() > 0){
        file << "[";
        file << gObj->writeConditionNames();
        if(t.conditions.size() > 0 && gObj->conditions.size() > 0){
            file << "&";
        }
        file << t.writeConditionNames();
        file << "]";
    }
    //write line
    file << "<tile>" << t.writeLine() << "\n";
}



void hdnesPackEditormainForm::findGameObjNotUniqueTile(){
    gameObjNode* ndata = (gameObjNode*)(treeGameObjs->GetItemData(tItmGameObjMenu));
    for(int i = 0; i < ndata->tiles.size(); ++i){
        ndata->tiles[i].isUnique = true;
    }
    for(int i = 0; i < ndata->tiles.size(); ++i){
        if(ndata->tiles[i].isUnique){
            for(int j = i + 1; j < ndata->tiles.size(); ++j){
                if(ndata->tiles[j].id.compareEqual(ndata->tiles[i].id)){
                    ndata->tiles[j].isUnique = false;
                    ndata->tiles[i].isUnique = false;
                }
            }
        }
    }
}

void hdnesPackEditormainForm::addGameObjNotUniqueTileCondition(){
}

void hdnesPackEditormainForm::SwapSeleted( wxListEvent& event ){
    selectedSwap = event.GetIndex();
    showSwap();
}

void hdnesPackEditormainForm::showSwap(){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;
    paletteSwap p;
    if(selectedSwap >= 0){
        p = ndata->swaps[selectedSwap];
    }
    txtSwapName->SetValue(wxString(p.name.c_str()));
    spnSwapNewBrightness->SetValue(p.brightness * 100);
    spnSwapRotateHue->SetValue(p.hueRotation * 360);
    spnSwapNewSaturation->SetValue(p.saturation * 100);

    lstPalettes->DeleteAllItems();
    stringstream s;
    long j;
    for(int i = 0; i < ndata->palettes.size(); ++i){
        s.str(std::string());
        s.clear();
        s << main::intToHex(ndata->palettes[i][0]);
        s << main::intToHex(ndata->palettes[i][1]);
        s << main::intToHex(ndata->palettes[i][2]);
        s << main::intToHex(ndata->palettes[i][3]);

        j = lstPalettes->InsertItem(i, wxString(s.str().c_str()), 0);
        lstPalettes->SetItem(j, 1, wxString(s.str().c_str()));

        for(int k = 0; k < p.orgPalettes.size(); ++k){
            if(ndata->palettes[i][0] == p.orgPalettes[k][0] && ndata->palettes[i][1] == p.orgPalettes[k][1] && ndata->palettes[i][2] == p.orgPalettes[k][2] && ndata->palettes[i][3] == p.orgPalettes[k][3]){
                s.str(std::string());
                s.clear();
                s << main::intToHex(p.newPalettes[k][0]);
                s << main::intToHex(p.newPalettes[k][1]);
                s << main::intToHex(p.newPalettes[k][2]);
                s << main::intToHex(p.newPalettes[k][3]);

                lstPalettes->SetItem(j, 1, wxString(s.str().c_str()));
            }
        }
    }
    if(ndata->palettes.size() > 0){
        selectedSwapPalette = 0;
        lstPalettes->SetItemState(selectedSwapPalette, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
        showSwapPalette();
    }
    else{
        selectedSwapPalette = -1;
    }
}

void hdnesPackEditormainForm::SwapPaletteSelected( wxListEvent& event ){
    selectedSwapPalette = event.GetIndex();
    showSwapPalette();
}

void hdnesPackEditormainForm::showSwapPalette(){
    Uint8 tmpPalette[4];
    lblOrgPalette->SetLabel(lstPalettes->GetItemText(selectedSwapPalette));
    main::hexToByteArray(lstPalettes->GetItemText(selectedSwapPalette).ToStdString(), (Uint8*)tmpPalette);
    if(tmpPalette[0] < 64){
        pnlOrgPaletteBG->SetBackgroundColour(coreData::cData->palette[tmpPalette[0]]);
    }
    else{
        pnlOrgPaletteBG->SetBackgroundColour(wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ));
    }
    pnlOrgPaletteBG->Refresh();
    pnlOrgPalette1->SetBackgroundColour(coreData::cData->palette[tmpPalette[1]]);
    pnlOrgPalette1->Refresh();
    pnlOrgPalette2->SetBackgroundColour(coreData::cData->palette[tmpPalette[2]]);
    pnlOrgPalette2->Refresh();
    pnlOrgPalette3->SetBackgroundColour(coreData::cData->palette[tmpPalette[3]]);
    pnlOrgPalette3->Refresh();

    txtSwapPaletteNew->SetValue(lstPalettes->GetItemText(selectedSwapPalette, 1));
}

void hdnesPackEditormainForm::SwapPaletteNewChanged( wxCommandEvent& event ){
    showNewSwapPalette();
    lstPalettes->SetItem(selectedSwapPalette, 1, txtSwapPaletteNew->GetValue());
}

void hdnesPackEditormainForm::SwapNewPaletteBGClicked( wxCommandEvent& event ){
    openColourDialog(COLOUR_CLIENT_NEW_SWAP_BG);
}

void hdnesPackEditormainForm::SwapNewPalette1Clicked( wxCommandEvent& event ){
    openColourDialog(COLOUR_CLIENT_NEW_SWAP_1);
}

void hdnesPackEditormainForm::SwapNewPalette2Clicked( wxCommandEvent& event ){
    openColourDialog(COLOUR_CLIENT_NEW_SWAP_2);
}

void hdnesPackEditormainForm::SwapNewPalette3Clicked( wxCommandEvent& event ){
    openColourDialog(COLOUR_CLIENT_ROM_VIEW_3);
}

void hdnesPackEditormainForm::AddSwapClicked( wxCommandEvent& event ){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;

    paletteSwap p;
    updateSwapData(p);
    ndata->addSwap(p);
    loadSwaps();
    coreData::cData->dataChanged();
}

void hdnesPackEditormainForm::UpdateSwapClicked( wxCommandEvent& event ){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;
    if(selectedSwap >= 0){
        updateSwapData(ndata->swaps[selectedSwap]);
        loadSwaps();
        coreData::cData->dataChanged();
    }
}

void hdnesPackEditormainForm::DeleteSwapClicked( wxCommandEvent& event ){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;
    if(selectedSwap >= 0){
        ndata->swaps.erase (ndata->swaps.begin()+selectedSwap);
        loadSwaps();
        coreData::cData->dataChanged();
    }
}

void hdnesPackEditormainForm::showNewSwapPalette(){
    main::hexToByteArray(txtSwapPaletteNew->GetValue().ToStdString(), (Uint8*)swapNewColours);
    if(swapNewColours[0] < 64){
        btnNewPaletteBG->SetBackgroundColour(coreData::cData->palette[swapNewColours[0]]);
        if(coreData::cData->palette[swapNewColours[0]].Red() + coreData::cData->palette[swapNewColours[0]].Green() + coreData::cData->palette[swapNewColours[0]].Blue() > 256){
            btnNewPaletteBG->SetForegroundColour(wxColour(0,0,0));
        }
        else{
            btnNewPaletteBG->SetForegroundColour(wxColour(255,255,255));
        }
    }
    else{
        btnNewPaletteBG->SetBackgroundColour(wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ));
        btnNewPaletteBG->SetForegroundColour(wxColour(0,0,0));
    }

    btnNewPalette1->SetBackgroundColour(coreData::cData->palette[swapNewColours[1]]);
    if(coreData::cData->palette[swapNewColours[1]].Red() + coreData::cData->palette[swapNewColours[1]].Green() + coreData::cData->palette[swapNewColours[1]].Blue() > 256){
        btnNewPalette1->SetForegroundColour(wxColour(0,0,0));
    }
    else{
        btnNewPalette1->SetForegroundColour(wxColour(255,255,255));
    }
    btnNewPalette2->SetBackgroundColour(coreData::cData->palette[swapNewColours[2]]);
    if(coreData::cData->palette[swapNewColours[2]].Red() + coreData::cData->palette[swapNewColours[2]].Green() + coreData::cData->palette[swapNewColours[2]].Blue() > 256){
        btnNewPalette2->SetForegroundColour(wxColour(0,0,0));
    }
    else{
        btnNewPalette2->SetForegroundColour(wxColour(255,255,255));
    }
    btnNewPalette3->SetBackgroundColour(coreData::cData->palette[swapNewColours[3]]);
    if(coreData::cData->palette[swapNewColours[3]].Red() + coreData::cData->palette[swapNewColours[3]].Green() + coreData::cData->palette[swapNewColours[3]].Blue() > 256){
        btnNewPalette3->SetForegroundColour(wxColour(0,0,0));
    }
    else{
        btnNewPalette3->SetForegroundColour(wxColour(255,255,255));
    }
}

void hdnesPackEditormainForm::updateNewSwapText(){
    stringstream s;
    s.str(std::string());
    s.clear();
    s << main::intToHex(swapNewColours[0]);
    s << main::intToHex(swapNewColours[1]);
    s << main::intToHex(swapNewColours[2]);
    s << main::intToHex(swapNewColours[3]);
    txtSwapPaletteNew->SetValue(wxString(s.str().c_str()));
}

void hdnesPackEditormainForm::updateSwapData(paletteSwap& s){
    s.name = txtSwapName->GetValue().ToStdString();
    s.brightness = (float)spnSwapNewBrightness->GetValue() / 100.0;
    s.hueRotation = (float)spnSwapRotateHue->GetValue() / 360.0;
    s.saturation = (float)spnSwapNewSaturation->GetValue() / 100.0;

    s.orgPalettes.clear();
    s.newPalettes.clear();

    Uint8 tmpPalette[4];
    array<Uint8, 4> arr;
    for(int i = 0; i < lstPalettes->GetItemCount(); ++i){
        main::hexToByteArray(lstPalettes->GetItemText(i).ToStdString(), (Uint8*)tmpPalette);
        for(int j = 0; j < 4; ++j){
            arr[j] = tmpPalette[j];
        }
        s.orgPalettes.push_back(arr);
        main::hexToByteArray(lstPalettes->GetItemText(i, 1).ToStdString(), (Uint8*)tmpPalette);
        for(int j = 0; j < 4; ++j){
            arr[j] = tmpPalette[j];
        }
        s.newPalettes.push_back(arr);
    }
}

void hdnesPackEditormainForm::ConditionSelected( wxListEvent& event ){
    selectedCondition = event.GetIndex();
    showCondition();
}

void hdnesPackEditormainForm::showCondition(){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;
    if(selectedCondition < 0) return;
    condition c = ndata->conditions[selectedCondition];
    chkConditionNegative->SetValue(ndata->conSigns[selectedCondition]);
    txtConditionName->SetValue(wxString(c.name.c_str()));
    cboConditionType->SetSelection(cboConditionType->FindString(wxString(c.conditionType.c_str())));
    showConditionPanel();

    if(c.conditionType == "tileNearby" || c.conditionType == "spriteNearby" || c.conditionType == "tileAtPosition" || c.conditionType == "spriteAtPosition"){
        txtConditionX->SetValue(main::intToStr(c.objCoordX));
        txtConditionY->SetValue(main::intToStr(c.objCoordY));

        txtConditionTile->SetValue(c.id.writeID());
        txtConditionPalette->SetValue(c.id.writePalette());
    }
    else if(c.conditionType == "memoryCheck" || c.conditionType == "ppuMemoryCheck"){
        txtConditionAddress1->SetValue(main::intToHex(c.address));
        cboConditionOp->SetSelection(cboConditionOp->FindString(wxString(c.op.c_str())));
        txtConditionAddress2->SetValue(main::intToHex(c.value));
    }
    else if(c.conditionType == "memoryCheckConstant" || c.conditionType == "ppuMemoryCheckConstant"){
        txtConditionAddress->SetValue(main::intToHex(c.address));
        cboConditionOp2->SetSelection(cboConditionOp2->FindString(wxString(c.op.c_str())));
        txtConditionValue->SetValue(main::intToHex(c.value));
    }
}

void hdnesPackEditormainForm::ConditionTypeSelect( wxCommandEvent& event ){
    showConditionPanel();
}

void hdnesPackEditormainForm::ConditionAdd( wxCommandEvent& event ){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;

    condition c;
    updateConditionData(c);
    ndata->addCondition(c, chkConditionNegative->GetValue());
    loadConditions();
    coreData::cData->dataChanged();
}

void hdnesPackEditormainForm::ConditionUpdate( wxCommandEvent& event ){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;

    if(selectedCondition >= 0){
        updateConditionData(ndata->conditions[selectedCondition]);
        ndata->conSigns[selectedCondition] = chkConditionNegative->GetValue();
        loadConditions();
        coreData::cData->dataChanged();
    }
}

void hdnesPackEditormainForm::ConditionDelete( wxCommandEvent& event ){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;
    if(selectedCondition >= 0){
        ndata->conditions.erase (ndata->conditions.begin()+selectedCondition);
        ndata->conSigns.erase (ndata->conSigns.begin()+selectedCondition);
        loadConditions();
        coreData::cData->dataChanged();
    }
}

void hdnesPackEditormainForm::updateConditionData(condition& c){
    c.conditionType = cboConditionType->GetString(cboConditionType->GetSelection());
    c.name = txtConditionName->GetValue().ToStdString();
    if(c.conditionType == "tileNearby" || c.conditionType == "spriteNearby" || c.conditionType == "tileAtPosition" || c.conditionType == "spriteAtPosition"){
        c.objCoordX = atoi(txtConditionX->GetValue());
        c.objCoordY = atoi(txtConditionY->GetValue());

        if(coreData::cData->isCHRROM){
            c.id.id = atoi(txtConditionTile->GetValue());
        }
        else{
            main::hexToByteArray(txtConditionTile->GetValue().ToStdString(), c.id.rawData);
        }
        main::hexToByteArray(txtConditionPalette->GetValue().ToStdString(), c.id.palette);
    }
    else if(c.conditionType == "memoryCheck" || c.conditionType == "ppuMemoryCheck"){
        c.address = strtol(txtConditionAddress1->GetValue(), NULL, 16);
        c.op = cboConditionOp->GetString(cboConditionOp->GetSelection());
        c.value = strtol(txtConditionAddress2->GetValue(), NULL, 16);
    }
    else if(c.conditionType == "memoryCheckConstant" || c.conditionType == "ppuMemoryCheckConstant"){
        c.address = strtol(txtConditionAddress->GetValue(), NULL, 16);
        c.op = cboConditionOp2->GetString(cboConditionOp2->GetSelection());
        c.value = strtol(txtConditionValue->GetValue(), NULL, 16);
    }
}

void hdnesPackEditormainForm::showConditionPanel(){
    string conType;
    conType = cboConditionType->GetString(cboConditionType->GetSelection());

    pnlConditionType0->Show(false);
    pnlConditionType1->Show(false);
    pnlConditionType2->Show(false);
    pnlConditionType3->Show(false);
    if(conType == "tileNearby" || conType == "spriteNearby" || conType == "tileAtPosition" || conType == "spriteAtPosition"){
        pnlConditionType1->Show(true);
    }
    else if(conType == "memoryCheck" || conType == "ppuMemoryCheck"){
        pnlConditionType2->Show(true);
    }
    else if(conType == "memoryCheckConstant" || conType == "ppuMemoryCheckConstant"){
        pnlConditionType3->Show(true);
    }
    else{
        pnlConditionType0->Show(true);
    }
    pnlConditions->Layout();
}

void hdnesPackEditormainForm::BGImageSelect( wxCommandEvent& event ){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(!ndata) return;

    wxFileDialog openFileDialog(this, _("Choose image file(PNG)"), "", "", "PNG files (*.png)|*.png", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    //check name against existing images
    bool hasExisting = false;
    bool sameFolder;
    string fullPath;
    string imgPath;
    string imgName;
    string dstPath;

    fullPath = openFileDialog.GetPath().ToStdString();
    imgPath = fullPath.substr(0, fullPath.find_last_of("/\\"));
    imgName = fullPath.substr(fullPath.find_last_of("/\\") + 1);
    dstPath = coreData::cData->packPath + "\\" + imgName;

    fstream file;
    file.open(dstPath, ios::in | ios::binary);
	if (file.is_open()){
	    hasExisting = true;
	}
    file.close();

    if(imgPath != coreData::cData->packPath){
        if(hasExisting){
            if (wxMessageBox(_("There is an image of the same name. This will replace that image. Proceed?"), _("Please confirm"),
                    wxICON_QUESTION | wxYES_NO, this) == wxNO )
            return;
        }
        std::cout << fullPath;
        ifstream  src(fullPath, ios::binary);
        ofstream  dst(dstPath, ios::binary);
        dst << src.rdbuf();
        dst.close();
        src.close();
    }
    ndata->fileName = imgName;
    drawBGImage();
    coreData::cData->dataChanged();
}

void hdnesPackEditormainForm::BGImageBrightness( wxSpinEvent& event ){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(ndata){
        ndata->brightness = (float)spnBGBrightness->GetValue() / 100.0;
        dataChanged();
    }
}

void hdnesPackEditormainForm::BGImageHScrollRate( wxSpinEvent& event ){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(ndata){
        ndata->hScrollRate = (float)spnBGHScrollRate->GetValue() / 100.0;
        dataChanged();
    }
}

void hdnesPackEditormainForm::BGImageVScrollRate( wxSpinEvent& event ){
    gameObjNode* ndata = getGameObjsSelectedObjectTreeNode();
    if(ndata){
        ndata->vScrollRate = (float)spnBGVScrollRate->GetValue() / 100.0;
        dataChanged();
    }
}

void hdnesPackEditormainForm::initHDImg(){
    lstHDImg->AppendColumn(wxString("Name"));
    lstHDImg->AppendColumn(wxString("Width"));
    lstHDImg->AppendColumn(wxString("Height"));

    lstHDImgTiles->AppendColumn(wxString("Index"));
    lstHDImgTiles->AppendColumn(wxString("Tile ID"));
    lstHDImgTiles->AppendColumn(wxString("Palette"));

    selectedHDImg = -1;
    hdImgRendering = false;
}

void hdnesPackEditormainForm::showHDImgImage(){
    hdImgScale = min(((float)pnlHDImg->GetSize().x) / ((float)coreData::cData->images[selectedHDImg]->imageData.GetWidth()), ((float)pnlHDImg->GetSize().y) / ((float)coreData::cData->images[selectedHDImg]->imageData.GetHeight()));

    wxImage scaledImg;
    scaledImg = coreData::cData->images[selectedHDImg]->imageData.Scale(coreData::cData->images[selectedHDImg]->imageData.GetWidth() * hdImgScale, coreData::cData->images[selectedHDImg]->imageData.GetHeight() * hdImgScale);

    int j;
    int tileSize;
    wxPoint pt;
    wxPoint pt2;
    wxPoint tileBoxSize;

    tileSize = 8 * coreData::cData->scale * hdImgScale;
    tileBoxSize.x = tileSize - 1;
    tileBoxSize.y = tileSize - 1;
    for(int i = 0; i < lstHDImgTiles->GetItemCount(); ++i){
        if(lstHDImgTiles->GetItemState(i, wxLIST_STATE_SELECTED) == wxLIST_STATE_SELECTED){
            j = atoi(lstHDImgTiles->GetItemText(i, 0));
            //draw outline of selected tiles
            pt.x = coreData::cData->tiles[j]->aniFrames[0].x * hdImgScale;
            pt.y = coreData::cData->tiles[j]->aniFrames[0].y * hdImgScale;
            pt2 = pt;
            ++(pt2.x);
            ++(pt2.y);
            main::drawRect(scaledImg, pt2, tileBoxSize, wxColour(0, 0, 0));
            main::drawRect(scaledImg, pt, tileBoxSize, wxColour(255, 255, 255));
        }
    }

    wxImage displayImg;
    displayImg = wxImage(pnlHDImg->GetSize(), true);
    displayImg.SetRGB(displayImg.GetSize(), 128, 0, 128);
    scaledImg.ConvertAlphaToMask(64);
    displayImg.Paste(scaledImg, (pnlHDImg->GetSize().x - scaledImg.GetWidth()) / 2, (pnlHDImg->GetSize().y - scaledImg.GetHeight()) / 2);
    displayImg.ConvertAlphaToMask(64);
    displayImg.SetMask(false);

    if(hdImgClicked){
        wxPoint p1;
        wxPoint p2;
        p1.x = min(hdImgLDownPos.x, hdImgLCurrPos.x);
        p1.y = min(hdImgLDownPos.y, hdImgLCurrPos.y);
        p2.x = max(hdImgLDownPos.x, hdImgLCurrPos.x);
        p2.y = max(hdImgLDownPos.y, hdImgLCurrPos.y);

        wxPoint rectSize;
        rectSize.x = p2.x - p1.x;
        rectSize.y = p2.y - p1.y;

        wxPoint p3 = p1;
        ++(p3.x);
        ++(p3.y);

        main::drawRect(displayImg, p3, rectSize, wxColour(0, 0, 0));
        main::drawRect(displayImg, p1, rectSize, wxColour(255, 255, 255));
    }

    wxBitmap bmp = wxBitmap(displayImg);
	if(bmp.IsOk()){
		wxClientDC* objDC;
		objDC = new wxClientDC(pnlHDImg);
		objDC->DrawBitmap(bmp, 0, 0);
		delete objDC;
	}
}

void hdnesPackEditormainForm::listOutHDImgImages(){
    long j;
    if(coreData::cData){
        lstHDImg->DeleteAllItems();
        for(int i = 0; i < coreData::cData->images.size(); ++i){
            j = lstHDImg->InsertItem(i, wxString(coreData::cData->images[i]->fileName.c_str()), 0);
            lstHDImg->SetItem(j, 1, wxString(main::intToStr(coreData::cData->images[i]->imageData.GetWidth()).c_str()));
            lstHDImg->SetItem(j, 2, wxString(main::intToStr(coreData::cData->images[i]->imageData.GetHeight()).c_str()));
        }
    }
}

void hdnesPackEditormainForm::HDImgSelected( wxListEvent& event ){
    selectedHDImg = event.GetIndex();
    showHDImgImage();
    listOutHDImgTiles();
}

void hdnesPackEditormainForm::HDImgSizeChanged( wxSizeEvent& event ){
    if(selectedHDImg > -1){
        showHDImgImage();
    }
}

void hdnesPackEditormainForm::listOutHDImgTiles(){
    long j;
    string tmpVal;
    if(coreData::cData){
        lstHDImgTiles->DeleteAllItems();
        for(int i = 0; i < coreData::cData->tiles.size(); ++i){
            if(coreData::cData->tiles[i]->hasReplacement && coreData::cData->tiles[i]->aniFrames[0].img == selectedHDImg){
                if(coreData::cData->isCHRROM){
                    tmpVal = main::intToStr(coreData::cData->tiles[i]->id.id);
                }
                else{
                    tmpVal = "";
                    for(Uint8 k = 0; k < 16; ++k){
                        tmpVal = tmpVal + main::intToHex(coreData::cData->tiles[i]->id.rawData[k]);
                    }
                }

                j = lstHDImgTiles->InsertItem(i, wxString(main::intToStr(i).c_str()), 0);
                lstHDImgTiles->SetItem(j, 1, wxString(tmpVal.c_str()));

                tmpVal = wxString((main::intToHex(coreData::cData->tiles[i]->id.palette[0])
                        + main::intToHex(coreData::cData->tiles[i]->id.palette[1])
                        + main::intToHex(coreData::cData->tiles[i]->id.palette[2])
                        + main::intToHex(coreData::cData->tiles[i]->id.palette[3])).c_str());
                lstHDImgTiles->SetItem(j, 2, wxString(tmpVal.c_str()));
            }
        }
    }
}

void hdnesPackEditormainForm::HDImgTileSelected( wxListEvent& event ){
    if(!hdImgRendering) showHDImgImage();
}

void hdnesPackEditormainForm::HDImgLDown( wxMouseEvent& event ){
    if(selectedHDImg == -1) return;
    hdImgRendering = true;
    if(event.GetModifiers() != wxMOD_CONTROL){
        //clear currently selected
        for(int i = 0; i < lstHDImgTiles->GetItemCount(); ++i){
            lstHDImgTiles->SetItemState(i, 0, wxLIST_STATE_SELECTED);
        }
    }
    hdImgLDownPos = event.GetPosition();
    hdImgLCurrPos = hdImgLDownPos;
    hdImgClicked = true;
    showHDImgImage();
    hdImgRendering = false;
}

void hdnesPackEditormainForm::HDImgLUp( wxMouseEvent& event ){
    if(selectedHDImg != -1){
        if(hdImgClicked){
            hdImgRendering = true;
            wxPoint p = event.GetPosition();
            wxPoint corner1;
            wxPoint corner2;
            corner1.x = min(p.x, hdImgLDownPos.x);
            corner2.x = max(p.x, hdImgLDownPos.x);
            corner1.y = min(p.y, hdImgLDownPos.y);
            corner2.y = max(p.y, hdImgLDownPos.y);
            corner1 = convertHDImgPosition(corner1);
            corner2 = convertHDImgPosition(corner2);

            int j;
            int tileSize;

            tileSize = 8 * coreData::cData->scale;
            for(int i = 0; i < lstHDImgTiles->GetItemCount(); ++i){
                j = atoi(lstHDImgTiles->GetItemText(i, 0));
                if(corner1.x <= coreData::cData->tiles[j]->aniFrames[0].x + tileSize
                   && corner2.x >= coreData::cData->tiles[j]->aniFrames[0].x
                   && corner1.y <= coreData::cData->tiles[j]->aniFrames[0].y + tileSize
                   && corner2.y >= coreData::cData->tiles[j]->aniFrames[0].y){
                    if(lstHDImgTiles->GetItemState(i, wxLIST_STATE_SELECTED) == wxLIST_STATE_SELECTED){
                        lstHDImgTiles->SetItemState(i, 0, wxLIST_STATE_SELECTED);
                    }
                    else{
                        lstHDImgTiles->SetItemState(i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
                    }
                }
            }

            hdImgClicked = false;
            showHDImgImage();
            hdImgRendering = false;
        }
    }
}

wxPoint hdnesPackEditormainForm::convertHDImgPosition(wxPoint pos){
    wxPoint result;
    int pnlWidth = pnlHDImg->GetSize().GetWidth();
    int pnlHeight = pnlHDImg->GetSize().GetHeight();
    result.x = pos.x - ((pnlWidth - (coreData::cData->images[selectedHDImg]->imageData.GetWidth() * hdImgScale)) / 2);
    result.y = pos.y - ((pnlHeight - (coreData::cData->images[selectedHDImg]->imageData.GetHeight() * hdImgScale)) / 2);
    //remove scale
    result.x = result.x / hdImgScale;
    result.y = result.y / hdImgScale;
    return result;
}

void hdnesPackEditormainForm::HDImgMove( wxMouseEvent& event ){
    if(selectedHDImg != -1){
        hdImgLCurrPos = event.GetPosition();
        if(hdImgClicked){
            hdImgLCurrPos = event.GetPosition();
            showHDImgImage();
        }
    }
}

void hdnesPackEditormainForm::HDImgEnter( wxMouseEvent& event ){
    if((selectedHDImg != -1) && !event.LeftIsDown()){
        hdImgClicked = false;
        showHDImgImage();
    }
}

void hdnesPackEditormainForm::HDImgRUp( wxMouseEvent& event ){
    if(selectedHDImg != -1){
        hdImgLCurrPos = event.GetPosition();
        wxPoint p = convertHDImgPosition(hdImgLCurrPos);
        wxMenu menu(wxT(""));

        //check right click on a selected tile
        int j;
        int tileSize;
        bool tileFound = false;
        tileSize = 8 * coreData::cData->scale;
        for(int i = 0; i < lstHDImgTiles->GetItemCount(); ++i){
            j = atoi(lstHDImgTiles->GetItemText(i, 0));
            if(p.x <= coreData::cData->tiles[j]->aniFrames[0].x + tileSize
                && p.x >= coreData::cData->tiles[j]->aniFrames[0].x
                && p.y <= coreData::cData->tiles[j]->aniFrames[0].y + tileSize
                && p.y >= coreData::cData->tiles[j]->aniFrames[0].y){
                if(lstHDImgTiles->GetItemState(i, wxLIST_STATE_SELECTED) == wxLIST_STATE_SELECTED){
                    tileFound = true;
                    rightClickedHDImgID = j;
                    rightClickedHDImgTileX = coreData::cData->tiles[j]->aniFrames[0].x;
                    rightClickedHDImgTileY = coreData::cData->tiles[j]->aniFrames[0].y;
                }
            }
        }
        if(tileFound){
            menu.Append(wxID_ANY, wxT("Copy"));
        }
        menu.Connect( wxEVT_MENU, wxCommandEventHandler(hdnesPackEditormainForm::hdImgMenu), NULL, this );
        pnlHDImg->PopupMenu(&menu, hdImgLCurrPos);
    }
}

void hdnesPackEditormainForm::hdImgMenu( wxCommandEvent& event ){
    string copyContent = "";
    int j;
    for(int i = 0; i < lstHDImgTiles->GetItemCount(); ++i){
        j = atoi(lstHDImgTiles->GetItemText(i, 0));
        if(lstHDImgTiles->GetItemState(i, wxLIST_STATE_SELECTED) == wxLIST_STATE_SELECTED){
            if(copyContent != ""){
                copyContent = copyContent + "\n";
            }
            copyContent = copyContent + lstHDImgTiles->GetItemText(i, 1).ToStdString()
                            + "," + lstHDImgTiles->GetItemText(i, 2).ToStdString()
                            + "," + main::intToStr((coreData::cData->tiles[j]->aniFrames[0].x - rightClickedHDImgTileX) / coreData::cData->scale)
                            + "," + main::intToStr((coreData::cData->tiles[j]->aniFrames[0].y - rightClickedHDImgTileY) / coreData::cData->scale);
        }
    }

    if (wxTheClipboard->Open()){
        wxTheClipboard->SetData( new wxTextDataObject(copyContent.c_str()) );
        wxTheClipboard->Close();
    }
}

void hdnesPackEditormainForm::HDImgAdd( wxCommandEvent& event ){
    wxFileDialog openFileDialog(this, _("Choose image file(PNG)"), "", "", "PNG files (*.png)|*.png", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    //check name against existing images
    bool hasExisting = false;
    int existIndex;
    bool sameFolder;
    string fullPath;
    string imgPath;
    string imgName;

    fullPath = openFileDialog.GetPath().ToStdString();
    imgPath = fullPath.substr(0, fullPath.find_last_of("/\\"));
    imgName = fullPath.substr(fullPath.find_last_of("/\\") + 1);

    if(coreData::cData){
        //check if image name is new
        for(int i = 0; i < coreData::cData->images.size(); ++i){
            if(coreData::cData->images[i]->fileName == imgName){
                hasExisting = true;
                existIndex = i;
            }
        }
        //if image is not already in folder then copy it
        if(imgPath != coreData::cData->packPath){
            if(hasExisting){
                if (wxMessageBox(_("There is an image of the same name. This will replace that image. Proceed?"), _("Please confirm"),
                         wxICON_QUESTION | wxYES_NO, this) == wxNO )
                return;
            }
            ifstream  src(fullPath, ios::binary);
            ofstream  dst(coreData::cData->packPath + "\\" + imgName, ios::binary);
            dst << src.rdbuf();
        }

        if(!hasExisting){
            coreData::cData->addImage(imgName);
            listOutHDImgImages();
        }
        else{
            coreData::cData->images[existIndex]->reloadImg();
        }
        coreData::cData->dataChanged();
    }
}

void hdnesPackEditormainForm::HDImgRemove( wxCommandEvent& event ){
    if(selectedHDImg > -1 && coreData::cData){
        coreData::cData->removeImage(selectedHDImg);
        removeGameObjImage(selectedHDImg);
        coreData::cData->dataChanged();
        listOutHDImgImages();
        lstHDImgTiles->DeleteAllItems();
        selectedHDImg = -1;
    }
}

