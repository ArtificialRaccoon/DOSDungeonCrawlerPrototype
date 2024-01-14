#ifndef GLOBALENUM_H
#define GLOBALENUM_H

typedef enum { NORTH, EAST, SOUTH, WEST} Rotation;
typedef enum { EMPTY, WALL, DOOR, SWITCH, ENTITY} SpaceType;

inline SpaceType operator|(SpaceType a, SpaceType b)
{
    return static_cast<SpaceType>(static_cast<int>(a) | static_cast<int>(b));
}

#endif
