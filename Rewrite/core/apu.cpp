#include "apu.h"

apu::apu()
{
    //ctor
}

apu::~apu()
{
    //dtor
}

Uint8 apu::readReg(Uint8 idx){
    return registers[idx];
}

void apu::writeReg(Uint8 idx, Uint8 value){
    registers[idx] = value;
}

void apu::reset(){
}

void apu::saveState(fstream* statefile){
}

void apu::loadState(fstream* statefile){
}


