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

        Uint8 readPRGData(Uint16 address);
        void writePRGData(Uint16 address, Uint8 value);
        Uint8 readCHRData(Uint16 address);
        void writeCHRData(Uint16 address, Uint8 value);

    protected:

    private:
};

#endif // MAPPER000_H
