#include "StdAfx.h"
#include "mapper16.h"
#include "sysState.h"


mapper16::mapper16(void)
{
    for (int i = 0; i < 8; ++i) {
        reg[i] = 0;
    }
    reg[0x8] = 0;
    reg[0x9] = 0;
    reg[0xA] = 0;
    reg[0xB] = 0;
    reg[0xC] = 0;
    reg[0xD] = 0;
    reg[0xE] = 0;
    reg[0xF] = 0;
	curCycle = 0;
    irqEnabled = false;
	irqFlag = false;
    
    eepromLines = 0;
    eepromMode = EEPROM_STANDBY;
    eepromType = EEPROM_TYPE_UNKNOWN;

    setMirroring();
	setBankSwitching();
}


mapper16::~mapper16(void)
{
}

void mapper16::setMirroring(){
    switch (reg[9] & 0x03) {
        case 0:
			memDat->nameTableMirroring[0][0] = 0;
			memDat->nameTableMirroring[0][1] = 0;
			memDat->nameTableMirroring[1][0] = 1;
			memDat->nameTableMirroring[1][1] = 1;
            break;
        case 1:
			memDat->nameTableMirroring[0][0] = 0;
			memDat->nameTableMirroring[0][1] = 1;
			memDat->nameTableMirroring[1][0] = 0;
			memDat->nameTableMirroring[1][1] = 1;
            break;
        case 2:
			memDat->nameTableMirroring[0][0] = 0;
			memDat->nameTableMirroring[0][1] = 0;
			memDat->nameTableMirroring[1][0] = 0;
			memDat->nameTableMirroring[1][1] = 0;
            break;
        case 3:
			memDat->nameTableMirroring[0][0] = 1;
			memDat->nameTableMirroring[0][1] = 1;
			memDat->nameTableMirroring[1][0] = 1;
			memDat->nameTableMirroring[1][1] = 1;
            break;
        default:
            break;
    }
}


void mapper16::setBankSwitching(){
    for (int i = 0; i < 8; ++i) {
        chrPtr[i] = &(romDat->chrROM[reg[i] << 10]);
    }
    prgPtr[0] = &(romDat->prgROM[reg[8] << 14]);
    prgPtr[1] = &(romDat->prgROM[(romDat->prgPageCount - 1) << 14]);
}


void mapper16::writeCPUData(Uint16 address, Uint8 data){
	Uint16 writeAddress;
	if(address >= 0x6000){
        writeAddress = address & 0x000F;
        reg[writeAddress] = data;
        switch(writeAddress){
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
	            setBankSwitching();
				break;
			case 9:
               setMirroring();
				break;
			case 0x0A:
                irqFlag = false;
                if (data & 0x01) {
                    irqEnabled = true;
                }
                else{
                    irqEnabled = false;
                }
				break;
			case 0x0B:
                irqCounter = (irqCounter & 0xFF00) | data;
                break;
			case 0x0C:
                irqCounter = (irqCounter & 0x00FF) | (data << 8);
                break;
            case 0x0D:
                handleEEPROMWrite();
                break;
        }
	}
}

Uint8 mapper16::readCPUData(Uint16 address, bool opRead){
	Uint16 bank;
	bank = (address >> 14) & 0x01;
	if(address >= 0x8000){
        if(opRead) lastPrgRead = &(prgPtr[bank][address & 0x3FFF]) - romDat->prgROM;
		return prgPtr[bank][address & 0x3FFF];
	}
	else if(address >= 0x6000){
        if (eepromMode == EEPROM_OUTPUT && bitCounter <= 8 && (reg[0xD] & 0xE0)) {
			if(eepromType == EEPROM_TYPE_256)
	            return (eepromRead & (0x80 >> bitCounter) ? 0x10 : 0x00);
			else
				return (eepromRead & (0x01 << bitCounter) ? 0x10 : 0x00);
        }
        else{
            return 0;
        }
	}
	else{
		return 0;
	}
}

