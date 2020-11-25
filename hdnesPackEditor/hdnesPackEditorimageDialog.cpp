#include "hdnesPackEditorimageDialog.h"
#include "coreData.h"
#include "image.h"

hdnesPackEditorimageDialog::hdnesPackEditorimageDialog( wxWindow* parent )
:
imageDialog( parent )
{
    if(coreData::cData){
        for(int i = 0; i < coreData::cData->images.size(); ++i){
            cboImage->Append(wxString(coreData::cData->images[i]->fileName.c_str()));
        }
    }
}

void hdnesPackEditorimageDialog::imageSelected( wxCommandEvent& event )
{
    if(cboImage->GetSelection() == wxNOT_FOUND) return;

    //calculate image location
    clientObj->imageSelected(cboImage->GetSelection());
    Show(false);
}

void hdnesPackEditorimageDialog::setClient(imageDialogClient* c){
    clientObj = c;
}
