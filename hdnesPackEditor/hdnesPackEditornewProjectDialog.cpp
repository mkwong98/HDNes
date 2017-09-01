#include <wx/msgdlg.h>
#include "hdnesPackEditornewProjectDialog.h"
#include "hdnesPackEditormainForm.h"
#include "coreData.h"
#include "main.h"

hdnesPackEditornewProjectDialog::hdnesPackEditornewProjectDialog( wxWindow* parent )
:
newProjectDialog( parent )
{

}

void hdnesPackEditornewProjectDialog::fileSelected( wxCommandEvent& event )
{
    if(dirPickPack->GetPath().empty()){
        wxMessageBox( wxT("Please select the location of the HD pack folder") );
    }
    else{
        if(!filePickRom->GetPath().empty()){
            coreData::cData->romPath = filePickRom->GetPath().ToStdString();
            coreData::cData->loadRom();
        }
        coreData::cData->packPath = dirPickPack->GetPath().ToStdString();
        coreData::cData->loadPackData();
        main::mForm->refreshCoreDataDisplay();
        Show(false);
    }

}
