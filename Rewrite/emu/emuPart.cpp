#include "emuPart.h"

using namespace std;

emuPart::emuPart()
{
    //ctor
}

emuPart::~emuPart()
{
    //dtor
}

void emuPart::saveConfig(fstream* fs){
    (*fs) << "<" << this->partName().c_str() << ">\n";
    this->saveConfigLines(fs);
    (*fs) << "</" << this->partName().c_str() << ">\n";
}

void emuPart::saveGameConfig(fstream* fs){
    (*fs) << "<" << this->partName().c_str() << ">\n";
    this->saveGameConfigLines(fs);
    (*fs) << "</" << this->partName().c_str() << ">\n";
}

void emuPart::saveConfigLine(fstream*fs, const string& hdr, const string& value){
    (*fs) << "<" << hdr.c_str() << ">" << value.c_str() << "</" << hdr.c_str() << ">\n";
}

void emuPart::loadConfig(fstream* fs){
    bool endReached = false;
    string line;
    string lineHdr;
    string lineVal;
    string endStr;
    endStr = string("/") + this->partName();
    while(!fs->fail() && !endReached){
        getline((*fs), line);
        lineHdr = getConfigLineHdr(line);
        if(lineHdr.compare(endStr) == 0){
            endReached = true;
        }
        else{
            lineVal = getConfigLineVal(line);
            this->loadConfigVal(lineHdr, lineVal);
        }
    }
}

string emuPart::getConfigLineHdr(string configLine){
    size_t found = configLine.find_first_of('>');
    if(configLine[0] == '<' && found > 0){
        return configLine.substr(1, found - 1);
    }
    else{
        return string();
    }
}

string emuPart::getConfigLineVal(string configLine){
    size_t found = configLine.find_first_of('>');
    size_t found2 = configLine.find_last_of('<');
    return configLine.substr(found + 1, found2 - found - 1);
}

string emuPart::intToString(int a){
    ostringstream temp;
    temp<<a;
    return temp.str();
}

int emuPart::stringToInt(const string& str){
    stringstream ss(str);
    int num;
    ss >> num;
    return num;
}

string emuPart::getFolderPath(const string& path){
    return path.substr(0, path.find_last_of("/\\") + 1);
}

string emuPart::getFileName(const string& path){
    return path.substr(0, path.find_last_of("."));
}

void emuPart::split(const string& str, const string& delim, vector<string>& v){
    v.clear();
    size_t current;
    size_t next = -1;
    do{
        next = str.find_first_not_of(delim, next + 1);
        if (next == string::npos) break;
        next -= 1;
        current = next + 1;
        next = str.find_first_of(delim, current );
        v.push_back(str.substr( current, next - current ) );
    }
    while (next != string::npos);

}
