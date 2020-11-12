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

        //type 1 condition
        tileReference id;
        int objCoordX;
        int objCoordY;

        bool hFlip;
        bool vFlip;

        //type 2 condition
        string op;
        int address;
        int value;

        //type 3 condition
        int frame1;
        int frame2;

        void readLine(string s);
        string writeLine();
        bool compareEqual(condition& c);
        void load(fstream& file);
        void save(fstream& file);
        bool isMatch(gameTile& owner, gameTile& conditionTile);
        int getType();
        condition clone();

    protected:

    private:
};

#endif // CONDITION_H
