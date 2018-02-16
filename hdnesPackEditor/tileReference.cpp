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

bool tileReference::compareEqual(tileReference& t){
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

void tileReference::readID(string s){
    if(coreData::cData->isCHRROM){
        id = atoi(s.c_str());
    }
    else{
        main::hexToByteArray(s, (Uint8*)(rawData));
    }
}

string tileReference::writeID(){
    if(coreData::cData->isCHRROM){
        return main::intToStr(id);
    }
    else{
        stringstream stream;
        for(int i = 0; i < 16; ++i){
            stream << main::intToHex(rawData[i]);
        }
        return stream.str();
    }
}

void tileReference::readPalette(string s){
    main::hexToByteArray(s, (Uint8*)(palette));
}

string tileReference::writePalette(){
    stringstream stream;
    for(int i = 0; i < 4; ++i){
        stream << main::intToHex(palette[i]);
    }
    return stream.str();
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
                readID(lineTail);
            }
            else if(lineHdr == "<palette>"){
                readPalette(lineTail);
            }
        }
        getline(file, line);
    }
}

void tileReference::save(fstream& file){
    file << "<tileReference>\n";
    file << "<id>" << writeID() << "\n";
    file << "<palette>" << writePalette() << "\n";
    file << "<endTileReference>\n";
}

