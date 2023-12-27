#include "DungeonViewState.h"

DungeonViewState DungeonViewState::mDungeonViewState;

void DungeonViewState::InitState()
{
    BUFFER = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    mazeUIObj.Init(BUFFER);
    dungeonObj.LoadDungeon();
    mazeRenderer.Init();

    facing = NORTH;
    playerX = 1;
    playerY = 1;

    ticks = 0;
    mouseDebounce = 0;
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
    //bool visionChanged = false;

    //Clear Wall Vision Cone
    for(int i = 0; i < 7; i++)
    {
        wallCone.Tier0[i] = 0;
        wallCone.Tier1[i] = 0;
        wallCone.Tier2[i] = 0;
        if(i < 5)
            wallCone.Tier3[i] = 0;
        if(i < 3)
            wallCone.Tier4[i] = 0;
    }

    //Clear Decoration Vision Cone
    for(int i = 0; i < 7; i++)
    {
        decoCone.Tier0[i] = 0;
        decoCone.Tier1[i] = 0;
        decoCone.Tier2[i] = 0;
        if(i < 5)
            decoCone.Tier3[i] = 0;
        if(i < 3)
            decoCone.Tier4[i] = 0;
    }

    if (calculateForX)
    {
        if (dungeonObj.WallMap[playerY - (deltaSign * deltaX)][playerX + (deltaSign * deltaY)] < 1)
        {
            playerX = playerX + (deltaSign * deltaY);
            playerY = playerY - (deltaSign * deltaX);
            //visionChanged = true;
        }

        a = playerX;
        b = playerY;
        mapN1 = dungeonObj.WallMap.size();
        mapN2 = dungeonObj.WallMap[0].size();
    }
    else
    {
        if (dungeonObj.WallMap[playerY + (deltaSign * deltaY)][playerX + (deltaSign * deltaX)] < 1)
        {
            playerY = playerY + (deltaSign * deltaY);
            playerX = playerX + (deltaSign * deltaX);
            //visionChanged = true;
        }

        a = playerY;
        b = playerX;
        mapN1 = dungeonObj.WallMap[0].size();
        mapN2 = dungeonObj.WallMap.size();
    }

    for (int i = 0; i < 7; i++)
    {
        if ((a + (deltaSign * 4)) >= 0 && (a + (deltaSign * 4)) < mapN1 && (b + (-3 + i)) >= 0 && (b + (-3 + i)) < mapN2)
        {
            if (calculateForX)
                wallCone.Tier0[(deltaSign < 0 ? abs(i - 6) : i)] = dungeonObj.WallMap[b + (-3 + i)][a + (deltaSign * 4)];
            else
                wallCone.Tier0[(deltaSign > 0 ? abs(i - 6) : i)] = dungeonObj.WallMap[a + (deltaSign * 4)][b + (-3 + i)];
        }
    }

    for (int i = 0; i < 7; i++)
    {
        if ((a + (deltaSign * 3)) >= 0 && (a + (deltaSign * 3)) < mapN1 && (b + (-3 + i)) >= 0 && (b + (-3 + i)) < mapN2)
        {
            if (calculateForX)
                wallCone.Tier1[(deltaSign < 0 ? abs(i - 6) : i)] = dungeonObj.WallMap[b + (-3 + i)][a + (deltaSign * 3)];
            else
                wallCone.Tier1[(deltaSign > 0 ? abs(i - 6) : i)] = dungeonObj.WallMap[a + (deltaSign * 3)][b + (-3 + i)];
        }
    }

    for (int i = 0; i < 7; i++)
    {
        if ((a + (deltaSign * 2)) >= 0 && (a + (deltaSign * 2)) < mapN1 && (b + (-3 + i)) >= 0 && (b + (-3 + i)) < mapN2)
        {
            if (calculateForX)
                wallCone.Tier2[(deltaSign < 0 ? abs(i - 6) : i)] = dungeonObj.WallMap[b + (-3 + i)][a + (deltaSign * 2)];
            else
                wallCone.Tier2[(deltaSign > 0 ? abs(i - 6) : i)] = dungeonObj.WallMap[a + (deltaSign * 2)][b + (-3 + i)];
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if ((a + (deltaSign * 1)) >= 0 && (a + (deltaSign * 1)) < mapN1 && (b + (-2 + i)) >= 0 && (b + (-2 + i)) < mapN2)
        {
            if (calculateForX)
                wallCone.Tier3[(deltaSign < 0 ? abs(i - 4) : i)] = dungeonObj.WallMap[b + (-2 + i)][a + (deltaSign * 1)];
            else
                wallCone.Tier3[(deltaSign > 0 ? abs(i - 4) : i)] = dungeonObj.WallMap[a + (deltaSign * 1)][b + (-2 + i)];
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (a >= 0 && a < mapN1 && (b + (-1 + i)) >= 0 && (b + (-1 + i)) < mapN2)
        {
            if (calculateForX)
            {
                wallCone.Tier4[(deltaSign < 0 ? abs(i - 2) : i)] = dungeonObj.WallMap[b + (-1 + i)][a];
                decoCone.Tier4[(deltaSign < 0 ? abs(i - 2) : i)] = dungeonObj.DecoMap[b + (-1 + i)][a];
            }
            else
            {
                wallCone.Tier4[(deltaSign > 0 ? abs(i - 2) : i)] = dungeonObj.WallMap[a][b + (-1 + i)];
                decoCone.Tier4[(deltaSign > 0 ? abs(i - 2) : i)] = dungeonObj.DecoMap[a][b + (-1 + i)];
            }
        }
    }
}

int DungeonViewState::Wrap(int const kX, int const kLowerBound, int const kUpperBound)
{
    int d = kUpperBound - kLowerBound + 1;
    return kLowerBound + (kX >= 0 ? kX % d : -kX % d ? d - (-kX % d) : 0);
}
