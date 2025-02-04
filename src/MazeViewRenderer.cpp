#include "MazeViewRenderer.h"

void MazeViewRenderer::Init(BITMAP* inputBUFFER, Dungeon &currentDungeon)
{    
    BACKGROUND = create_bitmap(MAZEVIEW_WIDTH, MAZEVIEW_HEIGHT);
    MAZEVIEW = create_sub_bitmap(inputBUFFER, MAZEVIEW_X, MAZEVIEW_Y, MAZEVIEW_WIDTH, MAZEVIEW_HEIGHT);    
    BACKGROUND = load_bitmap((".\\BACKSETS\\" + currentDungeon.FloorSet + ".bmp").c_str(), CommonGUI::Instance().GetPalette());
    if (!BACKGROUND) {
      set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      allegro_message("Error reading backset bitmap");
      allegro_message(currentDungeon.FloorSet.c_str());
      exit(0);
    }
}

void MazeViewRenderer::RenderVisionCone(Dungeon &currentDungeon, VisionCone &wallCone, VisionCone &decoCone)
{
  currentDungeon.WallSets[0].DrawWall(MAZEVIEW, WallPartId::FORWARDC_RIGHT1);
}