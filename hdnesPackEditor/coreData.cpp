#include "common.h"
#include "coreData.h"
#include "image.h"
#include "main.h"
#include "hdnesPackEditormainForm.h"

coreData* coreData::cData;

coreData::coreData()
{
    projectPath = "";
    romPath = "";
    packPath = "";
    romSize = 0;
    isCHRROM = true;
    notSaved = true;
}

coreData::~coreData()
{
    if(romSize > 0) free(romData);
}

void coreData::initPath(string rPath, string pPath){
    romPath = rPath;
    packPath = pPath;
    loadRom();
    loadPackData();
    main::mForm->dataChanged();
    if(!notSaved){
        main::mForm->dataSaved();
    }
}

void coreData::loadPackData(){
    string hiresPath;
    hiresPath = packPath + string("\\hires.txt");

    fstream fs;
    string line;
    string lineHdr;
    string lineTail;
    fs.open(hiresPath, fstream::in);
    if(fs.is_open()){
        while(getline(fs, line)){
            size_t found = line.find_first_of(">");
            if(found!=string::npos){
                lineHdr = line.substr(0, found + 1);
                lineTail = line.substr(found + 1);
                if(lineHdr == "<scale>"){
                    scale = atoi(lineTail.c_str());
                }
                else if(lineHdr == "<img>" ){
                    //load image and add to list
                    image* i = new image();
                    i->load(lineTail);
                    images.push_back(i);
                }
                else if(lineHdr == "condition"){

                }
                else if(lineHdr == "<tile>" ){

                }
                else{
                    //put all other lines away at the moment
                    otherLines.push_back(line);
                }
            }
        }
        fs.close();
    }
    loadPalette();
}

void coreData::loadRom(){
    fstream romfile;
	Uint8 fileType[4];
	Uint8 header[12];

	if(romSize > 0) free(romData);

    romfile.open(romPath, ios::in | ios::binary);
	if (romfile.is_open()){
		romfile.read((char*)fileType, 4);
		if(fileType[0] == 0x4E
		&& fileType[1] == 0x45
		&& fileType[2] == 0x53
		&& fileType[3] == 0x1A){
			//first 4 bytes are correct, read rest of the header
			romfile.read((char*)header, 12);
            Uint8 prgPageCount = header[0];
            Uint8 chrPageCount = header[1];
            //skip trainer
            if((header[2] & 0x04) == 0x04) romfile.seekg(528, ios_base::cur);
            if(chrPageCount > 0){
                //skip prg
                if(prgPageCount > 0) romfile.seekg(prgPageCount * 0x4000, ios_base::cur);
                romSize = chrPageCount * 0x2000;
                romData = (Uint8*) malloc(romSize);
                romfile.read((char*)(romData), romSize);
                isCHRROM = true;
            }
            else{
                romSize = prgPageCount * 0x4000;
                romData = (Uint8*) malloc(romSize);
                romfile.read((char*)(romData), romSize);
                isCHRROM = false;
            }
		}
	}
    romfile.close();
    main::mForm->romChanged();
}

void coreData::loadPalette(){
    string palettePath;
    palettePath = packPath + string("\\palette.dat");

    fstream palettefile;
    char rawPalette[192];
    palettefile.open(palettePath, ios::in | ios::binary);
    if (!palettefile.is_open()){
        palettefile.open(main::exeDir + string("\\default.pal"), ios::in | ios::binary);
    }
    if (palettefile.is_open()){
        palettefile.read(rawPalette, 192);
        palettefile.close();

        for(int i = 0; i < 64; i++){
            palette[i] = wxColour(rawPalette[i * 3], rawPalette[i * 3 + 1], rawPalette[i * 3 + 2]);
        }
    }
}

void coreData::load(string path){
    projectPath = path;

    fstream fs;
    string line;
    string lineHdr;
    string lineTail;
    fs.open(projectPath, fstream::in);
    if(fs.is_open()){
        while(getline(fs, line)){
            size_t found = line.find_first_of(">");
            if(found!=string::npos){
                lineHdr = line.substr(0, found + 1);
                lineTail = line.substr(found + 1);
                if(lineHdr == "<romPath>"){
                    romPath = lineTail;
                }
                else if(lineHdr == "<packPath>"){
                    packPath = lineTail;
                }
                else if(lineHdr == "<palette>"){
                    vector<string> lineTokens;
                    split(lineTail, ',', lineTokens);
                    palette[atoi(lineTokens[0].c_str())].SetRGBA(atoi(lineTokens[1].c_str()));

                }
            }
        }
        fs.close();
        loadRom();
        main::mForm->dataChanged();
        main::mForm->dataSaved();
    }
}

void coreData::save(){
    notSaved = false;

	fstream inifile;
    ostringstream convert;
    string s;

	inifile.open(projectPath, ios::out);
	inifile << "<romPath>" + romPath + "\n";
	inifile << "<packPath>" + packPath + "\n";

    for(int i = 0; i < 64; ++i){
        inifile << "<palette>";
        convert.str("");
        convert.clear();
        convert << i;
        s = convert.str();
        inifile << s;

        convert.str("");
        convert.clear();
        convert << palette[i].GetRGBA();
        s = convert.str();
        inifile << "," + s;

        inifile << "\n";
    }

    inifile.close();
    main::mForm->dataSaved();
}

void coreData::saveAs(string path){
    projectPath = path;
    save();
}

void coreData::dataChanged(){
    notSaved = true;
    main::mForm->dataChanged();
}

vector<string> coreData::split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

string coreData::getTileID(int tileIndex){
    if(isCHRROM){
        return main::intToStr(tileIndex);
    }
    else{
        Uint8* tileData = romData + (tileIndex * 16);
        string tmpVal = "";
        for(Uint8 i = 0; i < 16; ++i){
            tmpVal = tmpVal + main::intToHex(tileData[i]);
        }
    }
}
