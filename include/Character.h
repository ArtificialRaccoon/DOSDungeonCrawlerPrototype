#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character
{
    public:
        Character();
        virtual ~Character();
        std::string Name;
        int Level;
        int CurrentHP;
        int MaxHP;
        int CurrentMP;
        int MaxMP;
        int Portrait;
};

#endif // CHARACTER_H
