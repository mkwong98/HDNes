#include "condition.h"

condition::condition()
{
    //ctor
}

condition::~condition()
{
    //dtor
}

bool condition::compareEqual(condition c){
    if(conditionType != c.conditionType) return false;
    if(!id.compareEqual(c.id)) return false;
    if(objCoordX != c.objCoordX) return false;
    if(objCoordY != c.objCoordY) return false;
    if(checkHFlip != c.checkHFlip) return false;
    if(checkHFlip && (hFlip != c.hFlip)) return false;
    if(checkVFlip != c.checkVFlip) return false;
    if(checkVFlip && (vFlip != c.vFlip)) return false;
    if(checkLayer != c.checkLayer) return false;
    if(checkLayer && (layer != c.layer)) return false;
    return true;
}

void condition::load(fstream& file){
}

void condition::save(fstream& file){
}

