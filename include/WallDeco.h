#ifndef WALLDECO_H
#define WALLDECO_H

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "CommonGUI.h"
#include "Globals.h"
#include "json.h"
#include "MazeDefines.h"
#include "WallPart.h"

class WallDeco
{
    public:
        WallDeco() {}
        virtual ~WallDeco() {}
        void LoadWallDeco(std::string wallDecoName);
        void DrawWallDeco(BITMAP *BUFFER, WallPartId wallPart, int xPosIndex, bool flip);
    protected:
        void DrawWallDeco(BITMAP *BUFFER, WallPart wallObj, int startX, bool flip);
    private:
        int tilesetWidth;
        int tilesetHeight;
        int tileWidth;
        int tileHeight;
        BITMAP* TILE;
        BITMAP* TILESHEET;
        WallPart FORWARD_A, FORWARD_B, FORWARD_C, FORWARD_D;
        WallPart SIDE_A, SIDE_B, SIDE_C, SIDE_D;
        WallPart FARSIDE_C, FARSIDE_D1, FARSIDE_D2;
        void LoadPartData(json::jobject parsedObject, std::string key, WallPart *partToLoad);
};

#endif // WALLDECO_H
