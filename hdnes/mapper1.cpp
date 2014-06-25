#include "StdAfx.h"
#include "mapper1.h"
#include "sysState.h"

mapper1::mapper1(void)
{
	if(romDat->mirrorV){
		reg[0] = 0x02;
	}
	else{
		reg[0] = 0x03;
	}
	setMirroring();
	writeNum = 0;
	writeRegBuffer = 0;
	chr8KMode = false;
	prg32KMode = false;
	slotCSwap = false;
	chrReg0 = 0;
	chrReg1 = 0;
	prgReg = 0;
	wramDisable = false;
	setBankSwitching();
}


mapper1::~mapper1(void)
{
}

void mapper1::setMirroring(){
	switch(reg[0] & 0x03){
	case 0x00:
		memDat->nameTableMirroring[0][0] = 0;
		memDat->nameTableMirroring[0][1] = 0;
		memDat->nameTableMirroring[1][0] = 0;
		memDat->nameTableMirroring[1][1] = 0;
		break;
	case 0x01:
		memDat->nameTableMirroring[0][0] = 1;
		memDat->nameTableMirroring[0][1] = 1;
		memDat->nameTableMirroring[1][0] = 1;
		memDat->nameTableMirroring[1][1] = 1;
		break;
	case 0x02:
		memDat->nameTableMirroring[0][0] = 0;
		memDat->nameTableMirroring[0][1] = 0;
		memDat->nameTableMirroring[1][0] = 1;
		memDat->nameTableMirroring[1][1] = 1;
		break;
	case 0x03:
		memDat->nameTableMirroring[0][0] = 0;
		memDat->nameTableMirroring[0][1] = 1;
		memDat->nameTableMirroring[1][0] = 0;
		memDat->nameTableMirroring[1][1] = 1;
		break;
	}
}

void mapper1::setBankSwitching(){
    Uint8 tmpReg;
	if(romDat->chrPageCount > 0){
		if(chr8KMode){
			tmpReg = chrReg0 & 0xFE;
            chrPtr[0] = &(romDat->chrROM[tmpReg << 12]);
            chrPtr[1] = &(romDat->chrROM[(tmpReg + 1) << 12]);
		}
		else{
            chrPtr[0] = &(romDat->chrROM[chrReg0 << 12]);
            chrPtr[1] = &(romDat->chrROM[chrReg1 << 12]);
		}
	}
	else{
		chrPtr[0] = &(romDat->chrRAM[0]);
		chrPtr[1] = &(romDat->chrRAM[0x1000]);
	}
	if(prg32KMode){
		prgPtr[0] = &(romDat->prgROM[(prgReg & 0xFE) << 14]);
		prgPtr[1] = &(romDat->prgROM[((prgReg & 0xFE) + 1) << 14]);
	}
	else{
		if(slotCSwap){
			prgPtr[0] = &(romDat->prgROM[0]);
			prgPtr[1] = &(romDat->prgROM[prgReg << 14]);
		}
		else{
			prgPtr[0] = &(romDat->prgROM[prgReg << 14]);
			if(romDat->prgPageCount <= 15){
				prgPtr[1] = &(romDat->prgROM[(romDat->prgPageCount - 1) << 14]); 
			}
			else{
				prgPtr[1] = &(romDat->prgROM[0x3C000]); 
			}
		}
	}
}


void mapper1::writeCPUData(Uint16 address, Uint8 data){
	Uint8 regID;
	if(address >= 0x6000){
		if(address < 0x8000){  
			if(!wramDisable){
                romDat->batDat[address & 0x1FFF] = data;
                if(romDat->useBat)romDat->batChanged = true;
            }
		}
		else{
			if(data & 0x80){
				writeNum = 0;
				writeRegBuffer = 0;
				reg[0] = reg[0] | 0x0c;
				writeReg0(reg[0]);
				setBankSwitching();
			}
			else{
				if(writeNum < 5){
					writeRegBuffer = writeRegBuffer | ((data & 0x01) << writeNum);
					++writeNum;
					if(writeNum == 5){
						regID = (address >> 13) & 0x03;
						reg[regID] = writeRegBuffer;

						switch(regID){
						case 0:
							writeReg0(writeRegBuffer);
							break;
						case 1:
							writeReg1(writeRegBuffer);
							break;
						case 2:
							writeReg2(writeRegBuffer);
							break;
						case 3:
							writeReg3(writeRegBuffer);
							break;
						}
						setBankSwitching();
						writeNum = 0;
						writeRegBuffer = 0;
					}
				}
			}
		}
	}
}

void mapper1::writeReg0(Uint8 data){
	setMirroring();
	chr8KMode = ((data & 0x10) == 0);
	prg32KMode = ((data & 0x08) == 0);
	slotCSwap = ((data & 0x04) == 0);
}

void mapper1::writeReg1(Uint8 data){
	chrReg0 = data & 0x1F;
}

void mapper1::writeReg2(Uint8 data){
	chrReg1 = data & 0x1F;
}

