#ifndef CPU_H
#define CPU_H

#include "../classList.h"
#include <corePart.h>


class cpu : public corePart
{
    public:
        Uint8 accumulator;
        Uint8 indexX;
        Uint8 indexY;
        Uint16 programCounter;
        Uint8 stackPointer;
        Uint8 statusRegister;

        Uint8 nextInstruction[3];
        Uint8 instructionLen[8];
        bool extraCycleReq;

        memBus* mb;

        cpu();
        virtual ~cpu();

        void reset();
        void saveState(fstream* statefile);
        void loadState(fstream* statefile);
        void init();

        Uint8 getNextInstructionLength();
        void runInstruction();
        bool hasExtraCycle();
    protected:

    private:
};

#endif // CPU_H
