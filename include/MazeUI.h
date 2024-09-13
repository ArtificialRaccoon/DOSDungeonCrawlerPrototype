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
        BITMAP *MAZEBORDER_CORNER;
        BITMAP *CHAR_TOPCORNER, *CHAR_BOTTOMCORNER;
        BITMAP *ARROW;
        BITMAP *BUFFER;
        MazeUI() {}
        virtual ~MazeUI();
        void Init(BITMAP *INPUT_BUFFER);
        void DrawMazeUI(int startX, int startY, Dungeon &currentDungeon, Rotation facing, int playerX, int playerY, GameProcessor* game, bool update);             
        void LoadUISprite(BITMAP *bmpData, BITMAP *sprite, PALETTE palData, int startX, int startY, int sizeW, int sizeH);
        void DrawMazeWindowBorder(int startX, int startY, int windowBorderH, int windowBorderW, Rotation facing);
        void DrawMazeBackground();
        void DrawCharacterWindowBorder(int startX, int startY, int windowBorderH, int windowBorderW);
        void DrawCharacterBackground(int startX, int startY, int windowH, int windowW);
        void DrawDigits(int startX, int startY, int value, int width);
        void DrawCharacterWindow(Character *characterObj, int xOffset, int yOffset, bool update);
        void DrawMiniMap(int xOffset, int yOffset, Dungeon &currentDungeon, Rotation facing, int playerX, int playerY, GameProcessor* game);
        void DrawNavigation();
        void DrawUserButtons();
        void DrawButton(BITMAP *SHEET, int xPos, int yPos, int sheetX, int sheetY, int buttonWidth, int buttonHeight);
};

#endif // MAZEUI_H
