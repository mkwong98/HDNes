#ifndef EMU_PART_H
#define EMU_PART_H

#include "../common.h"

using namespace std;

class emu_part
{
    public:
        emu_part();
        ~emu_part();

        virtual void saveConfig(fstream* statefile) = 0;
        virtual void loadConfig(fstream* statefile) = 0;
        virtual void startGame() = 0;
        virtual void endGame() = 0;
    protected:

    private:
};

#endif // EMU_PART_H
