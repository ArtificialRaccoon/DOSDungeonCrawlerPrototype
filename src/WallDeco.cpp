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
        partToLoad->startX = jsonObj["startx"];
    }
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
