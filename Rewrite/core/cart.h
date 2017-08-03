#ifndef CART_H
#define CART_H

#include "corePart.h"
#include "../classList.h"

#define CHR_PAGE_SIZE	0x2000
#define PRG_PAGE_SIZE	0x4000
#define CHR_RAM_SIZE	0x2000
#define BATTERY_SIZE	0x2000



class cart : public corePart
{
    public:
        Uint8 chrPageCount;
        Uint8 prgPageCount;
        bool mirrorV;
        bool scr4x;
        Uint8* mirrorPtr[4];
        Uint8* prgROM;
        Uint8* chrROM;
        Uint8* chrRAM;
        bool batChanged;
        Uint8 batDat[0x2000];
        Uint8 scr4RAM[0x1000];
        string romFileName;

        cart();
        virtual ~cart();

        void reset();
        void saveState(fstream* statefile);
        void loadState(fstream* statefile);
        void init();
        void init2();

        static cart* getCartFromROMFile(const string& fileName);
        void readROMFile(fstream* fs, Uint8* header, const string& fileName);
        void loadBat();
        void saveBat();

        Uint8 readPRGData(Uint16 address);
        void writePRGData(Uint16 address, Uint8 value);
        Uint8 readCHRData(Uint16 address);
        void writeCHRData(Uint16 address, Uint8 value);
        Uint8 readNameTable(Uint16 address);
        void writeNameTable(Uint16 address, Uint8 value);

        virtual Uint8 readMapperPRGData(Uint16 address) = 0;
        virtual void writeMapperPRGData(Uint16 address, Uint8 value) = 0;
        virtual Uint8 readMapperCHRData(Uint16 address) = 0;
        virtual void writeMapperCHRData(Uint16 address, Uint8 value) = 0;


    protected:

    private:
};

#endif // CART_H
