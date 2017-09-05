#ifndef COREDATA_H
#define COREDATA_H

#include "common.h"
#include "classList.h"


class coreData
{
    public:
        static coreData* cData;

        coreData();
        virtual ~coreData();

        string romPath;
        string packPath;
        string projectPath;

        //rom data
        bool isCHRROM;
        Uint16 romSize;
        Uint8* romData;

        //pack data
        Uint8 scale;
        vector<image*> images;
        vector<condition*> conditions;
        vector<tile*> tiles;
        vector<string> otherLines;
        Uint32 palette[64];

        //project data


        void load(string path);
        void save();
        void saveAs(string path);

        void loadPackData();
        void loadRom();

    protected:

    private:
};

#endif // COREDATA_H
