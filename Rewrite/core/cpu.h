#ifndef CPU_H
#define CPU_H

#include "../classList.h"
#include <corePart.h>

#define OP_TYPE_NOP	0x00
#define OP_TYPE_CPU	0x01
#define OP_TYPE_OUT	0x02

struct cpu_state{
    Uint8 accumulator;
    Uint8 indexX;
    Uint8 indexY;
    Uint16 programCounter;
    Uint8 stackPointer;
    Uint8 statusRegister;
};


class cpu : public corePart
{
    public:
        cpu_state state;
        cpu_state newState;

        Uint8 nextInstruction[3];
        Uint8 instructionType;
        Uint8 instructionLen[8];
        Uint8 instructionTicks;
        Uint8 extraCycleReq;

        memBus* mb;

        cpu();
        virtual ~cpu();

        void reset();
        void saveState(fstream* statefile);
        void loadState(fstream* statefile);
        void init();
        void init2();

        void processInstruction();
        void runInstruction();
        Uint8 getNextInstructionLength();
    protected:

    private:
};

#endif // CPU_H
