#include "memBus.h"
#include "../gameManager.h"
#include "cart.h"
#include "cpu.h"
#include "ppu.h"
#include "apu.h"
#include "gamepad.h"


memBus::memBus()
{
}

memBus::~memBus()
{
    //dtor
}

Uint8 memBus::memRead(Uint16 address){
	if(address < 0x2000){
		return internalRAM[address & 0x07FF];
	}
    else if(address < 0x4000){
        return pp->readReg(address & 0x0007);
    }
    else if(address < 0x4014){
        return ap->readReg(address & 0x0013);
    }
    else if(address == 0x4014){
        return pp->read4014();
    }
    else if(address == 0x4015){
        return ap->read4015();
    }
    else if(address == 0x4016){
        return gp->read4016();
    }
    else if(address == 0x4017){
        return gp->read4017();
    }
    else if(address >= 0x4020){
        return rom->readPRGData(address);
    }
}

void memBus::memWrite(Uint16 address, Uint8 value){
}

Uint8 memBus::ppuRead(Uint16 address){
	if(address < 0x2000){
		return rom->readCHRData(address);
	}
    else if(address < 0x3F00){
        return rom->readNameTable(address);
    }
    else{
        return pp->paletteTable[address & 0x001F];
    }
}

void memBus::ppuWrite(Uint16 address, Uint8 value){
}


void memBus::reset(){
}

void memBus::saveState(fstream* statefile){
}

void memBus::loadState(fstream* statefile){
}

void memBus::init(){
    rom = gameManager::gm->rom;
    cp = gameManager::gm->cp;
    pp = gameManager::gm->pp;
    ap = gameManager::gm->ap;
    gp = gameManager::gm->gp;
}

void memBus::init2(){
    for(int i = 0; i < 0x800; ++i){
        internalRAM[i] = rand() % 0x100;
    }
}
