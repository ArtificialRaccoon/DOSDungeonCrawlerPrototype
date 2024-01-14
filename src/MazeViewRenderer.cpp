#include "MazeViewRenderer.h"

void MazeViewRenderer::Init(Dungeon &currentDungeon)
{
    BACKGROUND = create_bitmap(BACK_WIDTH, BACK_HEIGHT);
    MAZEVIEW = create_bitmap(BACK_WIDTH, BACK_HEIGHT);

    BACKGROUND = load_bitmap((".\\BACKSETS\\" + currentDungeon.FloorSet + ".bmp").c_str(), palette_background);
    if (!BACKGROUND) {
      set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      allegro_message("Error reading bitmap file");
      exit(0);
    }
}

void MazeViewRenderer::DrawBackground(bool flip)
{
    if(flip)
        draw_sprite_h_flip(MAZEVIEW, BACKGROUND, 0, 0);
    else
        draw_sprite(MAZEVIEW, BACKGROUND, 0, 0);
}

void MazeViewRenderer::DrawForwardWall(std::vector<WallSet> wallSets, WallPartId wallPart, int wallSetIndex, int xPos)
{
    WallSet &selectedWall = wallSets[wallSetIndex - 1];
    selectedWall.DrawWall(MAZEVIEW, wallPart, xPos, false);
}

void MazeViewRenderer::DrawForwardDecoration(Dungeon &currentDungeon, WallPartId wallPart, int wallSetIndex, int xPos)
{    
    WallDeco &selectedDecoration = currentDungeon.WallDecos[wallSetIndex - 1];
    selectedDecoration.DrawWallDeco(MAZEVIEW, wallPart, xPos, false);
}

void MazeViewRenderer::DrawSideWall(Dungeon &currentDungeon, WallPartId wallPart, bool flip, int wallSetIndex, int xPos)
{
    WallSet &selectedWall = currentDungeon.WallSets[wallSetIndex - 1];
    selectedWall.DrawWall(MAZEVIEW, wallPart, xPos, flip);
}

void MazeViewRenderer::DrawSideDecoration(Dungeon &currentDungeon, WallPartId wallPart, bool flip, int wallSetIndex, int xPos)
{
    WallDeco &selectedWall = currentDungeon.WallDecos[wallSetIndex - 1];
    selectedWall.DrawWallDeco(MAZEVIEW, wallPart, xPos, flip);
}

