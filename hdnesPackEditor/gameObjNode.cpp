#include "gameObjNode.h"

gameObjNode::gameObjNode()
{
    //ctor
    effectedByMove = false;
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
    objectWidth = 0;
    objectHeight = 0;
    bgColour = 0;
}

gameObjNode::~gameObjNode()
{
    //dtor
}

void gameObjNode::addTile(gameTile g){
    tiles.push_back(g);
    addToObjectSize(tiles.size() - 1);
}

void gameObjNode::addToObjectSize(int gIdx){
    x1 = min(x1, tiles[gIdx].objCoordX);
    x2 = max(x2, tiles[gIdx].objCoordX + 8);
    y1 = min(y1, tiles[gIdx].objCoordY);
    y2 = max(y2, tiles[gIdx].objCoordY + 8);
    objectWidth = x2 - x1;
    objectHeight = y2 - y1;
}

void gameObjNode::clearAllTiles(){
    tiles.clear();
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
    objectWidth = 0;
    objectHeight = 0;
}
