#ifndef APU_H
#define APU_H

#include <corePart.h>


class apu : public corePart
{
    public:
        Uint8 registers[0x14];
        Uint8 reg4015;

        apu();
        virtual ~apu();

        void reset();
        void saveState(fstream* statefile);
        void loadState(fstream* statefile);
        void init();
        void init2();

        Uint8 readReg(Uint8 idx);
        void writeReg(Uint8 idx, Uint8 value);
        Uint8 read4015();
        void write4015(Uint8 value);

        void runCycle();

    protected:

    private:
};

#endif // APU_H
