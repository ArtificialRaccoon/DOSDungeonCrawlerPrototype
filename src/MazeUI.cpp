#include <algorithm>
#include "MazeUI.h"
#include "MazeDefines.h"
#include "GlobalEnumerations.h"
#include "Dungeon.h"

const unsigned FLIPPED_HORIZONTALLY_FLAG  = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG    = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG    = 0x20000000;
const int backgroundWidth = 40;
const int backgroundHeight = 25;

void MazeUI::Init(BITMAP *INPUT_BUFFER)
{
    BUFFER = INPUT_BUFFER;

    SHEET = load_bitmap(".\\OTHER\\MAZEUI.bmp", CommonGUI::Instance().GetPalette());
    PORTSHEET = load_bitmap(".\\OTHER\\CHARPORT.bmp", CommonGUI::Instance().GetPalette());

    if (!SHEET || !PORTSHEET) {
      set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      allegro_message("Error reading UI bitmap files");
      return;
    }

    std::ifstream ifs(".\\OTHER\\DUN-UI.tmj");
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    json::jobject guiJson = json::jobject::parse(content);

    guiWidth = guiJson["width"];
    guiHeight = guiJson["height"];
    tileWidth = guiJson["tilewidth"];
    tileHeight = guiJson["tileheight"];
    this->backgroundTileData = guiJson["background"];
    this->mazeborderTileData = guiJson["mazeborder"];
    this->mainuiTileData = guiJson["mainui"];
    this->portraitbackgroundTileData = guiJson["portraitbackground"];
    this->portraitbordersTileData = guiJson["portraitborders"];
}

MazeUI::~MazeUI()
{

}

void MazeUI::DrawMazeUI()
{
    this->DrawMazeUILayer(&this->backgroundTileData);
    this->DrawMazeUILayer(&this->mazeborderTileData);
    this->DrawMazeUILayer(&this->mainuiTileData);
    this->DrawMazeUILayer(&this->portraitbackgroundTileData);
    this->DrawMazeUILayer(&this->portraitbordersTileData);
}

void MazeUI::DrawMazeUILayer(std::vector<int>* tileData)
{
    int tilesetWidth = 16;
    int tilesetHeight = 16;

    int destXPos = 0;
    int destYPos = 0;
    int srcXPos = 0;
    int srcYPos = 0;

    unsigned tile_index = 0;

    for (int y = 0; y < backgroundHeight; y++)
    {
        destXPos = 0;
        tile_index = y * backgroundWidth;

        for (int x = 0; x < backgroundWidth; x++)
        {
            unsigned tileID = (*tileData)[tile_index];
            tileID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
            srcXPos = tileWidth * ((tileID - 1) % tilesetWidth);
            srcYPos = tileHeight * floor((tileID - 1) / tilesetWidth);
            masked_blit(SHEET, BUFFER, srcXPos, srcYPos, destXPos, destYPos, tileWidth, tileHeight);

            tile_index += 1;
            destXPos += tileWidth;
        }

        destYPos += tileHeight;
    }
}

void MazeUI::DrawTile(int tileIndex)
{
    this->DrawTileLayer(&this->backgroundTileData, tileIndex);
    this->DrawTileLayer(&this->mazeborderTileData, tileIndex);
    this->DrawTileLayer(&this->mainuiTileData, tileIndex);
    this->DrawTileLayer(&this->portraitbackgroundTileData, tileIndex);
    this->DrawTileLayer(&this->portraitbordersTileData, tileIndex);    
}

void MazeUI::DrawTileLayer(std::vector<int>* tileData, int tileIndex)
{
    int tilesetWidth = 16;
    int tilesetHeight = 16;
    int destXPos = (tileIndex % backgroundWidth) * tileWidth;
    int destYPos = (tileIndex / backgroundWidth) * tileHeight;

    unsigned tileID = (*tileData)[tileIndex];
    tileID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
    int srcXPos = tileWidth * ((tileID - 1) % tilesetWidth);
    int srcYPos = tileHeight * floor((tileID - 1) / tilesetWidth);
    masked_blit(SHEET, BUFFER, srcXPos, srcYPos, destXPos, destYPos, tileWidth, tileHeight);
}