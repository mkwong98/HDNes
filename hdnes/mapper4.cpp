#include "StdAfx.h"
#include "mapper4.h"
#include "sysState.h"


mapper4::mapper4(void)
{
    setMirroring();
	chrMask = 0xE001;
	chrSwitchMask = ((CHR_PAGE_SIZE * romDat->chrPageCount) >> 10) - 1;
	prgSwitchMask = ((PRG_PAGE_SIZE * romDat->prgPageCount) >> 13) - 1;
	chrMode = 0;
	prgMode = 0;
	regAddress = 0;
    irqEnabled = false;
	irqFlag = false;
    
    mapReg[0] = 0;
    mapReg[1] = 2;
    mapReg[2] = 4;
    mapReg[3] = 5;
    mapReg[4] = 6;
    mapReg[5] = 7;
    mapReg[6] = 0;
    mapReg[7] = 1;
	setBankSwitching();
}


mapper4::~mapper4(void)
{
}

void mapper4::setMirroring(){
	if(!romDat->scr4x){
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
	}
	else{
		memDat->nameTableMirroring[0][0] = 0;
		memDat->nameTableMirroring[0][1] = 1;
		memDat->nameTableMirroring[1][0] = 2;
		memDat->nameTableMirroring[1][1] = 3;
	}
}


void mapper4::setBankSwitching(){
    if (chrMode == 0) {
        chrPtr[0] = &(romDat->chrROM[((mapReg[0] & 0xFE) & chrSwitchMask) << 10]);
        chrPtr[1] = &(romDat->chrROM[(((mapReg[0] & 0xFE) + 1) & chrSwitchMask) << 10]);
        chrPtr[2] = &(romDat->chrROM[((mapReg[1] & 0xFE) & chrSwitchMask) << 10]);
        chrPtr[3] = &(romDat->chrROM[(((mapReg[1] & 0xFE) + 1) & chrSwitchMask) << 10]);
        chrPtr[4] = &(romDat->chrROM[(mapReg[2] & chrSwitchMask) << 10]);
        chrPtr[5] = &(romDat->chrROM[(mapReg[3] & chrSwitchMask) << 10]);
        chrPtr[6] = &(romDat->chrROM[(mapReg[4] & chrSwitchMask) << 10]);
        chrPtr[7] = &(romDat->chrROM[(mapReg[5] & chrSwitchMask) << 10]);

    }
    else{
        chrPtr[0] = &(romDat->chrROM[(mapReg[2] & chrSwitchMask) << 10]);
        chrPtr[1] = &(romDat->chrROM[(mapReg[3] & chrSwitchMask) << 10]);
        chrPtr[2] = &(romDat->chrROM[(mapReg[4] & chrSwitchMask) << 10]);
        chrPtr[3] = &(romDat->chrROM[(mapReg[5] & chrSwitchMask) << 10]);
        chrPtr[4] = &(romDat->chrROM[((mapReg[0] & 0xFE) & chrSwitchMask) << 10]);
        chrPtr[5] = &(romDat->chrROM[(((mapReg[0] & 0xFE) + 1) & chrSwitchMask) << 10]);
        chrPtr[6] = &(romDat->chrROM[((mapReg[1] & 0xFE) & chrSwitchMask) << 10]);
        chrPtr[7] = &(romDat->chrROM[(((mapReg[1] & 0xFE) + 1) & chrSwitchMask) << 10]);


    }

    if (prgMode == 0) {
        prgPtr[0] = &(romDat->prgROM[(mapReg[6] & prgSwitchMask) << 13]);
        prgPtr[2] = &(romDat->prgROM[(romDat->prgPageCount * 2 - 2) << 13]);
    }
    else{
        prgPtr[2] = &(romDat->prgROM[(mapReg[6] & prgSwitchMask) << 13]);
        prgPtr[0] = &(romDat->prgROM[(romDat->prgPageCount * 2 - 2) << 13]);
    }
    prgPtr[1] = &(romDat->prgROM[(mapReg[7] & prgSwitchMask) << 13]);
    prgPtr[3] = &(romDat->prgROM[(romDat->prgPageCount * 2 - 1) << 13]);
}


void mapper4::writeCPUData(Uint16 address, Uint8 data){
	Uint16 writeAddress;
	if(address >= 0x6000){
		if(address < 0x8000){  
            if(!romDat->scr4x){
				romDat->batDat[address & 0x1FFF] = data;
				if(romDat->useBat)
					romDat->batChanged = true;
			}
		}
		else{
			writeAddress = (address & chrMask);
			switch(writeAddress){
			case 0x8000:
				chrMode = data >> 7;
				prgMode = (data >> 6) & 0x01;
				regAddress = data & 0x07;
	            setBankSwitching();            
				break;
			case 0x8001:
				mapReg[regAddress] = data;
	            setBankSwitching();            
				break;
			case 0xA000:
                //disable writes to mirroring when 4 screen
				if(!romDat->scr4x){
                    romDat->mirrorV = ((data & 0x01) == 0);
                    setMirroring();
				}
				break;
			case 0xA001:
				break;
			case 0xC000:
                irqValue = data;
				break;
			case 0xC001:
                irqCounter = 0;
				break;
			case 0xE000:
				irqFlag = false;
				irqEnabled = false;
				break;
			case 0xE001:
                irqEnabled = true;
				scanlineNo = -1;
				break;

			}
		}
	}
}

