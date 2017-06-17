#include "mapper000.h"

mapper000::mapper000()
{
    //ctor
}

mapper000::~mapper000()
{
    //dtor
}

Uint8 mapper000::readPRGData(Uint16 address){
    if(address & 0x8000){
        if(prgPageCount == 1){
            return prgROM[address & 0x3FFF];
        }
        else{
            return prgROM[address & 0x7FFF];
        }
    }
    else{
        return 0;
    }
}

void mapper000::writePRGData(Uint16 address, Uint8 value){
}

Uint8 mapper000::readCHRData(Uint16 address){
}

void mapper000::writeCHRData(Uint16 address, Uint8 value){
}


void mapper000::reset(){
}

void mapper000::saveState(fstream* statefile){
}

void mapper000::loadState(fstream* statefile){
}

void mapper000::init(){
}

void mapper000::init2(){
}
