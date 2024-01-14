#include <algorithm>
#include "MazeUI.h"
#include "MazeDefines.h"
#include "GlobalEnumerations.h"
#include "Dungeon.h"

void MazeUI::Init(BITMAP *INPUT_BUFFER)
{
    BUFFER = INPUT_BUFFER;

    SHEET = load_bitmap(".\\OTHER\\MAZEUI.bmp", palette);
    PORTSHEET = load_bitmap(".\\OTHER\\CHARPORT.bmp", palette);

    if (!SHEET || !PORTSHEET) {
      set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      allegro_message("Error reading UI bitmap files");
      return;
    }

    MAZEBORDER_CORNER = create_bitmap(MAPWINC_WIDTH, MAPWINC_HEIGHT);
    CHAR_TOPCORNER = create_bitmap(CHARWINC_WIDTH, CHARWINC_HEIGHT);
    CHAR_BOTTOMCORNER = create_bitmap(CHARWINC_WIDTH, CHARWINC_HEIGHT);
    ARROW = create_bitmap(8, 8);
    clear_bitmap(ARROW);
    clear_bitmap(MAZEBORDER_CORNER);
    clear_bitmap(CHAR_TOPCORNER);
    clear_bitmap(CHAR_BOTTOMCORNER);

    LoadUISprite(SHEET, MAZEBORDER_CORNER, palette, MAPWINC_STARTX, MAPWINC_STARTY, MAPWINC_WIDTH, MAPWINC_HEIGHT);
    LoadUISprite(SHEET, CHAR_TOPCORNER, palette, CHARWINTC_STARTX, CHARWINTC_STARTY, CHARWINC_WIDTH, CHARWINC_HEIGHT);
    LoadUISprite(SHEET, CHAR_BOTTOMCORNER, palette, CHARWINBC_STARTX, CHARWINBC_STARTY, CHARWINC_WIDTH, CHARWINC_HEIGHT);
    LoadUISprite(SHEET, ARROW, palette, ARROW_X, ARROW_Y, ARROW_WIDTH, ARROW_HEIGHT);
}

MazeUI::~MazeUI()
{

}

void MazeUI::LoadUISprite(BITMAP *bmpData, BITMAP *sprite, PALETTE palData, int startX, int startY, int sizeW, int sizeH)
{
    set_palette(palData);
    masked_blit(bmpData, sprite, startX, startY, 0, 0, sizeW, sizeH);
}

void MazeUI::DrawMazeUI(int startX, int startY, Dungeon &currentDungeon, Rotation facing, int playerX, int playerY, GameProcessor* game, bool update)
{
    //Draw Maze Border
    DrawMazeWindowBorder(startX, startY + 8, MAZEBORDER_H, MAZEBORDER_V, facing);

    //Draw Character Windows
    DrawCharacterWindow(&game->playerData.Party[0], 2, 2, update);
    DrawCharacterWindow(&game->playerData.Party[1], 250, 2, update);
    DrawCharacterWindow(&game->playerData.Party[2], 2, 101, update);
    DrawCharacterWindow(&game->playerData.Party[3], 250, 101, update);

    //Draw Minimap
    DrawMiniMap(MINIMAP_X, MINIMAP_Y, currentDungeon, facing, playerX, playerY, game);

    //Draw UI
    DrawNavigation();
    DrawUserButtons();
}

