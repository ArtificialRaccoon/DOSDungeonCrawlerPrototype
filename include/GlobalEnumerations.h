#ifndef GLOBALENUM_H
#define GLOBALENUM_H

typedef enum { NORTH, EAST, SOUTH, WEST} Rotation;

typedef enum {
    NONE          = 1,
    STRENGTH      = 2,
    DEXTERITY     = 4,
    INTELLIGENCE  = 8,
    INSIGHT       = 16,
    CONSTITUTION  = 32
} StatType;

inline StatType operator|(StatType a, StatType b)
{
    return static_cast<StatType>(static_cast<int>(a) | static_cast<int>(b));
}

inline StatType operator&(StatType a, StatType b)
{
    return static_cast<StatType>(static_cast<int>(a) & static_cast<int>(b));
}

typedef enum {     
    EMPTY       = 1, 
    WALL        = 2, 
    DOOR        = 4, 
    SWITCH      = 8, 
    ENTITY      = 16 } SpaceType;

inline SpaceType operator|(SpaceType a, SpaceType b)
{
    return static_cast<SpaceType>(static_cast<int>(a) | static_cast<int>(b));
}

inline SpaceType operator&(SpaceType a, SpaceType b)
{
    return static_cast<SpaceType>(static_cast<int>(a) & static_cast<int>(b));
}

#endif
