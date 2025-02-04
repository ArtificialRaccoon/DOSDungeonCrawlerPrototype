#ifndef MAZEUI_H
#define MAZEUI_H

#include "CommonGUI.h"
#include "GameUIDefines.h"
#include "GlobalEnumerations.h"
#include "GameProcessor.h"
#include "Character.h"
#include "Dungeon.h"

class MazeUI
{
    public:
        BITMAP *SHEET;
        BITMAP *PORTSHEET;
        BITMAP *BUFFER;
        MazeUI() {}
        virtual ~MazeUI();
        void Init(BITMAP *INPUT_BUFFER);
        void DrawMazeUI();
        void DrawMazeUILayer(std::vector<int>*);        
        void DrawTile(int tileIndex);
        void DrawTileLayer(std::vector<int>* tileData, int tileIndex);

    private:
        int guiWidth;
        int guiHeight;
        int tileWidth;
        int tileHeight;    
        std::vector<int> backgroundTileData;
        std::vector<int> mazeborderTileData;
        std::vector<int> mainuiTileData;
        std::vector<int> portraitbackgroundTileData;
        std::vector<int> portraitbordersTileData;
};

#endif // MAZEUI_H
