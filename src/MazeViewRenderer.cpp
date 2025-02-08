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
        
	for(int i = FORWARDD_LEFT3; i <= FORWARDD_RIGHT3; i++)
	{
		if(wallCone.Tier0[i].TypeFlag != SpaceType::EMPTY)
			currentDungeon.WallSets[wallCone.Tier0[i].WallSetId - 1].DrawWall(MAZEVIEW, (WallPartId)i, 0, lastDrawn);			
	}	

	for(int i = FARSIDED2_LEFT1; i <= FARSIDED2_RIGHT1; i++)
	{
		int conePosition = i - FARSIDED2_LEFT1; 
		if(conePosition >= 3)
			conePosition++;

		if(wallCone.Tier1[conePosition].TypeFlag != SpaceType::EMPTY)
			currentDungeon.WallSets[wallCone.Tier1[conePosition].WallSetId - 1].DrawWall(MAZEVIEW, (WallPartId)i, 0, lastDrawn);
	}

	for(int i = FORWARDC_LEFT2; i <= FORWARDC_RIGHT2; i++)
	{
		int conePosition = i - FORWARDC_LEFT2 + 1;
		if(wallCone.Tier1[conePosition].TypeFlag != SpaceType::EMPTY)
			currentDungeon.WallSets[wallCone.Tier1[conePosition].WallSetId - 1].DrawWall(MAZEVIEW, (WallPartId)i, 0, lastDrawn);		
	}

	for(int i = FARSIDEC_LEFT1; i <= FARSIDEC_RIGHT1; i++)
	{
		int conePosition = i - FARSIDEC_LEFT1 + 1;
		if(conePosition >= 3)
			conePosition++;		
		if(wallCone.Tier2[conePosition].TypeFlag != SpaceType::EMPTY)
			currentDungeon.WallSets[wallCone.Tier2[conePosition].WallSetId - 1].DrawWall(MAZEVIEW, (WallPartId)i, 0, lastDrawn);		
	}

	for(int i = FORWARDB_LEFT1; i <= FORWARDB_RIGHT1; i++)
	{
		int conePosition = i - FORWARDB_LEFT1 + 2;
		if(wallCone.Tier2[conePosition].TypeFlag != SpaceType::EMPTY)
			currentDungeon.WallSets[wallCone.Tier2[conePosition].WallSetId - 1].DrawWall(MAZEVIEW, (WallPartId)i, 0, lastDrawn);
	}

	for(int i = SIDEB_LEFT1; i <= SIDEB_RIGHT1; i++)
	{
		int conePosition = i - SIDEB_LEFT1 + 1;
		if(conePosition >= 2)
			conePosition++;			
		if(wallCone.Tier3[conePosition].TypeFlag != SpaceType::EMPTY)
			currentDungeon.WallSets[wallCone.Tier3[conePosition].WallSetId - 1].DrawWall(MAZEVIEW, (WallPartId)i, 0, lastDrawn);
	}

	for(int i = FORWARDA_LEFT1; i <= FORWARDA_RIGHT1; i++)
	{
		int conePosition = i - FORWARDA_LEFT1 + 1;
		if(wallCone.Tier3[conePosition].TypeFlag != SpaceType::EMPTY)
			currentDungeon.WallSets[wallCone.Tier3[conePosition].WallSetId - 1].DrawWall(MAZEVIEW, (WallPartId)i, 0, lastDrawn);
	}

	for(int i = SIDEA_LEFT1; i <= SIDEA_RIGHT1; i++)
	{
		int conePosition = i - SIDEA_LEFT1;
		if(conePosition >= 1)
			conePosition++;		
		if(wallCone.Tier4[conePosition].TypeFlag != SpaceType::EMPTY)
			currentDungeon.WallSets[wallCone.Tier4[conePosition].WallSetId - 1].DrawWall(MAZEVIEW, (WallPartId)i, 0, lastDrawn);
	}
}