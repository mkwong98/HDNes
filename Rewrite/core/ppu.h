#ifndef PPU_H
#define PPU_H

#include "../classList.h"
#include <corePart.h>

#define REG_PPUCTRL     0
#define REG_PPUMASK     1
#define REG_PPUSTATUS   2
#define REG_OAMADDR     3
#define REG_OAMDATA     4
#define REG_PPUSCROLL   5
#define REG_PPUADDR     6
#define REG_PPUDATA     7

#define FLAG_MASK_PPUCTRL_V  0x80
#define FLAG_MASK_PPUCTRL_P  0x40
#define FLAG_MASK_PPUCTRL_H  0x20
#define FLAG_MASK_PPUCTRL_B  0x10
#define FLAG_MASK_PPUCTRL_S  0x08
#define FLAG_MASK_PPUCTRL_I  0x04
#define FLAG_MASK_PPUCTRL_NN 0x03

#define FLAG_MASK_PPUMASK_B  0x80
#define FLAG_MASK_PPUMASK_G  0x40
#define FLAG_MASK_PPUMASK_R  0x20
#define FLAG_MASK_PPUMASK_s  0x10
#define FLAG_MASK_PPUMASK_b  0x08
#define FLAG_MASK_PPUMASK_M  0x04
#define FLAG_MASK_PPUMASK_m  0x02
#define FLAG_MASK_PPUMASK_g  0x02

#define FLAG_MASK_PPUSTATUS_V  0x80
#define FLAG_MASK_PPUSTATUS_S  0x40
#define FLAG_MASK_PPUSTATUS_O  0x20

class ppu : public corePart
{
    public:
        Uint8 registers[8];
        Uint8 reg4014;
        Uint8 busValue; //_io_db
        Uint8 addressLatch;
        bool frameReady;
        bool oddFrame;
        bool isRendering;
        Uint16 bootUpCycles;
        Uint16 renderingX;
        Uint16 renderingY;

        Uint8 nameTable1[0x400];
        Uint8 nameTable2[0x400];
        Uint8 paletteTable[0x20];
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
