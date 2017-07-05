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

    branchFlag[0] = FLAG_N;
    branchFlag[1] = FLAG_V;
    branchFlag[2] = FLAG_C;
    branchFlag[3] = FLAG_Z;

    opHdl[0] = &cpu::opcodeHandler0;
    opHdl[1] = &cpu::opcodeHandler1;
    opHdl[2] = &cpu::opcodeHandler2;
    opHdl[3] = &cpu::opcodeHandler3;

    adHdl[0] = &cpu::resolveAddress0;
    adHdl[1] = &cpu::resolveAddress1;
    adHdl[2] = &cpu::resolveAddress2;
    adHdl[3] = &cpu::resolveAddress3;
    adHdl[4] = &cpu::resolveAddress4;
    adHdl[5] = &cpu::resolveAddress5;
    adHdl[6] = &cpu::resolveAddress6;
    adHdl[7] = &cpu::resolveAddress7;
    adHdl[8] = &cpu::resolveAddress8;

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
    addressMode = (nextInstruction[0] >> 2) & 0x07;
    operation = (nextInstruction[0] >> 5) & 0x07;
    opGroup = nextInstruction[0] & 0x03;

    if(addressMode == 4 && opGroup == 0){ //branch xxx10000
        opcodeBranch();
    }
    else if(addressMode == 6 && opGroup == 0){ //flag xxx11000
        instructionTicks = 2;
        instructionType = OP_TYPE_CPU;
        if(nextInstruction[0] == 0x98){
            newState.indexY = newState.accumulator;
            updateFlag(FLAG_Z, !newState.indexY);
            updateFlag(FLAG_N, newState.indexY & 0x80);
        }
        else{
            opcodeFlag();
        }
    }
    else if(addressMode > 4 && operation > 4 && opGroup == 0){ //0xx0xx00
        opcodeCtrl();
    }
    else if((nextInstruction[0] & 0x8F) == 0x8A){ //1xxx1010
        opcodeMis2();
    }
    else if((nextInstruction[0] & 0x9F) == 0x88){ //1xx01000
        opcodeMis0()
    }
    else{

    }
    (this->*opHdl[nextInstruction[0] & 0x03])();
}

void cpu::opcodeBranch(){
        instructionType = OP_TYPE_CPU;
        instructionTicks = 2;
        nextInstruction[1] = mb->memRead(newState.programCounter);
        ++newState.programCounter;
        bool branchResult;
        if(operation & 0x01){
            branchResult = checkFlag(branchFlag[(operation >> 1) & 0x03]);
        }
        else{
            branchResult = !checkFlag(branchFlag[(operation >> 1) & 0x03]);
        }
        if(branchResult){
            ++instructionTicks;
            Uint16 pcPage;
            pcPage = newState.programCounter & 0xFF00;
            newState.programCounter += (nextInstruction[1] & 0x80 ? -(nextInstruction[1] & 0x7F) - 1 : nextInstruction[1]);
            if(pcPage != (newState.programCounter & 0xFF00)) ++instructionTicks;
        }
}

void cpu::opcodeFlag(){
    Uint8 flagID;
    switch(operation & 0x06){
    case 0:
        flagID = FLAG_C;
        break;
    case 2:
        flagID = FLAG_I;
        break;
    case 4:
        flagID = FLAG_V;
        break;
    case 6:
        flagID = FLAG_D;
        break;
    }
    if((operation & 0x01) && (operation != 0x05)){
        setFlag(flagID);
    }
    else{
        clearFlag(flagID);
    }
}

