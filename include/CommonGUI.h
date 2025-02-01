#ifndef COMMONGUI_H
#define COMMONGUI_H

#include "allegro.h"

class CommonGUI
{
    public:        
        BITMAP* GetBitmap() { return GUI_SHEET; }
        FONT* GetFont() { return SCRIPT_FONT; }
        RGB* GetPalette() { return palette; }
        static CommonGUI& Instance()
        {
            static CommonGUI mCommonGUI;
            return mCommonGUI;
        }

    private:
        CommonGUI();
        BITMAP *GUI_SHEET;
        FONT *SCRIPT_FONT;
        FONT *ARCANA_FONT;
        PALETTE palette;
};

#endif // COMMONGUI_H