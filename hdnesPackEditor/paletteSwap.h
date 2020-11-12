#ifndef PALETTESWAP_H
#define PALETTESWAP_H

#include "common.h"

class paletteSwap
{
    public:
        paletteSwap();
        virtual ~paletteSwap();

        string name;
        vector<array<Uint8, 4>> orgPalettes;
        vector<array<Uint8, 4>> newPalettes;
        double brightness;
        double hueRotation;
        double saturation;

        void load(fstream& file);
        void save(fstream& file);
        paletteSwap clone();
    protected:

    private:
};

#endif // PALETTESWAP_H
