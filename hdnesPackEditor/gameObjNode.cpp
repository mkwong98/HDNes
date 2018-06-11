#include "gameObjNode.h"
#include "gameTile.h"
#include "paletteSwap.h"
#include "main.h"
#include "hdnesPackEditormainForm.h"

gameObjNode::gameObjNode()
{
    //ctor
    effectedByMove = false;
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
    objectWidth = 0;
    objectHeight = 0;
    bgColour = 0;
    isSprite = false;
    brightness = 1;
    isDefault = false;
    hScrollRate = 0;
    vScrollRate = 0;
    fileName = "";
}

gameObjNode::~gameObjNode()
{
    //dtor
}

void gameObjNode::addTile(gameTile g){
    tiles.push_back(g);
    addToObjectSize(tiles.size() - 1);
}

void gameObjNode::addSwap(paletteSwap g){
    swaps.push_back(g);
}

void gameObjNode::addCondition(condition c, bool isNegative){
    conditions.push_back(c);
    conSigns.push_back(isNegative);
}

void gameObjNode::addToObjectSize(int gIdx){
    x1 = min(x1, tiles[gIdx].objCoordX);
    x2 = max(x2, tiles[gIdx].objCoordX + 8);
    y1 = min(y1, tiles[gIdx].objCoordY);
    y2 = max(y2, tiles[gIdx].objCoordY + 8);
    objectWidth = x2 - x1;
    objectHeight = y2 - y1;
}

void gameObjNode::clearAllTiles(){
    tiles.clear();
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
    objectWidth = 0;
    objectHeight = 0;
}

void gameObjNode::load(fstream& file, wxTreeItemId newItm){
    string line;
    string lineHdr;
    string lineTail;
    vector<string> tailStrs;
    gameTile g;
    paletteSwap p;
    condition c;

    getline(file, line);
    while(line != "<endGameObject>"){
        size_t found = line.find_first_of(">");
        if(found!=string::npos){
            lineHdr = line.substr(0, found + 1);
            lineTail = line.substr(found + 1);
            main::split(lineTail, ',', tailStrs);

            if(lineHdr == "<type>"){
                nodeType = atoi(lineTail.c_str());
            }
            else if(lineHdr == "<name>"){
                nodeName = lineTail;
            }
            else if(lineHdr == "<fileName>"){
                fileName = lineTail;
            }
            else if(lineHdr == "<bgColour>"){
                bgColour = strtol(lineTail.c_str(), NULL, 16);
            }
            else if(lineHdr == "<isSprite>"){
                isSprite = (lineTail == "Y");
            }
            else if(lineHdr == "<brightness>"){
                brightness = atof(lineTail.c_str());
            }
            else if(lineHdr == "<isDefault>"){
                isDefault = (lineTail == "Y");
            }
            else if(lineHdr == "<childObjects>"){
                main::mForm->loadChildGameObjs(file, newItm);
            }
            else if(lineHdr == "<scrollRate>"){
                hScrollRate = atof(tailStrs[0].c_str());
                vScrollRate = atof(tailStrs[1].c_str());
            }
            else if(lineHdr == "<tiles>"){
                getline(file, line);
                while(line != "<endTiles>"){
                    g = gameTile();
                    g.load(file);
                    addTile(g);
                    getline(file, line);
                }
                updatePalettes();
            }
            else if(lineHdr == "<swaps>"){
                getline(file, line);
                while(line != "<endSwaps>"){
                    p = paletteSwap();
                    p.load(file);
                    addSwap(p);
                    getline(file, line);
                }
            }
            else if(lineHdr == "<conditions>"){
                getline(file, line);
                while(line != "<endConditions>"){
                    c = condition();
                    c.load(file);
                    conditions.push_back(c);
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

void gameObjNode::save(fstream& file, wxTreeItemId newItm){
    file << "<gameObject>\n";
    file << "<type>" << (int)nodeType << "\n";

    if(nodeType != GAME_OBJ_NODE_TYPE_ROOT){
        file << "<name>" << nodeName << "\n";
    }
    if(nodeType == GAME_OBJ_NODE_TYPE_OBJECT || nodeType == GAME_OBJ_NODE_TYPE_BGIMAGE){
        file << "<brightness>" << brightness << "\n";
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

        if(nodeType == GAME_OBJ_NODE_TYPE_OBJECT){
            file << "<bgColour>" << main::intToHex(bgColour) << "\n";
            file << "<isSprite>" << (isSprite ? "Y" : "N") << "\n";
            file << "<isDefault>" << (isDefault ? "Y" : "N") << "\n";

            file << "<tiles>\n";
            for(int i = 0; i < tiles.size(); ++i){
                tiles[i].save(file);
            }
            file << "<endTiles>\n";

            file << "<swaps>\n";
            for(int i = 0; i < swaps.size(); ++i){
                swaps[i].save(file);
            }
            file << "<endSwaps>\n";
        }
        else if(nodeType == GAME_OBJ_NODE_TYPE_BGIMAGE){
            file << "<fileName>" << fileName << "\n";
            file << "<scrollRate>" << hScrollRate << "," << vScrollRate << "\n";
        }
    }
    else{
        file << "<childObjects>\n";
        main::mForm->saveChildGameObjs(file, newItm);
        file << "<endChildObjects>\n";
    }
    file << "<endGameObject>\n";
}

void gameObjNode::updatePalettes(){
    array<Uint8, 4> p;
    bool paletteFound;
    palettes.clear();
    for(int i = 0; i < tiles.size(); ++i){
        paletteFound = false;
        for(int j = 0; j < palettes.size(); ++j){
            if(palettes[j][0] == tiles[i].id.palette[0] && palettes[j][1] == tiles[i].id.palette[1] && palettes[j][2] == tiles[i].id.palette[2] && palettes[j][3] == tiles[i].id.palette[3]){
                paletteFound = true;
            }
        }
        if(!paletteFound){
            p[0] = tiles[i].id.palette[0];
            p[1] = tiles[i].id.palette[1];
            p[2] = tiles[i].id.palette[2];
            p[3] = tiles[i].id.palette[3];
            palettes.push_back(p);
        }
    }
}

string gameObjNode::writeConditionNames(){
    stringstream stream;
    for(int i = 0; i < conditions.size(); ++i){
        if(i > 0) stream << "&";
        if(conSigns[i]) stream << "!";
        stream << nodeName << "_" << conditions[i].name;
    }
    return stream.str();
}

string gameObjNode::writeLine(){
    stringstream stream;
    stream << fileName << "," << brightness << "," << hScrollRate << "," << vScrollRate;
    return stream.str();
}


