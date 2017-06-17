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
    registers[idx] = value;
}

Uint8 ppu::read4014(){
}

void ppu::write4014(Uint8 value){
}

void ppu::runCycle(){
}



void ppu::reset(){
}

void ppu::saveState(fstream* statefile){
}

void ppu::loadState(fstream* statefile){
}

void ppu::init(){
}

void ppu::init2(){
}
