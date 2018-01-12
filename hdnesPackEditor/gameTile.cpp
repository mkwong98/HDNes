#include "common.h"
#include "coreData.h"
#include "gameTile.h"
#include "main.h"

gameTile::gameTile()
{
    //ctor
    hasReplacement = false;
}

gameTile::~gameTile()
{
    //dtor
}

void gameTile::readLine(string s){
    vector<string> tokens;
    main::split(s, ',', tokens);

    hasReplacement = true;
    img = atoi(tokens[0].c_str());

    if(coreData::cData->isCHRROM){
        id.id = atoi(tokens[1].c_str());
    }
    else{
        main::hexToByteArray(tokens[1], (Uint8*)(id.rawData));
    }
    main::hexToByteArray(tokens[2], (Uint8*)(id.palette));

    x = atoi(tokens[3].c_str());
    y = atoi(tokens[4].c_str());
    brightness = atof(tokens[5].c_str());
    isDefault = (tokens[6] == "Y");
}

bool gameTile::compareEqual(gameTile t){
    if(conditions.size() != t.conditions.size()) return false;
    for(int i = 0; i < conditions.size(); ++i){
        if(!conditions[i].compareEqual(t.conditions[i])) return false;
    }
    if(!id.compareEqual(t.id)) return false;
    return true;
}
