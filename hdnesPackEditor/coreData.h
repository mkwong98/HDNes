#ifndef COREDATA_H
#define COREDATA_H

#include "common.h"
#include "classList.h"
#include <wx/wx.h>

class coreData
{
    public:
        static coreData* cData;

        coreData();
        virtual ~coreData();

        //project data
        string romPath;
        string packPath;
        string projectPath;
        bool notSaved;

        //rom data
        bool isCHRROM;
        Uint32 romSize;
        Uint8* romData;

        //pack data
        Uint8 scale;
        vector<image*> images;
        vector<condition*> conditions;
        vector<tile*> tiles;
        vector<string> otherLines;
        wxColour palette[64];


        void dataChanged();
        void initPath(string rPath, string pPath);
        void load(string path);
        void save();
        void saveAs(string path);

        void loadPackData();
        void loadRom();

        vector<string> split(const string &s, char delim, vector<string> &elems);

    protected:

    private:
};

#endif // COREDATA_H
