#include "ppu.h"

ppu::ppu()
{
    //ctor
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

void ppu::reset(){
}

void ppu::saveState(fstream* statefile){
}

void ppu::loadState(fstream* statefile){
}

