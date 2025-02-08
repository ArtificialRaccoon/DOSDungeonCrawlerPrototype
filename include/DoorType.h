#ifndef DOORTYPE_H
#define DOORTYPE_H
#include "globals.h"

class DoorType
{
    public:
        DoorType() {}
        virtual ~DoorType() {}
        int Id;
        int WallSetId;
        std::string DoorSpriteSheet;
        bool IsOpen = false;
        std::map<int, int> Combination;
        std::string Effect;
};

#endif // DOORTYPE_H