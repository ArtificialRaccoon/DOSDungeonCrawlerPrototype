#ifndef BUTTONELEMENT_H
#define BUTTONELEMENT_H

#include <string>
#include <vector>
#include <cmath>
#include "GUIElement.h"
#include "json.h"
#include "globals.h"

class ButtonElement : public GUIElement
{
    public:
        ButtonElement(std::string inputJson);
        void DrawElement(BITMAP *BUFFER, BITMAP *SHEET, PALETTE palette, FONT *FONT, int tilesetWidth, int tilesetHeight, bool drawText);     
};

#endif //BUTTONELEMENT_H