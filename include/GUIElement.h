#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <string>
#include <vector>
#include <cmath>
#include "json.h"
#include "globals.h"

class GUIElement 
{
    public:
        virtual void DrawElement(BITMAP *BUFFER, BITMAP *SHEET, PALETTE palette, FONT *FONT, int tilesetWidth, int tilesetHeight, bool drawText) = 0;
        bool HitTest(int px, int py) const { return (px >= x && px <= (x + width) && py >= y && py <= (y + height)); }  
        int getAction() const { return action; }
        std::string getId() const { return id; }                
        std::string getTextOverlay() const { return textOverlay; }
        void setSelected(bool input) { selected = input; }    
        bool getSelected() const { return selected; }       

    protected:
        std::string id = "";
        int x = 0;
        int y = 0;
        int textX = 0;
        int textY = 0;        
        int width = 0;
        int height = 0;
        int spriteWidth = 0;
        int spriteHeight = 0;
        std::vector<int> spriteTiles;
        std::string textOverlay = "";
        std::vector<int> overlayTiles;
        int overlayX = 0;
        int overlayY = 0;
        int overlayWidth = 0;
        int overlayHeight = 0;     
        int action = -1;
        bool selected = false;

    protected:
        const int tileWidth = 8;
        const int tileHeight = 8;
        const unsigned FLIPPED_HORIZONTALLY_FLAG  = 0x80000000;
        const unsigned FLIPPED_VERTICALLY_FLAG    = 0x40000000;
        const unsigned FLIPPED_DIAGONALLY_FLAG    = 0x20000000;        
};

#endif //GUIELEMENT_H