void MazeUI::DrawCharacterWindow(Character *characterObj, int xOffset, int yOffset, bool update)
{
    if(update)
    {
        //Blank Out Point Regions
        rectfill(BUFFER, xOffset + 21, yOffset + 60, xOffset + 36, yOffset + 68, makecol(55,55,255));
        rectfill(BUFFER, xOffset + 44, yOffset + 66, xOffset + 59, yOffset + 74, makecol(55,55,255));
        rectfill(BUFFER, xOffset + 21, yOffset + 76, xOffset + 36, yOffset + 84, makecol(55,55,255));
        rectfill(BUFFER, xOffset + 44, yOffset + 82, xOffset + 59, yOffset + 88, makecol(55,55,255));

        //Hit Points
        masked_blit(SHEET, BUFFER, CHAR_HEART_STARTX, CHAR_HEART_STARTY, xOffset + 3, yOffset + 60, CHAR_HEART_WIDTH, CHAR_HEART_HEIGHT);
        DrawDigits(xOffset + 21, yOffset + 60, characterObj->CurrentHP, 3);
        DrawDigits(xOffset + 44, yOffset + 66, characterObj->MaxHP, 3);

        //Mind Points
        masked_blit(SHEET, BUFFER, CHAR_MIND_STARTX, CHAR_MIND_STARTY, xOffset + 3, yOffset + 76, CHAR_MIND_WIDTH, CHAR_MIND_HEIGHT);
        DrawDigits(xOffset + 21, yOffset + 76, characterObj->CurrentMP, 3);
        DrawDigits(xOffset + 44, yOffset + 82, characterObj->MaxMP, 3);
    }
    else
    {
        DrawCharacterBackground(xOffset, yOffset, CHARWIN_HEIGHT, CHARWIN_WIDTH);
        DrawCharacterWindowBorder(xOffset, yOffset, CHARWIN_HEIGHT, CHARWIN_WIDTH);

        //Character Portrait
        masked_blit(PORTSHEET, BUFFER, characterObj->Portrait * PORT_WIDTH, 0, xOffset + 12, yOffset + 7, PORT_WIDTH, PORT_HEIGHT);

        //Draw the forward slash
        line(BUFFER, xOffset + 39, yOffset + 68, xOffset + 42, yOffset + 65, makecol(255, 255, 255));
        line(BUFFER, xOffset + 39, yOffset + 69, xOffset + 43, yOffset + 65, makecol(255, 255, 255));
        line(BUFFER, xOffset + 40, yOffset + 69, xOffset + 43, yOffset + 66, makecol(255, 255, 255));

        //Draw the forward slash
        line(BUFFER, xOffset + 39, yOffset + 84, xOffset + 42, yOffset + 81, makecol(255, 255, 255));
        line(BUFFER, xOffset + 39, yOffset + 85, xOffset + 43, yOffset + 81, makecol(255, 255, 255));
        line(BUFFER, xOffset + 40, yOffset + 85, xOffset + 43, yOffset + 82, makecol(255, 255, 255));
    }    
}

void MazeUI::DrawDigits(int startX, int startY, int value, int width)
{
    int valueCopy = value;
    std::vector<int> digits;
    while (valueCopy > 0)
    {
        digits.push_back(valueCopy % 10);
        valueCopy /= 10;
    }

    int currentXpos = startX;
    int padValue = width - digits.size();
    if(padValue > 0)
        currentXpos = currentXpos + (DIGIT_WIDTH * padValue);

    std::reverse(digits.begin(), digits.end());
    for(size_t i = 0; i < digits.size(); i++)
    {
        int currentDigit = digits[i];
        masked_blit(SHEET, BUFFER, DIGIT_STARTX + (DIGIT_WIDTH + 1) * currentDigit, DIGIT_STARTY, currentXpos, startY, DIGIT_WIDTH, DIGIT_HEIGHT);
        currentXpos += DIGIT_WIDTH;
    }
}

