#include "common.h"
#include "hdnesPackEditorcolourSelectDialog.h"
#include "coreData.h"

hdnesPackEditorcolourSelectDialog::hdnesPackEditorcolourSelectDialog( wxWindow* parent )
:
colourSelectDialog( parent )
{

}

void hdnesPackEditorcolourSelectDialog::colourSelectInit( wxInitDialogEvent& event )
{
    Uint16 colSize = grdColour->GetSize().GetWidth() / 17;
    Uint16 rowSize = grdColour->GetSize().GetHeight() / 5;

    grdColour->SetRowLabelSize(colSize);
    for(int i = 0; i < 16; ++i){
        stringstream stream;
        stream << std::hex << i;
        string result( stream.str() );
        grdColour->SetColLabelValue(i, wxString(result));
        grdColour->SetColSize(i, colSize);
    }

    grdColour->SetColLabelSize(rowSize);
    for(int j = 0; j < 4; ++j){
        grdColour->SetRowSize(j, rowSize);
    }

    for(int i = 0; i < 16; ++i){
        for(int j = 0; j < 4; ++j){
            grdColour->SetCellBackgroundColour(j, i, coreData::cData->palette[j * 16 + i]);
        }
    }

}

void hdnesPackEditorcolourSelectDialog::setSelectedCell(Uint8 index){
    grdColour->SelectBlock(index >> 4, index & 0x0F, index >> 4, index & 0x0F);
}
