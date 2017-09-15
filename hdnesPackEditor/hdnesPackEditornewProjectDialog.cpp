#include <wx/wx.h>

#include "hdnesPackEditornewProjectDialog.h"
#include "hdnesPackEditormainForm.h"
#include "main.h"
#include "coreData.h"

hdnesPackEditornewProjectDialog::hdnesPackEditornewProjectDialog( wxWindow* parent )
:
newProjectDialog( parent )
{
    filePickRom->SetPath(wxString(main::mForm->romDir));
    dirPickPack->SetPath(wxString(main::mForm->packDir));
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
        main::mForm->romDir = coreData::cData->romPath;
        main::mForm->packDir = coreData::cData->packPath;
        Show(false);
    }
}
