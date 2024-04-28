#ifndef GLOBALENUM_H
#define GLOBALENUM_H

typedef enum { NORTH, EAST, SOUTH, WEST} Rotation;
typedef enum {     
    EMPTY       = 0b00000001, 
    WALL        = 0b00000010, 
    DOOR        = 0b00000100, 
    SWITCH      = 0b00001000, 
    ENTITY      = 0b00010000 } SpaceType;

inline SpaceType operator|(SpaceType a, SpaceType b)
{
    return static_cast<SpaceType>(static_cast<int>(a) | static_cast<int>(b));
}

inline SpaceType operator&(SpaceType a, SpaceType b)
{
    return static_cast<SpaceType>(static_cast<int>(a) & static_cast<int>(b));
}

#endif
