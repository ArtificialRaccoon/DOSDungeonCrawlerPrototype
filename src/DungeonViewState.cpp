#include "DungeonViewState.h"

DungeonViewState DungeonViewState::mDungeonViewState;

void DungeonViewState::InitState()
{
    DISPLAY = create_video_bitmap(SCREEN_W, SCREEN_H);
    BUFFER = create_video_bitmap(SCREEN_W, SCREEN_H);
    mazeUIObj.Init(BUFFER);
    dungeonObj.LoadDungeon();
    mazeRenderer.Init(BUFFER, dungeonObj);

    facing = NORTH;
    playerX = 1;
    playerY = 1;

    ticks = 0;
    mouseDebounce = 0;

	theme = load_midi((".\\MUSIC\\" + dungeonObj.Theme + ".MID").c_str());
	play_midi(theme, TRUE);    
}

void DungeonViewState::Pause()
{

}

void DungeonViewState::Resume()
{

}

void DungeonViewState::AquireInput(GameProcessor* game)
{
    if(keypressed())
    {
        switch(readkey() >> 8)
        {
            case KEY_W:
                deltaY = 1;  
                break;
            case KEY_A:
                facing = (Rotation)(Wrap((int)facing - 1, 0, 3));
                screenInvalidated = true;
                break;
            case KEY_S:
                deltaY = -1;
                break;
            case KEY_D:
                facing = (Rotation)(Wrap((int)facing + 1, 0, 3));
                screenInvalidated = true;
                break;
            case KEY_Q:
                deltaX = 1;
                break;
            case KEY_E:
                deltaX = -1;
                break;
            case KEY_ENTER:
                interactPressed = true;
                break;
            case KEY_ESC:
                game->PushState(PauseState::Instance());
                break;
        }
    }

    if(mouse_b & 1 && mouseDebounce == 0)
    {
        if(!(mouse_x < BUTTON_FORWARD_X || mouse_x > BUTTON_FORWARD_X + NAV_WIDTH || mouse_y < BUTTON_FORWARD_Y || mouse_y > BUTTON_FORWARD_Y + NAV_HEIGHT))
            deltaY = 1;
        else if(!(mouse_x < BUTTON_ROTLEFT_X || mouse_x > BUTTON_ROTLEFT_X + NAV_WIDTH || mouse_y < BUTTON_ROTLEFT_Y || mouse_y > BUTTON_ROTLEFT_Y + NAV_HEIGHT))
            facing = (Rotation)(Wrap((int)facing - 1, 0, 3));
        else if(!(mouse_x < BUTTON_BACKWARD_X || mouse_x > BUTTON_BACKWARD_X + NAV_WIDTH || mouse_y < BUTTON_BACKWARD_Y || mouse_y > BUTTON_BACKWARD_Y + NAV_HEIGHT))
            deltaY = -1;
        else if(!(mouse_x < BUTTON_ROTRIGHT_X || mouse_x > BUTTON_ROTRIGHT_X + NAV_WIDTH || mouse_y < BUTTON_ROTRIGHT_Y || mouse_y > BUTTON_ROTRIGHT_Y + NAV_HEIGHT))
            facing = (Rotation)(Wrap((int)facing + 1, 0, 3));
        else if(!(mouse_x < BUTTON_LEFT_X || mouse_x > BUTTON_LEFT_X + NAV_WIDTH || mouse_y < BUTTON_LEFT_Y || mouse_y > BUTTON_LEFT_Y + NAV_HEIGHT))
            deltaX = 1;
        else if(!(mouse_x < BUTTON_RIGHT_X || mouse_x > BUTTON_RIGHT_X + NAV_WIDTH || mouse_y < BUTTON_RIGHT_Y || mouse_y > BUTTON_RIGHT_Y + NAV_HEIGHT))
            deltaX = -1;

        mouseDebounce++;
    }

    ticks++;
    if(ticks == 60)
        ticks = 0;

    if(mouseDebounce > 0)
    {
        if(mouse_b & 1)
        {
            mouseDebounce++;
            if(mouseDebounce >= 15)
                mouseDebounce = 0;
        }
        else
            mouseDebounce = 0;
    }
}

void DungeonViewState::ProcessInput(GameProcessor* game)
{    
    switch(facing)
    {
        case NORTH:
            ComputeVision(false, -1, deltaY, deltaX);
            break;
        case SOUTH:
            ComputeVision(false, 1, deltaY, deltaX);
            break;
        case EAST:
            ComputeVision(true, 1, deltaY, deltaX);
            break;
        case WEST:
            ComputeVision(true, -1, deltaY, deltaX);
            break;
    }

    deltaX = deltaY = 0;

    if(interactPressed)
    {
        interactPressed = false;
        int interactPosition[2] = { playerY, playerX };                
        switch (facing)
        {
            case NORTH:
                interactPosition[0]--; 
                break;
            case EAST:
                interactPosition[1]++;
                break;
            case SOUTH:
                interactPosition[0]++;
                break;
            case WEST:
                interactPosition[1]--;
                break;
        }

        //Check Switches
        for (std::map<int, SwitchType>::iterator it = dungeonObj.SwitchList.begin(); it != dungeonObj.SwitchList.end(); it++)
        {
            SwitchType& gameSwitch = it->second;
            if(interactPosition[0] == gameSwitch.Location[0] && interactPosition[1] == gameSwitch.Location[1])
            {
                gameSwitch.SwitchState = (gameSwitch.SwitchState == 0 ? 1 : 0);                            
                play_sample(dungeonObj.Effects.at(gameSwitch.Effect), 255, 128, 1000, FALSE);
            }
        }           
        
        //Update Door States (check combinations)
        for (std::map<int, DoorType>::iterator doorIt = dungeonObj.DoorList.begin(); doorIt != dungeonObj.DoorList.end(); doorIt++)
        {            
            DoorType& door = doorIt->second;                        
            bool doorUnlocked = true;
            bool currentDoorState = door.IsOpen;

            for (std::map<int, int>::iterator comboIt = door.Combination.begin(); comboIt != door.Combination.end(); comboIt++)
            {
                if(dungeonObj.SwitchList.at(comboIt->first).SwitchState != comboIt->second)
                    doorUnlocked = false;                
            }

            door.IsOpen = doorUnlocked;       
            if(currentDoorState != door.IsOpen)  
                play_sample(dungeonObj.Effects.at(door.Effect), 255, 128, 1000, FALSE);
        }        
    }
}

