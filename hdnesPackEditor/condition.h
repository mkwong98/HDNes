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

        bool hFlip;
        bool vFlip;

        void readLine(string s);
        string writeLine();
        bool compareEqual(condition& c);
        void load(fstream& file);
        void save(fstream& file);
        bool isMatch(gameTile& owner, gameTile& conditionTile);

    protected:

    private:
};

#endif // CONDITION_H
