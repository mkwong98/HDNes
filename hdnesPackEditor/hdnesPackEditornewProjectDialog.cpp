#include <wx/wx.h>

#include "hdnesPackEditornewProjectDialog.h"
#include "hdnesPackEditormainForm.h"
#include "main.h"
#include "coreData.h"

hdnesPackEditornewProjectDialog::hdnesPackEditornewProjectDialog( wxWindow* parent )
:
newProjectDialog( parent )
{

}

void hdnesPackEditornewProjectDialog::fileSelected( wxCommandEvent& event )
{
    if(filePickRom->GetPath().empty()){
        wxMessageBox( wxT("Please select the location of the ROM file") );
    }
    else if(dirPickPack->GetPath().empty()){
        wxMessageBox( wxT("Please select the location of the HD pack folder") );
    }
    else{
        coreData::cData->romPath = filePickRom->GetPath().ToStdString();
        coreData::cData->loadRom();
        coreData::cData->packPath = dirPickPack->GetPath().ToStdString();
        coreData::cData->loadPackData();
        main::mForm->refreshCoreDataDisplay();
        Show(false);
    }
}
