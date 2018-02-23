#ifndef GAMEOBJNODE_H
#define GAMEOBJNODE_H

#include "common.h"
#include "gameTile.h"
#include <wx/treebase.h>

#define GAME_OBJ_NODE_TYPE_ROOT         0
#define GAME_OBJ_NODE_TYPE_GROUP        1
#define GAME_OBJ_NODE_TYPE_OBJECT       2

#define GAME_OBJ_NODE_MENU_ADD_FOLDER   1
#define GAME_OBJ_NODE_MENU_ADD_OBJECT   2
#define GAME_OBJ_NODE_MENU_DEL          3
#define GAME_OBJ_NODE_MENU_MOVE_UP      4
#define GAME_OBJ_NODE_MENU_MOVE_DOWN    5
#define GAME_OBJ_NODE_MENU_MOVE_TO_FOLDER   6
#define GAME_OBJ_NODE_MENU_MOVE_HERE    7

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

        vector<gameTile> tiles;

        void addTile(gameTile g);
        void addToObjectSize(int gIdx);
        void clearAllTiles();
        void load(fstream& file, wxTreeItemId newItm);
        void save(fstream& file, wxTreeItemId newItm);
    protected:

    private:
};

#endif // GAMEOBJNODE_H
