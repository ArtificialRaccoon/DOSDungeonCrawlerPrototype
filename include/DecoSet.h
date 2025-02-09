#ifndef DECOSET_H
#define DECOSET_H

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

class DecoSet
{
    public:
    DecoSet() {}
        virtual ~DecoSet() {}
        void LoadDecoSet(std::string decoSetName);    
        void DrawDeco(BITMAP *BUFFER, WallPartId wallPart);
        void DrawDeco(BITMAP *BUFFER, WallPartId wallPart, int layer, std::vector<TileReference> &lastDrawn);

    private:
        int tilesetWidth;
        int tilesetHeight;
        int tileWidth;
        int tileHeight;
        
        std::vector<std::vector<int>> DecoTileMap;

        BITMAP* TILE;
        BITMAP* TILESHEET;
};

#endif // DECO_H
