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
    romViewColours[0] = 13;
    romViewColours[1] = 18;
    romViewColours[2] = 22;
    romViewColours[3] = 26;
    lastDir = "";
    romDir = "";
    packDir = "";
    m_menu3->FindItem(m_menu3->FindItem(wxString("Save Project")))->Enable(false);
    m_menu3->FindItem(m_menu3->FindItem(wxString("Save Project As...")))->Enable(false);
    m_menu3->FindItem(m_menu3->FindItem(wxString("Generate Pack Data")))->Enable(false);

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
                if(lineHdr == "<lastDir>"){
                    lastDir = lineTail;
                }
                else if(lineHdr == "<romDir>" ){
                    romDir = lineTail;
                }
                else if(lineHdr == "<packDir>"){
                    packDir = lineTail;
                }
                else if(lineHdr == "<romViewColour0>" ){
                    romViewColours[0] = atoi(lineTail.c_str());
                }
                else if(lineHdr == "<romViewColour1>" ){
                    romViewColours[1] = atoi(lineTail.c_str());
                }
                else if(lineHdr == "<romViewColour2>" ){
                    romViewColours[2] = atoi(lineTail.c_str());
                }
                else if(lineHdr == "<romViewColour3>" ){
                    romViewColours[3] = atoi(lineTail.c_str());
                }
                else{
                }
            }
        }
        fs.close();
    }
    romViewPaletteToText();
}

void hdnesPackEditormainForm::closeWindow( wxCloseEvent& event ){
	fstream inifile;
    ostringstream convert;
    string s;

	inifile.open(main::exeDir + "\\config.txt", ios::out);
	inifile << "<lastDir>" + lastDir + "\n";
	inifile << "<romDir>" + romDir + "\n";
	inifile << "<packDir>" + packDir + "\n";

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
	inifile.close();

    if ( event.CanVeto() && notSaved )
    {
        if ( wxMessageBox("The file has not been saved... continue closing?",
                          "Please confirm",
                          wxICON_QUESTION | wxYES_NO) != wxYES )
        {
            event.Veto();
            return;
        }
    }

	Show(false);
	Destroy();
}

void hdnesPackEditormainForm::MenuFileNew( wxCommandEvent& event )
{
    hdnesPackEditornewProjectDialog* fp = new hdnesPackEditornewProjectDialog(this);
    fp->Show(true);
}

void hdnesPackEditormainForm::MenuFileOpen( wxCommandEvent& event )
{
    wxFileDialog dialog(this, wxString("Open project"), lastDir, lastDir, wxString("*.hnp"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if(dialog.ShowModal() == wxID_OK){
        if(coreData::cData){
            delete(coreData::cData);
        }
        coreData::cData = new coreData();
        coreData::cData->load(dialog.GetPath().ToStdString());
    }
}

void hdnesPackEditormainForm::MenuFileSave( wxCommandEvent& event )
{
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

void hdnesPackEditormainForm::MenuFileSaveAs( wxCommandEvent& event )
{
    string romName = coreData::cData->projectPath.substr(coreData::cData->projectPath.find_last_of("\\/") + 1);
    romName = romName.substr(0, romName.find_last_of("."));
    wxFileDialog dialog(this, wxString("Save As"), coreData::cData->projectPath, wxString(string(romName + ".hnp").c_str()), wxString("*.hnp"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if(dialog.ShowModal() == wxID_OK){
        coreData::cData->saveAs(dialog.GetPath().ToStdString());
    }
}

void hdnesPackEditormainForm::MenuFileGen( wxCommandEvent& event )
{
// TODO: Implement MenuFileGen
}

void hdnesPackEditormainForm::MenuFileExit( wxCommandEvent& event )
{
// TODO: Implement MenuFileExit
}

void hdnesPackEditormainForm::zoomRomChanged( wxSpinEvent& event )
{
    refreshROMView();
}

void hdnesPackEditormainForm::romBGColour( wxCommandEvent& event )
{
    openColourDialog(COLOUR_CLIENT_ROM_VIEW_BG);
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
    refreshROMView();
}

void hdnesPackEditormainForm::romViewVScrolled( wxScrollEvent& event ){
    drawROMView();
}

void hdnesPackEditormainForm::romViewHScrolled( wxScrollEvent& event ){
    drawROMView();
}

void hdnesPackEditormainForm::refreshCoreDataDisplay(){
    refreshROMView();
}

void hdnesPackEditormainForm::refreshROMView()
{

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

    Uint32 curH = romHScroll->GetThumbPosition() * romHScroll->GetThumbSize();
    Uint32 curV = romVScroll->GetThumbPosition() * romVScroll->GetThumbSize();

    romHScroll->SetRange(romViewDisplayWidth);
    romVScroll->SetRange(romViewDisplayHeight);
    romHScroll->SetThumbSize(pnlRom->GetSize().GetWidth() / tileSize);
    romVScroll->SetThumbSize(pnlRom->GetSize().GetHeight() / tileSize);

    drawROMView();
}

void hdnesPackEditormainForm::drawROMView(){
    Uint16 visibleCols = min(romViewDisplayWidth, romHScroll->GetThumbSize());
    Uint16 visibleRows = min(romViewDisplayHeight, romVScroll->GetThumbSize());
    wxImage img = wxImage(visibleCols * 8, visibleRows * 8, true);

    Uint32 memAddress;
    Uint16 drawX;
    Uint16 drawY;
    for(Uint16 j = 0; j < visibleRows; ++j){
        for(Uint16 i = 0; i < visibleCols; ++i){
            memAddress = ((romVScroll->GetThumbPosition() + j) * 16 + romHScroll->GetThumbPosition() + i) * 16;
            if(memAddress < coreData::cData->romSize){
                drawX = i * 8;
                drawY = j * 8;
                paintTile(img, coreData::cData->romData + memAddress, drawX, drawY,
                          coreData::cData->palette[romViewColours[0]],
                          coreData::cData->palette[romViewColours[1]],
                          coreData::cData->palette[romViewColours[2]],
                          coreData::cData->palette[romViewColours[3]]);
            }
        }
    }
    wxImage scaledImg = img.Scale(visibleCols * 8 * zoomRom->GetValue(), visibleRows * 8 * zoomRom->GetValue());


    wxBitmap bmp = wxBitmap(scaledImg);
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
    wxPoint p = event.GetPosition();
    romViewLDownX = romHScroll->GetThumbPosition() + (p.x / (8 * zoomRom->GetValue()));
    romViewLDownY = romVScroll->GetThumbPosition() + (p.y / (8 * zoomRom->GetValue()));
}

void hdnesPackEditormainForm::romViewLUp( wxMouseEvent& event ){
}

void hdnesPackEditormainForm::romViewRUp( wxMouseEvent& event ){
}

void hdnesPackEditormainForm::romViewMove( wxMouseEvent& event ){

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


