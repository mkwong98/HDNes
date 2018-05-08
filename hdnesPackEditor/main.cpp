#include "common.h"
#include "hdnesPackEditormainForm.h"
#include "main.h"

using namespace std;
IMPLEMENT_APP(main)

hdnesPackEditormainForm* main::mForm;
string main::exeDir;

string main::trim(string pStr){
    string s = pStr;
    s.erase(s.find_last_not_of(" \t\n\r\f\v") + 1);
    s.erase(0, s.find_first_not_of(" \t\n\r\f\v"));
    return s;
}

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

string main::floatToStr(float value){
    stringstream stream;
    stream << value;
    return stream.str();
}

string main::paletteToStr(vector<array<Uint8, 4>> p){
    stringstream stream;
    for(int i = 0; i < p.size(); ++i){
        stream << main::intToHex(p[i][0]);
        stream << main::intToHex(p[i][1]);
        stream << main::intToHex(p[i][2]);
        stream << main::intToHex(p[i][3]);
        if(i < (p.size() - 1)){
            stream << ",";
        }
    }
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

void main::drawRect(wxImage &img, wxPoint pt, wxPoint rectSize, wxColour c){
    drawLine(img, pt, rectSize.x, c, true);
    drawLine(img, pt, rectSize.y, c, false);

    wxPoint p = pt;
    p.x += rectSize.x;
    drawLine(img, p, rectSize.y, c, false);
    p = pt;
    p.y += rectSize.y;
    drawLine(img, p, rectSize.x, c, true);
}

void main::drawLine(wxImage &img, wxPoint pt, int len, wxColour c, bool hDir){
    wxPoint p = pt;
    for(int i = 0; i < len; ++i){
        if(p.x >= 0 && p.x < img.GetWidth()
        && p.y >= 0 && p.y < img.GetHeight()){
            img.SetRGB(p.x, p.y, c.Red(), c.Green(), c.Blue());
        }
        if(hDir){
            ++(p.x);
        }
        else{
            ++(p.y);
        }
    }
}


main::main(void){
    SDL_SetMainReady();
    SDL_Init(0);

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
    SDL_Quit();
    return wxApp::OnExit();
}
