#include "common.h"
#include "coreData.h"
#include "gameObjNode.h"
#include "gameTile.h"
#include "main.h"

gameTile::gameTile()
{
    //ctor
    replacement r;
    r.frameID = 0;
    r.hasReplacement = false;
    r.img = 0;
    r.x = 0;
    r.y = 0;
    r.brightness = 0;

    aniFrames.push_back(r);
    markForDelete = false;
}

gameTile::~gameTile()
{
    //dtor
}

void gameTile::readLine(string s){
    vector<string> tokens;
    main::split(s, ',', tokens);

    aniFrames[0].hasReplacement = true;
    aniFrames[0].img = atoi(tokens[0].c_str());

    id.readID(tokens[1], coreData::cData->verNo >= 103);
    id.readPalette(tokens[2]);

    aniFrames[0].x = atoi(tokens[3].c_str());
    aniFrames[0].y = atoi(tokens[4].c_str());
    aniFrames[0].brightness = atof(tokens[5].c_str());
    isDefault = (tokens[6] == "Y");
}

string gameTile::writeLine(){
    return writeFrameLine(0, 1.0);
}

string gameTile::writeFrameLine(int pFrameID, double pSwapBrightness){
    stringstream stream;
    for(int i = 0; i < aniFrames.size(); ++i){
        if(aniFrames[i].frameID == pFrameID){
            stream << aniFrames[i].img << "," << id.writeID(coreData::cData->verNo >= 103) << "," << id.writePalette() << "," << aniFrames[i].x << "," << aniFrames[i].y << "," << (aniFrames[i].brightness * pSwapBrightness) << "," << (isDefault ? "Y" : "N");
        }
    }
    return stream.str();
}

bool gameTile::compareEqual(gameTile& t){
    if(conditions.size() != t.conditions.size()) return false;
    for(int i = 0; i < conditions.size(); ++i){
        if(conSigns[i] != t.conSigns[i] || !conditions[i].compareEqual(t.conditions[i])) return false;
    }
    if(!id.compareEqual(t.id)) return false;
    return true;
}

void gameTile::load(fstream& file){
    string line;
    string lineHdr;
    string lineTail;
    vector<string> tailStrs;
    condition g;

    conditions.clear();
    getline(file, line);
    while(line != "<endGameTile>"){
        size_t found = line.find_first_of(">");
        if(found!=string::npos){
            lineHdr = line.substr(0, found + 1);
            lineTail = line.substr(found + 1);
            main::split(lineTail, ',', tailStrs);

            if(lineHdr == "<tileReference>"){
                id.load(file);
            }
            else if(lineHdr == "<objCoord>"){
                objCoordX = atoi(tailStrs[0].c_str());
                objCoordY = atoi(tailStrs[1].c_str());
            }
            else if(lineHdr == "<flip>"){
                hFlip = (tailStrs[0] == "Y");
                vFlip = (tailStrs[1] == "Y");
            }
            else if(lineHdr == "<replacement>"){
                aniFrames[0].hasReplacement = (tailStrs[0] == "Y");
                isDefault = (tailStrs[1] == "Y");
                aniFrames[0].img = atoi(tailStrs[2].c_str());
                aniFrames[0].x = atoi(tailStrs[3].c_str());
                aniFrames[0].y = atoi(tailStrs[4].c_str());
                aniFrames[0].brightness = atof(tailStrs[5].c_str());
            }
            else if(lineHdr == "<frames>"){
                getline(file, line);
                while(line != "<endFrames>"){
                    main::split(line, ',', tailStrs);
                    replacement r;
                    r.frameID = atoi(tailStrs[0].c_str());
                    r.hasReplacement = (tailStrs[1] == "Y");
                    r.img = atoi(tailStrs[2].c_str());
                    r.x = atoi(tailStrs[3].c_str());
                    r.y = atoi(tailStrs[4].c_str());
                    r.brightness = atof(tailStrs[5].c_str());
                    aniFrames.push_back(r);
                    getline(file, line);
                }
            }
            else if(lineHdr == "<conditions>"){
                getline(file, line);
                while(line != "<endConditions>"){
                    g.load(file);
                    conditions.push_back(g);
                    getline(file, line);
                }
            }
            else if(lineHdr == "<conSigns>"){
                getline(file, line);
                while(line != "<endConSigns>"){
                    conSigns.push_back(line == "Y");
                    getline(file, line);
                }
            }
        }
        getline(file, line);
    }
}

void gameTile::save(fstream& file){
    file << "<gameTile>\n";
    id.save(file);
    file << "<objCoord>" << objCoordX << "," << objCoordY << "\n";
    file << "<flip>" << (hFlip ? "Y" : "N") << "," << (vFlip ? "Y" : "N") << "\n";
    file << "<replacement>" << (aniFrames[0].hasReplacement ? "Y" : "N")
                     << "," << (isDefault ? "Y" : "N")
                     << "," << aniFrames[0].img
                     << "," << aniFrames[0].x
                     << "," << aniFrames[0].y
                     << "," << aniFrames[0].brightness
                     << "\n";
    if(aniFrames.size() > 1){
        file << "<frames>\n";
        for(int i = 1; i < aniFrames.size(); ++i){
            file << aniFrames[i].frameID
                     << "," << (aniFrames[i].hasReplacement ? "Y" : "N")
                     << "," << aniFrames[i].img
                     << "," << aniFrames[i].x
                     << "," << aniFrames[i].y
                     << "," << aniFrames[i].brightness
                     << "\n";
        }
        file << "<endFrames>\n";
    }
    file << "<conditions>\n";
    for(int i = 0; i < conditions.size(); ++i){
        conditions[i].save(file);
    }
    file << "<endConditions>\n";
    file << "<conSigns>\n";
    for(int i = 0; i < conSigns.size(); ++i){
        file << (conSigns[i] ? "Y" : "N") << "\n";
    }
    file << "<endConSigns>\n";
    file << "<endGameTile>\n";
}

gameTile gameTile::clone(){
    gameTile c = gameTile();
    c.id = id.clone();
    c.objCoordX = objCoordX;
    c.objCoordY = objCoordY;
    c.hFlip = hFlip;
    c.vFlip = vFlip;
    for(int i = 0; i < aniFrames.size(); i++){
        c.aniFrames.push_back(aniFrames[i]);
    }
    for(int i = 0; i < conditions.size(); i++){
        c.conditions.push_back(conditions[i].clone());
    }
    for(int i = 0; i < conSigns.size(); i++){
        c.conSigns.push_back(conSigns[i]);
    }
    return c;
}

string gameTile::writeConditionNames(){
    stringstream stream;
    for(int i = 0; i < conditions.size(); ++i){
        if(i > 0) stream << "&";
        if(conSigns[i]) stream << "!";
        stream << conditions[i].name;
    }
    return stream.str();
}
