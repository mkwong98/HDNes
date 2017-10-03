#ifndef GAMEOBJNODE_H
#define GAMEOBJNODE_H

#include "common.h"
#include <wx/treebase.h>

#define GAME_OBJ_NODE_TYPE_ROOT     0
#define GAME_OBJ_NODE_TYPE_GROUP    1
#define GAME_OBJ_NODE_TYPE_OBJECT   2

#define GAME_OBJ_NODE_MENU_ADD_FOLDER   1
#define GAME_OBJ_NODE_MENU_ADD_OBJECT   2
#define GAME_OBJ_NODE_MENU_DEL          3
#define GAME_OBJ_NODE_MENU_MOVE_UP      4
#define GAME_OBJ_NODE_MENU_MOVE_DOWN    5

class gameObjNode : public wxTreeItemData
{
    public:
        gameObjNode();
        virtual ~gameObjNode();

        Uint8 nodeType;
        string nodeName;

    protected:

    private:
};

#endif // GAMEOBJNODE_H
