#ifndef COREPART_H
#define COREPART_H

#include "../common.h"

using namespace std;

class corePart
{
    public:
        corePart();
        ~corePart();

        virtual void reset() = 0;
        virtual void saveState(fstream* statefile) = 0;
        virtual void loadState(fstream* statefile) = 0;

    protected:

    private:
};

#endif // COREPART_H
