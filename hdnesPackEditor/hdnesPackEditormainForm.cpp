#include "hdnesPackEditormainForm.h"
#include "hdnesPackEditornewProjectDialog.h"
#include "hdnesPackEditorcolourSelectDialog.h"
#include "coreData.h"
#include <wx/wx.h>

hdnesPackEditormainForm::hdnesPackEditormainForm( wxWindow* parent )
:
mainForm( parent )
{
    romViewColours[0] = 13;
    romViewColours[1] = 18;
    romViewColours[2] = 22;
    romViewColours[3] = 26;
}

void hdnesPackEditormainForm::MenuFileNew( wxCommandEvent& event )
{
    if(coreData::cData){
        delete(coreData::cData);
    }
    coreData::cData = new coreData();
    hdnesPackEditornewProjectDialog* fp = new hdnesPackEditornewProjectDialog(this);
    fp->Show(true);
}

void hdnesPackEditormainForm::MenuFileOpen( wxCommandEvent& event )
{
// TODO: Implement MenuFileOpen
}

void hdnesPackEditormainForm::MenuFileSave( wxCommandEvent& event )
{
// TODO: Implement MenuFileSave
}

void hdnesPackEditormainForm::MenuFileSaveAs( wxCommandEvent& event )
{
// TODO: Implement MenuFileSaveAs
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
        refreshROMView();
        break;
    case COLOUR_CLIENT_ROM_VIEW_1:
        romViewColours[1] = selectedColour;
        refreshROMView();
        break;
    case COLOUR_CLIENT_ROM_VIEW_2:
        romViewColours[2] = selectedColour;
        refreshROMView();
        break;
    case COLOUR_CLIENT_ROM_VIEW_3:
        romViewColours[3] = selectedColour;
        refreshROMView();
        break;
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

void hdnesPackEditormainForm::rowViewSizeChanged( wxSizeEvent& event ){
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

    Uint32 tileCnt = coreData::cData->romSize / 16;
    Uint32 tileSize = 8 * zoomRom->GetValue();
    //display 32 tiles across
    Uint32 displayWidth = 32;
    Uint32 displayHeight = ((tileCnt / 32) + 1);

    Uint32 curH = romHScroll->GetThumbPosition() * romHScroll->GetThumbSize();
    Uint32 curV = romVScroll->GetThumbPosition() * romVScroll->GetThumbSize();

    romHScroll->SetRange(displayWidth);
    romVScroll->SetRange(displayHeight);
    romHScroll->SetThumbSize(pnlRom->GetSize().GetWidth() / tileSize);
    romVScroll->SetThumbSize(pnlRom->GetSize().GetHeight() / tileSize);

    drawROMView();
}

void hdnesPackEditormainForm::drawROMView(){
    wxImage img = wxImage(romHScroll->GetThumbSize() * 8, romVScroll->GetThumbSize() * 8, true);

    Uint32 memAddress;
    Uint16 drawX;
    Uint16 drawY;
    for(Uint16 j = 0; j < romVScroll->GetThumbSize(); ++j){
        for(Uint16 i = 0; i < romHScroll->GetThumbSize(); ++i){
            memAddress = ((romVScroll->GetThumbPosition() + j) * 32 + romHScroll->GetThumbPosition() + i) * 16;
            if(memAddress < coreData::cData->romSize){
                drawX = i * 8;
                drawY = j * 8;
                paintTile(img, coreData::cData->romData + memAddress, drawX, drawY, coreData::cData->palette[romViewColours[0]], coreData::cData->palette[romViewColours[1]], coreData::cData->palette[romViewColours[2]], coreData::cData->palette[romViewColours[3]]);
            }
        }
    }

    wxBitmap bmp = wxBitmap(img);
	if(bmp.IsOk()){
		pnlRom->ClearBackground();
		wxClientDC* objDC;
		objDC = new wxClientDC(pnlRom);
		objDC->DrawBitmap(bmp, 0, 0);
		delete objDC;
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
        decodeByte1 = tileData[dy * 2];
        decodeByte2 = tileData[dy * 2 + 1];
        for(Uint8 dx = 0; dx < 8; ++dx){
            decodedVal = ((decodeByte1 >> dx) & 0x01) | (((decodeByte2 >> dx) << 1) & 0x02);
            img.SetRGB(x + dx, y + dy, useColour[decodedVal].Red(), useColour[decodedVal].Green(), useColour[decodedVal].Blue());
        }
    }
}

