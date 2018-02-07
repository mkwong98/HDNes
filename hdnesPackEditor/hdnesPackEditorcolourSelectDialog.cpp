#include "common.h"
#include "hdnesPackEditorcolourSelectDialog.h"
#include "coreData.h"
#include "colourDialogClient.h"
#include "main.h"
#include "hdnesPackEditormainForm.h"
#include <wx/colordlg.h>

hdnesPackEditorcolourSelectDialog::hdnesPackEditorcolourSelectDialog( wxWindow* parent )
:
colourSelectDialog( parent )
{
    colourPanels[0x00] = pnlColour00;
    colourPanels[0x01] = pnlColour01;
    colourPanels[0x02] = pnlColour02;
    colourPanels[0x03] = pnlColour03;
    colourPanels[0x04] = pnlColour04;
    colourPanels[0x05] = pnlColour05;
    colourPanels[0x06] = pnlColour06;
    colourPanels[0x07] = pnlColour07;
    colourPanels[0x08] = pnlColour08;
    colourPanels[0x09] = pnlColour09;
    colourPanels[0x0a] = pnlColour0A;
    colourPanels[0x0b] = pnlColour0B;
    colourPanels[0x0c] = pnlColour0C;
    colourPanels[0x0d] = pnlColour0D;
    colourPanels[0x0e] = pnlColour0E;
    colourPanels[0x0f] = pnlColour0F;

    colourPanels[0x10] = pnlColour10;
    colourPanels[0x11] = pnlColour11;
    colourPanels[0x12] = pnlColour12;
    colourPanels[0x13] = pnlColour13;
    colourPanels[0x14] = pnlColour14;
    colourPanels[0x15] = pnlColour15;
    colourPanels[0x16] = pnlColour16;
    colourPanels[0x17] = pnlColour17;
    colourPanels[0x18] = pnlColour18;
    colourPanels[0x19] = pnlColour19;
    colourPanels[0x1a] = pnlColour1A;
    colourPanels[0x1b] = pnlColour1B;
    colourPanels[0x1c] = pnlColour1C;
    colourPanels[0x1d] = pnlColour1D;
    colourPanels[0x1e] = pnlColour1E;
    colourPanels[0x1f] = pnlColour1F;

    colourPanels[0x20] = pnlColour20;
    colourPanels[0x21] = pnlColour21;
    colourPanels[0x22] = pnlColour22;
    colourPanels[0x23] = pnlColour23;
    colourPanels[0x24] = pnlColour24;
    colourPanels[0x25] = pnlColour25;
    colourPanels[0x26] = pnlColour26;
    colourPanels[0x27] = pnlColour27;
    colourPanels[0x28] = pnlColour28;
    colourPanels[0x29] = pnlColour29;
    colourPanels[0x2a] = pnlColour2A;
    colourPanels[0x2b] = pnlColour2B;
    colourPanels[0x2c] = pnlColour2C;
    colourPanels[0x2d] = pnlColour2D;
    colourPanels[0x2e] = pnlColour2E;
    colourPanels[0x2f] = pnlColour2F;

    colourPanels[0x30] = pnlColour30;
    colourPanels[0x31] = pnlColour31;
    colourPanels[0x32] = pnlColour32;
    colourPanels[0x33] = pnlColour33;
    colourPanels[0x34] = pnlColour34;
    colourPanels[0x35] = pnlColour35;
    colourPanels[0x36] = pnlColour36;
    colourPanels[0x37] = pnlColour37;
    colourPanels[0x38] = pnlColour38;
    colourPanels[0x39] = pnlColour39;
    colourPanels[0x3a] = pnlColour3A;
    colourPanels[0x3b] = pnlColour3B;
    colourPanels[0x3c] = pnlColour3C;
    colourPanels[0x3d] = pnlColour3D;
    colourPanels[0x3e] = pnlColour3E;
    colourPanels[0x3f] = pnlColour3F;
}

void hdnesPackEditorcolourSelectDialog::colourSelectInit( wxInitDialogEvent& event )
{
    for(int i = 0; i < 64; ++i){
        colourPanels[i]->SetBackgroundColour(coreData::cData->palette[i]);
    }
}

void hdnesPackEditorcolourSelectDialog::colourLClick( wxMouseEvent& event ){
    for(int i = 0; i < 64; ++i){
        if(event.GetEventObject() == colourPanels[i]){
            Show(false);
            clientObj->colourSelected(i);
        }
    }
}

void hdnesPackEditorcolourSelectDialog::colourRClick( wxMouseEvent& event ){
    wxColourDialog dialog(this);
    if(dialog.ShowModal() == wxID_OK){
        wxColourData retData = dialog.GetColourData();
        wxColour col = retData.GetColour();
        for(int i = 0; i < 64; ++i){
            if(event.GetEventObject() == colourPanels[i]){
                colourPanels[i]->SetBackgroundColour(col);
                coreData::cData->palette[i] = col;
                coreData::cData->dataChanged();
                colourPanels[i]->Refresh();
            }
        }
    }
}

void hdnesPackEditorcolourSelectDialog::setClientObj(colourDialogClient* obj){
    clientObj = obj;
}
