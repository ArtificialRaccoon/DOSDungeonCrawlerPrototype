#include "MazeViewRenderer.h"

const unsigned FLIPPED_HORIZONTALLY_FLAG  = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG    = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG    = 0x20000000;
const int backgroundWidth = 22;
const int backgroundHeight = 15;

void MazeViewRenderer::Init(BITMAP* inputBUFFER, Dungeon &currentDungeon)
{    
    BACKGROUND = create_bitmap(MAZEVIEW_WIDTH, MAZEVIEW_HEIGHT);
    MAZEVIEW = create_sub_bitmap(inputBUFFER, MAZEVIEW_X, MAZEVIEW_Y, MAZEVIEW_WIDTH, MAZEVIEW_HEIGHT);    
    LoadBackground(currentDungeon.FloorSet);
	lastDrawn.resize(15 * 22, TileReference(-1, -1));
}

void MazeViewRenderer::LoadBackground(std::string backgroundName)
{
	std::ifstream ifs((".\\BACKSETS\\" + backgroundName + ".tmj").c_str());
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));    
    json::jobject parsedObject = json::jobject::parse(content);
    
    backgroundTileWidth = parsedObject["tilewidth"];
    backgroundTileHeight = parsedObject["tileheight"];
    backgroundTilesetWidth = parsedObject["width"];
    backgroundTilesetHeight = parsedObject["height"];
	normalTileMap = parsedObject["data"];
	flippedTileMap = parsedObject["data"];
	for (int row = 0; row < backgroundTilesetHeight; row++) 
	{
        std::reverse(flippedTileMap.begin() + row * backgroundTilesetWidth, flippedTileMap.begin() + (row + 1) * backgroundTilesetWidth);
    }

	BACKGROUND = load_bitmap((".\\BACKSETS\\" + ((std::string)parsedObject["TileSet"]) + ".bmp").c_str(), CommonGUI::Instance().GetPalette());
	if (!BACKGROUND)
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Error reading backset bitmap");
		allegro_message(backgroundName.c_str());
		exit(0);
    }

	TILE = create_bitmap(backgroundTileWidth, backgroundTileHeight);
}

void MazeViewRenderer::DrawBackground()
{
	std::vector<int> *tileMap = flippedHorizontally ? &flippedTileMap : &normalTileMap;
	int destYPos = 0;
	for (int y = 0; y < backgroundHeight; y++)
    {
        int destXPos = 0;
        unsigned tileIndex = y * backgroundWidth;

        for (int x = 0; x < backgroundWidth; x++)
        {                        
            unsigned tileID = (*tileMap)[tileIndex];
            TileReference newTile(0, tileID);

            if (lastDrawn[tileIndex] != newTile)
            {                
                lastDrawn[tileIndex] = newTile;
                if (tileID == 0)
                {
                    tileIndex++;
                    destXPos += backgroundTileWidth;
                    continue;
                }

                tileID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);                
                int srcXPos = backgroundTileWidth * ((tileID - 1) % backgroundTilesetWidth);
                int srcYPos = backgroundTileHeight * ((tileID - 1) / backgroundTilesetWidth);

				if (flippedHorizontally)
                {
                    blit(BACKGROUND, TILE, srcXPos, srcYPos, 0, 0, backgroundTileWidth, backgroundTileHeight);
                    draw_sprite_h_flip(MAZEVIEW, TILE, destXPos, destYPos);
                }
				else
					masked_blit(BACKGROUND, MAZEVIEW, srcXPos, srcYPos, destXPos, destYPos, backgroundTileWidth, backgroundTileHeight);            
            }

            tileIndex++;
            destXPos += backgroundTileWidth;
        }
        destYPos += backgroundTileHeight;
    }
}

