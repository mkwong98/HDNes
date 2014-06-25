#include "StdAfx.h"
#include "mapper10.h"
#include "sysState.h"


mapper10::mapper10(void)
{
	chrMask = 0xF000;
	chrSwitchMask = ((CHR_PAGE_SIZE * romDat->chrPageCount) >> 10) - 1;
	prgSwitchMask = ((PRG_PAGE_SIZE * romDat->prgPageCount) >> 14) - 1;
	chrMode[0] = 0;
	chrMode[1] = 0;
    mapReg[0] = 0;
    mapReg[1] = 0;
    mapReg[2] = 0;
    mapReg[3] = 0;
    mapReg[4] = 0;
    mapReg[5] = 0;
	setMirroring();
	setBankSwitching();
	setChrBankSwitching();
}


mapper10::~mapper10(void)
{
}

void mapper10::setMirroring(){
	if((mapReg[5] & 0x01) == 0){
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
}

void mapper10::setBankSwitching(){
    prgPtr[0] = &(romDat->prgROM[(mapReg[0] & prgSwitchMask) << 14]);
    prgPtr[1] = &(romDat->prgROM[(((mapReg[0] & prgSwitchMask) << 1) + 1) << 13]);
    prgPtr[2] = &(romDat->prgROM[(romDat->prgPageCount * 2 - 2) << 13]);
    prgPtr[3] = &(romDat->prgROM[(romDat->prgPageCount * 2 - 1) << 13]);
}

void mapper10::setChrBankSwitching(){
    if (chrMode[0] == 0) {
        chrPtr[0] = &(romDat->chrROM[(mapReg[1] & chrSwitchMask) << 12]);
    }
    else{
        chrPtr[0] = &(romDat->chrROM[(mapReg[2] & chrSwitchMask) << 12]);
    }
    if (chrMode[1] == 0) {
        chrPtr[1] = &(romDat->chrROM[(mapReg[3] & chrSwitchMask) << 12]);
    }
    else{
        chrPtr[1] = &(romDat->chrROM[(mapReg[4] & chrSwitchMask) << 12]);
    }
}


void mapper10::writeCPUData(Uint16 address, Uint8 data){
	Uint16 writeAddress;
	if(address >= 0x6000){
		if(address < 0x8000){  
			romDat->batDat[address & 0x1FFF] = data;
			if(romDat->useBat) romDat->batChanged = true;
		}
		else{
			writeAddress = (address & chrMask);
			switch(writeAddress){
			case 0xA000:
				mapReg[0] = data;
	            setBankSwitching();            
				break;
			case 0xB000:
				mapReg[1] = data;
	            setChrBankSwitching();            
				break;
			case 0xC000:
				mapReg[2] = data;
	            setChrBankSwitching();            
				break;
			case 0xD000:
				mapReg[3] = data;
	            setChrBankSwitching();            
				break;
			case 0xE000:
				mapReg[4] = data;
	            setChrBankSwitching();            
				break;
			case 0xF000:
				mapReg[5] = data;
	            setMirroring();            
				break;
			}
		}
	}

}

Uint8 mapper10::readCPUData(Uint16 address, bool opRead){
	Uint16 bank;
	bank = (address >> 13) & 0x03;
	if(address >= 0x8000){
        if(opRead) lastPrgRead = &(prgPtr[bank][address & 0x1FFF]) - romDat->prgROM;
		return prgPtr[bank][address & 0x1FFF];
	}
	else if(address >= 0x6000 && !romDat->scr4x){
		return romDat->batDat[address & 0x1FFF]; 
	}
	else{
		return 0;
	}
}

void mapper10::writePPUData(Uint16 address, Uint8 data){
	if(address < 0x2000){
		if(romDat->chrPageCount == 0){
			romDat->chrRAM[address] = data;
			if(lastPrgRead != BAD_ADDRESS)
	            romDat->chrRAMAddress[address >> 4] = lastPrgRead >> 4;
		}
	}
}

void mapper10::setChrMode(Uint16 address){
	Uint16 modeCheck;
	modeCheck = address & 0x1FF0;
	switch(modeCheck){
	case 0x0FD0:
		chrMode[0] = 0;
		break;
	case 0x0FE0:
		chrMode[0] = 1;
		break;
	case 0x1FD0:
		chrMode[1] = 0;
		break;
	case 0x1FE0:
		chrMode[1] = 1;
		break;
	}
	switch(modeCheck){
	case 0x0FD0:
	case 0x0FE0:
	case 0x1FD0:
	case 0x1FE0:
		setChrBankSwitching();
		break;
	}
}


Uint8 mapper10::readPPUData(Uint16 address){
	Uint16 bank;
	Uint8 data;
	bank = (address >> 12) & 0x03;

	if(romDat->chrPageCount > 0){
		data = chrPtr[bank][address & 0xFFF];
		setChrMode(address);
		return data;
	}
	else{
		return romDat->chrRAM[address];
	}
}

void mapper10::getPattern(Uint16 address, Uint8 row, bool isFirst, Uint8& data, Uint32& patternAddress, Uint32& ramAddress){
	Uint16 tmpAddress;
	Uint16 bank;
	Uint32 realAddress;

	tmpAddress = address;
	if(row >= 8){ 
		tmpAddress += 16;
		row -= 8;
	}
	if(!isFirst) tmpAddress += 8;

	bank = ((tmpAddress>> 12) & 0x03);
	if(romDat->chrPageCount > 0){
		data = chrPtr[bank][(tmpAddress + row) & 0xFFF];
		realAddress = (&(chrPtr[bank][(tmpAddress + row) & 0xFFF])) - romDat->chrROM;
        patternAddress = realAddress >> 4;
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
	setChrMode(tmpAddress);
}

void mapper10::saveState(fstream* statefile){
    Uint32 offset;
 
    statefile->write((char *)(&chrMask), sizeof(Uint16));
    statefile->write((char *)(&chrSwitchMask), sizeof(Uint16));
    statefile->write((char *)(&prgSwitchMask), sizeof(Uint16));
    statefile->write((char *)(chrMode), sizeof(Uint8) * 2);
    statefile->write((char *)(mapReg), sizeof(Uint8) * 6);
    statefile->write((char *)(&lastPrgRead), sizeof(Uint32));

    for (int i = 0; i < 2; ++i) {
        offset = chrPtr[i] - romDat->chrROM;
        statefile->write((char *)(&offset), sizeof(Uint32));
    }
    for (int i = 0; i < 4; ++i) {
        offset = prgPtr[i] - romDat->prgROM;
        statefile->write((char *)(&offset), sizeof(Uint32));
    }
}


void mapper10::loadState(fstream* statefile){
    Uint32 offset;

    statefile->read((char *)(&chrMask), sizeof(Uint16));
    statefile->read((char *)(&chrSwitchMask), sizeof(Uint16));
    statefile->read((char *)(&prgSwitchMask), sizeof(Uint16));
    statefile->read((char *)(chrMode), sizeof(Uint8) * 2);
    statefile->read((char *)(mapReg), sizeof(Uint8) * 8);
    statefile->read((char *)(&lastPrgRead), sizeof(Uint32));
	
	for (int i = 0; i < 2; ++i) {
        statefile->read((char *)(&offset), sizeof(Uint32));
        chrPtr[i] = &(romDat->chrROM[offset]);
    }
    for (int i = 0; i < 4; ++i) {
        statefile->read((char *)(&offset), sizeof(Uint32));
		prgPtr[i] = &(romDat->prgROM[offset]);
    }
    setMirroring();
	setBankSwitching();
	setChrBankSwitching();
}

void mapper10::runCatchUp(unsigned int cycle){
}

void mapper10::resetCycleCount(){
}