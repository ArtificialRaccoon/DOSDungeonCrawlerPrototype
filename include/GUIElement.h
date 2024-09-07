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
        GUIElement(std::string inputJson);
        void DrawElement(BITMAP *BUFFER, BITMAP *SHEET, PALETTE palette, FONT *FONT, bool drawText);
        bool HitTest(int px, int py) const { return (px >= x && px <= (x + width) && py >= y && py <= (y + height)); }  
        std::string getId() const { return id; }        
        std::string getAction() const { return action; }
        std::string getTextOverlay() const { return textOverlay; }
        void setSelected(bool input) { selected = input; }    
        bool getSelected() const { return selected; }           
    private:
        std::string id = "";
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        std::vector<int> spriteTiles;
        std::string textOverlay = "";
        std::vector<int> overlayTiles;
        int overlayX = 0;
        int overlayY = 0;
        int overlayWidth = 0;
        int overlayHeight = 0;     
        std::string action= "unset";
        bool selected = false;
        BITMAP* spriteSheet;
};

#endif //GUIELEMENT_H