#include "paletteSwap.h"
#include "main.h"

paletteSwap::paletteSwap()
{
    brightness = 1.0;
    hueRotation = 0.0;
    saturation = 1.0;
}

paletteSwap::~paletteSwap()
{
    //dtor
}

void paletteSwap::load(fstream& file){
    string line;
    string lineHdr;
    string lineTail;
    vector<string> tailStrs;
    Uint8 palette[4];
    array<Uint8, 4> paletteA;

    orgPalettes.clear();
    newPalettes.clear();
    getline(file, line);
    while(line != "<endPaletteSwap>"){
        size_t found = line.find_first_of(">");
        if(found!=string::npos){
            lineHdr = line.substr(0, found + 1);
            lineTail = line.substr(found + 1);
            main::split(lineTail, ',', tailStrs);

            if(lineHdr == "<name>"){
                name = lineTail;
            }
            else if(lineHdr == "<change>"){
                brightness = atof(tailStrs[0].c_str());
                hueRotation = atof(tailStrs[1].c_str());
                saturation = atof(tailStrs[2].c_str());
            }
            else if(lineHdr == "<orgPalettes>"){
                for(int i = 0; i < tailStrs.size(); ++i){
                     main::hexToByteArray(tailStrs[i], palette);
                     paletteA[0] = palette[0];
                     paletteA[1] = palette[1];
                     paletteA[2] = palette[2];
                     paletteA[3] = palette[3];
                     orgPalettes.push_back(paletteA);
                }
            }
            else if(lineHdr == "<newPalettes>"){
                for(int i = 0; i < tailStrs.size(); ++i){
                     main::hexToByteArray(tailStrs[i], palette);
                     paletteA[0] = palette[0];
                     paletteA[1] = palette[1];
                     paletteA[2] = palette[2];
                     paletteA[3] = palette[3];
                     newPalettes.push_back(paletteA);
                }
            }
        }
        getline(file, line);
    }
}

void paletteSwap::save(fstream& file){
    file << "<paletteSwap>\n";
    file << "<name>" << name << "\n";
    file << "<orgPalettes>" << main::paletteToStr(orgPalettes) << "\n";
    file << "<newPalettes>" << main::paletteToStr(newPalettes) << "\n";
    file << "<change>" << brightness << "," << hueRotation << "," << saturation << "\n";
    file << "<endPaletteSwap>\n";
}

paletteSwap paletteSwap::clone(){
    paletteSwap p = paletteSwap();
    p.brightness = brightness;
    p.hueRotation = hueRotation;
    p.name = name;
    for(int i = 0; i < newPalettes.size(); i++){
        p.newPalettes.push_back(newPalettes[i]);
    }
    for(int i = 0; i < orgPalettes.size(); i++){
        p.orgPalettes.push_back(orgPalettes[i]);
    }
    p.saturation = saturation;
    return p;
}
