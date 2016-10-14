#include "gameFile.h"

using namespace std;

gameFile::gameFile(){
    romPath = "";
    rotateState = true;
    overwriteBat = true;
    initGameConfig();
}

gameFile::~gameFile(){
    //dtor
}

void gameFile::initGameConfig(){
    currentStateSlot = 0;
    lastSavedSlot = 0;
}

string gameFile::partName(){
    return string("gameFile");
}

void gameFile::saveConfigLines(fstream* fs){
    saveConfigLine(fs, string("romPath"), romPath);
    saveConfigLine(fs, string("rotateState"), (rotateState ? string("Y") : string("N")));
    saveConfigLine(fs, string("overwriteBat"), (overwriteBat ? string("Y") : string("N")));
}

void gameFile::saveGameConfigLines(fstream* fs){
    saveConfigLine(fs, string("currentStateSlot"), intToString(currentStateSlot));
    saveConfigLine(fs, string("lastSavedSlot"), intToString(currentStateSlot));
}

void gameFile::loadConfigVal(const string& hdr, const string& value){
    if(hdr.compare("romPath") == 0){
        romPath = value;
    }
    else if(hdr.compare("rotateState") == 0){
        rotateState = (value.compare("Y") == 0);
    }
    else if(hdr.compare("overwriteBat") == 0){
        overwriteBat = (value.compare("Y") == 0);
    }
    else if(hdr.compare("currentStateSlot") == 0){
        currentStateSlot = stringToInt(value);
    }
    else if(hdr.compare("lastSavedSlot") == 0){
        lastSavedSlot = stringToInt(value);
    }
}

void gameFile::startGame(){

}

void gameFile::endGame(){

}
