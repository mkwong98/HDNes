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
        vector<string> supportedRom;
        vector<string> overscan;
        vector<string> patch;
        vector<string> background;
        vector<string> options;
        vector<string> bgm;
        vector<string> sfx;

        Uint32 verNo;
        Uint8 scale;
        vector<image*> images;
        vector<condition*> conditions;
        vector<gameTile*> tiles;
        wxColour palette[64];
        int saveNo;

        void dataChanged();
        void initPath(string rPath, string pPath);
        void load(string path);
        void save();
        void saveAs(string path);
        void checkAndLoadPaths();
        void loadProjectData();

        string writeConditionNames(vector<condition>& cond);
        void loadPackData();
        void genPackData();
        void genSection(fstream& inifile, vector<string>& sect);
        void loadRom();
        void loadPalette();
        void genPalette();
        string getTileID(int tileIndex);
        void loadScreenData();
        void readScreen(string screenId);

        void addImage(string path);
        void removeImage(int index);
    protected:

    private:
};

#endif // COREDATA_H
