#include "WallSet.h"

const unsigned FLIPPED_HORIZONTALLY_FLAG  = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG    = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG    = 0x20000000;

WallSet::~WallSet()
{

}

void WallSet::LoadWallSet(std::string wallSetName)
{
    std::ifstream ifs((".\\WALLSETS\\" + wallSetName + ".tmj").c_str());
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    json::jobject parsedObject = json::jobject::parse(content);

    tileWidth = parsedObject["tilewidth"];
    tileHeight = parsedObject["tileheight"];
    tilesetWidth = parsedObject["tilesetwidth"];
    tilesetHeight = parsedObject["tilesetheight"];

    json::jobject jsonObj = parsedObject["FORWARDA"];
    FORWARD_A.height = jsonObj["height"];
    FORWARD_A.width = jsonObj["width"];
    FORWARD_A.tileData = jsonObj["data"];
    FORWARD_A.startY = jsonObj["starty"];

    jsonObj = parsedObject["SIDEA"];
    SIDE_A.height = jsonObj["height"];
    SIDE_A.width = jsonObj["width"];
    SIDE_A.tileData = jsonObj["data"];
    SIDE_A.startY = jsonObj["starty"];

    jsonObj = parsedObject["FORWARDB"];
    FORWARD_B.height = jsonObj["height"];
    FORWARD_B.width = jsonObj["width"];
    FORWARD_B.tileData = jsonObj["data"];
    FORWARD_B.startY = jsonObj["starty"];

    jsonObj = parsedObject["SIDEB"];
    SIDE_B.height = jsonObj["height"];
    SIDE_B.width = jsonObj["width"];
    SIDE_B.tileData = jsonObj["data"];
    SIDE_B.startY = jsonObj["starty"];

    jsonObj = parsedObject["FORWARDC"];
    FORWARD_C.height = jsonObj["height"];
    FORWARD_C.width = jsonObj["width"];
    FORWARD_C.tileData = jsonObj["data"];
    FORWARD_C.startY = jsonObj["starty"];

    jsonObj = parsedObject["SIDEC"];
    SIDE_C.height = jsonObj["height"];
    SIDE_C.width = jsonObj["width"];
    SIDE_C.tileData = jsonObj["data"];
    SIDE_C.startY = jsonObj["starty"];

    jsonObj = parsedObject["FARSIDEC"];
    FARSIDE_C.height = jsonObj["height"];
    FARSIDE_C.width = jsonObj["width"];
    FARSIDE_C.tileData = jsonObj["data"];
    FARSIDE_C.startY = jsonObj["starty"];

    jsonObj = parsedObject["FORWARDD"];
    FORWARD_D.height = jsonObj["height"];
    FORWARD_D.width = jsonObj["width"];
    FORWARD_D.tileData = jsonObj["data"];
    FORWARD_D.startY = jsonObj["starty"];

    jsonObj = parsedObject["SIDED"];
    SIDE_D.height = jsonObj["height"];
    SIDE_D.width = jsonObj["width"];
    SIDE_D.tileData = jsonObj["data"];
    SIDE_D.startY = jsonObj["starty"];

    jsonObj = parsedObject["FARSIDED1"];
    FARSIDE_D1.height = jsonObj["height"];
    FARSIDE_D1.width = jsonObj["width"];
    FARSIDE_D1.tileData = jsonObj["data"];
    FARSIDE_D1.startY = jsonObj["starty"];

    jsonObj = parsedObject["FARSIDED2"];
    FARSIDE_D2.height = jsonObj["height"];
    FARSIDE_D2.width = jsonObj["width"];
    FARSIDE_D2.tileData = jsonObj["data"];
    FARSIDE_D2.startY = jsonObj["starty"];

    TILESHEET = load_bitmap((".\\WALLSETS\\" + wallSetName + ".bmp").c_str(), palette_tile);
    TILE = create_bitmap(tileWidth, tileHeight);
}

void WallSet::DrawWall(BITMAP *BUFFER, WallPartId wallPart, int startX, bool flip)
{
    switch(wallPart)
    {
        case FORWARDA:
            DrawWall(BUFFER, FORWARD_A, startX, flip);
            break;
        case FORWARDB:
            DrawWall(BUFFER, FORWARD_B, startX, flip);
            break;
        case FORWARDC:
            DrawWall(BUFFER, FORWARD_C, startX, flip);
            break;
        case FORWARDD:
            DrawWall(BUFFER, FORWARD_D, startX, flip);
            break;
        case SIDEA:
            DrawWall(BUFFER, SIDE_A, startX, flip);
            break;
        case SIDEB:
            DrawWall(BUFFER, SIDE_B, startX, flip);
            break;
        case SIDEC:
            DrawWall(BUFFER, SIDE_C, startX, flip);
            break;
        case SIDED:
            DrawWall(BUFFER, SIDE_D, startX, flip);
            break;
        case FARSIDEC:
            DrawWall(BUFFER, FARSIDE_C, startX, flip);
            break;
        case FARSIDED1:
            DrawWall(BUFFER, FARSIDE_D1, startX, flip);
            break;
        case FARSIDED2:
            DrawWall(BUFFER, FARSIDE_D2, startX, flip);
            break;
        default:
            break;
    }
}

void WallSet::DrawWall(BITMAP *BUFFER, WallPart wallObj, int startX, bool flip)
{
    int destXPos = 0;
    int destYPos = 0;
    int srcXPos = 0;
    int srcYPos = 0;

    unsigned tile_index = 0;
    BITMAP* wall = create_bitmap(wallObj.width * tileWidth, wallObj.height * tileHeight);
    clear_bitmap(wall);

    for (int y = 0; y < wallObj.height; y++)
    {
        destXPos = 0;
        for (int x = 0; x < wallObj.width; x++)
        {
            bool H = wallObj.tileData[tile_index] & FLIPPED_HORIZONTALLY_FLAG;
            //bool V = wallObj.tileData[tile_index] & FLIPPED_VERTICALLY_FLAG;
            //bool D = wallObj.tileData[tile_index] & FLIPPED_DIAGONALLY_FLAG;
            unsigned tileID = wallObj.tileData[tile_index];

            tileID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
            tile_index++;

            srcXPos = tileWidth * ((tileID-1) % tilesetWidth);
            srcYPos = tileHeight * floor((tileID-1) / tilesetWidth);

            if(H)
            {
                clear_bitmap(TILE);
                masked_blit(TILESHEET, TILE, srcXPos, srcYPos, 0, 0, tileWidth, tileHeight);
                draw_sprite_h_flip(wall, TILE, destXPos, destYPos);
            }
            else
                blit(TILESHEET, wall, srcXPos, srcYPos, destXPos, destYPos, tileWidth, tileHeight);
            destXPos += tileWidth;
        }
        destYPos += tileHeight;
    }

    if(flip)
        draw_sprite_h_flip(BUFFER, wall, startX, wallObj.startY);
    else
        masked_blit(wall, BUFFER, 0, 0, startX, wallObj.startY, wallObj.width * tileWidth, wallObj.height * tileHeight);
    destroy_bitmap(wall);
}