#include "hdnesPackEditormainForm.h"
#include "hdnesPackEditornewProjectDialog.h"
#include "coreData.h"
#include <wx/wx.h>

hdnesPackEditormainForm::hdnesPackEditormainForm( wxWindow* parent )
:
mainForm( parent )
{

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

void hdnesPackEditormainForm::skipBytesChanged( wxSpinEvent& event )
{
    refreshROMView();
}

void hdnesPackEditormainForm::zoomRomChanged( wxSpinEvent& event )
{
    refreshROMView();
}

void hdnesPackEditormainForm::romBGColour( wxCommandEvent& event )
{
    refreshROMView();
}

void hdnesPackEditormainForm::romColour1( wxCommandEvent& event ){
    refreshROMView();
}

void hdnesPackEditormainForm::romColour2( wxCommandEvent& event ){
    refreshROMView();
}

void hdnesPackEditormainForm::romColour3( wxCommandEvent& event ){
    refreshROMView();
}

void hdnesPackEditormainForm::romViewVScrolled( wxScrollEvent& event ){
    refreshROMView();
}


void hdnesPackEditormainForm::romViewHScrolled( wxScrollEvent& event ){
    refreshROMView();
}

void hdnesPackEditormainForm::refreshCoreDataDisplay(){
    refreshROMView();
}

void hdnesPackEditormainForm::refreshROMView()
{
    Uint16 displayWidth = 32 * 8 * zoomRom->GetValue() / 100;
    Uint16 displayHeight = coreData::((cData->romSize - spnSkipBytes->GetValue()) / (32 * 16)) * 8  * zoomRom->GetValue() / 100;
    Uint16 curH = romHScroll->GetThumbPosition() * romHScroll->GetThumbSize();
    Uint16 curV = romVScroll->GetThumbPosition() * romVScroll->GetThumbSize();

    romHScroll->SetRange(displayWidth);

}



