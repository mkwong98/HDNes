#include "common.h"
#include "coreData.h"

coreData* coreData::cData;

coreData::coreData()
{
    romPath = "";
    romSize = 0;
}

coreData::~coreData()
{
    if(romSize > 0) free(chrROM);
}

void coreData::loadPackData(){
}

void coreData::loadRom(){
    fstream romfile;
	Uint8 fileType[4];
	Uint8 header[12];

	if(romSize > 0) free(chrROM);

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
            if(chrPageCount > 0){
                //skip trainer
                if((header[2] & 0x04) == 0x04) romfile.seekg(528);
                //skip prg
                if(prgPageCount > 0) romfile.seekg(prgPageCount * 0x4000);
                chrROM = (Uint8*) malloc(chrPageCount * 0x2000);
                romfile.read((char*)(chrROM), chrPageCount * 0x2000);
            }
            else{
                romSize = 0;
            }
		}
	}
    romfile.close();
}