Uint8 mapper4::readCPUData(Uint16 address, bool opRead){
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

void mapper4::writePPUData(Uint16 address, Uint8 data){
	if(address < 0x2000){
		if(romDat->chrPageCount == 0){
			romDat->chrRAM[address] = data;
			if(lastPrgRead != BAD_ADDRESS)
	            romDat->chrRAMAddress[address >> 4] = lastPrgRead >> 4;
		}
	}
}

Uint8 mapper4::readPPUData(Uint16 address){
	Uint16 bank;
	bank = (address >> 10) & 0x07;
	if(romDat->chrPageCount > 0){
		return chrPtr[bank][address & 0x3FF];
	}
	else{
		return romDat->chrRAM[address];
	}
}

void mapper4::getPattern(Uint16 address, Uint8 row, bool isFirst, Uint8& data, Uint32& patternAddress, Uint32& ramAddress){
	Uint16 tmpAddress;
	Uint16 bank;
	Uint32 realAddress;

	tmpAddress = address;
	if(row >= 8){ 
		tmpAddress += 16;
		row -= 8;
	}
	if(!isFirst) tmpAddress += 8;

	bank = ((tmpAddress>> 10) & 0x07);
	if(romDat->chrPageCount > 0){
		data = chrPtr[bank][(tmpAddress + row) & 0x3FF];
		realAddress = (&(chrPtr[bank][(tmpAddress + row) & 0x3FF])) - romDat->chrROM;
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

	if(address & 0x1000){
		if(scanlineNo != ppuCore->screenY){
			scanlineNo = ppuCore->screenY;
			if(irqCounter == 0){
				irqCounter = irqValue;
			}
			else{
				--irqCounter;
				if(irqCounter == 0 && irqEnabled && !irqFlag){
					irqFlag = true;
				}
			}
		}
	}
	if(irqFlag){
		cpuCore->setIRQ();
	}
}

void mapper4::saveState(fstream* statefile){
    Uint32 offset;
 
    statefile->write((char *)(&chrMask), sizeof(Uint16));
    statefile->write((char *)(&chrSwitchMask), sizeof(Uint16));
    statefile->write((char *)(&prgSwitchMask), sizeof(Uint16));
    statefile->write((char *)(&chrMode), sizeof(Uint8));
    statefile->write((char *)(&prgMode), sizeof(Uint8));
    statefile->write((char *)(&regAddress), sizeof(Uint8));
    statefile->write((char *)(mapReg), sizeof(Uint8) * 8);
    statefile->write((char *)(&lastPrgRead), sizeof(Uint32));
    statefile->write((char *)(&irqEnabled), sizeof(bool));
    statefile->write((char *)(&irqValue), sizeof(Uint8));
    statefile->write((char *)(&irqCounter), sizeof(Uint8));
    statefile->write((char *)(&irqFlag), sizeof(bool));
    statefile->write((char *)(&scanlineNo), sizeof(int));

    for (int i = 0; i < 8; ++i) {
        offset = chrPtr[i] - romDat->chrROM;
        statefile->write((char *)(&offset), sizeof(Uint32));
    }
    for (int i = 0; i < 4; ++i) {
        offset = prgPtr[i] - romDat->prgROM;
        statefile->write((char *)(&offset), sizeof(Uint32));
    }
}


void mapper4::loadState(fstream* statefile){
    Uint32 offset;

    statefile->read((char *)(&chrMask), sizeof(Uint16));
    statefile->read((char *)(&chrSwitchMask), sizeof(Uint16));
    statefile->read((char *)(&prgSwitchMask), sizeof(Uint16));
    statefile->read((char *)(&chrMode), sizeof(Uint8));
    statefile->read((char *)(&prgMode), sizeof(Uint8));
    statefile->read((char *)(&regAddress), sizeof(Uint8));
    statefile->read((char *)(mapReg), sizeof(Uint8) * 8);
    statefile->read((char *)(&lastPrgRead), sizeof(Uint32));
    statefile->read((char *)(&irqEnabled), sizeof(bool));
    statefile->read((char *)(&irqValue), sizeof(Uint8));
    statefile->read((char *)(&irqCounter), sizeof(Uint8));
    statefile->read((char *)(&irqFlag), sizeof(bool));
    statefile->read((char *)(&scanlineNo), sizeof(int));
	
	for (int i = 0; i < 8; ++i) {
        statefile->read((char *)(&offset), sizeof(Uint32));
        chrPtr[i] = &(romDat->chrROM[offset]);
    }
    for (int i = 0; i < 4; ++i) {
        statefile->read((char *)(&offset), sizeof(Uint32));
		prgPtr[i] = &(romDat->prgROM[offset]);
    }
    setMirroring();
	setBankSwitching();
}

void mapper4::runCatchUp(unsigned int cycle){
}

void mapper4::resetCycleCount(){
}