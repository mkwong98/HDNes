#ifndef MAPPER000_H
#define MAPPER000_H

#include <cart.h>


class mapper000 : public cart
{
    public:
        mapper000();
        virtual ~mapper000();

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

#endif // MAPPER000_H
