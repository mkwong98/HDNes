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
    if(coreData::cData){
        hdnesPackEditorcolourSelectDialog* fp = new hdnesPackEditorcolourSelectDialog(this);
        fp->setSelectedCell(romViewColours[0]);
        fp->Show(true);
    }
}

void hdnesPackEditormainForm::romColour1( wxCommandEvent& event ){
    drawROMView();
}

void hdnesPackEditormainForm::romColour2( wxCommandEvent& event ){
    drawROMView();
}

void hdnesPackEditormainForm::romColour3( wxCommandEvent& event ){
    drawROMView();
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

}



