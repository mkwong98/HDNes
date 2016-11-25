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

Uint8 apu::read4015(){
}

void apu::write4015(Uint8 value){
}

void apu::runCycle(){
}

void apu::reset(){
}

void apu::saveState(fstream* statefile){
}

void apu::loadState(fstream* statefile){
}

void apu::init(){
}


