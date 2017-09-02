#define SDL_MAIN_HANDLED
#include "common.h"
#include "hdnesPackEditormainForm.h"
#include "main.h"

using namespace std;
IMPLEMENT_APP(main)

hdnesPackEditormainForm* main::mForm;

main::main(void){
    wxInitAllImageHandlers();
}

main::~main(void){
}

bool main::OnInit(){
	mForm = new hdnesPackEditormainForm(NULL);
	mForm->Show(true);
	return true;
}
