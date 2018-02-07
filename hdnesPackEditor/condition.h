#ifndef CONDITION_H
#define CONDITION_H

#include "common.h"
#include "classList.h"
#include "tileReference.h"

class condition
{
    public:
        condition();
        virtual ~condition();

        string name;
        string conditionType;

        tileReference id;

        int objCoordX;
        int objCoordY;

        bool checkHFlip;
        bool hFlip;
        bool checkVFlip;
        bool vFlip;
        bool checkLayer;
        int layer;

        bool compareEqual(condition c);
        void load(fstream& file);
        void save(fstream& file);

    protected:

    private:
};

#endif // CONDITION_H
