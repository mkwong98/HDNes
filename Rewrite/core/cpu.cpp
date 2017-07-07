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

    for(Uint8 i = 0; i < 256; ++i){
        addressMode = (i >> 2) & 0x07;
        operation = (i >> 5) & 0x07;
        opGroup = i & 0x03;
        if(addressMode == 4 && opGroup == 0){ //branch xxx10000
            opHdl[i] = &cpu::opcodeBranch;
        }
        else if(addressMode == 6 && opGroup == 0){ //flag xxx11000
            opHdl[i] = &cpu::opcodeFlag;
        }
        else if(addressMode > 4 && operation > 4 && opGroup == 0){ //0xx0xx00
            opHdl[i] = &cpu::opcodeCtrl;
        }
        else if((nextInstruction[0] & 0x8F) == 0x8A){ //1xxx1010
            opHdl[i] = &cpu::opcodeMisB;
        }
        else if((nextInstruction[0] & 0x9F) == 0x88){ //1xx01000
            opHdl[i] = &cpu::opcodeMisA;
        }
        else if(operation == 4){
            opHdl[i] = &cpu::opcodeST;
        }
        else if(operation == 5){
            opHdl[i] = &cpu::opcodeLD;
        }
        else if(opGroup == 0){
            opHdl[i] = &cpu::opcodeHandler0;
        }
        else if(opGroup == 1){
            opHdl[i] = &cpu::opcodeHandler1;
        }
        else if(opGroup == 2){
            opHdl[i] = &cpu::opcodeHandler2;
        }
        else if(opGroup == 3){
            opHdl[i] = &cpu::opcodeHandler3;
        }
    }

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
    ++(newState.programCounter);
    addressMode = (nextInstruction[0] >> 2) & 0x07;
    operation = (nextInstruction[0] >> 5) & 0x07;
    opGroup = nextInstruction[0] & 0x03;
    (this->*opHdl[nextInstruction[0]])();
}

