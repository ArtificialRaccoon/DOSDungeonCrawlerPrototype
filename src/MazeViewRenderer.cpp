#include "MazeViewRenderer.h"

void MazeViewRenderer::Init(BITMAP* inputBUFFER, Dungeon &currentDungeon)
{    
    BACKGROUND = create_bitmap(MAZEVIEW_WIDTH, MAZEVIEW_HEIGHT);
    MAZEVIEW = create_sub_bitmap(inputBUFFER, MAZEVIEW_X, MAZEVIEW_Y, MAZEVIEW_WIDTH, MAZEVIEW_HEIGHT);    
    BACKGROUND = load_bitmap((".\\BACKSETS\\" + currentDungeon.FloorSet + ".bmp").c_str(), CommonGUI::Instance().GetPalette());
	lastDrawn.resize(15 * 22, TileReference(-1, -1));

    if (!BACKGROUND) {
      set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      allegro_message("Error reading backset bitmap");
      allegro_message(currentDungeon.FloorSet.c_str());
      exit(0);
    }
}

void MazeViewRenderer::RenderVisionCone(Dungeon &currentDungeon, VisionCone &wallCone, VisionCone &decoCone)
{
	clear_bitmap(MAZEVIEW);	

	if(wallCone.Tier0[0].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDD_LEFT3, 0, lastDrawn);
	if(wallCone.Tier0[1].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDD_LEFT2, 0, lastDrawn);
	if(wallCone.Tier0[2].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDD_LEFT1, 0, lastDrawn);
	if(wallCone.Tier0[3].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDD_CENTER, 0, lastDrawn);
	if(wallCone.Tier0[4].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDD_RIGHT1, 0, lastDrawn);
	if(wallCone.Tier0[5].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDD_RIGHT2, 0, lastDrawn);
	if(wallCone.Tier0[6].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDD_RIGHT3, 0, lastDrawn);	

	if(wallCone.Tier1[0].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FARSIDED2_LEFT1, 0, lastDrawn);
	if(wallCone.Tier1[1].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FARSIDED1_LEFT1, 0, lastDrawn);
	if(wallCone.Tier1[2].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, SIDED_LEFT1, 0, lastDrawn);
	if(wallCone.Tier1[4].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, SIDED_RIGHT1, 0, lastDrawn);
	if(wallCone.Tier1[5].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FARSIDED1_RIGHT1, 0, lastDrawn);	
	if(wallCone.Tier1[6].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FARSIDED2_RIGHT1, 0, lastDrawn);	

	if(wallCone.Tier1[1].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDC_LEFT2, 0, lastDrawn);
	if(wallCone.Tier1[2].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDC_LEFT1, 0, lastDrawn);
	if(wallCone.Tier1[3].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDC_CENTER, 0, lastDrawn);
	if(wallCone.Tier1[4].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDC_RIGHT1, 0, lastDrawn);
	if(wallCone.Tier1[5].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDC_RIGHT2, 0, lastDrawn);

	if(wallCone.Tier2[1].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FARSIDEC_LEFT1, 0, lastDrawn);
	if(wallCone.Tier2[2].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, SIDEC_LEFT1, 0, lastDrawn);
	if(wallCone.Tier2[4].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, SIDEC_RIGHT1, 0, lastDrawn);
	if(wallCone.Tier2[5].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FARSIDEC_RIGHT1, 0, lastDrawn);	

	if(wallCone.Tier2[2].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDB_LEFT1, 0, lastDrawn);
	if(wallCone.Tier2[3].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDB_CENTER, 0, lastDrawn);
	if(wallCone.Tier2[4].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDB_RIGHT1, 0, lastDrawn);

	if(wallCone.Tier3[1].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, SIDEB_LEFT1, 0, lastDrawn);
	if(wallCone.Tier3[3].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, SIDEB_RIGHT1, 0, lastDrawn);

	if(wallCone.Tier3[1].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDA_LEFT1, 0, lastDrawn);
	if(wallCone.Tier3[2].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDA_CENTER, 0, lastDrawn);
	if(wallCone.Tier3[3].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FORWARDA_RIGHT1, 0, lastDrawn);

	if(wallCone.Tier4[0].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, SIDEA_LEFT1, 0, lastDrawn);
	if(wallCone.Tier4[2].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, SIDEA_RIGHT1, 0, lastDrawn);
}