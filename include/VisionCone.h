#ifndef VISIONCONE_H
#define VISIONCONE_H

class VisionCone
{
    public:
        VisionCone() {}
        virtual ~VisionCone() {}
        int Tier0[7] {0, 0, 0, 0, 0, 0, 0};
        int Tier1[7] {0, 0, 0, 0, 0, 0, 0};
        int Tier2[7] {0, 0, 0, 0, 0, 0, 0};
        int Tier3[5]    {0, 0, 0, 0, 0};
        int Tier4[3]       {0, 0, 0};
};

#endif // VISIONCONE_H
