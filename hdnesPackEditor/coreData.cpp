#include "common.h"
#include "coreData.h"
#include "image.h"
#include "main.h"
#include "gameTile.h"
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
    while(images.size() > 0){
        delete(images.back());
        images.pop_back();
    }
    while(tiles.size() > 0){
        delete(tiles.back());
        tiles.pop_back();
    }
    while(conditions.size() > 0){
        delete(conditions.back());
        conditions.pop_back();
    }
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
    string orgLine;
    bool editorSection = false;
    vector<string> conNames;
    string conNameStr;

    fs.open(hiresPath, fstream::in);
    if(fs.is_open()){
        while(getline(fs, line)){
            if(!editorSection){
                orgLine = line;
                conNames.clear();
                if(line.substr(0, 1) == "["){
                    //is condition
                    size_t conTagPos = line.find_first_of("]");
                    if(conTagPos!=string::npos){
                        conNameStr = line.substr(1, conTagPos - 1);
                        main::split(conNameStr, '&', conNames);
                        line = line.substr(conTagPos + 1);
                    }
                }
                size_t found = line.find_first_of(">");
                if(found!=string::npos){
                    lineHdr = line.substr(0, found + 1);
                    lineTail = line.substr(found + 1);
                    if(lineHdr == "<ver>"){
                        ver.push_back(line);
                    }
                    else if(lineHdr == "<scale>"){
                        scale = atoi(lineTail.c_str());
                    }
                    else if(lineHdr == "<supportedRom>"){
                        supportedRom.push_back(line);
                    }
                    else if(lineHdr == "<overscan>"){
                        overscan.push_back(line);
                    }
                    else if(lineHdr == "<patch>"){
                        patch.push_back(line);
                    }
                    else if(lineHdr == "<img>" ){
                        addImage(lineTail);
                    }
                    else if(lineHdr == "<condition>"){
                        condition* c = new condition();
                        c->readLine(lineTail);
                        conditions.push_back(c);
                    }
                    else if(lineHdr == "<tile>" ){
                        gameTile* t = new gameTile();
                        t->readLine(lineTail);
                        if(conNames.size() > 0){
                            //add conditions
                            for(int i = 0; i < conditions.size(); ++i){
                                for(int j = 0; j < conNames.size(); ++j){
                                    if(conditions[i]->name == conNames[j]){
                                        t->conditions.push_back(*conditions[i]);
                                    }
                                }
                            }
                        }
                        tiles.push_back(t);
                    }
                    else if(lineHdr == "<background>"){
                        background.push_back(orgLine);
                    }
                    else if(lineHdr == "<options>"){
                        options.push_back(line);
                    }
                    else if(lineHdr == "<bgm>"){
                        bgm.push_back(line);
                    }
                    else if(lineHdr == "<sfx>"){
                        sfx.push_back(line);
                    }
                }
                else if(line == "#editorSection"){
                    editorSection = true;
                }
            }
            else if(line == "#endEditorSection"){
                editorSection = false;
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
                    loadRom();
                }
                else if(lineHdr == "<packPath>"){
                    packPath = lineTail;
                    loadPackData();
                    images.clear();
                }
                else if(lineHdr == "<saveNo>"){
                    saveNo = atoi(lineTail.c_str());
                }
                else if(lineHdr == "<palette>"){
                    vector<string> lineTokens;
                    main::split(lineTail, ',', lineTokens);
                    palette[atoi(lineTokens[0].c_str())].SetRGBA(atoi(lineTokens[1].c_str()));

                }
                else if(lineHdr == "<gameObject>"){
                    main::mForm->loadGameObjs(fs);
                }
                else if(lineHdr == "<img>"){
                    addImage(lineTail);
                }
            }
        }
        fs.close();

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
	inifile << "<saveNo>" << saveNo << "\n";

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
        inifile << "," + s << "\n";
    }

    main::mForm->saveGameObjs(inifile);
    for(int i = 0; i < images.size(); ++i){
        inifile << "<img>" << images[i]->fileName << "\n";
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
        return tmpVal;
    }
}

void coreData::addImage(string path){
    //load image and add to list
    image* i = new image();
    i->load(path);
    images.push_back(i);
}

void coreData::removeImage(int index){
    int i = 0;
    //update index of tiles
    while(i < tiles.size()){
        if(tiles[i]->hasReplacement){
            if(tiles[i]->img == index){
                delete(tiles[i]);
                tiles.erase(tiles.begin() + i);
                --i;
            }
            else if(tiles[i]->img > index){
                --(tiles[i]->img);
            }
        }
        ++i;
    }
    delete(images[index]);
    images.erase(images.begin() + index);
}

void coreData::genPackData(){
    string hiresPath;
    hiresPath = packPath + string("\\hires.txt");

    //back up old file
    string backPath;
    backPath = packPath + string("\\hiresBak") + main::intToStr(saveNo) + string(".txt");
    std::ifstream  src(hiresPath, std::ios::binary);
    std::ofstream  dst(backPath, std::ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();

    //save project first
    ++saveNo;
    save();

	fstream inifile;
    string s;

	inifile.open(projectPath, ios::out);
	genSection(inifile, ver);
	inifile << "<scale>" << scale << "\n";
	genSection(inifile, supportedRom);
	genSection(inifile, overscan);
	genSection(inifile, patch);

	for(int i = 0; i < images.size(); ++i){
        inifile << "<img>" << images[i]->fileName << "\n";
	}

	inifile << "#editorSection\n";
	inifile << "#endEditorSection\n";

	genSection(inifile, background);
	genSection(inifile, options);
	genSection(inifile, bgm);
	genSection(inifile, sfx);


}

void coreData::genSection(fstream& inifile, vector<string>& sect){
    for(int i = 0; i < sect.size(); ++i){
        inifile << sect[i] << "\n";
    }
}

void coreData::genPalette(){
    string palettePath;
    palettePath = packPath + string("\\palette.dat");

    fstream palettefile;
    char rawPalette[192];
    for(int i = 0; i < 64; i++){
        rawPalette[i * 3] = palette[i].Red();
        rawPalette[i * 3 + 1] = palette[i].Green();
        rawPalette[i * 3 + 2] = palette[i].Blue();
    }

    palettefile.open(palettePath, ios::out | ios::binary);
    if (palettefile.is_open()){
        palettefile.write(rawPalette, 192);
        palettefile.close();
    }
}
