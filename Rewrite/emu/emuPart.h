#ifndef EMUPART_H
#define EMUPART_H

#include "../common.h"

using namespace std;

class emuPart
{
    public:
        emuPart();
        ~emuPart();

        virtual string partName() = 0;

        //config secton
        //save config
        void saveConfig(fstream* fs);
        virtual void saveConfigLines(fstream* fs) = 0;
        static void saveConfigLine(fstream*fs, string hdr, string value);
        //load config
        void loadConfig(fstream* fs);
        static string getConfigLineHdr(string configLine);
        static string getConfigLineVal(string configLine);
        virtual void loadConfigVal(string hdr, string value) = 0;

        virtual void startGame() = 0;
        virtual void endGame() = 0;
    protected:

    private:
};

#endif // EMUPART_H
