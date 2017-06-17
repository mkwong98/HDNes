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
    return instructionTicks;
    /*
    if(nextInstruction[0] & 0x03 == 0x01){
        Uint8 pattern = (nextInstruction[0] >> 3) & 0x07;
        return instructionLen[pattern] + extraCycleReq;
    }
    else if(nextInstruction[0] & 0x1F == 0x10){
        return 2 + extraCycleReq;
    }
    else{

    }
    */
}

void cpu::processInstruction(){
    newState = state;
    nextInstruction[0] = mb->memRead(state.programCounter);
    if(nextInstruction[0] & 0x07 == 0x07){
        ++newState.programCounter;
        instructionType = OP_TYPE_NOP;
        instructionTicks = 2;
    }
    else if(nextInstruction[0] & 0x03 == 0x01){
        ++newState.programCounter;
        instructionType = OP_TYPE_CPU;
        Uint8 addressMode = (nextInstruction[0] >> 3) & 0x07;
        instructionTicks = instructionLen[addressMode];

    }

}

void cpu::runInstruction(){
    switch(instructionType){
    case OP_TYPE_NOP:
        state = newState;
        break;
    }
}


void cpu::reset(){
    state.stackPointer -= 3;
    state.statusRegister |= 0x04;
    state.programCounter = ((mb->memRead(0xFFFD) << 8) | mb->memRead(0xFFFC));
}

void cpu::saveState(fstream* statefile){
}

void cpu::loadState(fstream* statefile){
}

void cpu::init(){
    mb = gameManager::gm->mb;
}

void cpu::init2(){
    state.statusRegister = 0x34;
    state.accumulator = 0;
    state.indexX = 0;
    state.indexY = 0;
    state.stackPointer = 0xFD;
    state.programCounter = ((mb->memRead(0xFFFD) << 8) | mb->memRead(0xFFFC));
}
