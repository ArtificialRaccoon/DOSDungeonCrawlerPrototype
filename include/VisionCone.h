#ifndef VISIONCONE_H
#define VISIONCONE_H

#include "MapSpace.h" 

class VisionCone
{
    public:
        VisionCone();
        virtual ~VisionCone() {}
        MapSpace Tier0[7];
        MapSpace Tier1[7];
        MapSpace Tier2[7];
        MapSpace Tier3[5];
        MapSpace Tier4[3];
};

#endif // VISIONCONE_H