void MazeUI::DrawMazeWindowBorder(int startX, int startY, int windowBorderH, int windowBorderW, Rotation facing)
{
    //Draw the corners
    masked_blit(MAZEBORDER_CORNER, BUFFER, 0, 0, startX, startY, MAPWINC_WIDTH, MAPWINC_HEIGHT);
    draw_sprite_h_flip(BUFFER, MAZEBORDER_CORNER, BACK_WIDTH - MAPWINC_WIDTH + startX, startY);
    draw_sprite_v_flip(BUFFER, MAZEBORDER_CORNER, startX, BACK_HEIGHT - MAPWINC_HEIGHT + startY);
    draw_sprite_vh_flip(BUFFER, MAZEBORDER_CORNER, BACK_WIDTH - MAPWINC_WIDTH + startX, BACK_HEIGHT - MAPWINC_HEIGHT + startY);

    //Draw the Top/Bottom
    for(int i = 0; i <= 79; i += 1)
    {
        masked_blit(SHEET, BUFFER, MAPWINS_STARTX, MAPWINS_STARTY, 9 + (i * 2) + startX, startY, MAPWINS_WIDTH, MAPWINS_HEIGHT);
        masked_blit(SHEET, BUFFER, MAPWINS_STARTX, MAPWINS_STARTY, 9 + (i * 2) + startX, BACK_HEIGHT - MAPWINS_HEIGHT + startY, MAPWINS_WIDTH, MAPWINS_HEIGHT);
    }

    //Draw the sides
    for(int i = 0; i <= 51; i += 1)
    {
        masked_blit(SHEET, BUFFER, MAPWINS_STARTX, MAPWINS_STARTY, startX, 9 + (i * 2) + startY, MAPWINS_WIDTH, MAPWINS_HEIGHT);
        masked_blit(SHEET, BUFFER, MAPWINS_STARTX, MAPWINS_STARTY, BACK_WIDTH - MAPWINS_WIDTH  + startX, 9 + (i * 2) + startY, MAPWINS_WIDTH, MAPWINS_HEIGHT);
    }

    //Draw Maze Compass
    masked_blit(SHEET, BUFFER, MAZECOMPASS_STARTX, MAZECOMPASS_STARTY, startX + 66, startY - 6, MAZECOMPASS_WIDTH, MAZECOMPASS_HEIGHT);
    switch(facing)
    {
        case NORTH:
                masked_blit(SHEET, BUFFER, CARDINAL_X, CARDINAL_Y, startX - 4 + MAZEBORDER_WIDTH / 2, startY - 2, CARDINAL_WIDTH, CARDINAL_HEIGHT);
                break;
        case SOUTH:
                masked_blit(SHEET, BUFFER, CARDINAL_X + CARDINAL_WIDTH, CARDINAL_Y, startX - 4 + MAZEBORDER_WIDTH / 2, startY - 2, CARDINAL_WIDTH, CARDINAL_HEIGHT);
                break;
        case EAST:
                masked_blit(SHEET, BUFFER, CARDINAL_X, CARDINAL_Y + CARDINAL_HEIGHT, startX - 4 + MAZEBORDER_WIDTH / 2, startY - 2, CARDINAL_WIDTH, CARDINAL_HEIGHT);
                break;
        case WEST:
                masked_blit(SHEET, BUFFER, CARDINAL_X  + CARDINAL_WIDTH, CARDINAL_Y + CARDINAL_HEIGHT, startX - 4 + MAZEBORDER_WIDTH / 2, startY - 2, CARDINAL_WIDTH, CARDINAL_HEIGHT);
                break;
    }

}

void MazeUI::DrawMiniMap(int xOffset, int yOffset, Dungeon &currentDungeon, Rotation facing, int playerX, int playerY, GameProcessor *game)
{
    //Blank Background
    rectfill(BUFFER, xOffset, yOffset, xOffset + 55, yOffset + 55, makecol(0, 0, 0));

    //Draw Cells
    int curOffset = 0;
    for(int i = 0; i < 6; i++)
    {
        line(BUFFER, xOffset, yOffset + curOffset, xOffset + 55, yOffset + curOffset, makecol(128, 128, 128));
        curOffset += 11;
    }

    curOffset = 0;
    for(int i = 0; i < 6; i++)
    {
        line(BUFFER, xOffset + curOffset, yOffset, xOffset + curOffset, yOffset + 55, makecol(128, 128, 128));
        curOffset += 11;
    }

    //Fill Cells
    int newX = xOffset + 2;
    int newY = yOffset + 2;

    int visibleMap[5][5];
    for(int i = -2; i <= 2; i ++)
    {
        for(int j = -2; j <= 2; j++)
        {
            int posA = playerY + i;
            int posB = playerX + j;

            if (((posA >= 0 && posA < currentDungeon.WallMap.size()) && (posB >= 0 && posB < currentDungeon.WallMap[0].size())))
            {
                if (currentDungeon.WallMap[posA][posB].WallSetId > 0)
                    visibleMap[i + 2][j + 2] = true;
                else
                    visibleMap[i + 2][j + 2] = false;
            }
            else
                visibleMap[i + 2][j + 2] = true;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if(visibleMap[i][j])
                rectfill(BUFFER, newX, newY, newX + 7, newY + 7, makecol(255, 255, 255));
            newX = newX + 11;
        }
        newX = xOffset + 2;
        newY = newY + 11;
    }

    //Draw Cursor
    switch(facing)
    {
        case NORTH:
            rotate_sprite(BUFFER, ARROW, xOffset + 24, yOffset + 24, itofix(0));
            break;
        case SOUTH:
            rotate_sprite(BUFFER, ARROW, xOffset + 24, yOffset + 24, itofix(128));
            break;
        case EAST:
            rotate_sprite(BUFFER, ARROW, xOffset + 24, yOffset + 24, itofix(64));
            break;
        case WEST:
            rotate_sprite(BUFFER, ARROW, xOffset + 24, yOffset + 24, itofix(192));
            break;
    }
}

