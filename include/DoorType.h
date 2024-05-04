#ifndef DOORTYPE_H
#define DOORTYPE_H

class DoorType
{
    public:
        DoorType() {}
        virtual ~DoorType() {}
        int Id;
        int DoorSetId;
        std::string DoorSpriteSheet;
        bool IsOpen = false;
        std::map<int, int> Combination;
};

#endif // DOORTYPE_H