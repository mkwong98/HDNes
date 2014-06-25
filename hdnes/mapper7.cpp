#include "StdAfx.h"
#include "mapper7.h"
#include "sysState.h"


mapper7::mapper7(void)
{
	prgReg = 0;
	setMirroring();
	setBankSwitching();
}


mapper7::~mapper7(void)
{
}

void mapper7::setMirroring(){
	if((prgReg & 0x10) == 0){
		memDat->nameTableMirroring[0][0] = 0;
		memDat->nameTableMirroring[0][1] = 0;
		memDat->nameTableMirroring[1][0] = 0;
		memDat->nameTableMirroring[1][1] = 0;
	}
	else{
		memDat->nameTableMirroring[0][0] = 1;
		memDat->nameTableMirroring[0][1] = 1;
		memDat->nameTableMirroring[1][0] = 1;
		memDat->nameTableMirroring[1][1] = 1;
	}
}

void mapper7::setBankSwitching(){
	Uint8 pID = ((prgReg & 0x07) << 1) & (romDat->prgPageCount - 1); 
	prgPtr[0] = &(romDat->prgROM[pID << 14]);
	prgPtr[1] = &(romDat->prgROM[(pID + 1) << 14]);
}

void mapper7::writeCPUData(Uint16 address, Uint8 data){
	if(address >= 0x6000){
		if(address < 0x8000){  
			romDat->batDat[address & 0x1FFF] = data;
            if(romDat->useBat)romDat->batChanged = true;
		}
		else{
			prgReg = data;
			setMirroring();
			setBankSwitching();
		}
	}
}

Uint8 mapper7::readCPUData(Uint16 address, bool opRead){
	Uint16 bank;
	bank = (address & 0xC000);
	if(bank == 0x8000){
        if(opRead)
			lastPrgRead = &(prgPtr[0][address & 0x3FFF]) - romDat->prgROM;
		return prgPtr[0][address & 0x3FFF];
	}
	else if(bank == 0xC000){
        if(opRead) 
			lastPrgRead = &(prgPtr[1][address & 0x3FFF]) - romDat->prgROM;
		return prgPtr[1][address & 0x3FFF];
	}
	else if(address >= 0x6000){
		return romDat->batDat[address & 0x1FFF];
	}
	else{
		return 0;
	}
}

void mapper7::writePPUData(Uint16 address, Uint8 data){
	if(address < 0x2000){
		romDat->chrRAM[address] = data;
		if(lastPrgRead != BAD_ADDRESS)
	        romDat->chrRAMAddress[address >> 4] = lastPrgRead >> 4;
	}
}

Uint8 mapper7::readPPUData(Uint16 address){
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

void mapper7::getPattern(Uint16 address, Uint8 row, bool isFirst, Uint8& data, Uint32& patternAddress, Uint32& ramAddress){
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
        //patternAddress = BAD_ADDRESS;
		if(vid->chrRamMatch){
			patternAddress = romDat->chrRAMAddress[tmpAddress >> 4];
		}
		else{
	        patternAddress = tmpAddress >> 4;
		}
	}
}

void mapper7::saveState(fstream* statefile){
    Uint32 offset;

	statefile->write((char *)(&prgReg), sizeof(Uint8));
    statefile->write((char *)(&lastPrgRead), sizeof(Uint32));

    offset = prgPtr[0] - romDat->prgROM;
    statefile->write((char *)(&offset), sizeof(Uint32));
    offset = prgPtr[1] - romDat->prgROM;
    statefile->write((char *)(&offset), sizeof(Uint32));
}


void mapper7::loadState(fstream* statefile){
    Uint32 offset;

	statefile->read((char *)(&prgReg), sizeof(Uint8));
    statefile->read((char *)(&lastPrgRead), sizeof(Uint32));
	
	statefile->read((char *)(&offset), sizeof(Uint32));
	prgPtr[0] = &(romDat->prgROM[offset]);
    statefile->read((char *)(&offset), sizeof(Uint32));
	prgPtr[1] = &(romDat->prgROM[offset]);
    setMirroring();
	setBankSwitching();
}

void mapper7::runCatchUp(unsigned int cycle){
}

void mapper7::resetCycleCount(){
}