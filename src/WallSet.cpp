#include "WallSet.h"

const unsigned FLIPPED_HORIZONTALLY_FLAG  = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG    = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG    = 0x20000000;
const int backgroundWidth = 22;
const int backgroundHeight = 15;

void WallSet::LoadWallSet(std::string wallSetName)
{
    std::ifstream ifs((".\\WALLSETS\\" + wallSetName + ".tmj").c_str());
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));    
    json::jobject parsedObject = json::jobject::parse(content);
    
    tileWidth = parsedObject["tilewidth"];
    tileHeight = parsedObject["tileheight"];
    tilesetWidth = parsedObject["width"];
    tilesetHeight = parsedObject["height"];

    WallTileMap.push_back(parsedObject["FORWARDA_CENTER"]);
    WallTileMap.push_back(parsedObject["FORWARDA_LEFT1"]);
    WallTileMap.push_back(parsedObject["FORWARDA_RIGHT1"]);
    WallTileMap.push_back(parsedObject["FORWARDB_CENTER"]);
    WallTileMap.push_back(parsedObject["FORWARDB_LEFT1"]);
    WallTileMap.push_back(parsedObject["FORWARDB_RIGHT1"]);
    WallTileMap.push_back(parsedObject["FORWARDC_CENTER"]);
    WallTileMap.push_back(parsedObject["FORWARDC_LEFT1"]);
    WallTileMap.push_back(parsedObject["FORWARDC_LEFT2"]);
    WallTileMap.push_back(parsedObject["FORWARDC_RIGHT1"]);
    WallTileMap.push_back(parsedObject["FORWARDC_RIGHT2"]);
    WallTileMap.push_back(parsedObject["FORWARDD_CENTER"]);
    WallTileMap.push_back(parsedObject["FORWARDD_LEFT1"]);
    WallTileMap.push_back(parsedObject["FORWARDD_LEFT2"]);
    WallTileMap.push_back(parsedObject["FORWARDD_LEFT3"]);
    WallTileMap.push_back(parsedObject["FORWARDD_RIGHT1"]);
    WallTileMap.push_back(parsedObject["FORWARDD_RIGHT2"]);
    WallTileMap.push_back(parsedObject["FORWARDD_RIGHT3"]);

    WallTileMap.push_back(parsedObject["SIDEA_LEFT1"]);
    WallTileMap.push_back(parsedObject["SIDEA_RIGHT1"]);
    WallTileMap.push_back(parsedObject["SIDEB_LEFT1"]);
    WallTileMap.push_back(parsedObject["SIDEB_RIGHT1"]);
    WallTileMap.push_back(parsedObject["SIDEC_LEFT1"]);
    WallTileMap.push_back(parsedObject["SIDEC_RIGHT1"]);
    WallTileMap.push_back(parsedObject["SIDED_LEFT1"]);
    WallTileMap.push_back(parsedObject["SIDED_RIGHT1"]);  

    WallTileMap.push_back(parsedObject["FARSIDEC_LEFT1"]);
    WallTileMap.push_back(parsedObject["FARSIDEC_RIGHT1"]);
    WallTileMap.push_back(parsedObject["FARSIDED1_LEFT1"]);
    WallTileMap.push_back(parsedObject["FARSIDED1_RIGHT1"]);
    WallTileMap.push_back(parsedObject["FARSIDED2_LEFT1"]);
    WallTileMap.push_back(parsedObject["FARSIDED2_RIGHT1"]);                  

    TILESHEET = load_bitmap((".\\WALLSETS\\" + ((std::string)parsedObject["TileSet"]) + ".bmp").c_str(), CommonGUI::Instance().GetPalette());
    TILE = create_bitmap(tileWidth, tileHeight);
}

void WallSet::DrawWall(BITMAP *BUFFER, WallPartId wallPart, int layer, std::vector<TileReference> &lastDrawn)
{
    int tilesetWidth = 26;
    int tilesetHeight = 22;

    int destXPos = 0;
    int destYPos = 0;
    int srcXPos = 0;
    int srcYPos = 0;

    unsigned tile_index = 0;
    const std::vector<int>& tileMapRow = WallTileMap[wallPart];

    for (int y = 0; y < backgroundHeight; y++)
    {
        destXPos = 0;
        tile_index = y * backgroundWidth;

        for (int x = 0; x < backgroundWidth; x++)
        {                        
            unsigned tileID = tileMapRow[tile_index];
            TileReference newTile(layer, tileID);

            if (lastDrawn[tile_index] != newTile)
            {                
                // Update lastDrawn with the newly drawn tile
                lastDrawn[tile_index] = newTile;
     
                bool flipped_horizontally = (tileID & FLIPPED_HORIZONTALLY_FLAG);
                bool flipped_vertically = (tileID & FLIPPED_VERTICALLY_FLAG);
                tileID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
                srcXPos = tileWidth * ((tileID - 1) % tilesetWidth);
                srcYPos = tileHeight * ((tileID - 1) / tilesetWidth);
            
                clear_bitmap(TILE);
                blit(TILESHEET, TILE, srcXPos, srcYPos, 0, 0, tileWidth, tileHeight);
                if(flipped_horizontally)
                    draw_sprite_h_flip(BUFFER, TILE, destXPos, destYPos);
                else
                    masked_blit(TILE, BUFFER, 0, 0, destXPos, destYPos, tileWidth, tileHeight);
            }

            tile_index += 1;
            destXPos += tileWidth;
        }
        destYPos += tileHeight;
    }
}