void cpu::opcodeCtrl(){
    if(addressMode == 0){
        switch(operation){
        case 0x00: //BRK
            instructionTicks = 7;
            instructionType = OP_TYPE_BRK;
            setFlag(FLAG_I);
            break;
        case 0x01: //JSR
            instructionTicks = 6;
            instructionType = OP_TYPE_JSR;
            nextInstruction[1] = mb->memRead(newState.programCounter);
            ++newState.programCounter;
            nextInstruction[2] = mb->memRead(newState.programCounter);
            break;
        case 0x02: //RTI
            instructionTicks = 6;
            instructionType = OP_TYPE_CPU;
            ++newState.stackPointer;
            newState.statusRegister = (mb->memRead(0x0100 + newState.stackPointer) & 0xCF) | (newState.statusRegister & 0x30); //ignore bit 4 and 5
            ++newState.stackPointer;
            newState.programCounter = (mb->memRead(0x0100 + newState.stackPointer) & 0x00FF);
            ++newState.stackPointer;
            newState.programCounter += (mb->memRead(0x0100 + newState.stackPointer) << 8) ;
            break;
        case 0x03: //RTS
            instructionTicks = 6;
            instructionType = OP_TYPE_CPU;
            ++newState.stackPointer;
            newState.programCounter = (mb->memRead(0x0100 + newState.stackPointer) & 0x00FF);
            ++newState.stackPointer;
            newState.programCounter += (mb->memRead(0x0100 + newState.stackPointer) << 8) ;
            ++newState.programCounter;
            break;
        }
    }
    else if(addressMode == 2){
        switch(operation){
        case 0x00:
            //PHP, bit 4 and 5 are always 1 in stack
            pushStack(newState.statusRegister | 0x30);
            break;
        case 0x01:
            //PLP , ignore bit 4 and 5
            newState.statusRegister = (pullStack() & 0xCF) | (newState.statusRegister & 0x30);
            break;
        case 0x028:
            //PHA
            pushStack(newState.accumulator);
            break;
        case 0x03:
            //PLA
            newState.accumulator = pullStack();
            break;
        }
    }
    else{
        if(operation == 0x01){ //BIT
            instructionType = OP_TYPE_CPU;
            instructionTicks = (addressMode == 0x01 ? 3 : 4);
            opValue = getValue((addressMode == 0x01 ? 1 : 3), pageCrossed);
            outValue = opValue & newState.accumulator;
            updateFlag(FLAG_Z, !outValue);
            updateFlag(FLAG_V, opValue & 0x40);
            updateFlag(FLAG_N, opValue & 0x80);
        }
        else{ //JMP
            instructionType = OP_TYPE_CPU;
            outAddress = resolveAddress(3, pageCrossed);
            if(operation == 0x02){
                instructionTicks = 3;
                newState.programCounter = outAddress;
            }
            else{
                instructionTicks = 5;
                newState.programCounter = (mb->memRead(outAddress + 1) << 8) + mb->memRead(outAddress);
            }
        }
    }
}

void cpu::opcodeMis0(){
    instructionTicks = 2;
    instructionType = OP_TYPE_CPU;
    switch(operation){
    case 0x04:
        //DEY
        newState.indexY = (newState.indexY ? newState.indexY - 1 : 0xFF);
        updateFlag(FLAG_Z, !newState.indexY);
        updateFlag(FLAG_N, newState.indexY & 0x80);
        break;
    case 0x05:
        //TAY
        newState.indexY = newState.accumulator;
        updateFlag(FLAG_Z, !newState.indexY);
        updateFlag(FLAG_N, newState.indexY & 0x80);
    case 0x06:
        //INY
        newState.indexY = (newState.indexY < 0xFF ? newState.indexY + 1 : 0);
        updateFlag(FLAG_Z, !newState.indexY);
        updateFlag(FLAG_N, newState.indexY & 0x80);
        break;
    case 0x07:
        //INX
        newState.indexX = (newState.indexX < 0xFF ? newState.indexX + 1 : 0);
        updateFlag(FLAG_Z, !newState.indexX);
        updateFlag(FLAG_N, newState.indexX & 0x80);
        break;
    }
}

void cpu::opcodeMis2(){
    instructionTicks = 2;
    instructionType = OP_TYPE_CPU;

    switch(operation){
    case 0x8A: //TXA
        newState.accumulator = newState.indexX;
        updateFlag(FLAG_Z, !newState.accumulator);
        updateFlag(FLAG_N, newState.accumulator & 0x80);
        break;
    case 0x9A: //TXS
        newState.stackPointer = newState.indexX;
        break;
    case 0xAA: //TAX
        newState.indexX = newState.accumulator;
        updateFlag(FLAG_Z, !newState.indexX);
        updateFlag(FLAG_N, newState.indexX & 0x80);
        break;
    case 0xBA: //TSX
        newState.indexX = newState.stackPointer;
        updateFlag(FLAG_Z, !newState.indexX);
        updateFlag(FLAG_N, newState.indexX & 0x80);
        break;
    case 0xCA: //DEX
        newState.indexX = (newState.indexX ? newState.indexX - 1 : 0xFF);
        updateFlag(FLAG_Z, !newState.indexX);
        updateFlag(FLAG_N, newState.indexX & 0x80);
        break;
    case 0xEA: //NOP
        break;
    }
}

