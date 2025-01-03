#include "ButtonElement.h"

ButtonElement::ButtonElement(std::string inputJson, int tilesetWidth, int tilesetHeight, bool drawText)
{
    this->drawText = drawText;
    json::jobject guiObject = json::jobject::parse(inputJson);
    this->id = guiObject.get("id");
    this->textOverlay = guiObject.get("textOverlay");
    this->textOverlay = this->textOverlay.substr(1, this->textOverlay.length() - 2);
    this->action = guiObject["action"];
    this->spriteTiles = guiObject["spriteTiles"];
    this->spriteWidth = guiObject["spriteWidth"];
    this->spriteHeight = guiObject["spriteHeight"];
    this->tilesetWidth = tilesetWidth;
    this->tilesetHeight = tilesetHeight;

    //Bounding Box
    this->x = guiObject["x"];
    this->y = guiObject["y"];
    this->height = this->spriteHeight * this->tileHeight;
    this->width = this->spriteWidth * this->tileWidth;

    //Overlay
    if(guiObject.has_key("spriteOverlay"))
    {
        json::jobject overlayObj = guiObject["spriteOverlay"];   
        this->overlayTiles = overlayObj["tiles"];
        this->overlayX = overlayObj["x"];
        this->overlayY = overlayObj["y"];
        this->overlayWidth = overlayObj["overlayWidth"];
        this->overlayHeight = overlayObj["overlayHeight"];
    }
}

void ButtonElement::DrawElement(BITMAP *BUFFER, BITMAP *SHEET, PALETTE palette, FONT *FONT)
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

        for (int y = 0; y < this->spriteHeight; y++)
        {
            destXPos = this->x;
            tile_index = y * this->spriteWidth;

            for (int x = 0; x < this->spriteWidth; x++)
            {
                bool H = this->spriteTiles[tile_index] & FLIPPED_HORIZONTALLY_FLAG;
                unsigned tileID = this->spriteTiles[tile_index];

                tileID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
                
                srcXPos = tileWidth * ((tileID - 1) % this->tilesetWidth);
                srcYPos = tileHeight * floor((tileID - 1) / this->tilesetWidth);
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
                
                srcXPos = tileWidth * ((tileID - 1) % this->tilesetWidth);
                srcYPos = tileHeight * floor((tileID - 1) / this->tilesetWidth);
                masked_blit(SHEET, BUFFER, srcXPos, srcYPos, destXPos, destYPos, tileWidth, tileHeight);
                
                tile_index += 1;
                destXPos += tileWidth;
            }
            destYPos += tileHeight;
        }
    }

    if(this->drawText)
    {
        if(getSelected())
            textout_centre_ex(BUFFER, 
            FONT, 
            this->textOverlay.c_str(), 
            this->x + this->width / 2, 
            this->y + 1, 
            makecol(255, 255, 255), 
            -1);
        else
            textout_centre_ex(BUFFER, 
            FONT, 
            this->textOverlay.c_str(), 
            this->x + this->width / 2, 
            this->y + 1, 
            makecol(55, 55, 55), 
            -1);
    }
}