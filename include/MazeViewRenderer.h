#ifndef MAZEVIEWRENDERER_H
#define MAZEVIEWRENDERER_H

#include "CommonGUI.h"
#include "Globals.h"
#include "MazeDefines.h"
#include "Dungeon.h"
#include "VisionCone.h"
#include "TileReference.h"

class MazeViewRenderer
{
    public:
        BITMAP *MAZEVIEW;
        BITMAP *BACKGROUND;
        MazeViewRenderer(){}
        virtual ~MazeViewRenderer(){}
        void Init(BITMAP* inputBUFFER, Dungeon &currentDungeon);
        void RenderVisionCone(Dungeon &currentDungeon, VisionCone &wallCone, VisionCone &decoCone);
        std::vector<TileReference> lastDrawn;
};

#endif // MAZEVIEWRENDERER_H