void MazeViewRenderer::RenderVisionCone(Dungeon &currentDungeon, VisionCone &wallCone, VisionCone &decoCone)
{
	DrawBackground();

	for(int i = FORWARDD_LEFT3; i <= FORWARDD_RIGHT3; i++)
	{
		if(wallCone.Tier0[i].TypeFlag != SpaceType::EMPTY)
			DrawMapSpace(currentDungeon, wallCone.Tier0[i], (WallPartId)i);			
	}	

	for(int i = FARSIDED2_LEFT1; i <= FARSIDED2_RIGHT1; i++)
	{
		int conePosition = i - FARSIDED2_LEFT1; 
		if(conePosition >= 3)
			conePosition++;

		if(wallCone.Tier1[conePosition].TypeFlag != SpaceType::EMPTY)
			DrawMapSpace(currentDungeon, wallCone.Tier1[conePosition], (WallPartId)i);
	}

	for(int i = FORWARDC_LEFT2; i <= FORWARDC_RIGHT2; i++)
	{
		int conePosition = i - FORWARDC_LEFT2 + 1;
		if(wallCone.Tier1[conePosition].TypeFlag != SpaceType::EMPTY)
			DrawMapSpace(currentDungeon, wallCone.Tier1[conePosition], (WallPartId)i);		
	}

	for(int i = FARSIDEC_LEFT1; i <= FARSIDEC_RIGHT1; i++)
	{
		int conePosition = i - FARSIDEC_LEFT1 + 1;
		if(conePosition >= 3)
			conePosition++;		
		if(wallCone.Tier2[conePosition].TypeFlag != SpaceType::EMPTY)
			DrawMapSpace(currentDungeon, wallCone.Tier2[conePosition], (WallPartId)i);		
	}

	for(int i = FORWARDB_LEFT1; i <= FORWARDB_RIGHT1; i++)
	{
		int conePosition = i - FORWARDB_LEFT1 + 2;
		if(wallCone.Tier2[conePosition].TypeFlag != SpaceType::EMPTY)
			DrawMapSpace(currentDungeon, wallCone.Tier2[conePosition], (WallPartId)i);
	}

	for(int i = SIDEB_LEFT1; i <= SIDEB_RIGHT1; i++)
	{
		int conePosition = i - SIDEB_LEFT1 + 1;
		if(conePosition >= 2)
			conePosition++;			
		if(wallCone.Tier3[conePosition].TypeFlag != SpaceType::EMPTY)
			DrawMapSpace(currentDungeon, wallCone.Tier3[conePosition], (WallPartId)i);
	}

	for(int i = FORWARDA_LEFT1; i <= FORWARDA_RIGHT1; i++)
	{
		int conePosition = i - FORWARDA_LEFT1 + 1;
		if(wallCone.Tier3[conePosition].TypeFlag != SpaceType::EMPTY)
			DrawMapSpace(currentDungeon, wallCone.Tier3[conePosition], (WallPartId)i);
	}

	for(int i = SIDEA_LEFT1; i <= SIDEA_RIGHT1; i++)
	{
		int conePosition = i - SIDEA_LEFT1;
		if(conePosition >= 1)
			conePosition++;		
		if(wallCone.Tier4[conePosition].TypeFlag != SpaceType::EMPTY)
			DrawMapSpace(currentDungeon, wallCone.Tier4[conePosition], (WallPartId)i);
	}
}

void MazeViewRenderer::DrawMapSpace(Dungeon &currentDungeon, MapSpace &space, WallPartId spriteId)
{
	if(space.TypeFlag & SpaceType::WALL || space.TypeFlag & SpaceType::DOOR)
		currentDungeon.WallSets[space.WallSetId - 1].DrawWall(MAZEVIEW, spriteId, space.WallSetId, lastDrawn);
	
	if(space.TypeFlag & SpaceType::SWITCH)
	{
		SwitchType switchObj = currentDungeon.SwitchList[space.SwitchId];
		if(switchObj.SwitchState == 0)		
			currentDungeon.DecoSets[switchObj.UpSpriteSheet].DrawDeco(MAZEVIEW, spriteId, switchObj.UpSpriteSheet, lastDrawn);
		else
			currentDungeon.DecoSets[switchObj.DownSpriteSheet].DrawDeco(MAZEVIEW, spriteId, switchObj.DownSpriteSheet, lastDrawn);
	}
}