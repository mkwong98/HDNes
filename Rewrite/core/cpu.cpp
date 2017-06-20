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

    flagMask[0] = 0x01;
    flagMask[1] = 0x02;
    flagMask[2] = 0x04;
    flagMask[3] = 0x08;
    flagMask[4] = 0x10;
    flagMask[5] = 0x20;
    flagMask[6] = 0x40;
    flagMask[7] = 0x80;
}

cpu::~cpu()
{
    //dtor
}

Uint8 cpu::getNextInstructionLength(){
    return instructionTicks;
}

void cpu::processInstruction(){
    newState = state;
    nextInstruction[0] = mb->memRead(newState.programCounter);
    ++newState.programCounter;
    if((nextInstruction[0] & 0x07) == 0x07){
        instructionType = OP_TYPE_NOP;
        instructionTicks = 2;
    }
    else if((nextInstruction[0] & 0x03) == 0x01){
        bool pageCrossed;
        //PPPAAA01 accumulator ops
        Uint8 addressMode = (nextInstruction[0] >> 2) & 0x07;
        instructionTicks = instructionLen[addressMode];
        Uint8 operation = (nextInstruction[0] >> 5) & 0x07;

        if(operation == 4){
            //STA
            instructionType = OP_TYPE_OUT;
            outValue = newState.accumulator;
            outAddress = resolveAddress(addressMode, pageCrossed);
            if(addressMode == 4 || addressMode == 6 || addressMode == 7) ++instructionTicks;
        }
        else{
            instructionType = OP_TYPE_CPU;
            Uint8 opValue;
            opValue = getValue(addressMode, pageCrossed);
            if(pageCrossed) ++instructionTicks;
            if(operation == 6){
                //CMP
                updateFlag(FLAG_C, newState.accumulator >= opValue);
                updateFlag(FLAG_Z, newState.accumulator == opValue);
                updateFlag(FLAG_N, ((newState.accumulator - opValue) & 0x80) != 0);
            }
            else{
                Uint16 tmpValue;
                switch(operation){
                case 0:
                    //ORA
                    newState.accumulator = newState.accumulator | opValue;
                    break;
                case 1:
                    //AND
                    newState.accumulator = newState.accumulator & opValue;
                    break;
                case 2:
                    //EOR
                    newState.accumulator = newState.accumulator ^ opValue;
                    break;
                case 3:
                    //ADC
                    tmpValue = newState.accumulator + opValue + (checkFlag(FLAG_C) ? 1 : 0);
                    newState.accumulator = tmpValue & 0x00FF;
                    updateFlag(FLAG_C, tmpValue > 0x00FF);
                    updateFlag(FLAG_V, (((newState.accumulator ^ opValue) & (newState.accumulator ^ state.accumulator) & 0x80) != 0));
                    break;
                case 5:
                    //LDA
                    newState.accumulator = opValue;
                    break;
                case 7:
                    //SBC
                    tmpValue = newState.accumulator;
                    tmpValue = tmpValue - opValue;
                    if(checkFlag(FLAG_C)) --tmpValue;
                    newState.accumulator = tmpValue & 0x00FF;
                    updateFlag(FLAG_C, tmpValue < 0x100);
                    updateFlag(FLAG_V, ((newState.accumulator ^ (opValue ^ 0xFF)) & (newState.accumulator ^ state.accumulator) & 0x80) != 0);
                }
                updateFlag(FLAG_Z, !newState.accumulator);
                updateFlag(FLAG_N, newState.accumulator & 0x80);
            }
        }
    }
    else if((nextInstruction[0] & 0x07) == 0x06){
        bool pageCrossed;
        Uint8 opValue;
        //PPPAA110
        Uint8 addressMode = (nextInstruction[0] >> 2) & 0x07;
        instructionTicks = instructionLen[addressMode];
        Uint8 operation = (nextInstruction[0] >> 5) & 0x07;
        if(operation == 4){
            //STX
            instructionType = OP_TYPE_OUT;
            outValue = newState.indexX;
            outAddress = resolveAddress((addressMode == 5 ? 8 : addressMode), pageCrossed);
        }
        else if(operation == 5){
            //LDX
            instructionType = OP_TYPE_CPU;
            if(addressMode < 5){
                opValue = getValue(addressMode, pageCrossed);
            }
            else if(addressMode == 5){
                opValue = getValue(8, pageCrossed);
            }
            else if(addressMode == 7){
                opValue = getValue(9, pageCrossed);
                if(pageCrossed) ++instructionTicks;
            }
            newState.indexX = opValue;
            updateFlag(FLAG_Z, !newState.indexX);
            updateFlag(FLAG_N, newState.indexX & 0x80);
        }
        else{
            instructionType = OP_TYPE_OUT;
            instructionTicks += 2;
            if(addressMode == 7) ++instructionTicks;
            outAddress = resolveAddress((addressMode == 5 ? 8 : addressMode), pageCrossed);
            opValue = getValue(addressMode, pageCrossed);

            switch(operation){
            case 0:
                //ASL
                outValue = (opValue << 1) & 0xFE;
                updateFlag(FLAG_C, opValue & 0x80);
                break;
            case 1:
                //ROL
                outValue = ((opValue << 1) & 0xFE) | (checkFlag(FLAG_C) ? 0x01 : 0x00);
                updateFlag(FLAG_C, opValue & 0x80);
                break;
            case 2:
                //LSR
                outValue = (opValue >> 1) & 0x7F;
                updateFlag(FLAG_C, opValue & 0x01);
                break;
            case 3:
                //ROR
                outValue = ((opValue >> 1) & 0x7F) | (checkFlag(FLAG_C) ? 0x80 : 0x00);
                updateFlag(FLAG_C, opValue & 0x01);
                break;
            case 6:
                //DEC
                outValue = (opValue ? opValue - 1 : 0xFF);
                break;
            case 7:
                //INC
                outValue = (opValue > 0xFF ? opValue + 1 : 0);
                break;
            }
            updateFlag(FLAG_Z, !outValue);
            updateFlag(FLAG_N, outValue & 0x80);
        }
    }
}

