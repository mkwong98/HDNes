#include "tileReference.h"
#include "coreData.h"
#include "main.h"

tileReference::tileReference()
{
    //ctor
}

tileReference::~tileReference()
{
    //dtor
}

bool tileReference::compareEqual(tileReference t){
    for(int i = 0; i < 4; ++i){
        if(palette[i] != t.palette[i]) return false;
    }
    if(coreData::cData->isCHRROM){
        if(id != t.id) return false;
    }
    else{
        for(int i = 0; i < 16; ++i){
            if(rawData[i] != t.rawData[i]) return false;
        }
    }
    return true;
}

void tileReference::load(fstream& file){
    string line;
    string lineHdr;
    string lineTail;

    getline(file, line);
    while(line != "<endTileReference>"){
        size_t found = line.find_first_of(">");
        if(found!=string::npos){
            lineHdr = line.substr(0, found + 1);
            lineTail = line.substr(found + 1);

            if(lineHdr == "<id>"){
                id = atoi(lineTail.c_str());
            }
            else if(lineHdr == "<rawData>"){
                main::hexToByteArray(lineTail, (Uint8*)rawData);
            }
            else if(lineHdr == "<palette>"){
                main::hexToByteArray(lineTail, (Uint8*)palette);
            }
        }
        getline(file, line);
    }
}

void tileReference::save(fstream& file){
    file << "<tileReference>\n";
    if(coreData::cData->isCHRROM){
        file << "<id>" << id << "\n";
    }
    else{
        file << "<rawData>";
        for(int i = 0; i < 16; ++i){
            file << main::intToHex(rawData[i]);
        }
        file << "\n";
    }
    file << "<palette>";
    for(int i = 0; i < 4; ++i){
        file << main::intToHex(palette[i]);
    }
    file << "\n";
    file << "<endTileReference>\n";
}