void mapper16::writePPUData(Uint16 address, Uint8 data){
	if(address < 0x2000){
		if(romDat->chrPageCount == 0){
			romDat->chrRAM[address] = data;
			if(lastPrgRead != BAD_ADDRESS)
	            romDat->chrRAMAddress[address >> 4] = lastPrgRead >> 4;
		}
	}
}

Uint8 mapper16::readPPUData(Uint16 address){
	Uint16 bank;
	bank = (address >> 10) & 0x07;
	if(romDat->chrPageCount > 0){
		return chrPtr[bank][address & 0x3FF];
	}
	else{
		return romDat->chrRAM[address];
	}
}

void mapper16::getPattern(Uint16 address, Uint8 row, bool isFirst, Uint8& data, Uint32& patternAddress, Uint32& ramAddress){
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

}

void mapper16::saveState(fstream* statefile){
    Uint32 offset;
    //statefile->write((char *)(this), sizeof(mapper16));

    statefile->write((char *)(reg), sizeof(Uint8)*16);
    statefile->write((char *)(&lastPrgRead), sizeof(Uint32));
    statefile->write((char *)(&curCycle), sizeof(Uint32));
    statefile->write((char *)(&irqCounter), sizeof(Uint16));
    statefile->write((char *)(&irqEnabled), sizeof(bool));
    statefile->write((char *)(&irqFlag), sizeof(bool));
    statefile->write((char *)(&eepromMode), sizeof(Uint8));
    statefile->write((char *)(&eepromLines), sizeof(Uint8));
    statefile->write((char *)(&eepromAddress), sizeof(Uint8));
    statefile->write((char *)(&bitCounter), sizeof(Uint8));
    statefile->write((char *)(&eepromTemp), sizeof(Uint8));
    statefile->write((char *)(&eepromIsReading), sizeof(bool));
    statefile->write((char *)(&eepromRead), sizeof(Uint8));
    statefile->write((char *)(&eepromType), sizeof(Uint8));
 
    for (int i = 0; i < 8; ++i) {
        offset = chrPtr[i] - romDat->chrROM;
        statefile->write((char *)(&offset), sizeof(Uint32));
    }
    for (int i = 0; i < 2; ++i) {
        offset = prgPtr[i] - romDat->prgROM;
        statefile->write((char *)(&offset), sizeof(Uint32));
    }
}


void mapper16::loadState(fstream* statefile){
    Uint32 offset;

    statefile->read((char *)(reg), sizeof(Uint8)*16);
    statefile->read((char *)(&lastPrgRead), sizeof(Uint32));
    statefile->read((char *)(&curCycle), sizeof(Uint32));
    statefile->read((char *)(&irqCounter), sizeof(Uint16));
    statefile->read((char *)(&irqEnabled), sizeof(bool));
    statefile->read((char *)(&irqFlag), sizeof(bool));
    statefile->read((char *)(&eepromMode), sizeof(Uint8));
    statefile->read((char *)(&eepromLines), sizeof(Uint8));
    statefile->read((char *)(&eepromAddress), sizeof(Uint8));
    statefile->read((char *)(&bitCounter), sizeof(Uint8));
    statefile->read((char *)(&eepromTemp), sizeof(Uint8));
    statefile->read((char *)(&eepromIsReading), sizeof(bool));
    statefile->read((char *)(&eepromRead), sizeof(Uint8));
    statefile->read((char *)(&eepromType), sizeof(Uint8));


    for (int i = 0; i < 8; ++i) {
        statefile->read((char *)(&offset), sizeof(Uint32));
        chrPtr[i] = &(romDat->chrROM[offset]);
     }
    for (int i = 0; i < 2; ++i) {
        statefile->read((char *)(&offset), sizeof(Uint32));
		prgPtr[i] = &(romDat->prgROM[offset]);
    }
    setMirroring();
	setBankSwitching();
}


