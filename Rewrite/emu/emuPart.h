#ifndef EMUPART_H
#define EMUPART_H

#include "../common.h"

using namespace std;

class emuPart
{
    public:
        emuPart();
        ~emuPart();

        virtual void saveConfig(fstream* fs) = 0;
        virtual void loadConfig(fstream* fs) = 0;
        virtual void startGame() = 0;
        virtual void endGame() = 0;
    protected:

    private:
};

#endif // EMUPART_H
