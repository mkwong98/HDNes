#ifndef MEMBUS_H
#define MEMBUS_H

#include <corePart.h>


class memBus : public corePart
{
    public:
        Uint8 internalRAM[0x800];

        memBus();
        ~memBus();

        Uint8 memRead(Uint16 address);

    protected:

    private:
};

#endif // MEMBUS_H
