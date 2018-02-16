#include "condition.h"
#include "coreData.h"
#include "gameTile.h"
#include "main.h"

condition::condition()
{
    //ctor
}

condition::~condition()
{
    //dtor
}

bool condition::compareEqual(condition& c){
    if(conditionType != c.conditionType) return false;
    if(!id.compareEqual(c.id)) return false;
    if(objCoordX != c.objCoordX) return false;
    if(objCoordY != c.objCoordY) return false;
    if(hFlip != c.hFlip) return false;
    if(vFlip != c.vFlip) return false;
    return true;
}

void condition::load(fstream& file){
    string line;
    string lineHdr;
    string lineTail;
    vector<string> tailStrs;

    getline(file, line);
    while(line != "<endCondition>"){
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
        }
        getline(file, line);
    }
}

void condition::save(fstream& file){
    file << "<condition>\n";
    id.save(file);
    file << "<objCoord>" << objCoordX << "," << objCoordY << "\n";
    file << "<flip>" << (hFlip ? "Y" : "N") << "," << (vFlip ? "Y" : "N") << "\n";
    file << "<endCondition>\n";
}

bool condition::isMatch(gameTile& owner, gameTile& conditionTile){
    if(!conditionTile.id.compareEqual(id)) return false;
    if(owner.objCoordX + (hFlip ? -objCoordX : objCoordX) != conditionTile.objCoordX) return false;
    if(owner.objCoordY + (vFlip ? -objCoordY : objCoordY) != conditionTile.objCoordY) return false;
    if(hFlip != (owner.hFlip == conditionTile.hFlip)) return false;
    if(vFlip != (owner.vFlip == conditionTile.vFlip)) return false;
    return true;
}

void condition::readLine(string s){
    vector<string> tokens;
    main::split(s, ',', tokens);

    name = tokens[0];
    conditionType = tokens[1];
    objCoordX = atoi(tokens[2].c_str());
    objCoordY = atoi(tokens[3].c_str());
    id.readID(tokens[4]);
    id.readPalette(tokens[5]);
}

string condition::writeLine(){
    stringstream stream;
    stream << name << "," << conditionType << "," << objCoordX << "," << objCoordY << "," << id.writeID() << "," << id.writePalette();
    return stream.str();
}
