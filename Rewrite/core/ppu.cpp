#include "ppu.h"
#include "cpu.h"
#include "../gameManager.h"


ppu::ppu(){
    frameReady = false;
    isRendering = false;
}

ppu::~ppu()
{
    //dtor
}

Uint8 ppu::readReg(Uint8 idx){
    if(idx == REG_PPUSTATUS){
        //only read bit 5-7
        busValue = (busValue & 0x1F) | (registers[idx] & 0xE0);
        //clear flag 7
        registers[idx] = registers[idx] & 0x7F;
    }
    else if(idx == REG_OAMDATA || idx == REG_PPUDATA){
        busValue = registers[idx];
    }
    return busValue;
}

void ppu::writeReg(Uint8 idx, Uint8 value){
    //skip for certain reg when not ready
    if(bootUpCycles && idx == REG_PPUCTRL) return;
    busValue = value;
    if(idx == REG_PPUCTRL || idx == REG_PPUMASK || idx == REG_OAMADDR || idx == REG_PPUSCROLL || idx == REG_PPUADDR || idx == REG_PPUDATA){
        registers[idx] = value;
    }
    else if(idx == REG_OAMDATA){
        oam[registers[REG_OAMADDR]] = busValue;
        ++(registers[REG_OAMADDR]);
    }
}

Uint8 ppu::read4014(){
}

void ppu::write4014(Uint8 value){
}

void ppu::runCycle(){
    if(bootUpCycles) --bootUpCycles;




    //rendering
    if(renderingY < 240){
        //pre render scan line
    }
    else if(renderingY == 241){
        if(renderingX == 1 && (registers[REG_PPUCTRL] & 0x80)){
            cp->pullNMILow();
        }
    }
    else if(renderingY == 261){
        if(renderingX == 1){
            //clear top 3 bits
            registers[REG_PPUSTATUS] = registers[REG_PPUSTATUS] & 0x1F;
        }
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
