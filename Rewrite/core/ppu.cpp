#include "ppu.h"

ppu::ppu(){
    frameReady = false;
}

ppu::~ppu()
{
    //dtor
}

Uint8 ppu::readReg(Uint8 idx){
    return registers[idx];
}

void ppu::writeReg(Uint8 idx, Uint8 value){
    //skip for certain reg when not ready
    if(bootUpCycles && idx == REG_PPUCTRL) return;

    registers[idx] = value;
}

Uint8 ppu::read4014(){
}

void ppu::write4014(Uint8 value){
}

void ppu::runCycle(){
    if(bootUpCycles) --bootUpCycles;

    if(renderingY == 241 && renderingX == 1 && (registers[REG_PPUCTRL] & 0x80){
        cp->pullNMILow();
    }

    //update x and y at the end of cycle
    if(renderingX == 339 && renderingY == 261 && oddFrame) ++renderingX;
    if(renderingX == 340){
        renderingX = 0;
        if(renderingY == 261){
            renderingY = 0;
            oddFrame = !oddFrame;
        }
        else{
            ++renderingY;
        }
    }
    else{
        ++renderingX;
    }

}



void ppu::reset(){
}

void ppu::saveState(fstream* statefile){
}

void ppu::loadState(fstream* statefile){
}

void ppu::init(){
    mb = gameManager::gm->mb;
    cp = gameManager::gm->cp;
}

void ppu::init2(){
    registers[REG_PPUCTRL] = 0;
    registers[REG_PPUMASK] = 0;
    registers[REG_PPUSTATUS] = 0xA0;
    registers[REG_OAMADDR] = 0x00;
    addressLatch = 0x00;
    registers[REG_PPUSCROLL] = 0x00;
    registers[REG_PPUADDR] = 0x00;
    registers[REG_PPUDATA] = 0x00;
    oddFrame = false;
    bootUpCycles = 29658;
    renderingX = 0;
    renderingY = 0;
}
