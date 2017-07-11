#ifndef PPU_H
#define PPU_H

#include <corePart.h>

#define REG_PPUCTRL     0
#define REG_PPUMASK     1
#define REG_PPUSTATUS   2
#define REG_OAMADDR     3
#define REG_OAMDATA     4
#define REG_PPUSCROLL   5
#define REG_PPUADDR     6
#define REG_PPUDATA     7

class ppu : public corePart
{
    public:
        Uint8 registers[8];
        Uint8 reg4014;
        Uint8 busValue;
        Uint8 addressLatch;
        bool frameReady;
        bool oddFrame;
        Uint16 bootUpCycles;
        Uint16 renderingX;
        Uint16 renderingY;

        Uint8 tableValues[0x4000];
        Uint8 oam[256];

        memBus* mb;
        cpu* cp;

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
