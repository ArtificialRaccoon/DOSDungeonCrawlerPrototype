#include "GUIElement.h"

const int tileWidth = 8;
const int tileHeight = 8;
const unsigned FLIPPED_HORIZONTALLY_FLAG  = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG    = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG    = 0x20000000;

GUIElement::GUIElement(std::string inputJson)
{
    json::jobject guiObject = json::jobject::parse(inputJson);
    this->id = guiObject.get("id");
    this->textOverlay = guiObject.get("text_overlay");
    this->action = guiObject["action"];
    this->spriteTiles = guiObject["sprite_tiles"];

    //Bounding Box
    if(guiObject.has_key("bounding_box"))
    {
        json::jobject bbObj = guiObject["bounding_box"];
        this->x = bbObj["x"];
        this->y = bbObj["y"];
        this->height = bbObj["height"];
        this->width = bbObj["width"];
    }
    
    //Overlay
    if(guiObject.has_key("sprite_overlay"))
    {
        json::jobject overlayObj = guiObject["sprite_overlay"];   
        this->overlayTiles = overlayObj["tiles"];
        this->overlayX = overlayObj["x"];
        this->overlayY = overlayObj["y"];
        this->overlayWidth = overlayObj["overlayWidth"];
        this->overlayHeight = overlayObj["overlayHeight"];
    }
}

void GUIElement::DrawElement(BITMAP *BUFFER, BITMAP *SHEET, PALETTE palette, FONT *FONT, bool drawText)
{    
    unsigned tile_index = 0;
    int srcXPos = 0;
    int srcYPos = 0;
    int destXPos = 0;
    int destYPos = 0;

    //Clean this up
    if(this->spriteTiles[0] != -1)
    {
        srcXPos = 0;
        srcYPos = 0;
        destXPos = this->x;
        destYPos = this->y;

        for (int y = 0; y < this->height; y++)
        {
            destXPos = this->x;
            tile_index = y * this->width;

            for (int x = 0; x < this->width; x++)
            {
                bool H = this->spriteTiles[tile_index] & FLIPPED_HORIZONTALLY_FLAG;
                unsigned tileID = this->spriteTiles[tile_index];

                tileID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
                
                srcXPos = tileWidth * ((tileID - 1) % 4);
                srcYPos = tileHeight * floor((tileID - 1) / 4);
                masked_blit(SHEET, BUFFER, srcXPos, srcYPos, destXPos, destYPos, tileWidth, tileHeight);
                
                tile_index += 1;
                destXPos += tileWidth;
            }
            destYPos += tileHeight;
        }
    }

    if(this->overlayTiles[0] != -1)
    {
        srcXPos = 0;
        srcYPos = 0;
        destXPos = this->overlayX;
        destYPos = this->overlayY;

        for (int y = 0; y < this->overlayHeight; y++)
        {
            destXPos = this->overlayX;
            tile_index = y * this->overlayWidth;

            for (int x = 0; x < this->overlayWidth; x++)
            {
                bool H = this->overlayTiles[tile_index] & FLIPPED_HORIZONTALLY_FLAG;
                unsigned tileID = this->overlayTiles[tile_index];

                tileID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
                
                srcXPos = tileWidth * ((tileID - 1) % 4);
                srcYPos = tileHeight * floor((tileID - 1) / 4);
                masked_blit(SHEET, BUFFER, srcXPos, srcYPos, destXPos, destYPos, tileWidth, tileHeight);
                
                tile_index += 1;
                destXPos += tileWidth;
            }
            destYPos += tileHeight;
        }
    }
    
    if(drawText)
        textout_centre_ex(BUFFER, FONT, this->textOverlay.c_str(), 234, 18, makecol(255, 255, 255), -1);
}