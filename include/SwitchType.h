#ifndef SWITCHTYPE_H
#define SWITCHTYPE_H

class SwitchType
{
    public:
        SwitchType() {}
        virtual ~SwitchType() {}
        int Id;
        int SwitchState;
        std::string SwitchSpriteSheet;
        int Location[2] = {-1, -1};
};

#endif // SWITCHTYPE_H