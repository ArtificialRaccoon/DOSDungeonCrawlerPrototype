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

void MazeViewRenderer::DrawForwardSwitch(Dungeon &currentDungeon, WallPartId wallPart, int switchId, int xPos)
{    
    std::string switchName = currentDungeon.SwitchList.at(switchId).SwitchSpriteSheet;
    if(currentDungeon.SwitchList.at(switchId).SwitchState == 0)
        switchName = switchName.append("A");
    else
        switchName = switchName.append("B");
    WallDeco &selectedDecoration = currentDungeon.SwitchSets[switchName];
    selectedDecoration.DrawWallDeco(MAZEVIEW, wallPart, xPos, false);
}

void MazeViewRenderer::DrawForwardDoor(Dungeon &currentDungeon, WallPartId wallPart, int doorId, int xPos)
{    
    if(!currentDungeon.DoorList[doorId].IsOpen)
    {
        std::string doorSheetName = currentDungeon.DoorList[doorId].DoorSpriteSheet;
        WallDeco &selectedDecoration = currentDungeon.DoorClosedSets[doorSheetName];
        selectedDecoration.DrawWallDeco(MAZEVIEW, wallPart, xPos, false);
    }
}

void MazeViewRenderer::DrawSideWall(std::vector<WallSet> wallSets, WallPartId wallPart, bool flip, int wallSetIndex, int xPos)
{
    WallSet &selectedWall = wallSets[wallSetIndex - 1];
    selectedWall.DrawWall(MAZEVIEW, wallPart, xPos, flip);
}

void MazeViewRenderer::DrawSideDecoration(Dungeon &currentDungeon, WallPartId wallPart, bool flip, int wallSetIndex, int xPos)
{
    WallDeco &selectedDecoration = currentDungeon.WallDecos[wallSetIndex - 1];
    selectedDecoration.DrawWallDeco(MAZEVIEW, wallPart, xPos, flip);
}

void MazeViewRenderer::DrawSideSwitch(Dungeon &currentDungeon, WallPartId wallPart, bool flip, int switchId, int xPos)
{
    std::string switchName = currentDungeon.SwitchList.at(switchId).SwitchSpriteSheet;
    if(currentDungeon.SwitchList.at(switchId).SwitchState == 0)
        switchName = switchName.append("A");
    else
        switchName = switchName.append("B");
    WallDeco &selectedDecoration = currentDungeon.SwitchSets[switchName];
    selectedDecoration.DrawWallDeco(MAZEVIEW, wallPart, xPos, flip);
}

