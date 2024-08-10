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

    LoadPartData(parsedObject, "FORWARDA", &FORWARD_A);
    LoadPartData(parsedObject, "SIDEA", &SIDE_A);
    LoadPartData(parsedObject, "FORWARDB", &FORWARD_B);
    LoadPartData(parsedObject, "SIDEB", &SIDE_B);    
    LoadPartData(parsedObject, "FORWARDC", &FORWARD_C);
    LoadPartData(parsedObject, "SIDEC", &SIDE_C);
    LoadPartData(parsedObject, "FARSIDEC", &FARSIDE_C);
    LoadPartData(parsedObject, "FORWARDD", &FORWARD_D);
    LoadPartData(parsedObject, "SIDED", &SIDE_D);
    LoadPartData(parsedObject, "FARSIDED1", &FARSIDE_D1);
    LoadPartData(parsedObject, "FARSIDED2", &FARSIDE_D2);

    TILESHEET = load_bitmap((".\\WALLDECO\\" + ((std::string)parsedObject["TileSet"]) + ".bmp").c_str(), palette_tile);
    TILE = create_bitmap(tileWidth, tileHeight);
}

void WallDeco::LoadPartData(json::jobject parsedObject, std::string key, WallPart *partToLoad)
{
    if(parsedObject.has_key(key))
    {
        json::jobject jsonObj = parsedObject[key];
        partToLoad->height = jsonObj["height"];
        partToLoad->width = jsonObj["width"];
        partToLoad->tileData = jsonObj["data"];
        partToLoad->startY = jsonObj["starty"];
        if(jsonObj.has_key("leftx"))
            partToLoad->leftX = jsonObj["leftx"];
        if(jsonObj.has_key("leftx-list"))
            partToLoad->leftXList = jsonObj["leftx-list"];
        if(jsonObj.has_key("rightx"))
            partToLoad->rightX = jsonObj["rightx"];
    }
}

void WallDeco::DrawWallDeco(BITMAP *BUFFER, WallPartId wallPart, int xPosIndex, bool flip)
{
    switch(wallPart)
    {
        case FORWARDA:
            DrawWallDeco(BUFFER, FORWARD_A, FORWARD_A.leftXList[xPosIndex], flip);
            break;
        case FORWARDB:
            DrawWallDeco(BUFFER, FORWARD_B, FORWARD_B.leftXList[xPosIndex], flip);
            break;
        case FORWARDC:
            DrawWallDeco(BUFFER, FORWARD_C, FORWARD_C.leftXList[xPosIndex], flip);
            break;
        case FORWARDD:
            DrawWallDeco(BUFFER, FORWARD_D, FORWARD_D.leftXList[xPosIndex], flip);
            break;
        case SIDEA:
            DrawWallDeco(BUFFER, SIDE_A, flip? SIDE_A.rightX : SIDE_A.leftX, flip);
            break;
        case SIDEB:
            DrawWallDeco(BUFFER, SIDE_B, flip? SIDE_B.rightX : SIDE_B.leftX, flip);
            break;
        case SIDEC:
            DrawWallDeco(BUFFER, SIDE_C, flip? SIDE_C.rightX : SIDE_C.leftX, flip);
            break;
        case SIDED:
            DrawWallDeco(BUFFER, SIDE_D, flip? SIDE_D.rightX : SIDE_D.leftX, flip);
            break;
        case FARSIDEC:
            DrawWallDeco(BUFFER, FARSIDE_C, flip? FARSIDE_C.rightX : FARSIDE_C.leftX, flip);
            break;
        default:
            break;
    }
}

void WallDeco::DrawWallDeco(BITMAP *BUFFER, WallPart wallObj, int startX, bool flip)
{
    int destXPos = startX;
    int destYPos = wallObj.startY;

    unsigned tile_index = 0;

    for (int y = 0; y < wallObj.height; y++)
    {
        int currentX = destXPos;
        tile_index = flip ? (y + 1) * wallObj.width - 1 : y * wallObj.width;

        for (int x = 0; x < wallObj.width; x++)
        {
            bool H = wallObj.tileData[tile_index] & FLIPPED_HORIZONTALLY_FLAG;
            unsigned tileID = wallObj.tileData[tile_index];
            tileID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);

            int srcXPos = tileWidth * ((tileID - 1) % tilesetWidth);
            int srcYPos = tileHeight * floor((tileID - 1) / tilesetWidth);

            if (flip)
            {
                clear_bitmap(TILE);
                masked_blit(TILESHEET, TILE, srcXPos, srcYPos, 0, 0, tileWidth, tileHeight);
                draw_sprite_h_flip(BUFFER, TILE, currentX, destYPos);
            }
            else
            {
                masked_blit(TILESHEET, BUFFER, srcXPos, srcYPos, currentX, destYPos, tileWidth, tileHeight);
            }
            
            tile_index += flip ? -1 : 1;
            currentX += tileWidth;
        }
        destYPos += tileHeight;
    }
}
