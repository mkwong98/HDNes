#ifndef GAMETILE_H
#define GAMETILE_H

#include "common.h"
#include "classList.h"
#include "tileReplacement.h"

class gameTile
{
    public:
        gameTile();
        virtual ~gameTile();

        int id;
        Uint8 rawData[16];
        Uint8 palette[4];

        bool hasReplacement;
        bool isDefault;
        vector<condition> conditions;
        image* img;
        int x;
        int y;

    protected:

    private:
};

#endif // GAMETILE_H
