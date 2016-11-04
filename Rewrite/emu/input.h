#ifndef INPUT_H
#define INPUT_H

#include "../classList.h"
#include <emuPart.h>


class input : public emuPart
{
    public:
        input();
        virtual ~input();
        string partName();

        void saveConfigLines(fstream* fs);
        void saveGameConfigLines(fstream* fs);
        void loadConfigVal(const string& hdr, const string& value);
        void initGameConfig();

        void startGame();
        void endGame();

    protected:

    private:
};

#endif // INPUT_H
