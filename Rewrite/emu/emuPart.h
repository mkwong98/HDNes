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
        void saveGameConfig(fstream* fs);
        virtual void saveConfigLines(fstream* fs) = 0;
        virtual void saveGameConfigLines(fstream* fs) = 0;
        static void saveConfigLine(fstream*fs, const string& hdr, const string& value);
        static string intToString(int a);
        static int stringToInt(const string& str);
        static string getFolderPath(const string& path);
        static string getFileName(const string& path);

        //load config
        void loadConfig(fstream* fs);
        static string getConfigLineHdr(string configLine);
        static string getConfigLineVal(string configLine);
        virtual void loadConfigVal(const string& hdr, const string& value) = 0;
        virtual void initGameConfig() = 0;

        virtual void startGame() = 0;
        virtual void endGame() = 0;
    protected:

    private:
};

#endif // EMUPART_H
