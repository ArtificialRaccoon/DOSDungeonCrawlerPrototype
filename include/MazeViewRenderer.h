#ifndef MAZEVIEWRENDERER_H
#define MAZEVIEWRENDERER_H

#include "Globals.h"
#include "MazeDefines.h"
#include "Dungeon.h"
#include "VisionCone.h"

class MazeViewRenderer
{
    public:
        BITMAP *MAZEVIEW;
        BITMAP *BACKGROUND;
        PALETTE palette_background;
        MazeViewRenderer(){}
        virtual ~MazeViewRenderer(){}
        void Init(Dungeon &currentDungeon);
        void DrawForwardWall(std::vector<WallSet> wallSets, WallPartId wallPart, int wallSetIndex, int xPos);
        void DrawForwardDecoration(Dungeon &currentDungeon, WallPartId wallPart, int wallSetIndex, int xPos);        
        void DrawForwardSwitch(Dungeon &currentDungeon, WallPartId wallPart, int switchId, int xPos);   
        void DrawForwardDoor(Dungeon &currentDungeon, WallPartId wallPart, int doorId, int xPos);   
        void DrawSideWall(std::vector<WallSet> wallSets, WallPartId wallPart, bool flip, int wallSetIndex, int xPos);
        void DrawSideDecoration(Dungeon &currentDungeon, WallPartId wallPart, bool flip, int wallSetIndex, int xPos);
        void DrawSideSwitch(Dungeon &currentDungeon, WallPartId wallPart, bool flip, int switchId, int xPos);
        void DrawBackground(bool flip);
        void RenderVisionCone(Dungeon &currentDungeon, VisionCone &wallCone, VisionCone &decoCone);
    private:
        WallPartId WallPartAtPosition[2][7] = {
            {
                FARSIDED2,
                FARSIDED1,
                SIDED,
                SIDED,
                SIDED,
                FARSIDED1,
                FARSIDED2
            },
            {
                FARSIDEC,
                FARSIDEC,
                SIDEC,
                SIDEC,
                SIDEC,
                FARSIDEC,
                FARSIDEC
            }
        };

        int SideXPosition[4][7] = {
            {
                0,
                FARSIDED1_STARTX,
                SIDED_STARTX,
                -1,
                SIDED_STARTX + FORWARDC_WIDTH - SIDED_WIDTH,
                FORWARDD_STARTX + FORWARDD_WIDTH * 2,
                FORWARDD_STARTX + FORWARDD_WIDTH * 3
            },
            {
                -1,
                0,
                SIDEC_STARTX,
                -1,
                SIDEC_STARTX + FORWARDB_WIDTH - SIDEC_WIDTH,
                (3 * FORWARDC_WIDTH) + FARSIDEC_WIDTH,
                -1
            },
            {
                -1,
                -1,
                SIDEB_STARTX,
                -1,
                SIDEB_STARTX + FORWARDB_WIDTH + SIDEB_WIDTH,
                -1,
                -1
            },
            {
                -1,
                -1,
                SIDEA_STARTX,
                -1,
                SIDEA_STARTX + FORWARDA_WIDTH + SIDEA_WIDTH,
                -1,
                -1
            }
        };

        int ForwardXPosition[4][7] = {
            {
                FORWARDD_STARTX + (-3 * FORWARDD_WIDTH), 
                FORWARDD_STARTX + (-2 * FORWARDD_WIDTH), 
                FORWARDD_STARTX + (-1 * FORWARDD_WIDTH), 
                FORWARDD_STARTX, 
                FORWARDD_STARTX + FORWARDD_WIDTH, 
                FORWARDD_STARTX + (2 * FORWARDD_WIDTH), 
                FORWARDD_STARTX + (3 * FORWARDD_WIDTH)
            },
            {
                0, 
                FORWARDC_STARTX + (-2 * FORWARDC_WIDTH), 
                FORWARDC_STARTX + (-1 * FORWARDC_WIDTH), 
                FORWARDC_STARTX, 
                FORWARDC_STARTX + FORWARDC_WIDTH, 
                FORWARDC_STARTX + (2 * FORWARDC_WIDTH), 
                0
            },
            {
                0, 
                0, 
                SIDEC_STARTX - FORWARDB_WIDTH,    
                SIDEC_STARTX,   
                SIDEC_STARTX + FORWARDB_WIDTH, 
                0, 
                0
            },
            {
                0, 
                0, 
                SIDEB_STARTX - FORWARDA_WIDTH,
                SIDEB_STARTX,
                SIDEB_STARTX + FORWARDA_WIDTH, 
                0, 
                0
            }
        };
};

#endif // MAZEVIEWRENDERER_H
