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
        void init2();

        Uint8 readMapperPRGData(Uint16 address);
        void writeMapperPRGData(Uint16 address, Uint8 value);
        Uint8 readMapperCHRData(Uint16 address);
        void writeMapperCHRData(Uint16 address, Uint8 value);


    protected:

    private:
};

#endif // MAPPER001_H
