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
        
        std::unordered_map<WallPartId, std::vector<int>> WallTileMap;

        BITMAP* TILE;
        BITMAP* TILESHEET;

    private:
        std::unordered_map<std::string, WallPartId> WallPartStrings = 
        {
            {"FORWARDA_LEFT1", FORWARDA_LEFT1}, {"FORWARDA_CENTER", FORWARDA_CENTER}, {"FORWARDA_RIGHT1", FORWARDA_RIGHT1},
            {"FORWARDB_LEFT1", FORWARDB_LEFT1}, {"FORWARDB_CENTER", FORWARDB_CENTER}, {"FORWARDB_RIGHT1", FORWARDB_RIGHT1},
            {"FORWARDC_LEFT2", FORWARDC_LEFT2}, {"FORWARDC_LEFT1", FORWARDC_LEFT1}, 
            {"FORWARDC_CENTER", FORWARDC_CENTER}, 
            {"FORWARDC_RIGHT1", FORWARDC_RIGHT1}, {"FORWARDC_RIGHT2", FORWARDC_RIGHT2},
            {"FORWARDD_LEFT3", FORWARDD_LEFT3}, {"FORWARDD_LEFT2", FORWARDD_LEFT2}, {"FORWARDD_LEFT1", FORWARDD_LEFT1}, 
            {"FORWARDD_CENTER", FORWARDD_CENTER}, 
            {"FORWARDD_RIGHT1", FORWARDD_RIGHT1}, {"FORWARDD_RIGHT2", FORWARDD_RIGHT2}, {"FORWARDD_RIGHT3", FORWARDD_RIGHT3}, 
            {"SIDEA_LEFT1", SIDEA_LEFT1}, {"SIDEA_RIGHT1", SIDEA_RIGHT1}, 
            {"SIDEB_LEFT1", SIDEB_LEFT1}, {"SIDEB_RIGHT1", SIDEB_RIGHT1},
            {"SIDEC_LEFT1", SIDEC_LEFT1}, {"SIDEC_RIGHT1", SIDEC_RIGHT1}, 
            {"SIDED_LEFT1", SIDED_LEFT1}, {"SIDED_RIGHT1", SIDED_RIGHT1},
            {"FARSIDEC_LEFT1", FARSIDEC_LEFT1}, {"FARSIDEC_RIGHT1", FARSIDEC_RIGHT1},
            {"FARSIDED1_LEFT1", FARSIDED1_LEFT1}, {"FARSIDED1_RIGHT1", FARSIDED1_RIGHT1},
            {"FARSIDED2_LEFT1", FARSIDED2_LEFT1}, {"FARSIDED2_RIGHT1", FARSIDED2_RIGHT1}
        };
};

#endif // WALLSET_H
