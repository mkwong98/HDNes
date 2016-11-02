#include "memBus.h"
#include "../gameManager.h"
#include "cart.h"
#include "cpu.h"
#include "ppu.h"
#include "apu.h"

memBus::memBus()
{
    rom = gameManager::gm->rom;
    cp = gameManager::gm->cp;
    pp = gameManager::gm->pp;
    ap = gameManager::gm->ap;
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
        return ap->readReg(address & 0x0013);
    }
    else if(address == 0x4015){
        return ap->readReg(address & 0x0013);
    }
}

void memBus::reset(){
}

void memBus::saveState(fstream* statefile){
}

void memBus::loadState(fstream* statefile){
}


