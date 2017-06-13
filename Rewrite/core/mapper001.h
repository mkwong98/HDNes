#ifndef MAPPER001_H
#define MAPPER001_H

#include "cart.h"


class mapper001 : public cart
{
    public:
        mapper001();
        virtual ~mapper001();

        void reset();
        void saveState(fstream* statefile);
        void loadState(fstream* statefile);
        void init();

        Uint8 readPRGData(Uint16 address);
        void writePRGData(Uint16 address, Uint8 value);
        Uint8 readCHRData(Uint16 address);
        void writeCHRData(Uint16 address, Uint8 value);


    protected:

    private:
};

#endif // MAPPER001_H
