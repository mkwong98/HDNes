#ifndef GAMEFILE_H
#define GAMEFILE_H

#include "../classList.h"
#include <emuPart.h>


class gameFile : public emuPart{
    public:
        //variables
        string romPath;
        int currentStateSlot;
        int lastSavedSlot;
        bool rotateState;

        //functions
        gameFile();
        virtual ~gameFile();
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

#endif // GAMEFILE_H