void cpu::opcodeBranch(){
    instructionType = OP_TYPE_CPU;
    instructionTicks = 2;
    nextInstruction[1] = mb->memRead(newState.programCounter);
    ++(newState.programCounter);
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
    instructionTicks = 2;
    instructionType = OP_TYPE_CPU;
    if(nextInstruction[0] == 0x98){ //TYA
        newState.reg[REG_INDEX_Y] = newState.reg[REG_ACCUMULATOR];
        updateFlag(FLAG_Z, !newState.reg[REG_INDEX_Y]);
        updateFlag(FLAG_N, newState.reg[REG_INDEX_Y] & 0x80);
    }
    else{
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
            ++(newState.programCounter);
            nextInstruction[2] = mb->memRead(newState.programCounter);
            break;
        case 0x02: //RTI
            instructionTicks = 6;
            instructionType = OP_TYPE_CPU;
            ++(newState.reg[REG_STACK_PTR]);
            newState.reg[REG_STATUS] = (mb->memRead(0x0100 + newState.reg[REG_STACK_PTR]) & 0xCF) | (newState.reg[REG_STATUS] & 0x30); //ignore bit 4 and 5
            //immediately effective
            state.reg[REG_STATUS] = newState.reg[REG_STATUS];
            ++(newState.reg[REG_STACK_PTR]);
            newState.programCounter = (mb->memRead(0x0100 + newState.reg[REG_STACK_PTR]) & 0x00FF);
            ++(newState.reg[REG_STACK_PTR]);
            newState.programCounter += (mb->memRead(0x0100 + newState.reg[REG_STACK_PTR]) << 8) ;
            break;
        case 0x03: //RTS
            instructionTicks = 6;
            instructionType = OP_TYPE_CPU;
            ++(newState.reg[REG_STACK_PTR]);
            newState.programCounter = (mb->memRead(0x0100 + newState.reg[REG_STACK_PTR]) & 0x00FF);
            ++(newState.reg[REG_STACK_PTR]);
            newState.programCounter += (mb->memRead(0x0100 + newState.reg[REG_STACK_PTR]) << 8) ;
            ++(newState.programCounter);
            break;
        }
    }
    else if(addressMode == 2){
        switch(operation){
        case 0x00:
            //PHP, bit 4 and 5 are always 1 in stack
            pushStack(newState.reg[REG_STATUS] | 0x30);
            break;
        case 0x01:
            //PLP , ignore bit 4 and 5
            newState.reg[REG_STATUS] = (pullStack() & 0xCF) | (newState.reg[REG_STATUS] & 0x30);
            break;
        case 0x028:
            //PHA
            pushStack(newState.reg[REG_ACCUMULATOR]);
            break;
        case 0x03:
            //PLA
            newState.reg[REG_ACCUMULATOR] = pullStack();
            break;
        }
    }
    else{
        if(operation == 0x01){ //BIT
            instructionType = OP_TYPE_CPU;
            instructionTicks = (addressMode == 0x01 ? 3 : 4);
            opValue = getValue((addressMode == 0x01 ? 1 : 3), pageCrossed);
            outValue = opValue & newState.reg[REG_ACCUMULATOR];
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

void cpu::opcodeMisA(){
    instructionTicks = 2;
    instructionType = OP_TYPE_CPU;
    switch(operation){
    case 0x04:
        //DEY
        newState.reg[REG_INDEX_Y] = (newState.reg[REG_INDEX_Y] ? newState.reg[REG_INDEX_Y] - 1 : 0xFF);
        updateFlag(FLAG_Z, !newState.reg[REG_INDEX_Y]);
        updateFlag(FLAG_N, newState.reg[REG_INDEX_Y] & 0x80);
        break;
    case 0x05:
        //TAY
        newState.reg[REG_INDEX_Y] = newState.reg[REG_ACCUMULATOR];
        updateFlag(FLAG_Z, !newState.reg[REG_INDEX_Y]);
        updateFlag(FLAG_N, newState.reg[REG_INDEX_Y] & 0x80);
    case 0x06:
        //INY
        newState.reg[REG_INDEX_Y] = (newState.reg[REG_INDEX_Y] < 0xFF ? newState.reg[REG_INDEX_Y] + 1 : 0);
        updateFlag(FLAG_Z, !newState.reg[REG_INDEX_Y]);
        updateFlag(FLAG_N, newState.reg[REG_INDEX_Y] & 0x80);
        break;
    case 0x07:
        //INX
        newState.reg[REG_INDEX_X] = (newState.reg[REG_INDEX_X] < 0xFF ? newState.reg[REG_INDEX_X] + 1 : 0);
        updateFlag(FLAG_Z, !newState.reg[REG_INDEX_X]);
        updateFlag(FLAG_N, newState.reg[REG_INDEX_X] & 0x80);
        break;
    }
}

void cpu::opcodeMisB(){
    instructionTicks = 2;
    instructionType = OP_TYPE_CPU;

    switch(operation){
    case 0x8A: //TXA
        newState.reg[REG_ACCUMULATOR] = newState.reg[REG_INDEX_X];
        updateFlag(FLAG_Z, !newState.reg[REG_ACCUMULATOR]);
        updateFlag(FLAG_N, newState.reg[REG_ACCUMULATOR] & 0x80);
        break;
    case 0x9A: //TXS
        newState.reg[REG_STACK_PTR] = newState.reg[REG_INDEX_X];
        break;
    case 0xAA: //TAX
        newState.reg[REG_INDEX_X] = newState.reg[REG_ACCUMULATOR];
        updateFlag(FLAG_Z, !newState.reg[REG_INDEX_X]);
        updateFlag(FLAG_N, newState.reg[REG_INDEX_X] & 0x80);
        break;
    case 0xBA: //TSX
        newState.reg[REG_INDEX_X] = newState.reg[REG_STACK_PTR];
        updateFlag(FLAG_Z, !newState.reg[REG_INDEX_X]);
        updateFlag(FLAG_N, newState.reg[REG_INDEX_X] & 0x80);
        break;
    case 0xCA: //DEX
        newState.reg[REG_INDEX_X] = (newState.reg[REG_INDEX_X] ? newState.reg[REG_INDEX_X] - 1 : 0xFF);
        updateFlag(FLAG_Z, !newState.reg[REG_INDEX_X]);
        updateFlag(FLAG_N, newState.reg[REG_INDEX_X] & 0x80);
        break;
    case 0xEA: //NOP
        break;
    }
}

void cpu::opcodeST(){
    instructionTicks = instructionLen[addressMode];
    instructionType = OP_TYPE_OUT;
    switch(opGroup){
    case 1:
        if(addressMode == 4 || addressMode == 6 || addressMode == 7) ++instructionTicks;
        break;
    case 2:
        if(addressMode == 5) addressMode = 8;
        break;
    }
    outValue = newState.reg[opGroup];
    outAddress = resolveAddress(addressMode, pageCrossed);
}

void cpu::opcodeLD(){
    if(opGroup != 1 && addressMode == 0) addressMode = 2;
    instructionTicks = instructionLen[addressMode];
    instructionType = OP_TYPE_CPU;

    if(opGroup == 2 && addressMode == 5) addressMode = 8;
    if(opGroup == 2 && addressMode == 7) addressMode = 6;

    newState.reg[opGroup] = getValue(addressMode, pageCrossed);
    updateFlag(FLAG_Z, !newState.reg[opGroup]);
    updateFlag(FLAG_N, newState.reg[opGroup] & 0x80);
    if(pageCrossed) ++instructionTicks;
}

void cpu::opcodeHandler0(){ //xxxxxx00
    if((nextInstruction[0] & 0x80) == 0x80){ //1xxxxx00
        if(operation == 6){ //CPY
            if(addressMode == 0) addressMode = 2;
            instructionTicks = instructionLen[addressMode];
            instructionType = OP_TYPE_CPU;
            opValue = getValue(addressMode, pageCrossed);
            compare(newState.reg[REG_INDEX_Y], opValue);
        }
        else if(operation == 7){ //CPX
            if(addressMode == 0) addressMode = 2;
            instructionTicks = instructionLen[addressMode];
            instructionType = OP_TYPE_CPU;
            opValue = getValue(addressMode, pageCrossed);
            compare(newState.reg[REG_INDEX_X], opValue);
        }
    }
}

void cpu::opcodeHandler1(){ //PPPAAA01
    instructionTicks = instructionLen[addressMode];
    instructionType = OP_TYPE_CPU;
    opValue = getValue(addressMode, pageCrossed);
    if(pageCrossed) ++instructionTicks;
    if(operation == 6){//CMP
        compare(newState.reg[REG_ACCUMULATOR], opValue);
    }
    else{
        Uint16 tmpValue;
        switch(operation){
        case 0:
            //ORA
            newState.reg[REG_ACCUMULATOR] = newState.reg[REG_ACCUMULATOR] | opValue;
            break;
        case 1:
            //AND
            newState.reg[REG_ACCUMULATOR] = newState.reg[REG_ACCUMULATOR] & opValue;
            break;
        case 2:
            //EOR
            newState.reg[REG_ACCUMULATOR] = newState.reg[REG_ACCUMULATOR] ^ opValue;
            break;
        case 3:
            //ADC
            tmpValue = newState.reg[REG_ACCUMULATOR] + opValue + (checkFlag(FLAG_C) ? 1 : 0);
            newState.reg[REG_ACCUMULATOR] = tmpValue & 0x00FF;
            updateFlag(FLAG_C, tmpValue > 0x00FF);
            updateFlag(FLAG_V, (((newState.reg[REG_ACCUMULATOR] ^ opValue) & (newState.reg[REG_ACCUMULATOR] ^ state.reg[REG_ACCUMULATOR]) & 0x80) != 0));
            break;
        case 7:
            //SBC
            tmpValue = newState.reg[REG_ACCUMULATOR];
            tmpValue = tmpValue - opValue;
            if(checkFlag(FLAG_C)) --tmpValue;
            newState.reg[REG_ACCUMULATOR] = tmpValue & 0x00FF;
            updateFlag(FLAG_C, tmpValue < 0x100);
            updateFlag(FLAG_V, ((newState.reg[REG_ACCUMULATOR] ^ (opValue ^ 0xFF)) & (newState.reg[REG_ACCUMULATOR] ^ state.reg[REG_ACCUMULATOR]) & 0x80) != 0);
        }
        updateFlag(FLAG_Z, !newState.reg[REG_ACCUMULATOR]);
        updateFlag(FLAG_N, newState.reg[REG_ACCUMULATOR] & 0x80);
    }
}

void cpu::opcodeHandler2(){ //xxxxxx10
    instructionTicks = 2;
    if(addressMode == 2){
        instructionType = OP_TYPE_CPU;
        opValue = newState.reg[REG_ACCUMULATOR];
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
        newState.reg[REG_ACCUMULATOR] = outValue;
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
    outAddress = 0x0100 + newState.reg[REG_STACK_PTR];
    --(newState.reg[REG_STACK_PTR]);
}

Uint8 cpu::pullStack(){
    instructionTicks = 4;
    instructionType = OP_TYPE_CPU;
    ++(newState.reg[REG_STACK_PTR]);
    return mb->memRead(0x0100 + newState.reg[REG_STACK_PTR]);
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
        ++(newState.programCounter);
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
    ++(newState.programCounter);
    hasCrossPage = false;
    return (this->*adHdl[addressMode])(hasCrossPage);
}

Uint16 cpu::resolveAddress0(bool& hasCrossPage){ //(d,x)
    return mb->memRead((nextInstruction[1] + state.reg[REG_INDEX_X]) & 0x00FF) + (mb->memRead((nextInstruction[1] + state.reg[REG_INDEX_X] + 1) & 0x00FF) << 8);
}

Uint16 cpu::resolveAddress1(bool& hasCrossPage){ //d
    return nextInstruction[1];
}

Uint16 cpu::resolveAddress2(bool& hasCrossPage){ //#v
    return 0;
}

Uint16 cpu::resolveAddress3(bool& hasCrossPage){ //a
    nextInstruction[2] = mb->memRead(newState.programCounter);
    ++(newState.programCounter);
    return (nextInstruction[2] >> 8) + nextInstruction[1];
}

Uint16 cpu::resolveAddress4(bool& hasCrossPage){ //(d),y
    Uint16 tmpAddress;
    tmpAddress = mb->memRead((nextInstruction[1]) + newState.reg[REG_INDEX_Y]);
    if(tmpAddress > 0x00FF){
        hasCrossPage = true;
    }
    return tmpAddress + (mb->memRead((nextInstruction[1] + state.reg[REG_INDEX_X] + 1) & 0x00FF) << 8);
}

Uint16 cpu::resolveAddress5(bool& hasCrossPage){ //d,x
    return (nextInstruction[1] + state.reg[REG_INDEX_X]) & 0x00FF;
}

Uint16 cpu::resolveAddress6(bool& hasCrossPage){ //a,y
    Uint16 tmpAddress;
    nextInstruction[2] = mb->memRead(newState.programCounter);
    ++(newState.programCounter);
    tmpAddress = nextInstruction[1] + newState.reg[REG_INDEX_Y];
    if(tmpAddress > 0x00FF){
        hasCrossPage = true;
    }
    return tmpAddress + mb->memRead(nextInstruction[2] << 8);
}

Uint16 cpu::resolveAddress7(bool& hasCrossPage){ //a,x
    Uint16 tmpAddress;
    nextInstruction[2] = mb->memRead(newState.programCounter);
    ++(newState.programCounter);
    tmpAddress = nextInstruction[1] + newState.reg[REG_INDEX_X];
    if(tmpAddress > 0x00FF){
        hasCrossPage = true;
    }
    return tmpAddress + mb->memRead(nextInstruction[2] << 8);
}

Uint16 cpu::resolveAddress8(bool& hasCrossPage){ //d,y
    return (nextInstruction[1] + state.reg[REG_INDEX_Y]) & 0x00FF;
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
    newState.reg[REG_STATUS] = newState.reg[REG_STATUS] | flagMask[flag];
}

void cpu::clearFlag(Uint8 flag){
    newState.reg[REG_STATUS] = newState.reg[REG_STATUS] & ~flagMask[flag];
}

bool cpu::checkFlag(Uint8 flag){
    return state.reg[REG_STATUS] & flagMask[flag];
}

void cpu::runInstruction(){
    if(instructionType == OP_TYPE_OUT){
        mb->memWrite(outAddress, outValue);
    }
    else if(instructionType == OP_TYPE_BRK){
        interruptJump(0xFFFE, 0xFFFF);
    }
    else if(instructionType == OP_TYPE_JSR){
        mb->memWrite(0x0100 + newState.reg[REG_STACK_PTR], newState.programCounter >> 8);
        --(newState.reg[REG_STACK_PTR]);
        mb->memWrite(0x0100 + newState.reg[REG_STACK_PTR], newState.programCounter);
        --(newState.reg[REG_STACK_PTR]);
        newState.programCounter = ((nextInstruction[2] << 8) | nextInstruction[1]);
    }
    state = newState;
    serviceInterrupt();
}

void cpu::reset(){
    state.reg[REG_STACK_PTR] -= 3;
    state.reg[REG_STATUS] |= 0x04;
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
    state.reg[REG_STATUS] = 0x34;
    state.reg[REG_ACCUMULATOR] = 0;
    state.reg[REG_INDEX_X] = 0;
    state.reg[REG_INDEX_Y] = 0;
    state.reg[REG_STACK_PTR] = 0xFD;
    state.programCounter = ((mb->memRead(0xFFFD) << 8) | mb->memRead(0xFFFC));

    for(Uint8 i = 0; i < 3; ++i){
        flagNMI[i] = false;
        flagIRQ[i] = false;
    }
}

void cpu::pullNMILow(){
    flagNMI[INTERRUPT_FLAG_IS_LOW_NEW] = true;
}

void cpu::pullIRQLow(){
    flagIRQ[INTERRUPT_FLAG_IS_LOW_NEW] = true;
}

void cpu::runInterruptDetector(){
    //NMI raises when becomes low or is raised already
    flagNMI[INTERRUPT_FLAG_DETECTOR_OUTPUT] = ((flagNMI[INTERRUPT_FLAG_IS_LOW_NEW] && !flagNMI[INTERRUPT_FLAG_IS_LOW_OLD]) || flagNMI[INTERRUPT_FLAG_DETECTOR_OUTPUT]);

    //IRQ raises when low
    flagIRQ[INTERRUPT_FLAG_DETECTOR_OUTPUT] = flagIRQ[INTERRUPT_FLAG_IS_LOW_NEW];
}

void cpu::updateOldInterruptFlag(){
    flagNMI[INTERRUPT_FLAG_IS_LOW_OLD] = flagNMI[INTERRUPT_FLAG_IS_LOW_NEW];
    flagIRQ[INTERRUPT_FLAG_IS_LOW_OLD] = flagIRQ[INTERRUPT_FLAG_IS_LOW_NEW];
}

void cpu::serviceInterrupt(){
    if(flagNMI[INTERRUPT_FLAG_DETECTOR_OUTPUT]){
        flagNMI[INTERRUPT_FLAG_DETECTOR_OUTPUT] = false;
        interruptJump(0xFFFA, 0xFFFB);
        state = newState;
    }
    else if(flagIRQ[INTERRUPT_FLAG_DETECTOR_OUTPUT] && !checkFlag(FLAG_I)){
        interruptJump(0xFFFE, 0xFFFF);
        state = newState;
    }
}

void cpu::interruptJump(Uint16 vectorL, Uint16 vectorH){
    mb->memWrite(0x0100 + newState.reg[REG_STACK_PTR], newState.programCounter >> 8);
    --(newState.reg[REG_STACK_PTR]);
    mb->memWrite(0x0100 + newState.reg[REG_STACK_PTR], newState.programCounter);
    --(newState.reg[REG_STACK_PTR]);
    mb->memWrite(0x0100 + newState.reg[REG_STACK_PTR], newState.reg[REG_STATUS] | 0x30);
    --(newState.reg[REG_STACK_PTR]);
    newState.programCounter = ((mb->memRead(vectorH) << 8) | mb->memRead(vectorL));
    setFlag(FLAG_I);
}

