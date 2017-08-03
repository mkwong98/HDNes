#include "../common.h"
#include "cart.h"
#include "mapper000.h"
#include "mapper001.h"
#include "../emu/emuPart.h"

cart::cart(){
    batChanged = false;
}

cart::~cart(){
    saveBat();
    if(prgPageCount > 0) free(prgROM);
    if(chrPageCount > 0){
        free(chrROM);
    }
    else{
        free(chrRAM);
    }
}

Uint8 cart::readPRGData(Uint16 address){
}

void cart::writePRGData(Uint16 address, Uint8 value){
}

Uint8 cart::readCHRData(Uint16 address){
    if(chrPageCount > 0){
        return readMapperCHRData(address);
    }
    else{
        return chrRAM[address];
    }
}

void cart::writeCHRData(Uint16 address, Uint8 value){
}

Uint8 cart::readNameTable(Uint16 address){
    return (mirrorPtr[(address & 0x0C00) >> 10])[address & 0x03FF];
}

void cart::writeNameTable(Uint16 address, Uint8 value){

}




cart* cart::getCartFromROMFile(const string& fileName){
    fstream romfile;
	Uint8 fileType[4];
	Uint8 header[12];
	Uint8 mapperID;
    cart* rs;

    romfile.open(fileName, ios::in | ios::binary);
	if (romfile.is_open()){
		romfile.read((char*)fileType, 4);
		if(fileType[0] == 0x4E
		&& fileType[1] == 0x45
		&& fileType[2] == 0x53
		&& fileType[3] == 0x1A){
			//first 4 bytes are correct, read rest of the header
			romfile.read((char*)header, 12);
		    mapperID = header[3] + ((header[2] >> 4) & 0x0F);

		    switch(mapperID){
                case 0:
                    rs = new mapper000();
                    break;
                case 1:
                    rs = new mapper001();
                    break;
                default:
                    rs = NULL;
                    break;
		    }
		    if(rs){
                rs->readROMFile(&romfile, &header[0], fileName);
		    }
		}
	}
	else{
        rs = NULL;
	}
    romfile.close();
    return rs;
}

void cart::readROMFile(fstream* fs, Uint8* header, const string& fileName){
    romFileName = fileName;
    prgPageCount = header[0];
    chrPageCount = header[1];
    mirrorV = ((header[2] & 0x01) == 0x01);
    scr4x = ((header[2] & 0x08) == 0x08);

    //skip trainer
    if((header[2] & 0x04) == 0x04) (*fs).seekg(528);

    //read prg pages
    if(prgPageCount > 0){
        prgROM = (Uint8*) malloc(PRG_PAGE_SIZE * prgPageCount);
        (*fs).read((char *)(prgROM), PRG_PAGE_SIZE * prgPageCount);
    }

    //read chr pages
    if(chrPageCount > 0){
        chrROM = (Uint8*) malloc(CHR_PAGE_SIZE * chrPageCount);
        (*fs).read((char *)(chrROM), CHR_PAGE_SIZE * chrPageCount);
    }
    else{
        chrRAM = (Uint8*) malloc(CHR_RAM_SIZE);
    }

    loadBat();
}



void cart::loadBat(){
	fstream romfile;
    string filename = emuPart::getConfigLineVal(romFileName) + ".sav";

	romfile.open(filename, ios::in | ios::binary);
	if (romfile.is_open()){
        romfile.read((char *)(batDat), BATTERY_SIZE);
		romfile.close();
	}
}

void cart::saveBat(){
    if(batChanged){
		fstream romfile;
		string filename = emuPart::getConfigLineVal(romFileName) + ".sav";

		romfile.open(filename, ios::out | ios::binary | ios::trunc);
		if (romfile.is_open()){
			romfile.write((char *)(batDat), BATTERY_SIZE);
			romfile.close();
		}
    }
}

void cart::init(){
}

void cart::init2(){
}

void cart::reset(){
}

void cart::saveState(fstream* statefile){
}

void cart::loadState(fstream* statefile){
}

