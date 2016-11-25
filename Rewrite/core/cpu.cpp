#include "cpu.h"
#include "memBus.h"
#include "../gameManager.h"

cpu::cpu()
{
}

cpu::~cpu()
{
    //dtor
}

Uint8 cpu::getNextInstructionLength(){

}

void cpu::runInstruction(){
}


void cpu::reset(){
    stackPointer -= 3;
    statusRegister |= 0x04;
    programCounter = ((mb->memRead(0xFFFD) << 8) | mb->memRead(0xFFFC));
}

void cpu::saveState(fstream* statefile){
}

void cpu::loadState(fstream* statefile){
}

void cpu::init(){
    mb = gameManager::gm->mb;
    statusRegister = 0x34;
    accumulator = 0;
    indexX = 0;
    indexY = 0;
    stackPointer = 0xFD;
    programCounter = ((mb->memRead(0xFFFD) << 8) | mb->memRead(0xFFFC));

}

