#include "cpu.h"
#include "memBus.h"
#include "../gameManager.h"

cpu::cpu()
{
    instructionLen[0] = 6;
    instructionLen[1] = 3;
    instructionLen[2] = 2;
    instructionLen[3] = 4;
    instructionLen[4] = 5;
    instructionLen[5] = 4;
    instructionLen[6] = 4;
    instructionLen[7] = 4;
}

cpu::~cpu()
{
    //dtor
}

Uint8 cpu::getNextInstructionLength(){
    nextInstruction[0] = mb->memRead(programCounter);
    ++programCounter;
    nextInstruction[1] = mb->memRead(programCounter);
    ++programCounter;

    if(nextInstruction[0] & 0x03 == 0x01){
        Uint8 pattern = (nextInstruction[0] >> 3) & 0x07;
        return instructionLen[pattern] + (hasExtraCycle() ? 1 : 0);
    }
    else if(nextInstruction[0] & 0x1F == 0x10){
        return 2;
    }
    else{

    }
}

void cpu::runInstruction(){
    extraCycleReq = false;
}

bool cpu::hasExtraCycle(){
    return extraCycleReq;
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