void MazeViewRenderer::RenderVisionCone(Dungeon &currentDungeon, VisionCone &wallCone, VisionCone &decoCone)
{
    DrawBackground(false);

    //Render ForwardD
    for(int i = 0; i < 7; i++)
    {
        if(wallCone.Tier0[i].TypeFlag & WALL)
            DrawForwardWall(currentDungeon.WallSets, FORWARDD, wallCone.Tier0[i].WallSetId, FORWARDD_STARTX + ((i - 3) * FORWARDD_WIDTH));
        if(wallCone.Tier0[i].TypeFlag & DOOR)
            DrawForwardWall(currentDungeon.DoorSets, FORWARDC, currentDungeon.DoorList[wallCone.Tier0[i].DoorId].DoorSetId, FORWARDD_STARTX + ((i - 3) * FORWARDD_WIDTH));                    
    }

    //Render Far/SideD
    if(wallCone.Tier1[0].TypeFlag & WALL)
        DrawSideWall(currentDungeon, FARSIDED2, false, wallCone.Tier1[0].WallSetId, 0);
    if(wallCone.Tier1[1].TypeFlag & WALL)
        DrawSideWall(currentDungeon, FARSIDED1, false, wallCone.Tier1[1].WallSetId, FARSIDED1_STARTX);
    if(wallCone.Tier1[2].TypeFlag & WALL)
        DrawSideWall(currentDungeon, SIDED, false, wallCone.Tier1[2].WallSetId, SIDED_STARTX);
    if(wallCone.Tier1[4].TypeFlag & WALL)
        DrawSideWall(currentDungeon, SIDED, true, wallCone.Tier1[4].WallSetId, SIDED_STARTX + FORWARDC_WIDTH - SIDED_WIDTH);
    if(wallCone.Tier1[5].TypeFlag & WALL)
        DrawSideWall(currentDungeon, FARSIDED1, true, wallCone.Tier1[5].WallSetId, FORWARDD_STARTX + FORWARDD_WIDTH * 2);
    if(wallCone.Tier1[6].TypeFlag & WALL)
        DrawSideWall(currentDungeon, FARSIDED2, true, wallCone.Tier1[6].WallSetId, FORWARDD_STARTX + FORWARDD_WIDTH * 3);


    //Render ForwardC
    for(int i = 1; i < 6; i++)
    {
        if(wallCone.Tier1[i].TypeFlag & WALL)
            DrawForwardWall(currentDungeon.WallSets, FORWARDC, wallCone.Tier1[i].WallSetId, FORWARDC_STARTX + ((i - 3) * FORWARDC_WIDTH));
        if(wallCone.Tier1[i].TypeFlag & DOOR)
            DrawForwardWall(currentDungeon.DoorSets, FORWARDC, currentDungeon.DoorList[wallCone.Tier1[i].DoorId].DoorSetId, FORWARDC_STARTX + ((i - 3) * FORWARDC_WIDTH));
    }

    //Render Far/SideC
    if(wallCone.Tier2[1].TypeFlag & WALL)
        DrawSideWall(currentDungeon, FARSIDEC, false, wallCone.Tier2[1].WallSetId, 0);
    if(wallCone.Tier2[2].TypeFlag & WALL)
        DrawSideWall(currentDungeon, SIDEC, false, wallCone.Tier2[2].WallSetId, SIDEC_STARTX);
    if(wallCone.Tier2[4].TypeFlag & WALL)
        DrawSideWall(currentDungeon, SIDEC, true, wallCone.Tier2[4].WallSetId, SIDEC_STARTX + FORWARDB_WIDTH - SIDEC_WIDTH);
    if(wallCone.Tier2[5].TypeFlag & WALL)
        DrawSideWall(currentDungeon, FARSIDEC, true, wallCone.Tier2[5].WallSetId, (3 * FORWARDC_WIDTH) + FARSIDEC_WIDTH);


    //Render ForwardB
    for(int i = 2; i < 5; i++)
    {
        if(wallCone.Tier2[i].TypeFlag & WALL)
            DrawForwardWall(currentDungeon.WallSets, FORWARDB, wallCone.Tier2[i].WallSetId, SIDEC_STARTX + ((i - 3) * FORWARDB_WIDTH));
        if(wallCone.Tier2[i].TypeFlag & DOOR)
            DrawForwardWall(currentDungeon.DoorSets, FORWARDB, currentDungeon.DoorList[wallCone.Tier2[i].DoorId].DoorSetId, SIDEC_STARTX + ((i - 3) * FORWARDB_WIDTH));  
    }

    //Render SideB
    if(wallCone.Tier3[1].TypeFlag & WALL)
        DrawSideWall(currentDungeon, SIDEB, false, wallCone.Tier3[1].WallSetId, SIDEB_STARTX);
    if(wallCone.Tier3[3].TypeFlag & WALL) 
        DrawSideWall(currentDungeon, SIDEB, true, wallCone.Tier3[3].WallSetId, SIDEB_STARTX + FORWARDB_WIDTH + SIDEB_WIDTH);

    //Render ForwardA
    for(int i = 1; i < 4; i++)
    {
        if(wallCone.Tier3[i].TypeFlag & WALL)
            DrawForwardWall(currentDungeon.WallSets, FORWARDA, wallCone.Tier3[i].WallSetId, SIDEB_STARTX + ((i - 2) * FORWARDA_WIDTH));
        if(wallCone.Tier3[i].TypeFlag & DOOR)
            DrawForwardWall(currentDungeon.DoorSets, FORWARDA, currentDungeon.DoorList[wallCone.Tier3[i].DoorId].DoorSetId, SIDEB_STARTX + ((i - 2) * FORWARDA_WIDTH));
    }

    //Render SideA
    if(wallCone.Tier4[0].TypeFlag & WALL)
        DrawSideWall(currentDungeon, SIDEA, false, wallCone.Tier4[0].WallSetId, 0);
    if(wallCone.Tier4[2].TypeFlag & WALL)
        DrawSideWall(currentDungeon, SIDEA, true, wallCone.Tier4[2].WallSetId, 0 + FORWARDA_WIDTH + SIDEA_WIDTH);
}
