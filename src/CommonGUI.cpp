#include "CommonGUI.h"

CommonGUI::CommonGUI()
{
    GUI_SHEET = load_bitmap(".\\OTHER\\MAINGUI.bmp", palette);
    SCRIPT_FONT = load_font(".\\OTHER\\BitScrip.bmp", palette, NULL);
    ARCANA_FONT = load_font(".\\OTHER\\Arcana.bmp", palette, NULL);
}