void MazeUI::DrawButton(BITMAP *SHEET, int xPos, int yPos, int sheetX, int sheetY, int buttonWidth, int buttonHeight)
{
    masked_blit(SHEET, BUFFER, xPos, yPos, sheetX, sheetY, buttonWidth, buttonHeight);
    if((mouse_b & 1) && !(mouse_x < sheetX || mouse_x > sheetX + buttonWidth || mouse_y < sheetY || mouse_y > sheetY + buttonHeight))
        rect(BUFFER, sheetX, sheetY, sheetX + buttonWidth - 1, sheetY + buttonHeight - 1, makecol(55,55,55));
}

void MazeUI::DrawNavigation()
{
    DrawButton(SHEET, NAV_SHEET_X + NAV_WIDTH * 0, NAV_SHEET_Y, BUTTON_ROTLEFT_X, BUTTON_ROTLEFT_Y, NAV_WIDTH, NAV_HEIGHT);
    DrawButton(SHEET, NAV_SHEET_X + NAV_WIDTH * 1, NAV_SHEET_Y, BUTTON_FORWARD_X, BUTTON_FORWARD_Y, NAV_WIDTH, NAV_HEIGHT);
    DrawButton(SHEET, NAV_SHEET_X + NAV_WIDTH * 2, NAV_SHEET_Y, BUTTON_ROTRIGHT_X, BUTTON_ROTRIGHT_Y, NAV_WIDTH, NAV_HEIGHT);
    DrawButton(SHEET, NAV_SHEET_X + NAV_WIDTH * 3, NAV_SHEET_Y, BUTTON_LEFT_X, BUTTON_LEFT_Y, NAV_WIDTH, NAV_HEIGHT);
    DrawButton(SHEET, NAV_SHEET_X + NAV_WIDTH * 4, NAV_SHEET_Y, BUTTON_BACKWARD_X, BUTTON_BACKWARD_Y, NAV_WIDTH, NAV_HEIGHT);
    DrawButton(SHEET, NAV_SHEET_X + NAV_WIDTH * 5, NAV_SHEET_Y, BUTTON_RIGHT_X, BUTTON_RIGHT_Y, NAV_WIDTH, NAV_HEIGHT);
}

void MazeUI::DrawUserButtons()
{
    DrawButton(SHEET, USER_SHEET_X + NAV_WIDTH * 0, USER_SHEET_Y, BUTTON_CHARACTER_X, BUTTON_CHARACTER_Y, NAV_WIDTH, NAV_HEIGHT);
    DrawButton(SHEET, USER_SHEET_X + NAV_WIDTH * 1, USER_SHEET_Y, BUTTON_MAGIC_X, BUTTON_MAGIC_Y, NAV_WIDTH, NAV_HEIGHT);
    DrawButton(SHEET, USER_SHEET_X + NAV_WIDTH * 2, USER_SHEET_Y, BUTTON_INVENTORY_X, BUTTON_INVENTORY_Y, NAV_WIDTH, NAV_HEIGHT);
    DrawButton(SHEET, USER_SHEET_X + NAV_WIDTH * 3, USER_SHEET_Y, BUTTON_CONFIG_X, BUTTON_CONFIG_Y, NAV_WIDTH, NAV_HEIGHT);
    DrawButton(SHEET, USER_SHEET_X + NAV_WIDTH * 4, USER_SHEET_Y, BUTTON_SAVE_X, BUTTON_SAVE_Y, NAV_WIDTH, NAV_HEIGHT);
    DrawButton(SHEET, USER_SHEET_X + NAV_WIDTH * 5, USER_SHEET_Y, BUTTON_LOAD_X, BUTTON_LOAD_Y, NAV_WIDTH, NAV_HEIGHT);
}

