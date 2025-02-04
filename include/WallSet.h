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

class WallSet
{
    public:
        WallSet() {}
        virtual ~WallSet() {}
        void LoadWallSet(std::string wallSetName);    
        void DrawWall(BITMAP *BUFFER, WallPartId wallPart);

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
            {"FORWARDC_LEFT2", FORWARDC_LEFT2}, {"FORWARDC_LEFT1", FORWARDC_LEFT1}, {"FORWARDC_CENTER", FORWARDC_CENTER},
            {"FORWARDC_RIGHT1", FORWARDC_RIGHT1}, {"FORWARDC_RIGHT2", FORWARDC_RIGHT2},
            {"FORWARDD_LEFT4", FORWARDD_LEFT4}, {"FORWARDD_LEFT3", FORWARDD_LEFT3}, {"FORWARDD_LEFT2", FORWARDD_LEFT2},
            {"FORWARDD_LEFT1", FORWARDD_LEFT1}, {"FORWARDD_CENTER", FORWARDD_CENTER}, 
            {"FORWARDD_RIGHT1", FORWARDD_RIGHT1}, {"FORWARDD_RIGHT2", FORWARDD_RIGHT2}, 
            {"FORWARDD_RIGHT3", FORWARDD_RIGHT3}, {"FORWARDD_RIGHT4", FORWARDD_RIGHT4},
            {"SIDEA_LEFT1", SIDEA_LEFT1}, {"SIDEA_RIGHT1", SIDEA_RIGHT1}, {"SIDEB_LEFT1", SIDEB_LEFT1}, {"SIDEB_RIGHT1", SIDEB_RIGHT1},
            {"SIDEC_LEFT1", SIDEC_LEFT1}, {"SIDEC_RIGHT1", SIDEC_RIGHT1}, {"SIDED_LEFT1", SIDED_LEFT1}, {"SIDED_RIGHT1", SIDED_RIGHT1},
            {"SIDEE_LEFT1", SIDEE_LEFT1}, {"SIDEE_LEFT2", SIDEE_LEFT2}, {"SIDEE_LEFT3", SIDEE_LEFT3}, {"SIDEE_LEFT4", SIDEE_LEFT4},
            {"SIDEE_RIGHT1", SIDEE_RIGHT1}, {"SIDEE_RIGHT2", SIDEE_RIGHT2}, {"SIDEE_RIGHT3", SIDEE_RIGHT3}, {"SIDEE_RIGHT4", SIDEE_RIGHT4},
            {"FARSIDEB_LEFT1", FARSIDEB_LEFT1}, {"FARSIDEB_RIGHT1", FARSIDEB_RIGHT1},
            {"FARSIDEC_LEFT1", FARSIDEC_LEFT1}, {"FARSIDEC_RIGHT1", FARSIDEC_RIGHT1},
            {"FARSIDED_LEFT1", FARSIDED_LEFT1}, {"FARSIDED_RIGHT1", FARSIDED_RIGHT1},
            {"FARSIDEE_LEFT1", FARSIDEE_LEFT1}, {"FARSIDEE_RIGHT1", FARSIDEE_RIGHT1}
        };
};

#endif // WALLSET_H
