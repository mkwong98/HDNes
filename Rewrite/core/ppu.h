#ifndef PPU_H
#define PPU_H

#include <corePart.h>


class ppu : public corePart
{
    public:
        Uint8 registers[8];
        Uint8 reg4014;
        bool frameReady;

        ppu();
        virtual ~ppu();

        void reset();
        void saveState(fstream* statefile);
        void loadState(fstream* statefile);
        void init();
        void init2();

        Uint8 readReg(Uint8 idx);
        void writeReg(Uint8 idx, Uint8 value);
        Uint8 read4014();
        void write4014(Uint8 value);

        void runCycle();

    protected:

    private:
};

#endif // PPU_H
