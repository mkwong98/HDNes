#include "StdAfx.h"
#include "mapper0.h"
#include "sysState.h"

mapper0::mapper0(void)
{
	if(romDat->mirrorV){
		memDat->nameTableMirroring[0][0] = 0;
		memDat->nameTableMirroring[0][1] = 0;
		memDat->nameTableMirroring[1][0] = 1;
		memDat->nameTableMirroring[1][1] = 1;
	}
	else{
		memDat->nameTableMirroring[0][0] = 0;
		memDat->nameTableMirroring[0][1] = 1;
		memDat->nameTableMirroring[1][0] = 0;
		memDat->nameTableMirroring[1][1] = 1;
	}
	prgPtr[0] = &(romDat->prgROM[0]);
	prgPtr[1] = &(romDat->prgROM[0x4000]);
}


mapper0::~mapper0(void)
{
}

void mapper0::writeCPUData(Uint16 address, Uint8 data){
	if((address < 0x8000) && (address >= 0x6000)){
		romDat->batDat[address & 0x1FFF] = data;
        if(romDat->useBat)romDat->batChanged = true;
    }
}

Uint8 mapper0::readCPUData(Uint16 address, bool opRead){
	Uint16 bank;
	bank = (address & 0xC000);
	if(bank == 0x8000){
        lastPrgRead = &(prgPtr[0][address & 0x3FFF]) - romDat->prgROM;
		return prgPtr[0][address & 0x3FFF];
	}
	else if(bank == 0xC000){
		if(romDat->prgPageCount == 1){
            if(opRead) lastPrgRead = &(prgPtr[0][address & 0x3FFF]) - romDat->prgROM;
			return prgPtr[0][address & 0x3FFF];
		}
		else{
            if(opRead) lastPrgRead = &(prgPtr[1][address & 0x3FFF]) - romDat->prgROM;
			return prgPtr[1][address & 0x3FFF];
		}
	}
	else if(address >= 0x6000){
		return romDat->batDat[address & 0x1FFF];
	}
	else{
		return 0;
	}
}

void mapper0::writePPUData(Uint16 address, Uint8 data){
	if(address < 0x2000){
		if(romDat->chrPageCount == 0){
			romDat->chrRAM[address] = data;
			if(lastPrgRead != BAD_ADDRESS)
	            romDat->chrRAMAddress[address >> 4] = lastPrgRead >> 4;
		}
	}
}

Uint8 mapper0::readPPUData(Uint16 address){
	if(address < 0x2000){
		if(romDat->chrPageCount > 0){
			return romDat->chrROM[address];
		}
		else{
			return romDat->chrRAM[address];
		}
	}
	else{
		return 0;
	}
}

void mapper0::getPattern(Uint16 address, Uint8 row, bool isFirst, Uint8& data, Uint32& patternAddress, Uint32& ramAddress){
	Uint16 tmpAddress;
	tmpAddress = address;
	if(row >= 8){ 
		tmpAddress += 16;
		row -= 8;
	}
	if(!isFirst) tmpAddress += 8;
	if(romDat->chrPageCount > 0){
		data = romDat->chrROM[tmpAddress + row];
        patternAddress = tmpAddress >> 4;
	}
	else{
		data = romDat->chrRAM[tmpAddress + row];
		ramAddress = tmpAddress & 0xFFF0;
		if(vid->chrRamMatch){
			patternAddress = romDat->chrRAMAddress[tmpAddress >> 4];
		}
		else{
	        patternAddress = tmpAddress >> 4;
		}
	}
}

void mapper0::saveState(fstream* statefile){
}


void mapper0::loadState(fstream* statefile){
}


void mapper0::runCatchUp(unsigned int cycle){
}

void mapper0::resetCycleCount(){
}
