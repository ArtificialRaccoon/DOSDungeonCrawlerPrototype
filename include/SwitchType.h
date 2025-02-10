#ifndef SWITCHTYPE_H
#define SWITCHTYPE_H
#include "globals.h"

class SwitchType
{
    public:
        SwitchType() {}
        virtual ~SwitchType() {}
        int Id;
        int SwitchState;
        int UpSpriteSheet;
        int DownSpriteSheet;
        int Location[2] = {-1, -1};
        std::string Effect;
};

#endif // SWITCHTYPE_H