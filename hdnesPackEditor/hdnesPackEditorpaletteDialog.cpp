#include "hdnesPackEditorpaletteDialog.h"
#include "coreData.h"
#include "main.h"

hdnesPackEditorpaletteDialog::hdnesPackEditorpaletteDialog( wxWindow* parent )
:
paletteDialog( parent )
{

}

void hdnesPackEditorpaletteDialog::paletteBGColour( wxCommandEvent& event )
{
    if(colours[0] == 0xff) return;

    openColourDialog(0);
}

void hdnesPackEditorpaletteDialog::paletteColour1( wxCommandEvent& event )
{
    openColourDialog(1);
}

void hdnesPackEditorpaletteDialog::paletteColour2( wxCommandEvent& event )
{
    openColourDialog(2);
}

void hdnesPackEditorpaletteDialog::paletteColour3( wxCommandEvent& event )
{
    openColourDialog(3);
}

void hdnesPackEditorpaletteDialog::openColourDialog(Uint8 clientID){
    if(coreData::cData){
        buttonClicked = clientID;
        hdnesPackEditorcolourSelectDialog* fp = new hdnesPackEditorcolourSelectDialog(this);
        fp->setClientObj(this);
        fp->Show(true);
    }
}

void hdnesPackEditorpaletteDialog::paletteHexChanged( wxCommandEvent& event )
{
    string v = txtPaletteHex->GetValue().ToStdString();
    main::hexToByteArray(v, (Uint8*)colours);
    refreshButtonColour();
}

void hdnesPackEditorpaletteDialog::refreshButtonColour(){
    if(colours[0] >= 64) colours[0] = 0xff;
    if(colours[1] >= 64) colours[1] = 0x0f;
    if(colours[2] >= 64) colours[2] = 0x0f;
    if(colours[3] >= 64) colours[3] = 0x0f;

    if(colours[0] == 0xff){
        btnPaletteBGColour->SetBackgroundColour(wxColour(128,128,128));
        btnPaletteBGColour->SetForegroundColour(wxColour(128,128,128));
    }
    else{
        btnPaletteBGColour->SetBackgroundColour(coreData::cData->palette[colours[0]]);
        if(coreData::cData->palette[colours[0]].Red() + coreData::cData->palette[colours[0]].Green() + coreData::cData->palette[colours[0]].Blue() > 256){
            btnPaletteBGColour->SetForegroundColour(wxColour(0,0,0));
        }
        else{
            btnPaletteBGColour->SetForegroundColour(wxColour(255,255,255));
        }
    }

    btnPaletteColour1->SetBackgroundColour(coreData::cData->palette[colours[1]]);
    if(coreData::cData->palette[colours[1]].Red() + coreData::cData->palette[colours[1]].Green() + coreData::cData->palette[colours[1]].Blue() > 256){
        btnPaletteColour1->SetForegroundColour(wxColour(0,0,0));
    }
    else{
        btnPaletteColour1->SetForegroundColour(wxColour(255,255,255));
    }

    btnPaletteColour2->SetBackgroundColour(coreData::cData->palette[colours[2]]);
    if(coreData::cData->palette[colours[2]].Red() + coreData::cData->palette[colours[2]].Green() + coreData::cData->palette[colours[2]].Blue() > 256){
        btnPaletteColour2->SetForegroundColour(wxColour(0,0,0));
    }
    else{
        btnPaletteColour2->SetForegroundColour(wxColour(255,255,255));
    }

    btnPaletteColour3->SetBackgroundColour(coreData::cData->palette[colours[3]]);
    if(coreData::cData->palette[colours[3]].Red() + coreData::cData->palette[colours[3]].Green() + coreData::cData->palette[colours[3]].Blue() > 256){
        btnPaletteColour3->SetForegroundColour(wxColour(0,0,0));
    }
    else{
        btnPaletteColour3->SetForegroundColour(wxColour(255,255,255));
    }
}

void hdnesPackEditorpaletteDialog::paletteSelected( wxCommandEvent& event )
{
    clientObj->paletteSelected(colours);
    Show(false);
}

void hdnesPackEditorpaletteDialog::colourSelected(Uint8 selectedColour){
    colours[buttonClicked] = selectedColour;
    paletteToText();
}

void hdnesPackEditorpaletteDialog::setPalette(array<Uint8, 4> p){

    colours[0] = p[0];
    colours[1] = p[1];
    colours[2] = p[2];
    colours[3] = p[3];
    paletteToText();
}

void hdnesPackEditorpaletteDialog::paletteToText(){
    wxString v;
    v = wxString((main::intToHex(colours[0])
                + main::intToHex(colours[1])
                + main::intToHex(colours[2])
                + main::intToHex(colours[3])).c_str());
    txtPaletteHex->ChangeValue(v);
    refreshButtonColour();
}

void hdnesPackEditorpaletteDialog::setClient(paletteDialogClient* c){
    clientObj = c;
}

