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
		if(wallCone.Tier1[i].TypeFlag != SpaceType::EMPTY)
			currentDungeon.WallSets[wallCone.Tier1[i].WallSetId - 1].DrawWall(MAZEVIEW, (WallPartId)i, 0, lastDrawn);			
	}	

	/*if(wallCone.Tier1[5].TypeFlag & SpaceType::DOOR)
        currentDungeon.DoorSets[0].DrawWall(MAZEVIEW, FARSIDED1_LEFT1, 0, lastDrawn);	
	if(wallCone.Tier1[5].TypeFlag & SpaceType::DOOR)
        currentDungeon.DoorSets[0].DrawWall(MAZEVIEW, FARSIDED1_RIGHT1, 0, lastDrawn);*/

	for(int i = FARSIDED2_LEFT1; i <= FARSIDED2_RIGHT1; i++)
	{
		int conePosition = i - FARSIDED2_LEFT1; 
		if(conePosition >= 3)
			conePosition++;
		
		if(wallCone.Tier1[conePosition].TypeFlag != SpaceType::EMPTY)
			currentDungeon.WallSets[wallCone.Tier1[conePosition].WallSetId - 1].DrawWall(MAZEVIEW, (WallPartId)i, 0, lastDrawn);
	}

	/*if(wallCone.Tier1[0].TypeFlag & SpaceType::WALL)
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
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FARSIDED2_RIGHT1, 0, lastDrawn);*/

	for(int i = FORWARDC_LEFT2; i <= FORWARDC_RIGHT2; i++)
	{
		int conePosition = i - FORWARDC_LEFT2 + 1;
		if(wallCone.Tier1[conePosition].TypeFlag != SpaceType::EMPTY)
			currentDungeon.WallSets[wallCone.Tier1[conePosition].WallSetId - 1].DrawWall(MAZEVIEW, (WallPartId)i, 0, lastDrawn);		
	}

	if(wallCone.Tier2[1].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FARSIDEC_LEFT1, 0, lastDrawn);
	if(wallCone.Tier2[2].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, SIDEC_LEFT1, 0, lastDrawn);
	if(wallCone.Tier2[4].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, SIDEC_RIGHT1, 0, lastDrawn);
	if(wallCone.Tier2[5].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, FARSIDEC_RIGHT1, 0, lastDrawn);	

	for(int i = FORWARDB_LEFT1; i <= FORWARDB_RIGHT1; i++)
	{
		int conePosition = i - FORWARDB_LEFT1 + 2;
		if(wallCone.Tier2[conePosition].TypeFlag != SpaceType::EMPTY)
			currentDungeon.WallSets[wallCone.Tier2[conePosition].WallSetId - 1].DrawWall(MAZEVIEW, (WallPartId)i, 0, lastDrawn);
	}

	if(wallCone.Tier3[1].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, SIDEB_LEFT1, 0, lastDrawn);
	if(wallCone.Tier3[3].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, SIDEB_RIGHT1, 0, lastDrawn);

	for(int i = FORWARDA_LEFT1; i <= FORWARDA_RIGHT1; i++)
	{
		int conePosition = i - FORWARDA_LEFT1 + 1;
		if(wallCone.Tier3[conePosition].TypeFlag != SpaceType::EMPTY)
			currentDungeon.WallSets[wallCone.Tier3[conePosition].WallSetId - 1].DrawWall(MAZEVIEW, (WallPartId)i, 0, lastDrawn);
	}

	if(wallCone.Tier4[0].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, SIDEA_LEFT1, 0, lastDrawn);
	if(wallCone.Tier4[2].TypeFlag & SpaceType::WALL)
        currentDungeon.WallSets[0].DrawWall(MAZEVIEW, SIDEA_RIGHT1, 0, lastDrawn);
}