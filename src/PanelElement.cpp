#include "PanelElement.h"

PanelElement::PanelElement(std::string inputJson, int tilesetWidth, int tilesetHeight)
{
    json::jobject guiObject = json::jobject::parse(inputJson);
    this->id = guiObject.get("id");
    this->x = guiObject["x"];
    this->y = guiObject["y"];
    this->textOverlay = guiObject.get("textOverlay");
    this->textX = guiObject["textX"];
    this->textY = guiObject["textY"];
    this->spriteTiles = guiObject["spriteTiles"];
    this->spriteWidth = guiObject["spriteWidth"];
    this->spriteHeight = guiObject["spriteHeight"];
    this->tilesetHeight = tilesetHeight;
    this->tilesetWidth = tilesetWidth;
}

void PanelElement::DrawElement(BITMAP *BUFFER, BITMAP *SHEET, PALETTE palette, FONT *FONT)
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

    textout_centre_ex(BUFFER, FONT, this->textOverlay.substr(1, this->textOverlay.length() - 2).c_str(), this->textX + this->width / 2, this->textY, makecol(255, 255, 255), -1);
}