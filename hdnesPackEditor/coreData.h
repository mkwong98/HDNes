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
        Uint16 romSize;
        Uint8* chrROM;

        //pack data
        vector<image*> images;
        vector<string> otherLines;

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
