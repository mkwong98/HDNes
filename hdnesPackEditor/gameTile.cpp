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

    id.readID(tokens[1]);
    id.readPalette(tokens[2]);

    x = atoi(tokens[3].c_str());
    y = atoi(tokens[4].c_str());
    brightness = atof(tokens[5].c_str());
    isDefault = (tokens[6] == "Y");
}

string gameTile::writeLine(){
    stringstream stream;
    stream << img << "," << id.writeID() << "," << id.writePalette() << "," << x << "," << y << "," << brightness << "," << (isDefault ? "Y" : "N");
    return stream.str();
}

bool gameTile::compareEqual(gameTile& t){
    if(conditions.size() != t.conditions.size()) return false;
    for(int i = 0; i < conditions.size(); ++i){
        if(!conditions[i].compareEqual(t.conditions[i])) return false;
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
                hasReplacement = (tailStrs[0] == "Y");
                isDefault = (tailStrs[1] == "Y");
                img = atoi(tailStrs[2].c_str());
                x = atoi(tailStrs[3].c_str());
                y = atoi(tailStrs[4].c_str());
                brightness = atof(tailStrs[5].c_str());
            }
            else if(lineHdr == "<conditions>"){
                getline(file, line);
                while(line != "<endConditions>"){
                    g.load(file);
                    conditions.push_back(g);
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
    file << "<replacement>" << (hasReplacement ? "Y" : "N")
                     << "," << (isDefault ? "Y" : "N")
                     << "," << img
                     << "," << x
                     << "," << y
                     << "," << brightness
                     << "\n";
    file << "<conditions>\n";
    for(int i = 0; i < conditions.size(); ++i){
        conditions[i].save(file);
    }
    file << "<endConditions>\n";
    file << "<endGameTile>\n";
}

