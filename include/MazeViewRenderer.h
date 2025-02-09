#ifndef MAZEVIEWRENDERER_H
#define MAZEVIEWRENDERER_H

#include <algorithm>
#include "CommonGUI.h"
#include "Globals.h"
#include "MazeDefines.h"
#include "Dungeon.h"
#include "VisionCone.h"
#include "TileReference.h"

class MazeViewRenderer
{
    public:
        MazeViewRenderer(){}
        virtual ~MazeViewRenderer(){}
        void Init(BITMAP* inputBUFFER, Dungeon &currentDungeon);
        void RenderVisionCone(Dungeon &currentDungeon, VisionCone &wallCone, VisionCone &decoCone);
        void FlipBackground() { flippedHorizontally = !flippedHorizontally; }

    private:
        void DrawBackground();
        void DrawMapSpace(Dungeon &currentDungeon, MapSpace &space, WallPartId spriteId);
        void LoadBackground(std::string backgroundName);

    private:
        int backgroundTileWidth;
        int backgroundTileHeight;
        int backgroundTilesetWidth;
        int backgroundTilesetHeight;
        std::vector<int> normalTileMap;
        std::vector<int> flippedTileMap;
        BITMAP *TILE;
        BITMAP *BACKGROUND;
        bool flippedHorizontally = false;

    private:
        BITMAP *MAZEVIEW;        
        std::vector<TileReference> lastDrawn;
};

#endif // MAZEVIEWRENDERER_H