void DungeonViewState::Render(GameProcessor* game)
{     
    unsigned long current_time = time(NULL);
    if (current_time != last_time) {
        fps = frame_count;
        frame_count = 0;
        last_time = current_time;
    }

    if(firstRender)
        mazeUIObj.DrawMazeUI();

    if(firstRender || screenInvalidated)
        mazeRenderer.RenderVisionCone(dungeonObj, wallCone, decoCone);

    rectfill(BUFFER, 8, 8, 100, 20, 66);
    sprintf(fps_text, "FPS: %.2f", fps);
    textout_ex(BUFFER, font, fps_text, 10, 10, 16, -1);
    frame_count++;

    show_mouse(BUFFER);
    blit(BUFFER, DISPLAY, 0, 0, 0, 0, 320, 200);
    
    firstRender = false;
    screenInvalidated = false;
}

void DungeonViewState::ComputeVision(bool calculateForX, int deltaSign, int deltaY, int deltaX)
{
    int a, b, mapN1, mapN2;

    // Update player position
    if (calculateForX)
    {
        if (dungeonObj.WallMap[playerY - (deltaSign * deltaX)][playerX + (deltaSign * deltaY)].WallSetId < 1) 
        {
            bool canMove = false;
            int doorIndex = dungeonObj.WallMap[playerY - (deltaSign * deltaX)][playerX + (deltaSign * deltaY)].DoorId;
            if(doorIndex > 0 && (dungeonObj.DoorList.at(doorIndex).IsOpen && doorIndex > 0) || doorIndex == 0)
                canMove = true;

            if(canMove)
            {
                playerX += deltaSign * deltaY;
                playerY -= deltaSign * deltaX;
                screenInvalidated |= (deltaSign * deltaY != 0) || (deltaSign * deltaX != 0);
            }
        }
        a = playerX;
        b = playerY;
        mapN1 = dungeonObj.WallMap.size();
        mapN2 = dungeonObj.WallMap[0].size();
    } 
    else
    {
        if (dungeonObj.WallMap[playerY + (deltaSign * deltaY)][playerX + (deltaSign * deltaX)].WallSetId < 1)
        {
            bool canMove = false;
            int doorIndex = dungeonObj.WallMap[playerY + (deltaSign * deltaY)][playerX + (deltaSign * deltaX)].DoorId;
            if(doorIndex > 0 && (dungeonObj.DoorList.at(doorIndex).IsOpen && doorIndex > 0) || doorIndex == 0)
                canMove = true;

            if(canMove)
            {
                playerY += deltaSign * deltaY;
                playerX += deltaSign * deltaX;
                screenInvalidated |= (deltaSign * deltaY != 0) || (deltaSign * deltaX != 0);
            }
        }
        a = playerY;
        b = playerX;
        mapN1 = dungeonObj.WallMap[0].size();
        mapN2 = dungeonObj.WallMap.size();
    }  

    UpdateCone(wallCone.Tier0, calculateForX, a, b, mapN1, mapN2, deltaSign, 4, 7, -3);
    UpdateCone(wallCone.Tier1, calculateForX, a, b, mapN1, mapN2, deltaSign, 3, 7, -3);
    UpdateCone(wallCone.Tier2, calculateForX, a, b, mapN1, mapN2, deltaSign, 2, 7, -3);
    UpdateCone(wallCone.Tier3, calculateForX, a, b, mapN1, mapN2, deltaSign, 1, 5, -2);
    UpdateCone(wallCone.Tier4, calculateForX, a, b, mapN1, mapN2, deltaSign, 0, 3, -1);
}

int DungeonViewState::Wrap(int const kX, int const kLowerBound, int const kUpperBound)
{
    int d = kUpperBound - kLowerBound + 1;
    return kLowerBound + (kX >= 0 ? kX % d : -kX % d ? d - (-kX % d) : 0);
}

void DungeonViewState::UpdateCone(MapSpace* coneArray, bool calculateForX, int a, int b, int mapN1, int mapN2, int deltaSign, int xOffset, int arrayLen, int pivotPoint) {
    int absLen = (arrayLen - 1);

    for (int i = 0; i < arrayLen; i++) {
        if ((a + (deltaSign * xOffset)) >= 0 && (a + (deltaSign * xOffset)) < mapN1 && (b + (pivotPoint + i)) >= 0 && (b + (pivotPoint + i)) < mapN2){
            if(calculateForX){
                coneArray[(deltaSign < 0 ? abs(i - absLen) : i)] = dungeonObj.WallMap[b + (pivotPoint + i)][a + (deltaSign * xOffset)];                
            }
            else{
                coneArray[(deltaSign > 0 ? abs(i - absLen) : i)] = dungeonObj.WallMap[a + (deltaSign * xOffset)][b + (pivotPoint + i)];         
            }
        }
    }
}

void DungeonViewState::UnloadResources()
{
    
}