Uint8 cpu::getValue(Uint8 addressMode, bool& hasCrossPage){

    if(addressMode == 2){
        //#v
        nextInstruction[1] = mb->memRead(newState.programCounter);
        ++newState.programCounter;
        hasCrossPage = false;
        return nextInstruction[1];
    }
    else{
        return mb->memRead(resolveAddress(addressMode, hasCrossPage));
    }
}

Uint16 cpu::resolveAddress(Uint8 addressMode, bool& hasCrossPage){
    Uint16 tmpAddress;
    nextInstruction[1] = mb->memRead(newState.programCounter);
    ++newState.programCounter;
    hasCrossPage = false;

    switch(addressMode){
    case 0:
        //(d,x)
        return mb->memRead((nextInstruction[1] + state.indexX) & 0x00FF) + (mb->memRead((nextInstruction[1] + state.indexX + 1) & 0x00FF) << 8);
        break;
    case 1:
        //d
        return nextInstruction[1];
        break;
    case 3:
        //a
        nextInstruction[2] = mb->memRead(newState.programCounter);
        ++newState.programCounter;
        return (nextInstruction[2] >> 8) + nextInstruction[1];
        break;
    case 4:
        //(d),y
        tmpAddress = mb->memRead((nextInstruction[1]) + newState.indexY);
        if(tmpAddress > 0x00FF){
            hasCrossPage = true;
        }
        return tmpAddress + (mb->memRead((nextInstruction[1] + state.indexX + 1) & 0x00FF) << 8);
        break;
    case 5:
        //d,x
        return (nextInstruction[1] + state.indexX) & 0x00FF;
        break;
    case 6:
        //a,y
        nextInstruction[2] = mb->memRead(newState.programCounter);
        ++newState.programCounter;
        tmpAddress = nextInstruction[1] + newState.indexY;
        if(tmpAddress > 0x00FF){
            hasCrossPage = true;
        }
        return tmpAddress + mb->memRead(nextInstruction[2] << 8);
        break;
    case 7:
        //a,x
        nextInstruction[2] = mb->memRead(newState.programCounter);
        ++newState.programCounter;
        tmpAddress = nextInstruction[1] + newState.indexX;
        if(tmpAddress > 0x00FF){
            hasCrossPage = true;
        }
        return tmpAddress + mb->memRead(nextInstruction[2] << 8);
        break;
    case 8:
        //d,y
        return (nextInstruction[1] + state.indexY) & 0x00FF;
        break;
    case 9:
        //a,y
        nextInstruction[2] = mb->memRead(newState.programCounter);
        ++newState.programCounter;
        tmpAddress = nextInstruction[1] + newState.indexY;
        if(tmpAddress > 0x00FF){
            hasCrossPage = true;
        }
        return tmpAddress + mb->memRead(nextInstruction[2] << 8);
        break;
    }
    return 0;
}

void cpu::updateFlag(Uint8 flag, bool value){
    if(value){
        setFlag(flag);
    }
    else{
        clearFlag(flag);
    }
}

void cpu::setFlag(Uint8 flag){
    newState.statusRegister = newState.statusRegister | flagMask[flag];
}

void cpu::clearFlag(Uint8 flag){
    newState.statusRegister = newState.statusRegister & ~flagMask[flag];
}

bool cpu::checkFlag(Uint8 flag){
    return newState.statusRegister & flagMask[flag];
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