void mapper1::writeReg3(Uint8 data){
	wramDisable = ((data & 0x10) != 0);
	prgReg = data & 0x0F;
}


Uint8 mapper1::readCPUData(Uint16 address, bool opRead){
	Uint8 bank;
	if(address >= 0x6000){
		if(address < 0x8000){
			if(!wramDisable) return romDat->batDat[address & 0x1FFF];
		}
		else{
			bank = ((address & 0x7FFF) >> 14);
            if(opRead) lastPrgRead = &(prgPtr[bank][address & 0x3FFF]) - romDat->prgROM;
			return prgPtr[bank][address & 0x3FFF];
		}
	}
	return 0;
}

void mapper1::writePPUData(Uint16 address, Uint8 data){
	if(address < 0x2000){
		if(romDat->chrPageCount == 0){
			romDat->chrRAM[address] = data;
			if(lastPrgRead != BAD_ADDRESS)
	            romDat->chrRAMAddress[address >> 4] = lastPrgRead >> 4;
		}
	}
}

Uint8 mapper1::readPPUData(Uint16 address){
	Uint8 bank;
	if(address < 0x2000){
		bank = (address >> 12);
		if(romDat->chrPageCount > 0){
			return chrPtr[bank][address & 0x0FFF];
		}
		else{
			return romDat->chrRAM[address];
		}
	}
	return 0;
}

void mapper1::getPattern(Uint16 address, Uint8 row, bool isFirst, Uint8& data, Uint32& patternAddress, Uint32& ramAddress){
	Uint16 tmpAddress;
	Uint32 realAddress;
	Uint8 bank;
	tmpAddress = address;
	if(row >= 8){ 
		tmpAddress += 16;
		row -= 8;
	}

	if(!isFirst) tmpAddress += 8;
	if(romDat->chrPageCount > 0){
		bank = (tmpAddress >> 12);
		data = chrPtr[bank][(tmpAddress + row) & 0x0FFF];
		realAddress = &(chrPtr[bank][(tmpAddress + row) & 0x0FFF]) - romDat->chrROM;
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

void mapper1::saveState(fstream* statefile){
    Uint32 offset;

    statefile->write((char *)(&writeRegBuffer), sizeof(Uint8));
    statefile->write((char *)(&writeNum), sizeof(Uint8));
    statefile->write((char *)(reg), sizeof(Uint8) * 4);
    statefile->write((char *)(&chr8KMode), sizeof(boolean));
    statefile->write((char *)(&prg32KMode), sizeof(boolean));
    statefile->write((char *)(&slotCSwap), sizeof(boolean));
    statefile->write((char *)(&chrReg0), sizeof(Uint8));
    statefile->write((char *)(&chrReg1), sizeof(Uint8));
    statefile->write((char *)(&wramDisable), sizeof(boolean));
    statefile->write((char *)(&prgReg), sizeof(Uint8));
    statefile->write((char *)(&lastPrgRead), sizeof(Uint32));

    offset = chrPtr[0] - romDat->chrROM;
    statefile->write((char *)(&offset), sizeof(Uint32));
    offset = chrPtr[1] - romDat->chrROM;
    statefile->write((char *)(&offset), sizeof(Uint32));
    offset = prgPtr[0] - romDat->prgROM;
    statefile->write((char *)(&offset), sizeof(Uint32));
    offset = prgPtr[1] - romDat->prgROM;
    statefile->write((char *)(&offset), sizeof(Uint32));
}


void mapper1::loadState(fstream* statefile){
    Uint32 offset;

	statefile->read((char *)(&writeRegBuffer), sizeof(Uint8));
    statefile->read((char *)(&writeNum), sizeof(Uint8));
    statefile->read((char *)(reg), sizeof(Uint8) * 4);
    statefile->read((char *)(&chr8KMode), sizeof(boolean));
    statefile->read((char *)(&prg32KMode), sizeof(boolean));
    statefile->read((char *)(&slotCSwap), sizeof(boolean));
    statefile->read((char *)(&chrReg0), sizeof(Uint8));
    statefile->read((char *)(&chrReg1), sizeof(Uint8));
    statefile->read((char *)(&wramDisable), sizeof(boolean));
    statefile->read((char *)(&prgReg), sizeof(Uint8));
    statefile->read((char *)(&lastPrgRead), sizeof(Uint32));
	
	statefile->read((char *)(&offset), sizeof(Uint32));
    chrPtr[0] = &(romDat->chrROM[offset]);
    statefile->read((char *)(&offset), sizeof(Uint32));
    chrPtr[1] = &(romDat->chrROM[offset]);
    statefile->read((char *)(&offset), sizeof(Uint32));
	prgPtr[0] = &(romDat->prgROM[offset]);
    statefile->read((char *)(&offset), sizeof(Uint32));
	prgPtr[1] = &(romDat->prgROM[offset]);

	setMirroring();
	setBankSwitching();

}

void mapper1::runCatchUp(unsigned int cycle){
}

void mapper1::resetCycleCount(){
}
