#ifndef GAMEOBJNODE_H
#define GAMEOBJNODE_H

#include "common.h"
#include "gameTile.h"
#include <wx/treebase.h>

#define GAME_OBJ_NODE_TYPE_ROOT         0
#define GAME_OBJ_NODE_TYPE_GROUP        1
#define GAME_OBJ_NODE_TYPE_OBJECT       2
#define GAME_OBJ_NODE_TYPE_BGIMAGE      3

#define GAME_OBJ_NODE_MENU_ADD_FOLDER       1
#define GAME_OBJ_NODE_MENU_ADD_OBJECT       2
#define GAME_OBJ_NODE_MENU_ADD_BGIMAGE      3
#define GAME_OBJ_NODE_MENU_DEL              4
#define GAME_OBJ_NODE_MENU_MOVE_UP          5
#define GAME_OBJ_NODE_MENU_MOVE_DOWN        6
#define GAME_OBJ_NODE_MENU_MOVE_TO_FOLDER   7
#define GAME_OBJ_NODE_MENU_MOVE_HERE        8
#define GAME_OBJ_NODE_MENU_CLONE_OBJECT     9
#define GAME_OBJ_NODE_MENU_REMOVE_REDUNDANT 10
#define GAME_OBJ_NODE_MENU_REREAD_SCREEN    11


struct frameRange{
    int frameID;
    int frameCnt;
    string frameName;
};

class gameObjNode : public wxTreeItemData
{
    public:
        gameObjNode();
        virtual ~gameObjNode();

        Uint8 nodeType;
        string nodeName;
        bool effectedByMove;

        int x1;
        int x2;
        int y1;
        int y2;
        int objectWidth;
        int objectHeight;
        Uint8 bgColour;
        bool isSprite;
        float brightness;
        bool isDefault;

        //bg image
        double hScrollRate;
        double vScrollRate;
        string fileName;
        bool showBehindBgSprites;

        vector<gameTile> tiles;
        vector<paletteSwap> swaps;
        vector<condition> conditions;
        vector<bool> conSigns;
        vector<frameRange> frameRanges;

        vector<array<Uint8, 4>> palettes;
        vector<int> images;

        void addTile(gameTile g);
        void addToObjectSize(int gIdx);
        void clearAllTiles();
        void addSwap(paletteSwap g);
        void addCondition(condition c, bool isNegative);
        void load(fstream& file, wxTreeItemId newItm);
        void save(fstream& file, wxTreeItemId newItm);
        void updatePalettes();
        void updateImages();
        gameObjNode* clone();
        string writeLine();
        string writeConditionNames();
    protected:

    private:
};

#endif // GAMEOBJNODE_H
