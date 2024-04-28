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
};

#endif // SWITCHTYPE_H