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
        void Init(BITMAP* inputBUFFER, Dungeon &currentDungeon);
        void RenderVisionCone(Dungeon &currentDungeon, VisionCone &wallCone, VisionCone &decoCone);
};

#endif // MAZEVIEWRENDERER_H
