#include "DungeonViewState.h"

DungeonViewState DungeonViewState::mDungeonViewState;

void DungeonViewState::InitState()
{
    BUFFER = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    mazeUIObj.Init(BUFFER);
    dungeonObj.LoadDungeon();
    mazeRenderer.Init(dungeonObj);

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
                break;
            case KEY_S:
                deltaY = -1;
                break;
            case KEY_D:
                facing = (Rotation)(Wrap((int)facing + 1, 0, 3));
                break;
            case KEY_Q:
                deltaX = 1;
                break;
            case KEY_E:
                deltaX = -1;
                break;
            case KEY_ESC:
                exit(0);
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
}

void DungeonViewState::Render(GameProcessor* game)
{
    mazeRenderer.RenderVisionCone(dungeonObj, wallCone, decoCone);
    clear_to_color(BUFFER, makecol(55,55,255));
    mazeUIObj.DrawMazeBackground();
    draw_sprite(BUFFER, mazeRenderer.MAZEVIEW, 72, 8);    
    mazeUIObj.DrawMazeUI(72, 0, dungeonObj, facing, playerX, playerY, game);    
    show_mouse(BUFFER);
    draw_sprite(screen, BUFFER, 0, 0);
}

void DungeonViewState::ComputeVision(bool calculateForX, int deltaSign, int deltaY, int deltaX)
{
    int a, b, mapN1, mapN2;
    bool visionChanged = false;

    // Clear vision cones
    ClearVisionCones(wallCone);
    ClearVisionCones(decoCone);

    // Update player position
    if (calculateForX) {
        if (dungeonObj.WallMap[playerY - (deltaSign * deltaX)][playerX + (deltaSign * deltaY)] < 1) {
            playerX += deltaSign * deltaY;
            playerY -= deltaSign * deltaX;
            visionChanged = true;
        }
        a = playerX;
        b = playerY;
        mapN1 = dungeonObj.WallMap.size();
        mapN2 = dungeonObj.WallMap[0].size();
    } else {
        if (dungeonObj.WallMap[playerY + (deltaSign * deltaY)][playerX + (deltaSign * deltaX)] < 1) {
            playerY += deltaSign * deltaY;
            playerX += deltaSign * deltaX;
            visionChanged = true;
        }
        a = playerY;
        b = playerX;
        mapN1 = dungeonObj.WallMap[0].size();
        mapN2 = dungeonObj.WallMap.size();
    }

    UpdateCone(wallCone.Tier0, decoCone.Tier0, calculateForX, a, b, mapN1, mapN2, deltaSign, 4, 7, -3);
    UpdateCone(wallCone.Tier1, decoCone.Tier1, calculateForX, a, b, mapN1, mapN2, deltaSign, 3, 7, -3);
    UpdateCone(wallCone.Tier2, decoCone.Tier2, calculateForX, a, b, mapN1, mapN2, deltaSign, 2, 7, -3);
    UpdateCone(wallCone.Tier3, decoCone.Tier3, calculateForX, a, b, mapN1, mapN2, deltaSign, 1, 5, -2);
    UpdateCone(wallCone.Tier4, decoCone.Tier4, calculateForX, a, b, mapN1, mapN2, deltaSign, 0, 3, -1);
}

int DungeonViewState::Wrap(int const kX, int const kLowerBound, int const kUpperBound)
{
    int d = kUpperBound - kLowerBound + 1;
    return kLowerBound + (kX >= 0 ? kX % d : -kX % d ? d - (-kX % d) : 0);
}

void DungeonViewState::ClearVisionCones(VisionCone& cone) {
    std::fill_n(cone.Tier0, 7, 0);
    std::fill_n(cone.Tier1, 7, 0);
    std::fill_n(cone.Tier2, 7, 0);
    std::fill_n(cone.Tier3, 5, 0);
    std::fill_n(cone.Tier4, 3, 0);
}

void DungeonViewState::UpdateCone(int* coneArray, int* decoArray, bool calculateForX, int a, int b, int mapN1, int mapN2, int deltaSign, int xOffset, int arrayLen, int pivotPoint) {
    int absLen = (arrayLen - 1);

    for (int i = 0; i < arrayLen; i++) {
        if ((a + (deltaSign * xOffset)) >= 0 && (a + (deltaSign * xOffset)) < mapN1 && (b + (pivotPoint + i)) >= 0 && (b + (pivotPoint + i)) < mapN2){
            if(calculateForX){
                coneArray[(deltaSign < 0 ? abs(i - absLen) : i)] = dungeonObj.WallMap[b + (pivotPoint + i)][a + (deltaSign * xOffset)];
                decoArray[(deltaSign < 0 ? abs(i - absLen) : i)] = dungeonObj.DecoMap[b + (pivotPoint + i)][a + (deltaSign * xOffset)];
            }
            else{
                coneArray[(deltaSign > 0 ? abs(i - absLen) : i)] = dungeonObj.WallMap[a + (deltaSign * xOffset)][b + (pivotPoint + i)];
                decoArray[(deltaSign > 0 ? abs(i - absLen) : i)] = dungeonObj.DecoMap[a + (deltaSign * xOffset)][b + (pivotPoint + i)];          
            }
        }
    }
}