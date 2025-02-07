#ifndef WALLSET_H
#define WALLSET_H

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include "CommonGUI.h"
#include "Globals.h"
#include "json.h"
#include "MazeDefines.h"
#include "WallPart.h"
#include "TileReference.h"

class WallSet
{
    public:
        WallSet() {}
        virtual ~WallSet() {}
        void LoadWallSet(std::string wallSetName);    
        void DrawWall(BITMAP *BUFFER, WallPartId wallPart);
        void DrawWall(BITMAP *BUFFER, WallPartId wallPart, int layer, std::vector<TileReference> &lastDrawn);

    private:
        int tilesetWidth;
        int tilesetHeight;
        int tileWidth;
        int tileHeight;
        
        std::vector<std::vector<int>> WallTileMap;

        BITMAP* TILE;
        BITMAP* TILESHEET;
};

#endif // WALLSET_H
