#include "condition.h"
#include "coreData.h"
#include "gameTile.h"
#include "main.h"

condition::condition()
{
    conditionType = "";
}

condition::~condition()
{
    //dtor
}

int condition::getType(){
    if(conditionType == "hmirror" || conditionType == "vmirror" || conditionType == "bgpriority"){
        //built in conditions
        return 0;
    }
    else if(conditionType == "tileNearby" || conditionType == "spriteNearby" || conditionType == "tileAtPosition" || conditionType == "spriteAtPosition" || conditionType == ""){
        return 1;
    }
    else if(conditionType == "memoryCheck" || conditionType == "ppuMemoryCheck" || conditionType == "memoryCheckConstant" || conditionType == "ppuMemoryCheckConstant"){
        return 2;
    }
    return 3;
}

bool condition::compareEqual(condition& c){
    if(conditionType != c.conditionType) return false;
    if(getType() == 0){
        if(name != c.name) return false;
    }
    else if(getType() == 1){
        if(!id.compareEqual(c.id)) return false;
        if(objCoordX != c.objCoordX) return false;
        if(objCoordY != c.objCoordY) return false;
        if(hFlip != c.hFlip) return false;
        if(vFlip != c.vFlip) return false;
    }
    else if(getType() == 2){
        if(address != c.address) return false;
        if(op != c.op) return false;
        if(value != c.value) return false;
    }
    else{
        if(frame1 != c.frame1) return false;
        if(frame2 != c.frame2) return false;
    }
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

            if(lineHdr == "<conditionType>"){
                if(lineTail == ""){
                    conditionType = "";
                }
                else{
                    conditionType = tailStrs[0];
                }
            }
            if(lineHdr == "<name>"){
                if(lineTail == ""){
                    name = "";
                }
                else{
                    name = tailStrs[0];
                }
            }
            else if(lineHdr == "<tileReference>"){
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
            else if(lineHdr == "<compare>"){
                address = atoi(tailStrs[0].c_str());
                op = tailStrs[1];
                value = atoi(tailStrs[2].c_str());
            }
            else if(lineHdr == "<frame>"){
                frame1 = atoi(tailStrs[0].c_str());
                frame2 = atoi(tailStrs[1].c_str());
            }
        }
        getline(file, line);
    }
}

void condition::save(fstream& file){
    file << "<condition>\n";
    file << "<conditionType>" << conditionType << "\n";
    file << "<name>" << name << "\n";
    if(getType() == 1){
        id.save(file);
        file << "<objCoord>" << objCoordX << "," << objCoordY << "\n";
        file << "<flip>" << (hFlip ? "Y" : "N") << "," << (vFlip ? "Y" : "N") << "\n";
    }
    else if(getType() == 2){
        file << "<compare>" << address << "," << op << "," << value << "\n";
    }
    else if(getType() == 3){
        file << "<frame>" << frame1 << "," << frame2 << "\n";
    }
    file << "<endCondition>\n";
}

bool condition::isMatch(gameTile& owner, gameTile& conditionTile){
    if(getType() == 1){
        if(!conditionTile.id.compareEqual(id)) return false;
        if(owner.objCoordX + (hFlip ? -objCoordX : objCoordX) != conditionTile.objCoordX) return false;
        if(owner.objCoordY + (vFlip ? -objCoordY : objCoordY) != conditionTile.objCoordY) return false;
        if(hFlip == (owner.hFlip == conditionTile.hFlip)) return false;
        if(vFlip == (owner.vFlip == conditionTile.vFlip)) return false;
        return true;
    }
    return false;
}

void condition::readLine(string s){
    vector<string> tokens;
    main::split(s, ',', tokens);

    name = tokens[0];
    conditionType = tokens[1];
    if(getType() == 1){
        objCoordX = atoi(tokens[2].c_str());
        objCoordY = atoi(tokens[3].c_str());
        id.readID(tokens[4], coreData::cData->verNo >= 103);
        id.readPalette(tokens[5]);
    }
    else if(getType() == 2){
        address = strtol(tokens[2].c_str(), NULL, 16);
        op = tokens[3];
        value = strtol(tokens[4].c_str(), NULL, 16);
    }
    else if(getType() == 3){
        frame1 = strtol(tokens[2].c_str(), NULL, 16);
        frame2 = strtol(tokens[3].c_str(), NULL, 16);
    }
}

string condition::writeLine(){
    stringstream stream;
    if(getType() == 1){
        if(conditionType == "spriteNearby"){
            id.palette[0] = 0xff;
        }
        stream << objCoordX << "," << objCoordY << "," << id.writeID(coreData::cData->verNo >= 103) << "," << id.writePalette();
    }
    else if(getType() == 2){
        stream << main::intToHex(address) << "," << op << "," << main::intToHex(value);
    }
    else if(getType() == 3){
        stream << main::intToHex(frame1) << "," << main::intToHex(frame2);
    }
    return stream.str();
}

condition condition::clone(){
    condition c = condition();
    c.id = id.clone();
    c.conditionType = conditionType;
    c.name = name;
    c.objCoordX = objCoordX;
    c.objCoordY = objCoordY;
    c.hFlip = hFlip;
    c.vFlip = vFlip;
    c.address = address;
    c.op = op;
    c.value = value;
    c.frame1 = frame1;
    c.frame2 = frame2;
    return c;
}
