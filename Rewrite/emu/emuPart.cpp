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

void emuPart::saveConfigLine(fstream*fs, string hdr, string value){
    (*fs) << "<" << hdr.c_str() << ">" << value.c_str() << "</" << hdr.c_str() << ">\n";
}

void emuPart::loadConfig(fstream* fs){
    bool endReached = false;
    string line;
    string lineHdr;
    string lineVal;
    string endStr;
    endStr = string("/") + this->partName();
    while(getline((*fs), line) && !endReached){
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

