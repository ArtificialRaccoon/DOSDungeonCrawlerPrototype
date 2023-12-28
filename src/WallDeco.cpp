#include "WallDeco.h"

const unsigned FLIPPED_HORIZONTALLY_FLAG  = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG    = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG    = 0x20000000;

void WallDeco::LoadWallDeco(std::string wallDecoName)
{
    std::ifstream ifs((".\\WALLDECO\\" + wallDecoName + ".tmj").c_str());
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
    FORWARD_A.startX = jsonObj["startx"];

    jsonObj = parsedObject["SIDEA"];
    SIDE_A.height = jsonObj["height"];
    SIDE_A.width = jsonObj["width"];
    SIDE_A.tileData = jsonObj["data"];
    SIDE_A.startY = jsonObj["starty"];
    SIDE_A.startX = jsonObj["startx"];

    jsonObj = parsedObject["FORWARDB"];
    FORWARD_B.height = jsonObj["height"];
    FORWARD_B.width = jsonObj["width"];
    FORWARD_B.tileData = jsonObj["data"];
    FORWARD_B.startY = jsonObj["starty"];
    FORWARD_B.startX = jsonObj["startx"];

    jsonObj = parsedObject["SIDEB"];
    SIDE_B.height = jsonObj["height"];
    SIDE_B.width = jsonObj["width"];
    SIDE_B.tileData = jsonObj["data"];
    SIDE_B.startY = jsonObj["starty"];
    SIDE_B.startX = jsonObj["startx"];

    jsonObj = parsedObject["FORWARDC"];
    FORWARD_C.height = jsonObj["height"];
    FORWARD_C.width = jsonObj["width"];
    FORWARD_C.tileData = jsonObj["data"];
    FORWARD_C.startY = jsonObj["starty"];
    FORWARD_C.startX = jsonObj["startx"];

    jsonObj = parsedObject["SIDEC"];
    SIDE_C.height = jsonObj["height"];
    SIDE_C.width = jsonObj["width"];
    SIDE_C.tileData = jsonObj["data"];
    SIDE_C.startY = jsonObj["starty"];
    SIDE_C.startX = jsonObj["startx"];

    jsonObj = parsedObject["FARSIDEC"];
    FARSIDE_C.height = jsonObj["height"];
    FARSIDE_C.width = jsonObj["width"];
    FARSIDE_C.tileData = jsonObj["data"];
    FARSIDE_C.startY = jsonObj["starty"];
    FARSIDE_C.startX = jsonObj["startx"];

    jsonObj = parsedObject["FORWARDD"];
    FORWARD_D.height = jsonObj["height"];
    FORWARD_D.width = jsonObj["width"];
    FORWARD_D.tileData = jsonObj["data"];
    FORWARD_D.startY = jsonObj["starty"];
    FORWARD_D.startX = jsonObj["startx"];

    jsonObj = parsedObject["SIDED"];
    SIDE_D.height = jsonObj["height"];
    SIDE_D.width = jsonObj["width"];
    SIDE_D.tileData = jsonObj["data"];
    SIDE_D.startY = jsonObj["starty"];
    SIDE_D.startX = jsonObj["startx"];

    jsonObj = parsedObject["FARSIDED1"];
    FARSIDE_D1.height = jsonObj["height"];
    FARSIDE_D1.width = jsonObj["width"];
    FARSIDE_D1.tileData = jsonObj["data"];
    FARSIDE_D1.startY = jsonObj["starty"];
    FARSIDE_D1.startX = jsonObj["startx"];

    jsonObj = parsedObject["FARSIDED2"];
    FARSIDE_D2.height = jsonObj["height"];
    FARSIDE_D2.width = jsonObj["width"];
    FARSIDE_D2.tileData = jsonObj["data"];
    FARSIDE_D2.startY = jsonObj["starty"];
    FARSIDE_D2.startX = jsonObj["startx"];

    TILESHEET = load_bitmap((".\\WALLDECO\\" + wallDecoName + ".bmp").c_str(), palette_tile);
    TILE = create_bitmap(tileWidth, tileHeight);
}

void WallDeco::DrawWallDeco(BITMAP *BUFFER, WallPartId wallPart, int startX, bool flip)
{
    switch(wallPart)
    {
        case FORWARDA:
            DrawWallDeco(BUFFER, FORWARD_A, FORWARDA_WIDTH, startX, flip);
            break;
        case FORWARDB:
            DrawWallDeco(BUFFER, FORWARD_B, FORWARDB_WIDTH, startX, flip);
            break;
        case FORWARDC:
            DrawWallDeco(BUFFER, FORWARD_C, FORWARDC_WIDTH, startX, flip);
            break;
        case FORWARDD:
            DrawWallDeco(BUFFER, FORWARD_D, FORWARDD_WIDTH, startX, flip);
            break;
        case SIDEA:
            DrawWallDeco(BUFFER, SIDE_A, SIDEA_WIDTH, startX, flip);
            break;
        case SIDEB:
            DrawWallDeco(BUFFER, SIDE_B, SIDEB_WIDTH, startX, flip);
            break;
        case SIDEC:
            DrawWallDeco(BUFFER, SIDE_C, SIDEC_WIDTH, startX, flip);
            break;
        case SIDED:
            DrawWallDeco(BUFFER, SIDE_D, SIDED_WIDTH, startX, flip);
            break;
        case FARSIDEC:
            DrawWallDeco(BUFFER, FARSIDE_C, FARSIDEC_WIDTH, startX, flip);
            break;
        default:
            break;
    }
}

void WallDeco::DrawWallDeco(BITMAP *BUFFER, WallPart wallObj, int wallWidth, int startX, bool flip)
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
        draw_sprite_h_flip(BUFFER, wall, startX + wallWidth - (wallObj.width * tileWidth) - wallObj.startX, wallObj.startY);
    else
        masked_blit(wall, BUFFER, 0, 0, startX + wallObj.startX, wallObj.startY, wallObj.width * tileWidth, wallObj.height * tileHeight);
    destroy_bitmap(wall);
}
