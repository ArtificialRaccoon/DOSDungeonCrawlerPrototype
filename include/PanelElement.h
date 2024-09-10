#ifndef PANELELEMENT_H
#define PANELELEMENT_H

#include <string>
#include <vector>
#include <cmath>
#include "GUIElement.h"
#include "json.h"
#include "globals.h"

class PanelElement : public GUIElement
{
    public:
        PanelElement(std::string inputJson);
        void DrawElement(BITMAP *BUFFER, BITMAP *SHEET, PALETTE palette, FONT *FONT, int tilesetWidth, int tilesetHeight, bool drawText);
};

#endif //PANELELEMENT_H