#include "common.h"
#include "hdnesPackEditormainForm.h"
#include "main.h"

using namespace std;
IMPLEMENT_APP(main)

hdnesPackEditormainForm* main::mForm;
string main::exeDir;

string main::intToHex(int value){
    stringstream stream;
    stream << std::setfill('0') << std::setw(2);
    stream << std::hex << value;
    return stream.str();
}

string main::intToStr(int value){
    stringstream stream;
    stream << value;
    return stream.str();
}

main::main(void){
    wxInitAllImageHandlers();

	CHAR szPath[MAX_PATH];

    GetModuleFileNameA( NULL, szPath, MAX_PATH );
	exeDir = string(szPath);
	exeDir = exeDir.substr(0, exeDir.find_last_of("\\/"));
}

main::~main(void){
}

bool main::OnInit(){
	mForm = new hdnesPackEditormainForm(NULL);
	mForm->Show(true);
	return true;
}
