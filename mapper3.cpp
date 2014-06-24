#include "StdAfx.h"
#include "mapper3.h"
#include "sysState.h"


mapper3::mapper3(void)
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
	chrReg = 0;
	chrMask = 0xFF;
	while(chrMask > romDat->chrPageCount){
		chrMask = chrMask >> 1;
	}
	setBankSwitching();
}


mapper3::~mapper3(void)
{
}

void mapper3::setBankSwitching(){
	chrPtr = &(romDat->chrROM[chrReg << 13]);
}


void mapper3::writeCPUData(Uint16 address, Uint8 data){
	if(address >= 0x6000){
		if(address < 0x8000){  
			romDat->batDat[address & 0x1FFF] = data;
            if(romDat->useBat)romDat->batChanged = true;
		}
		else{
			chrReg = (data & chrMask);
			setBankSwitching();
		}
	}
}

Uint8 mapper3::readCPUData(Uint16 address, bool opRead){
	Uint16 bank;
	bank = (address & 0xC000);
	if(bank == 0x8000){
        if(opRead) lastPrgRead = (&(prgPtr[0][address & 0x3FFF])) - romDat->prgROM;
		return prgPtr[0][address & 0x3FFF];
	}
	else if(bank == 0xC000){
		if(romDat->prgPageCount == 1){
            if(opRead) lastPrgRead = (&(prgPtr[0][address & 0x3FFF])) - romDat->prgROM;
			return prgPtr[0][address & 0x3FFF];
		}
		else{
            if(opRead) lastPrgRead = (&(prgPtr[1][address & 0x3FFF])) - romDat->prgROM;
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

void mapper3::writePPUData(Uint16 address, Uint8 data){
	if(address < 0x2000){
		if(romDat->chrPageCount == 0){
			romDat->chrRAM[address] = data;
			if(lastPrgRead != BAD_ADDRESS)
				romDat->chrRAMAddress[address >> 4] = lastPrgRead >> 4;
		}
	}
}

Uint8 mapper3::readPPUData(Uint16 address){
	if(address < 0x2000){
		if(romDat->chrPageCount > 0){
			return chrPtr[address];
		}
		else{
			return romDat->chrRAM[address];
		}
	}
	else{
		return 0;
	}
}

void mapper3::getPattern(Uint16 address, Uint8 row, bool isFirst, Uint8& data, Uint32& patternAddress, Uint32& ramAddress){
	Uint16 tmpAddress;
	Uint32 realAddress;
	tmpAddress = address;
	if(row >= 8){ 
		tmpAddress += 16;
		row -= 8;
	}
	if(!isFirst) tmpAddress += 8;
	if(romDat->chrPageCount > 0){
		data = chrPtr[tmpAddress + row];
		realAddress = (&(chrPtr[tmpAddress + row])) - romDat->chrROM;
		patternAddress = realAddress >> 4;
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

void mapper3::saveState(fstream* statefile){
    Uint32 offset;

    statefile->write((char *)(&chrReg), sizeof(Uint8));
    statefile->write((char *)(&chrMask), sizeof(Uint8));
    statefile->write((char *)(&lastPrgRead), sizeof(Uint32));

    offset = chrPtr - romDat->chrROM;
    statefile->write((char *)(&offset), sizeof(Uint32));
    offset = prgPtr[0] - romDat->prgROM;
    statefile->write((char *)(&offset), sizeof(Uint32));
    offset = prgPtr[1] - romDat->prgROM;
    statefile->write((char *)(&offset), sizeof(Uint32));
}


void mapper3::loadState(fstream* statefile){
    Uint32 offset;

    statefile->read((char *)(&chrReg), sizeof(Uint8));
    statefile->read((char *)(&chrMask), sizeof(Uint8));
    statefile->read((char *)(&lastPrgRead), sizeof(Uint32));

    statefile->read((char *)(&offset), sizeof(Uint32));
    chrPtr = &(romDat->chrROM[offset]);
    statefile->read((char *)(&offset), sizeof(Uint32));
	prgPtr[0] = &(romDat->prgROM[offset]);
    statefile->read((char *)(&offset), sizeof(Uint32));
	prgPtr[1] = &(romDat->prgROM[offset]);
	setBankSwitching();
}

void mapper3::runCatchUp(unsigned int cycle){
}

void mapper3::resetCycleCount(){
}