void cpu::opcodeHandler0(){ //xxxxxx00
    if((nextInstruction[0] & 0x80) == 0x80){ //1xxxxx00
        if(operation == 4){ //STY
            ++addressMode;
            instructionTicks = instructionLen[addressMode];
            instructionType = OP_TYPE_OUT;
            outValue = newState.indexY;
            outAddress = resolveAddress(addressMode, pageCrossed);
        }
        else if(operation == 5){ //LDY
            if(addressMode == 0) addressMode = 2;
            instructionTicks = instructionLen[addressMode];
            instructionType = OP_TYPE_CPU;
            newState.indexY = getValue(addressMode, pageCrossed);
            updateFlag(FLAG_Z, !newState.indexY);
            updateFlag(FLAG_N, newState.indexY & 0x80);
            if(pageCrossed) ++instructionTicks;
        }
        else if(operation == 6){ //CPY
            if(addressMode == 0) addressMode = 2;
            instructionTicks = instructionLen[addressMode];
            instructionType = OP_TYPE_CPU;
            opValue = getValue(addressMode, pageCrossed);
            compare(newState.indexY, opValue);
        }
        else if(operation == 7){ //CPX
            if(addressMode == 0) addressMode = 2;
            instructionTicks = instructionLen[addressMode];
            instructionType = OP_TYPE_CPU;
            opValue = getValue(addressMode, pageCrossed);
            compare(newState.indexX, opValue);
        }
    }
}

