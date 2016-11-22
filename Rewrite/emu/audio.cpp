#include "audio.h"
#include "../gameManager.h"

using namespace std;

audio::audio()
{
    volume = 50;
    useHDPack = true;
}

audio::~audio()
{
    //dtor
}

void audio::initGameConfig(){
}

string audio::partName(){
    return string("audio");
}

void audio::saveConfigLines(fstream* fs){
    saveConfigLine(fs, "volume", intToString(volume));
    saveConfigLine(fs, "useHDPack", (useHDPack ? "Y" : "N"));
}

void audio::saveGameConfigLines(fstream* fs){
}

void audio::loadConfigVal(const string& hdr, const string& value){
    if(hdr.compare("volume") == 0){
        volume = stringToInt(value);
    }
    else if(hdr.compare("useHDPack") == 0){
        useHDPack = (value.compare("Y") == 0);
    }
}

void audio::startGame(){

}

void audio::endGame(){

}

void audio::setVolume(int vol){
    volume = vol;
}

void audio::setUseHDPack(bool use){
    useHDPack = use;
}
