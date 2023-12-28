#include "MazeViewRenderer.h"

void MazeViewRenderer::Init()
{
    BACKGROUND = create_bitmap(BACK_WIDTH, BACK_HEIGHT);
    MAZEVIEW = create_bitmap(BACK_WIDTH, BACK_HEIGHT);

    BACKGROUND = load_bitmap(".\\BACKSETS\\OVERLOOK.bmp", palette_background);
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

void MazeViewRenderer::DrawForwardWall(Dungeon &currentDungeon, WallPartId wallPart, int wallSetIndex, int xPos)
{
    WallSet &selectedWall = currentDungeon.WallSets[wallSetIndex - 1];
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
        if(wallCone.Tier0[i] > 0)
            DrawForwardWall(currentDungeon, FORWARDD, wallCone.Tier0[i], FORWARDD_STARTX + ((i - 3) * FORWARDD_WIDTH));
        if(decoCone.Tier0[i] > 0)
            DrawForwardDecoration(currentDungeon, FORWARDD, decoCone.Tier0[i], FORWARDD_STARTX + ((i - 3) * FORWARDD_WIDTH));        
    }

    //Render Far/SideD
    if(wallCone.Tier1[0] > 0)
        DrawSideWall(currentDungeon, FARSIDED2, false, wallCone.Tier1[0], 0);
    if(wallCone.Tier1[1] > 0)
        DrawSideWall(currentDungeon, FARSIDED1, false, wallCone.Tier1[1], FARSIDED1_STARTX);
    if(wallCone.Tier1[2] > 0)
        DrawSideWall(currentDungeon, SIDED, false, wallCone.Tier1[2], SIDED_STARTX);
    if(wallCone.Tier1[4] > 0)
        DrawSideWall(currentDungeon, SIDED, true, wallCone.Tier1[4], SIDED_STARTX + FORWARDC_WIDTH - SIDED_WIDTH);
    if(wallCone.Tier1[5] > 0)
        DrawSideWall(currentDungeon, FARSIDED1, true, wallCone.Tier1[5], FORWARDD_STARTX + FORWARDD_WIDTH * 2);
    if(wallCone.Tier1[6] > 0)
        DrawSideWall(currentDungeon, FARSIDED2, true, wallCone.Tier1[6], FORWARDD_STARTX + FORWARDD_WIDTH * 3);
    if(decoCone.Tier1[0] > 0)
        DrawSideDecoration(currentDungeon, FARSIDED2, false, decoCone.Tier1[0], 0);
    if(decoCone.Tier1[1] > 0)
        DrawSideDecoration(currentDungeon, FARSIDED1, false, decoCone.Tier1[1], FARSIDED1_STARTX);
    if(decoCone.Tier1[2] > 0)
        DrawSideDecoration(currentDungeon, SIDED, false, decoCone.Tier1[2], SIDED_STARTX);
    if(decoCone.Tier1[4] > 0)
        DrawSideDecoration(currentDungeon, SIDED, true, decoCone.Tier1[4], SIDED_STARTX + FORWARDC_WIDTH - SIDED_WIDTH);
    if(decoCone.Tier1[5] > 0)
        DrawSideDecoration(currentDungeon, FARSIDED1, true, decoCone.Tier1[5], FORWARDD_STARTX + FORWARDD_WIDTH * 2);
    if(decoCone.Tier1[6] > 0)
        DrawSideDecoration(currentDungeon, FARSIDED2, true, decoCone.Tier1[6], FORWARDD_STARTX + FORWARDD_WIDTH * 3);


    //Render ForwardC
    for(int i = 0; i < 7; i++)
    {
        if(wallCone.Tier1[i] > 0)
            DrawForwardWall(currentDungeon, FORWARDC, wallCone.Tier1[i], FORWARDC_STARTX + ((i - 3) * FORWARDC_WIDTH));
        if(decoCone.Tier1[i] > 0)
            DrawForwardDecoration(currentDungeon, FORWARDC, decoCone.Tier1[i], FORWARDC_STARTX + ((i - 3) * FORWARDC_WIDTH));
    }

    //Render Far/SideC
    if(wallCone.Tier2[1] > 0)
        DrawSideWall(currentDungeon, FARSIDEC, false, wallCone.Tier2[1], 0);
    if(wallCone.Tier2[2] > 0)
        DrawSideWall(currentDungeon, SIDEC, false, wallCone.Tier2[2], SIDEC_STARTX);
    if(wallCone.Tier2[4] > 0)
        DrawSideWall(currentDungeon, SIDEC, true, wallCone.Tier2[4], SIDEC_STARTX + FORWARDB_WIDTH - SIDEC_WIDTH);
    if(wallCone.Tier2[5] > 0)
        DrawSideWall(currentDungeon, FARSIDEC, true, wallCone.Tier2[5], (3 * FORWARDC_WIDTH) + FARSIDEC_WIDTH);
    if(decoCone.Tier2[1] > 0)
        DrawSideDecoration(currentDungeon, FARSIDEC, false, decoCone.Tier2[1], 0);
    if(decoCone.Tier2[2] > 0)
        DrawSideDecoration(currentDungeon, SIDEC, false, decoCone.Tier2[2], SIDEC_STARTX);
    if(decoCone.Tier2[4] > 0)
        DrawSideDecoration(currentDungeon, SIDEC, true, decoCone.Tier2[4], SIDEC_STARTX + FORWARDB_WIDTH - SIDEC_WIDTH);
    if(decoCone.Tier2[5] > 0)
        DrawSideDecoration(currentDungeon, FARSIDEC, true, decoCone.Tier2[5], (3 * FORWARDC_WIDTH) + FARSIDEC_WIDTH);


    //Render ForwardB
    for(int i = 0; i < 7; i++)
    {
        if(wallCone.Tier2[i] > 0)
            DrawForwardWall(currentDungeon, FORWARDB, wallCone.Tier2[i], SIDEC_STARTX + ((i - 3) * FORWARDB_WIDTH));
        if(decoCone.Tier2[i] > 0)
            DrawForwardDecoration(currentDungeon, FORWARDB, decoCone.Tier2[i], SIDEC_STARTX + ((i - 3) * FORWARDB_WIDTH));
    }

    //Render SideB
    if(wallCone.Tier3[1] > 0)
        DrawSideWall(currentDungeon, SIDEB, false, wallCone.Tier3[1], SIDEB_STARTX);
    if(wallCone.Tier3[3] > 0)
        DrawSideWall(currentDungeon, SIDEB, true, wallCone.Tier3[3], SIDEB_STARTX + FORWARDB_WIDTH + SIDEB_WIDTH);
    if(decoCone.Tier3[1] > 0)
        DrawSideDecoration(currentDungeon, SIDEB, false, decoCone.Tier3[1], SIDEB_STARTX);
    if(decoCone.Tier3[3] > 0)
        DrawSideDecoration(currentDungeon, SIDEB, true, decoCone.Tier3[3], SIDEB_STARTX + FORWARDB_WIDTH + SIDEB_WIDTH);

    //Render ForwardA
     for(int i = 1; i < 4; i++)
    {
        if(wallCone.Tier3[i] > 0)
            DrawForwardWall(currentDungeon, FORWARDA, wallCone.Tier3[i], SIDEB_STARTX + ((i - 2) * FORWARDA_WIDTH));
        if(decoCone.Tier3[i] > 0)
            DrawForwardDecoration(currentDungeon, FORWARDA, decoCone.Tier3[i], SIDEB_STARTX + ((i - 2) * FORWARDA_WIDTH));
    }

    //Render SideA
    if(wallCone.Tier4[0] > 0)
        DrawSideWall(currentDungeon, SIDEA, false, wallCone.Tier4[0], 0);
    if(wallCone.Tier4[2] > 0)
        DrawSideWall(currentDungeon, SIDEA, true, wallCone.Tier4[2], 0 + FORWARDA_WIDTH + SIDEA_WIDTH);
    if(decoCone.Tier4[0] > 0)
        DrawSideDecoration(currentDungeon, SIDEA, false, decoCone.Tier4[0], 0);
    if(decoCone.Tier4[2] > 0)
        DrawSideDecoration(currentDungeon, SIDEA, true, decoCone.Tier4[2], 0 + FORWARDA_WIDTH + SIDEA_WIDTH);    
}
