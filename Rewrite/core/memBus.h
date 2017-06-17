#ifndef MEMBUS_H
#define MEMBUS_H

#include "../classList.h"
#include <corePart.h>


class memBus : public corePart
{
    public:
        Uint8 internalRAM[0x800];

        //short cut pointers
        cart* rom;
        cpu* cp;
        ppu* pp;
        apu* ap;
        gamepad* gp;

        memBus();
        virtual ~memBus();

        void reset();
        void saveState(fstream* statefile);
        void loadState(fstream* statefile);
        void init();
        void init2();

        Uint8 readByte();
        Uint8 memRead(Uint16 address);

    protected:

    private:
};

#endif // MEMBUS_H
