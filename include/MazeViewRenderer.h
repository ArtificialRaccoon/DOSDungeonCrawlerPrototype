#ifndef MAZEVIEWRENDERER_H
#define MAZEVIEWRENDERER_H

#include "CommonGUI.h"
#include "Globals.h"
#include "MazeDefines.h"
#include "Dungeon.h"
#include "VisionCone.h"

class MazeViewRenderer
{
    public:
        BITMAP *MAZEVIEW;
        BITMAP *BACKGROUND;
        MazeViewRenderer(){}
        virtual ~MazeViewRenderer(){}
        void Init(Dungeon &currentDungeon);
        void DrawForwardWall(std::vector<WallSet> wallSets, WallPartId wallPart, int wallSetIndex, int xPosIndex);
        void DrawForwardDecoration(Dungeon &currentDungeon, WallPartId wallPart, int wallSetIndex, int xPosIndex);        
        void DrawForwardSwitch(Dungeon &currentDungeon, WallPartId wallPart, int switchId, int xPosIndex);   
        void DrawForwardDoor(Dungeon &currentDungeon, WallPartId wallPart, int doorId, int xPosIndex);   
        void DrawSideWall(std::vector<WallSet> wallSets, WallPartId wallPart, bool flip, int wallSetIndex);
        void DrawSideDecoration(Dungeon &currentDungeon, WallPartId wallPart, bool flip, int wallSetIndex);
        void DrawSideSwitch(Dungeon &currentDungeon, WallPartId wallPart, bool flip, int switchId);
        void DrawBackground(bool flip);
        void RenderVisionCone(Dungeon &currentDungeon, VisionCone &wallCone, VisionCone &decoCone);
    private:
        WallPartId WallPartAtPosition[3][7] = {
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
};

#endif // MAZEVIEWRENDERER_H
