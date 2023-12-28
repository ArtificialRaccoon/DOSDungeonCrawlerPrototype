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
        void Init();
        void DrawForwardWall(Dungeon &currentDungeon, WallPartId wallPart, int wallSetIndex, int xPos);
        void DrawForwardDecoration(Dungeon &currentDungeon, WallPartId wallPart, int wallSetIndex, int xPos);        
        void DrawSideWall(Dungeon &currentDungeon, WallPartId wallPart, bool flip, int wallSetIndex, int xPos);
        void DrawSideDecoration(Dungeon &currentDungeon, WallPartId wallPart, bool flip, int wallSetIndex, int xPos);
        void DrawBackground(bool flip);
        void RenderVisionCone(Dungeon &currentDungeon, VisionCone &wallCone, VisionCone &decoCone);
};

#endif // MAZEVIEWRENDERER_H
