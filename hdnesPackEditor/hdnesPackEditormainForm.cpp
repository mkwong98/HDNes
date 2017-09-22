#include "hdnesPackEditormainForm.h"
#include "hdnesPackEditornewProjectDialog.h"
#include "hdnesPackEditorcolourSelectDialog.h"
#include "coreData.h"
#include "main.h"
#include "common.h"
#include <wx/wx.h>

hdnesPackEditormainForm::hdnesPackEditormainForm( wxWindow* parent )
:
mainForm( parent )
{
    initROMView();
    initGeneral();

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
            }
        }
        fs.close();
    }
}

void hdnesPackEditormainForm::closeWindow( wxCloseEvent& event ){
	fstream inifile;
	inifile.open(main::exeDir + "\\config.txt", ios::out);

    saveCfgGeneral(inifile);
	saveCfgROMView(inifile);

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
        wxFileDialog dialog(this, wxString("Save As"), lastDir, wxString(string(romName + ".hnp").c_str()), wxString("*.hnp"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
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
    wxFileDialog dialog(this, wxString("Save As"), coreData::cData->projectPath, wxString(string(romName + ".hnp").c_str()), wxString("*.hnp"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if(dialog.ShowModal() == wxID_OK){
        coreData::cData->saveAs(dialog.GetPath().ToStdString());
    }
}

void hdnesPackEditormainForm::MenuFileGen( wxCommandEvent& event ){
// TODO: Implement MenuFileGen
}

void hdnesPackEditormainForm::MenuFileExit( wxCommandEvent& event ){
// TODO: Implement MenuFileExit
}

void hdnesPackEditormainForm::colourSelected(Uint8 selectedColour){
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

void hdnesPackEditormainForm::paintTile(wxImage &img, Uint8* tileData, Uint16 x, Uint16 y, wxColour cBG, wxColour c1, wxColour c2, wxColour c3){
    wxColour useColour[4];
    useColour[0] = cBG;
    useColour[1] = c1;
    useColour[2] = c2;
    useColour[3] = c3;
    Uint8 decodeByte1;
    Uint8 decodeByte2;
    Uint8 decodedVal;
    for(Uint8 dy = 0; dy < 8; ++dy){
        decodeByte1 = tileData[dy];
        decodeByte2 = tileData[dy + 8];
        for(Uint8 dx = 0; dx < 8; ++dx){
            decodedVal = ((decodeByte1 >> dx) & 0x01) | (((decodeByte2 >> dx) << 1) & 0x02);
            img.SetRGB(x + 7 - dx, y + dy, useColour[decodedVal].Red(), useColour[decodedVal].Green(), useColour[decodedVal].Blue());
        }
    }
}

void hdnesPackEditormainForm::drawRect(wxImage &img, wxPoint pt, wxPoint rectSize, wxColour c){
    drawLine(img, pt, rectSize.x, c, true);
    drawLine(img, pt, rectSize.y, c, false);

    wxPoint p = pt;
    p.x += rectSize.x;
    drawLine(img, p, rectSize.y, c, false);
    p = pt;
    p.y += rectSize.y;
    drawLine(img, p, rectSize.x, c, true);
}


void hdnesPackEditormainForm::drawLine(wxImage &img, wxPoint pt, int len, wxColour c, bool hDir){
    wxPoint p = pt;
    for(int i = 0; i < len; ++i){
        if(p.x >= 0 && p.x < img.GetWidth()
        && p.y >= 0 && p.y < img.GetHeight()){
            img.SetRGB(p.x, p.y, c.Red(), c.Green(), c.Blue());
        }
        if(hDir){
            ++(p.x);
        }
        else{
            ++(p.y);
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
    romViewCtrPressed = false;
    romViewPaletteToText();
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
    ostringstream convert;
    string s;

	convert << romViewColours[0];
	s = convert.str();
	inifile << "<romViewColour0>" + s + "\n";
	convert.str("");
	convert.clear();
	convert << romViewColours[1];
	s = convert.str();
	inifile << "<romViewColour1>" + s + "\n";
	convert.str("");
	convert.clear();
	convert << romViewColours[2];
	s = convert.str();
	inifile << "<romViewColour2>" + s + "\n";
	convert.str("");
	convert.clear();
	convert << romViewColours[3];
	s = convert.str();
	inifile << "<romViewColour3>" + s + "\n";
}

void hdnesPackEditormainForm::zoomRomChanged( wxSpinEvent& event ){
    refreshROMView();
}

void hdnesPackEditormainForm::romBGColour( wxCommandEvent& event ){
    openColourDialog(COLOUR_CLIENT_ROM_VIEW_BG);
}

void hdnesPackEditormainForm::romViewPaletteHexChanged( wxCommandEvent& event ){
    string v = txtRomViewPalette->GetValue().ToStdString();
    if(v.length() == 8){
         romViewColours[0] = strtol(v.substr(0, 2).c_str(), NULL, 16);
         romViewColours[1] = strtol(v.substr(2, 2).c_str(), NULL, 16);
         romViewColours[2] = strtol(v.substr(4, 2).c_str(), NULL, 16);
         romViewColours[3] = strtol(v.substr(6, 2).c_str(), NULL, 16);
    }
    refreshROMView();
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
}

void hdnesPackEditormainForm::refreshROMView(){
    btnRomViewBGColour->SetBackgroundColour(coreData::cData->palette[romViewColours[0]]);
    if(coreData::cData->palette[romViewColours[0]].Red() + coreData::cData->palette[romViewColours[0]].Green() + coreData::cData->palette[romViewColours[0]].Blue() > 128){
        btnRomViewBGColour->SetForegroundColour(wxColour(0,0,0));
    }
    else{
        btnRomViewBGColour->SetForegroundColour(wxColour(255,255,255));
    }

    btnRomViewColour1->SetBackgroundColour(coreData::cData->palette[romViewColours[1]]);
    if(coreData::cData->palette[romViewColours[1]].Red() + coreData::cData->palette[romViewColours[1]].Green() + coreData::cData->palette[romViewColours[1]].Blue() > 128){
        btnRomViewColour1->SetForegroundColour(wxColour(0,0,0));
    }
    else{
        btnRomViewColour1->SetForegroundColour(wxColour(255,255,255));
    }

    btnRomViewColour2->SetBackgroundColour(coreData::cData->palette[romViewColours[2]]);
    if(coreData::cData->palette[romViewColours[2]].Red() + coreData::cData->palette[romViewColours[2]].Green() + coreData::cData->palette[romViewColours[2]].Blue() > 128){
        btnRomViewColour2->SetForegroundColour(wxColour(0,0,0));
    }
    else{
        btnRomViewColour2->SetForegroundColour(wxColour(255,255,255));
    }

    btnRomViewColour3->SetBackgroundColour(coreData::cData->palette[romViewColours[3]]);
    if(coreData::cData->palette[romViewColours[3]].Red() + coreData::cData->palette[romViewColours[3]].Green() + coreData::cData->palette[romViewColours[3]].Blue() > 128){
        btnRomViewColour3->SetForegroundColour(wxColour(0,0,0));
    }
    else{
        btnRomViewColour3->SetForegroundColour(wxColour(255,255,255));
    }

    tileCnt = coreData::cData->romSize / 16;
    Uint32 tileSize = 8 * zoomRom->GetValue();
    //display 32 tiles across
    romViewDisplayWidth = 16;
    romViewDisplayHeight = ((tileCnt / 16) + 1);

    romHScroll->SetRange(romViewDisplayWidth);
    romVScroll->SetRange(romViewDisplayHeight);
    romHScroll->SetThumbSize(pnlRom->GetSize().GetWidth() / tileSize);
    romVScroll->SetThumbSize(pnlRom->GetSize().GetHeight() / tileSize);

    drawROMView();
}

void hdnesPackEditormainForm::drawROMView(){
    Uint16 visibleCols = min(romViewDisplayWidth, romHScroll->GetThumbSize()) + 1;
    Uint16 visibleRows = min(romViewDisplayHeight, romVScroll->GetThumbSize()) + 1;
    romViewImage = wxImage(visibleCols * 8, visibleRows * 8, true);

    Uint32 memAddress;
    Uint16 drawX;
    Uint16 drawY;
    for(Uint16 j = 0; j < visibleRows; ++j){
        for(Uint16 i = 0; i < visibleCols; ++i){
            if(romHScroll->GetThumbPosition() + i < romViewDisplayWidth && romVScroll->GetThumbPosition() + j < romViewDisplayHeight){
                memAddress = ((romVScroll->GetThumbPosition() + j) * 16 + romHScroll->GetThumbPosition() + i) * 16;
                if(memAddress < coreData::cData->romSize){
                    drawX = i * 8;
                    drawY = j * 8;
                    paintTile(romViewImage, coreData::cData->romData + memAddress, drawX, drawY,
                              coreData::cData->palette[romViewColours[0]],
                              coreData::cData->palette[romViewColours[1]],
                              coreData::cData->palette[romViewColours[2]],
                              coreData::cData->palette[romViewColours[3]]);
                }
            }
        }
    }
    showROMView();
}

void hdnesPackEditormainForm::showROMView(){
    wxImage baseImg = wxImage(pnlRom->GetSize().x, pnlRom->GetSize().y);
    wxImage scaledImg = romViewImage.Scale(romViewImage.GetWidth() * zoomRom->GetValue(), romViewImage.GetHeight() * zoomRom->GetValue());
    baseImg.Paste(scaledImg, 0, 0);
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

        drawRect(baseImg, p3, rectSize, wxColour(0, 0, 0));
        drawRect(baseImg, p1, rectSize, wxColour(255, 255, 255));
    }

    wxBitmap bmp = wxBitmap(baseImg);
	if(bmp.IsOk()){
		pnlRom->ClearBackground();
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
        if(event.GetModifiers() != wxMOD_ALT){
            //clear currently selected
            romViewSelectedTiles.clear();
            romViewCtrPressed = false;
        }
        else{
            romViewCtrPressed = true;
        }
        romViewLDownPos = event.GetPosition();
        romViewLCurrPos = romViewLDownPos;
        romViewClicked = true;
        showROMView();
    }
}

void hdnesPackEditormainForm::romViewLUp( wxMouseEvent& event ){
    //romViewLDownPos.x = romHScroll->GetThumbPosition() + (p.x / (8 * zoomRom->GetValue()));
    //romViewLDownPos.y = romVScroll->GetThumbPosition() + (p.y / (8 * zoomRom->GetValue()));
    romViewClicked = false;
}

void hdnesPackEditormainForm::romViewRUp( wxMouseEvent& event ){
}

void hdnesPackEditormainForm::romViewMove( wxMouseEvent& event ){
    if(coreData::cData){
        if(romViewClicked){
            romViewLCurrPos = event.GetPosition();
            showROMView();
        }
    }
}

void hdnesPackEditormainForm::romViewLeave( wxMouseEvent& event ){
    if(coreData::cData){
        romViewClicked = false;
        romViewCtrPressed = false;
        showROMView();
    }
}