void MazeUI::DrawMazeBackground()
{
    int xPos = 0;
    int yPos = 0;
    int blitWidth = 0;
    int blitHeight = 0;

    for(int i = 0; i < 320; i+= MAZE_BACKGROUND_WIDTH)
    {
        for (int j = 0; j < 320; j+= MAZE_BACKGROUND_HEIGHT)
        {
            if(320 - j < 32)
                blitWidth = 320 - j;
            else
                blitWidth = 32;

            if(200 - i < 32)
                blitHeight = 200 - i;
            else
                blitHeight = 32;

            masked_blit(SHEET, BUFFER, MAZE_BACKGROUND_X, MAZE_BACKGROUND_Y, xPos, yPos, blitWidth, blitHeight);
            xPos += 32;
        }
        xPos = 0;
        yPos += 32;
    }
}

void MazeUI::DrawCharacterBackground(int startX, int startY, int windowH, int windowW)
{
    int xPos = startX;
    int yPos = startY;
    int blitWidth = 0;
    int blitHeight = 0;

    for(int i = 0; i < windowH; i+= CHARBACK_HEIGHT)
    {
        for (int j = 0; j < windowW; j+= CHARBACK_WIDTH)
        {
            if(windowW - j < CHARBACK_WIDTH)
                blitWidth = windowW - j;
            else
                blitWidth = CHARBACK_WIDTH;

            if(windowH - i < CHARBACK_HEIGHT)
                blitHeight = windowH - i;
            else
                blitHeight = CHARBACK_HEIGHT;

            masked_blit(SHEET, BUFFER, CHARBACK_STARTX, CHARBACK_STARTY, xPos, yPos, blitWidth, blitHeight);
            xPos += CHARBACK_WIDTH;
        }
        xPos = startX;
        yPos += CHARBACK_HEIGHT;
    }
}

void MazeUI::DrawCharacterWindowBorder(int startX, int startY, int windowBorderH, int windowBorderW)
{
    //Draw corners
    masked_blit(CHAR_TOPCORNER, BUFFER, 0, 0, startX, startY, CHARWINC_WIDTH, CHARWINC_HEIGHT);
    draw_sprite_h_flip(BUFFER, CHAR_TOPCORNER, startX + (CHARWIN_WIDTH - CHARWINC_WIDTH), startY);
    masked_blit(CHAR_BOTTOMCORNER, BUFFER, 0, 0, startX, startY + (CHARWIN_HEIGHT - CHARWINC_HEIGHT), CHARWINC_WIDTH, CHARWINC_HEIGHT);
    draw_sprite_h_flip(BUFFER, CHAR_BOTTOMCORNER, startX + (CHARWIN_WIDTH - CHARWINC_WIDTH), startY + (CHARWIN_HEIGHT - CHARWINC_HEIGHT));

    //Draw Horizontal borders
    for(int i = 14; i < CHARWIN_WIDTH - 14; i+=MAPWINS_WIDTH)
    {
        masked_blit(SHEET, BUFFER, MAPWINS_STARTX, MAPWINS_STARTY, startX + i, startY, MAPWINS_WIDTH, 1);
        masked_blit(SHEET, BUFFER, MAPWINS_STARTX, MAPWINS_STARTY, startX + i, startY + CHARWIN_HEIGHT - 1, MAPWINS_WIDTH, 1);
    }

    //Draw Vertical borders
    for(int i = 14; i < CHARWIN_HEIGHT - 14; i+=MAPWINS_HEIGHT)
    {
        masked_blit(SHEET, BUFFER, MAPWINS_STARTX, MAPWINS_STARTY, startX, startY + i, 1, MAPWINS_HEIGHT);
        masked_blit(SHEET, BUFFER, MAPWINS_STARTX, MAPWINS_STARTY, startX + (CHARWIN_WIDTH - 1), startY + i, 1, MAPWINS_HEIGHT);
    }
}
