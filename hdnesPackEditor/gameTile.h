#ifndef GAMETILE_H
#define GAMETILE_H

#include "common.h"
#include "classList.h"
#include "condition.h"
#include "tileReference.h"

class gameTile
{
    public:
        gameTile();
        virtual ~gameTile();

        tileReference id;

        int objCoordX;
        int objCoordY;
        bool hFlip;
        bool vFlip;
        bool markForDelete;

        bool hasReplacement;
        bool isDefault;
        vector<condition> conditions;
        int img;
        int x;
        int y;
        double brightness;

        void readLine(string s);
        bool compareEqual(gameTile t);

    protected:

    private:
};

#endif // GAMETILE_H