void mapper16::runCatchUp(unsigned int cycle){
	if (irqEnabled) {
        for (unsigned int i = 0; i < cycle - curCycle; ++i) {
            if (irqCounter > 0) {
                --irqCounter;
                if (irqCounter == 0) {
                    irqFlag = true;
                }
            }
            else{
                irqCounter = 0xFFFF;
            }
        }
    }
	if(irqFlag){
		cpuCore->setIRQ();
	}
	curCycle = cycle;
}

void mapper16::resetCycleCount(){
	curCycle = 0;
}


void mapper16::handleEEPROMWrite(){
    /*
     Data out = bit 4
     SCL = bit 5
     SDA = bit 6
     R/W = bit 7 (1 = read, 0 = write)
    */

    if ((eepromLines & reg[0xD] & 0x20) && (eepromLines & 0x40) && (!(reg[0xD] & 0x40))) {
        //11 -> 01
        eepromMode = EEPROM_STANDBY_END;
        bitCounter = 0;
        eepromTemp = 0;
    }

    if (eepromMode != EEPROM_STANDBY) {
        if ((eepromLines & reg[0xD] & 0x20) && (!(eepromLines & 0x40)) && (reg[0xD] & 0x40)) {
            //10 -> 11
            eepromMode = EEPROM_STANDBY;
        }
        else{
			if ((eepromLines & 0x20) && !(reg[0xD] & 0x20)){
				//?1 -> ?0
				if (eepromMode == EEPROM_STANDBY_END){
					eepromMode = EEPROM_RW_SELECT;
				}
				else if(bitCounter < 8){
					if(eepromMode != EEPROM_OUTPUT){
						if(eepromType == EEPROM_TYPE_UNKNOWN || eepromType == EEPROM_TYPE_256)
							eepromTemp = eepromTemp | (reg[0xD] & 0x40 ? 0x80 >> bitCounter : 0);
						else
							eepromTemp = eepromTemp | (reg[0xD] & 0x40 ? 0x01 << bitCounter : 0);
						++bitCounter;
					}
					else
						if(reg[0xD] & 0x40)
							++bitCounter;
				}
				else{
					++bitCounter;
				}
				if(bitCounter == 9){
					if(eepromType == EEPROM_TYPE_UNKNOWN){
						if((eepromTemp & 0xF0) == 0xA0){
							eepromType = EEPROM_TYPE_256;
						}
						else{
							eepromType = EEPROM_TYPE_128;
							Uint8 reverseTemp = 0;
							for(int i = 0; i < 8; ++i){
								//reverse the byte
								reverseTemp = reverseTemp |(((eepromTemp >> i) & 0x01) << (7 - i));
							}
							eepromTemp = reverseTemp;
						}
					}
					switch (eepromMode){
					case EEPROM_RW_SELECT:
						if(eepromType == EEPROM_TYPE_256){
							eepromIsReading = ((eepromTemp & 0x01) != 0);
							eepromMode = (eepromIsReading ? EEPROM_OUTPUT : EEPROM_WAIT_ADDRESS);
						}
						else{
							eepromIsReading = ((eepromTemp & 0x80) != 0);
							eepromAddress = eepromTemp & 0x7F;
							eepromMode = (eepromIsReading ? EEPROM_OUTPUT : EEPROM_WAIT_DATA);
						}
						if(eepromIsReading) 
							eepromRead = romDat->batDat[eepromAddress & 0xFF];
						break;
					case EEPROM_WAIT_ADDRESS:
						eepromAddress = eepromTemp;
						eepromMode = EEPROM_WAIT_DATA;
						break;
                    case EEPROM_WAIT_DATA:
                        romDat->batDat[eepromAddress & 0xFF] = eepromTemp;
                        romDat->batChanged = true;
						//can only move the last 3 bits, can't change page
						eepromAddress = (eepromAddress & 0xF8) | ((eepromAddress + 1) & 0x7);
						break;
					case EEPROM_OUTPUT:
						++eepromAddress;
						eepromRead = romDat->batDat[eepromAddress & 0xFF];
					}
					bitCounter = 0;
					eepromTemp = 0;
				}
			}
        }
    }
    eepromLines = reg[0xD];
}
