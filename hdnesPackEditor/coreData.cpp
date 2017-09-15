#include "common.h"
#include "coreData.h"
#include "image.h"
#include "main.h"

coreData* coreData::cData;

coreData::coreData()
{
    romPath = "";
    romSize = 0;
    isCHRROM = true;
}

coreData::~coreData()
{
    if(romSize > 0) free(romData);
}

void coreData::loadPackData(){
    string hiresPath;
    hiresPath = packPath + string("\\hires.txt");

    string palettePath;
    palettePath = packPath + string("\\palette.dat");


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
}


