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

vector<string> main::split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    elems.clear();
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

void main::hexToByteArray(const string &s, UINT8* ar){
    for(int i = 0; i < s.length() / 2; ++i){
        ar[i] = strtol(s.substr(i * 2, 2).c_str(), NULL, 16);
    }
}

main::main(void){
    SDL_SetMainReady();
    SDL_Init(0);
    IMG_Init(IMG_INIT_PNG);

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

int main::OnExit(){
    IMG_Quit();
    SDL_Quit();
    return wxApp::OnExit();
}
