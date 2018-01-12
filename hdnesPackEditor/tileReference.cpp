#include "tileReference.h"
#include "coreData.h";

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
