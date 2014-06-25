#include "StdAfx.h"
#include "memory.h"
#include "sysState.h"


memory::memory(void)
{
}


memory::~memory(void)
{
}

Uint8 memory::cpuBusRead(Uint16 address){
	return cpuBusRead(address, false);
}

Uint8 memory::cpuBusRead(Uint16 address, bool opRead){
	if(address < 0x2000){
		return cpuRAM[address & 0x07FF];
	}
	else if(address < 0x4000){
		return ppuCore->readReg(address & 0x0007);
	}
	else if(address < 0x4016){
		if(address != 0x4014){
			return apuCore->readReg(address & 0x001F);
		}
		else{
			return 0;
		}
	}
	else if(address < 0x4018){
		return inputCore->readReg(address & 0x001F);
	}
	else if(address < 0x4020){
		return ppuCore->readReg(address - 0x17);
	}
	else{
		return mmc->readCPUData(address, opRead);
	}
}

void memory::cpuBusWrite(Uint16 address, Uint8 data){
	if(address < 0x2000){
		cpuRAM[address & 0x07FF] = mixer->handleRAMWrite(address, data);
	}
	else if(address < 0x4000){
		ppuCore->writeReg(address & 0x0007, data);
	}
	else if(address < 0x4016){
		if(address != 0x4014){
			apuCore->writeReg(address & 0x001F, data);
		}
		else{
			ppuCore->transferDMA(data);
		}
	}
	else if(address < 0x4017){
		inputCore->writeReg(address & 0x001F, data);
	}
	else if(address < 0x4018){
		apuCore->writeReg(address & 0x001F, data);
	}
	else if(address < 0x4020){
		ppuCore->writeReg(address - 0x17, data);
	}
	else{
		mmc->writeCPUData(address, data);
	}
}

void memory::cpuBusInit(){
	memset(cpuRAM, 0x00, 0x800);
	cpuRAM[0x008] = 0xF7;
	cpuRAM[0x009] = 0xEF;
	cpuRAM[0x00A] = 0xDF;
	cpuRAM[0x00F] = 0xBF;
	bgColourID = 0;
}



Uint8 memory::ppuBusRead(Uint16 address){
	Uint8 tableID;
	Uint16 tmpAddress;
	if(address < 0x2000){
		return mmc->readPPUData(address);
	}
	else if(address < 0x3F00){
		//0x2?00 => 10YX0000000000 => [X][Y]
		//0x3?00 => 11YX0000000000 => [X][Y]
		tableID = nameTableMirroring[(address & 0x0400) >> 10][(address & 0x0800) >> 11];
		tmpAddress = address & 0x03FF;
		if(tmpAddress < 0x03C0){
			return nameTable[tableID][tmpAddress];
		}
		else{
			return attributeTable[tableID][tmpAddress & 0x003F];
		}
	}
	else if(address < 0x4000){
		return paletteTable[(address & 0x001C) >> 2][address & 0x0003];
	}
	else{
		return 0;
	}
}

void memory::ppuBusWrite(Uint16 address, Uint8 data){
	Uint8 tableID;
	Uint16 tmpAddress;
	if(address < 0x2000){
		mmc->writePPUData(address, data);
	}
	else if(address < 0x3F00){
		//0x2?00 => 10YX0000000000 => [X][Y]
		//0x3?00 => 11YX0000000000 => [X][Y]
		tableID = nameTableMirroring[(address & 0x0400) >> 10][(address & 0x0800) >> 11];
		tmpAddress = address & 0x03FF;
		if(tmpAddress < 0x03C0){
			nameTable[tableID][tmpAddress] = data;
		}
		else{
			attributeTable[tableID][tmpAddress & 0x003F] = data;
		}
	}
	else if(address < 0x4000){
		if((address & 0x000F) == 0) bgColourID = data;
		if((address & 0x0003) == 0){
			//mirroring
			paletteTable[(address & 0x000C) >> 2][0] = data;
			paletteTable[((address & 0x000C) | 0x0010) >> 2][0] = data;
		}
		else{
			paletteTable[(address & 0x001C) >> 2][address & 0x0003] = data;
		}
	}
}

void memory::saveState(fstream* statefile){
    statefile->write((char *)(this), sizeof(memory));
}


void memory::loadState(fstream* statefile){
    statefile->read((char *)(this), sizeof(memory));
}
