#include "hdnesPackEditormainForm.h"
#include "hdnesPackEditornewProjectDialog.h"
#include "coreData.h"

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









