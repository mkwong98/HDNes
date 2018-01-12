#ifndef TILEREFERENCE_H
#define TILEREFERENCE_H

#include "common.h"

class tileReference
{
    public:
        tileReference();
        virtual ~tileReference();

        int id;
        Uint8 rawData[16];
        Uint8 palette[4];

        bool compareEqual(tileReference t);
    protected:

    private:
};

#endif // TILEREFERENCE_H
