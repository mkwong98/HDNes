#include "StdAfx.h"
#include "cart.h"
#include "sysState.h"
#include "mapperList.h"

#include <fstream>
#include <Shlwapi.h>

using namespace std;

cart::cart()
{
	romLoaded = false;
}


cart::~cart(void)
{
	clean();
}

void cart::clean(){
	if(romLoaded){
        saveBat();
		if(prgPageCount > 0){
			free(prgROM);
		}
		if(chrPageCount > 0){
			free(chrROM);
		}
		else{
			free(chrRAM);
            free(chrRAMAddress);
		} 
		free(batDat);
		delete mmc;
	}

}

void cart::loadRom(string name){
	fstream romfile;
	char fileType[4];
	char header[12];

	clean();
	gameName = name;
	setting->gamePath = name;
	romfile.open(gameName, ios::in | ios::binary);
	if (romfile.is_open()){
		romfile.read(fileType, 4);
		if(fileType[0] == 0x4E 
		&& fileType[1] == 0x45
		&& fileType[2] == 0x53
		&& fileType[3] == 0x1A){
			//first 4 bytes are correct, read rest of the header
			romfile.read(header, 12);
			prgPageCount = header[0];
			chrPageCount = header[1];
			
			mapperID = header[3] + ((header[2] >> 4) & 0x0F);

			mirrorV =  ((header[2] & 0x01) == 0x01);
			useBat =   ((header[2] & 0x02) == 0x02);
			useTrain = ((header[2] & 0x04) == 0x04);
			scr4x =    ((header[2] & 0x08) == 0x08);
			//skip trainer
			if(useTrain){
				romfile.seekg(528);
			}

			//read prg pages
			if(prgPageCount > 0){
				prgROM = (Uint8*) malloc(PRG_PAGE_SIZE * prgPageCount);
				romfile.read((char *)(prgROM), 0x4000 * prgPageCount);
			}
			//read chr pages
			if(chrPageCount > 0){
				chrROM = (Uint8*) malloc(CHR_PAGE_SIZE * chrPageCount);
				romfile.read((char *)(chrROM), 0x2000 * chrPageCount);
			}
			else{
				chrRAM = (Uint8*) malloc(0x4000);
                chrRAMAddress = (Uint32*) malloc(0x400 * sizeof(Uint32));
				for(int i = 0; i < 0x400; ++i){
					chrRAMAddress[i] = BAD_ADDRESS;
				}
				lastPrgRead = BAD_ADDRESS;
			}

			batDat = (Uint8*) malloc(0x2000);
			loadBat();
            //if (useBat) {
            //    loadBat();
            //}
            batChanged = false;

			scr4RAM = (Uint8*) malloc(0x1000);

            romLoaded = true;
			switch(mapperID){
			case 0:
				mmc = new mapper0();
				break;
			case 1:
				mmc = new mapper1();
				break;
			case 2:
				mmc = new mapper2();
				break;
			case 3:
				mmc = new mapper3();
				break;
			case 4:
				mmc = new mapper4();
				break;
			case 7:
				mmc = new mapper7();
				break;
			case 9:
				mmc = new mapper9();
				break;
			case 10:
				mmc = new mapper10();
				break;
            case 16:
            case 153:
            case 159:
                mmc = new mapper16();
                break;
            default:
				writeLog("Unsupported mapper:" + to_string((long double)mapperID));
                romLoaded = false;
			}
		}
		romfile.close();
	}
}

void cart::loadBat(){
	fstream romfile;
    string filename = getROMDirPath() + "\\" + getROMName() + ".sav";
    
	romfile.open(filename, ios::in | ios::binary);
	if (romfile.is_open()){
        romfile.read((char *)(batDat), 0x2000);
		romfile.close();
	}
}

void cart::saveBat(){
    if(batChanged){
		fstream romfile;
		string filename = getROMDirPath() + "\\" + getROMName() + ".sav";
    
		romfile.open(filename, ios::out | ios::binary | ios::trunc);
		if (romfile.is_open()){
			romfile.write((char *)(batDat), 0x2000);
			romfile.close();
		}
    }
}


bool cart::getLoadState(){
	return romLoaded;
}

void cart::saveState(fstream* statefile){
    if (chrPageCount == 0) {
        statefile->write((char *)(chrRAM), 0x4000);        
    }
    statefile->write((char *)(batDat), 0x2000);
    statefile->write((char *)(scr4RAM), 0x1000);
}


void cart::loadState(fstream* statefile){
    if (chrPageCount == 0) {
        statefile->read((char *)(chrRAM), 0x4000);
    }
    statefile->read((char *)(batDat), 0x2000);
    statefile->read((char *)(scr4RAM), 0x1000);
}
