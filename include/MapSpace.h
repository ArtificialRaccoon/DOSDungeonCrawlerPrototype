#ifndef MAPSPACE_H
#define MAPSPACE_H

#include "GlobalEnumerations.h"

class MapSpace
{
    public:
        MapSpace() {}
        virtual ~MapSpace() {}
        SpaceType TypeFlag = EMPTY;
        int WallSetId = 0;
        int DoorId = 0;
        int SwitchId = 0;
        int EntityId = 0;
};

#endif // MAPSPACE_H