void MazeViewRenderer::RenderVisionCone(Dungeon &currentDungeon, VisionCone &wallCone, VisionCone &decoCone)
{
    DrawBackground(false);

    //Render ForwardD
    for(int i = 0; i < 7; i++)
    {
        if(wallCone.Tier0[i].TypeFlag & SpaceType::WALL)
            DrawForwardWall(currentDungeon.WallSets, FORWARDD, wallCone.Tier0[i].WallSetId, ForwardXPosition[0][i]);
        if(wallCone.Tier0[i].TypeFlag & SpaceType::DOOR)
            DrawForwardWall(currentDungeon.DoorSets, FORWARDD, currentDungeon.DoorList[wallCone.Tier0[i].DoorId].DoorSetId, ForwardXPosition[0][i]);                    
        if(wallCone.Tier0[i].TypeFlag & SpaceType::SWITCH)
            DrawForwardSwitch(currentDungeon, FORWARDD, wallCone.Tier0[i].SwitchId, ForwardXPosition[0][i]);          
    }

    //Render Far/SideD
    for(int i = 0; i < 7; i++)
    {
        if(wallCone.Tier1[i].TypeFlag & SpaceType::WALL && i != 3)
            DrawSideWall(currentDungeon.WallSets, WallPartAtPosition[0][i], i > 3 ? true : false, wallCone.Tier1[i].WallSetId, SideXPosition[0][i]);
        if(wallCone.Tier1[i].TypeFlag & SpaceType::DOOR && i != 3)
            DrawSideWall(currentDungeon.DoorSets, WallPartAtPosition[0][i], i > 3 ? true : false, currentDungeon.DoorList[wallCone.Tier1[i].DoorId].DoorSetId, SideXPosition[0][i]);        
    }
    if(wallCone.Tier1[2].TypeFlag & SpaceType::SWITCH)
        DrawSideSwitch(currentDungeon, SIDED, false, wallCone.Tier1[2].SwitchId, SIDED_STARTX);
    if(wallCone.Tier1[4].TypeFlag & SpaceType::SWITCH)
        DrawSideSwitch(currentDungeon, SIDED, true, wallCone.Tier1[4].SwitchId, SIDED_STARTX + FORWARDC_WIDTH - SIDED_WIDTH); 

    //Render ForwardC
    for(int i = 1; i < 6; i++)
    {
        if(wallCone.Tier1[i].TypeFlag & SpaceType::WALL)
            DrawForwardWall(currentDungeon.WallSets, FORWARDC, wallCone.Tier1[i].WallSetId, ForwardXPosition[1][i]);
        if(wallCone.Tier1[i].TypeFlag & SpaceType::DOOR)
        {
            DrawForwardWall(currentDungeon.DoorSets, FORWARDC, currentDungeon.DoorList[wallCone.Tier1[i].DoorId].DoorSetId, ForwardXPosition[1][i]);
            DrawForwardDoor(currentDungeon, FORWARDC, wallCone.Tier1[i].DoorId, ForwardXPosition[1][i]);
        }
        if(wallCone.Tier1[i].TypeFlag & SpaceType::SWITCH)
            DrawForwardSwitch(currentDungeon, FORWARDC, wallCone.Tier1[i].SwitchId, ForwardXPosition[1][i]);        
    }

    //Render Far/SideC
    for(int i = 1; i < 6; i++)
    {
        if(wallCone.Tier2[i].TypeFlag & SpaceType::WALL && i != 3)
            DrawSideWall(currentDungeon.WallSets, WallPartAtPosition[1][i], i > 3 ? true : false, wallCone.Tier2[i].WallSetId, SideXPosition[1][i]);
        if(wallCone.Tier2[i].TypeFlag & SpaceType::DOOR && i != 3)
            DrawSideWall(currentDungeon.DoorSets, WallPartAtPosition[1][i], i > 3 ? true : false, currentDungeon.DoorList[wallCone.Tier2[i].DoorId].DoorSetId, SideXPosition[1][i]);        
    }     
    if(wallCone.Tier2[2].TypeFlag & SpaceType::SWITCH)
        DrawSideSwitch(currentDungeon, SIDEC, false, wallCone.Tier2[2].SwitchId, SIDEC_STARTX);
    if(wallCone.Tier2[4].TypeFlag & SpaceType::SWITCH)
        DrawSideSwitch(currentDungeon, SIDEC, true, wallCone.Tier2[4].SwitchId, SIDEC_STARTX + FORWARDB_WIDTH - SIDEC_WIDTH); 

    //Render ForwardB
    for(int i = 2; i < 5; i++)
    {
        if(wallCone.Tier2[i].TypeFlag & SpaceType::WALL)
            DrawForwardWall(currentDungeon.WallSets, FORWARDB, wallCone.Tier2[i].WallSetId, ForwardXPosition[2][i]);
        if(wallCone.Tier2[i].TypeFlag & SpaceType::DOOR)
        {
            DrawForwardWall(currentDungeon.DoorSets, FORWARDB, currentDungeon.DoorList[wallCone.Tier2[i].DoorId].DoorSetId, ForwardXPosition[2][i]);  
            DrawForwardDoor(currentDungeon, FORWARDB, wallCone.Tier2[i].DoorId, ForwardXPosition[2][i]);
        }
        if(wallCone.Tier2[i].TypeFlag & SpaceType::SWITCH)
            DrawForwardSwitch(currentDungeon, FORWARDB, wallCone.Tier2[i].SwitchId, ForwardXPosition[2][i]);
    }

    //Render SideB
    for(int i = 1; i < 4; i++)
    {
        if(wallCone.Tier3[i].TypeFlag & SpaceType::WALL && i != 2)
            DrawSideWall(currentDungeon.WallSets, SIDEB, i == 3 ? true : false, wallCone.Tier3[i].WallSetId, SideXPosition[2][i + 1]);    
        if(wallCone.Tier3[i].TypeFlag & SpaceType::DOOR && i != 2)
            DrawSideWall(currentDungeon.DoorSets, SIDEB, i == 3 ? true : false, currentDungeon.DoorList[wallCone.Tier3[i].DoorId].DoorSetId, SideXPosition[2][i + 1]);    
        if(wallCone.Tier3[i].TypeFlag & SpaceType::SWITCH && i != 2)
            DrawSideSwitch(currentDungeon, SIDEB, i == 3 ? true : false, wallCone.Tier3[i].SwitchId, SideXPosition[2][i + 1]);            
    }  

    //Render ForwardA
    for(int i = 1; i < 4; i++)
    {
        if(wallCone.Tier3[i].TypeFlag & SpaceType::WALL)
            DrawForwardWall(currentDungeon.WallSets, FORWARDA, wallCone.Tier3[i].WallSetId, ForwardXPosition[3][i + 1]);
        if(wallCone.Tier3[i].TypeFlag & SpaceType::DOOR)
        {
            DrawForwardWall(currentDungeon.DoorSets, FORWARDA, currentDungeon.DoorList[wallCone.Tier3[i].DoorId].DoorSetId, ForwardXPosition[3][i + 1]);
            DrawForwardDoor(currentDungeon, FORWARDA, wallCone.Tier3[i].DoorId, ForwardXPosition[3][i + 1]);
        }
        if(wallCone.Tier3[i].TypeFlag & SpaceType::SWITCH)
            DrawForwardSwitch(currentDungeon, FORWARDA, wallCone.Tier3[i].SwitchId, ForwardXPosition[3][i + 1]);
    }

    //Render SideA
    for(int i = 0; i < 3; i++)
    {
        if(wallCone.Tier4[i].TypeFlag & SpaceType::WALL && i != 1)
            DrawSideWall(currentDungeon.WallSets, SIDEA, i == 2 ? true : false, wallCone.Tier4[i].WallSetId, SideXPosition[3][i + 2]);    
        if(wallCone.Tier4[i].TypeFlag & SpaceType::DOOR && i != 1)
            DrawSideWall(currentDungeon.DoorSets, SIDEA, i == 2 ? true : false, currentDungeon.DoorList[wallCone.Tier4[i].DoorId].DoorSetId, SideXPosition[3][i + 2]);    
        if(wallCone.Tier4[i].TypeFlag & SpaceType::SWITCH && i != 1)
            DrawSideSwitch(currentDungeon, SIDEA, i == 2 ? true : false, wallCone.Tier4[i].SwitchId, SideXPosition[3][i + 2]);            
    }  
}
