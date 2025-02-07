#ifndef TILEREFERENCE_H
#define TILEREFERENCE_H

struct TileReference 
{
    uint32_t TileIndex;
    uint32_t TileSheetIndex;
    TileReference(uint32_t tilesheetIndex = 0, uint32_t tileIndex = 0) 
    { 
        TileIndex = tileIndex;
        TileSheetIndex = tilesheetIndex;
    }
    uint32_t getTilesheetIndex() const { return TileSheetIndex; }
    uint32_t getTileIndex() const { return TileIndex; }
    bool operator==(const TileReference& other) const { return (TileIndex == other.TileIndex) && (TileSheetIndex == other.TileSheetIndex); }
};

#endif // TILEREFERENCE_H