void cpu::opcodeHandler1(){ //PPPAAA01
    instructionTicks = instructionLen[addressMode];
    if(operation == 4){
        //STA
        instructionType = OP_TYPE_OUT;
        outValue = newState.accumulator;
        outAddress = resolveAddress(addressMode, pageCrossed);
        if(addressMode == 4 || addressMode == 6 || addressMode == 7) ++instructionTicks;
    }
    else{
        instructionType = OP_TYPE_CPU;
        opValue = getValue(addressMode, pageCrossed);
        if(pageCrossed) ++instructionTicks;
        if(operation == 6){//CMP
            compare(newState.accumulator, opValue);
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

void cpu::opcodeHandler2(){ //xxxxxx10
    instructionTicks = 2;
    instructionType = OP_TYPE_CPU;


        //handle general case
        if(operation == 4){
            //STX
            instructionType = OP_TYPE_OUT;
            outValue = newState.indexX;
            outAddress = resolveAddress((addressMode == 5 ? 8 : addressMode), pageCrossed);
        }
        else if(operation == 5){
            //LDX
            instructionType = OP_TYPE_CPU;
            if(addressMode == 0){
                opValue = getValue(2, pageCrossed);
            }
            else if(addressMode < 5){
                opValue = getValue(addressMode, pageCrossed);
            }
            else if(addressMode == 5){
                opValue = getValue(8, pageCrossed);
            }
            else if(addressMode == 7){
                opValue = getValue(6, pageCrossed);
                if(pageCrossed) ++instructionTicks;
            }
            newState.indexX = opValue;
            updateFlag(FLAG_Z, !newState.indexX);
            updateFlag(FLAG_N, newState.indexX & 0x80);
        }
        else{
            if(addressMode == 2){
                opValue = newState.accumulator;
            }
            else{
                instructionType = OP_TYPE_OUT;
                instructionTicks += 2;
                if(addressMode == 7) ++instructionTicks;
                outAddress = resolveAddress(addressMode, pageCrossed);
                opValue = mb->memRead(outAddress);
            }
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
                outValue = (opValue < 0xFF ? opValue + 1 : 0);
                break;
            }
            updateFlag(FLAG_Z, !outValue);
            updateFlag(FLAG_N, outValue & 0x80);
            if(addressMode == 2){
                newState.accumulator = outValue;
            }
        }
}

void cpu::opcodeHandler3(){ //xxxxxx11
    //unsupported op
    instructionType = OP_TYPE_CPU;
    instructionTicks = 2;
}

void cpu::pushStack(Uint8 value){
    instructionTicks = 3;
    instructionType = OP_TYPE_OUT;
    outValue = value;
    outAddress = 0x0100 + newState.stackPointer;
    --newState.stackPointer;
}

Uint8 cpu::pullStack(){
    instructionTicks = 4;
    instructionType = OP_TYPE_CPU;
    ++newState.stackPointer;
    return mb->memRead(0x0100 + newState.stackPointer);
}

void cpu::compare(Uint8 regValue, Uint8 opValue){
    updateFlag(FLAG_C, regValue >= opValue);
    updateFlag(FLAG_Z, regValue == opValue);
    updateFlag(FLAG_N, ((regValue - opValue) & 0x80) != 0);
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
    return (this->*adHdl[addressMode])(hasCrossPage);
}

Uint16 cpu::resolveAddress0(bool& hasCrossPage){ //(d,x)
    return mb->memRead((nextInstruction[1] + state.indexX) & 0x00FF) + (mb->memRead((nextInstruction[1] + state.indexX + 1) & 0x00FF) << 8);
}

Uint16 cpu::resolveAddress1(bool& hasCrossPage){ //d
    return nextInstruction[1];
}

Uint16 cpu::resolveAddress2(bool& hasCrossPage){ //#v
    return 0;
}

Uint16 cpu::resolveAddress3(bool& hasCrossPage){ //a
    nextInstruction[2] = mb->memRead(newState.programCounter);
    ++newState.programCounter;
    return (nextInstruction[2] >> 8) + nextInstruction[1];
}

Uint16 cpu::resolveAddress4(bool& hasCrossPage){ //(d),y
    Uint16 tmpAddress;
    tmpAddress = mb->memRead((nextInstruction[1]) + newState.indexY);
    if(tmpAddress > 0x00FF){
        hasCrossPage = true;
    }
    return tmpAddress + (mb->memRead((nextInstruction[1] + state.indexX + 1) & 0x00FF) << 8);
}

Uint16 cpu::resolveAddress5(bool& hasCrossPage){ //d,x
    return (nextInstruction[1] + state.indexX) & 0x00FF;
}

Uint16 cpu::resolveAddress6(bool& hasCrossPage){ //a,y
    Uint16 tmpAddress;
    nextInstruction[2] = mb->memRead(newState.programCounter);
    ++newState.programCounter;
    tmpAddress = nextInstruction[1] + newState.indexY;
    if(tmpAddress > 0x00FF){
        hasCrossPage = true;
    }
    return tmpAddress + mb->memRead(nextInstruction[2] << 8);
}

Uint16 cpu::resolveAddress7(bool& hasCrossPage){ //a,x
    Uint16 tmpAddress;
    nextInstruction[2] = mb->memRead(newState.programCounter);
    ++newState.programCounter;
    tmpAddress = nextInstruction[1] + newState.indexX;
    if(tmpAddress > 0x00FF){
        hasCrossPage = true;
    }
    return tmpAddress + mb->memRead(nextInstruction[2] << 8);
}

Uint16 cpu::resolveAddress8(bool& hasCrossPage){ //d,y
    return (nextInstruction[1] + state.indexY) & 0x00FF;
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
    if(instructionType == OP_TYPE_OUT){
        mb->memWrite(outAddress, outValue);
    }
    else if(instructionType == OP_TYPE_BRK){
        mb->memWrite(0x0100 + newState.stackPointer, newState.programCounter >> 8);
        --newState.stackPointer;
        mb->memWrite(0x0100 + newState.stackPointer, newState.programCounter);
        --newState.stackPointer;
        mb->memWrite(0x0100 + newState.stackPointer, newState.statusRegister | 0x30);
        --newState.stackPointer;
        newState.programCounter = ((mb->memRead(0xFFFF) << 8) | mb->memRead(0xFFFE));
    }
    else if(instructionType == OP_TYPE_JSR){
        mb->memWrite(0x0100 + newState.stackPointer, newState.programCounter >> 8);
        --newState.stackPointer;
        mb->memWrite(0x0100 + newState.stackPointer, newState.programCounter);
        --newState.stackPointer;
        newState.programCounter = ((nextInstruction[2] << 8) | nextInstruction[1]);
    }
    state = newState;
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
