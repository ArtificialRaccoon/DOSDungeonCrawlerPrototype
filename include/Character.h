#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <cmath>
#include "GlobalEnumerations.h"

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

        //Equipment
        //Weapon
        //Armor
        //Sheild
        //Accessory1
        //Accessory2


        int Strength;
        int Dexterity;
        int Intelligence;
        int Insight;
        int Constitution;

        int Proficiency() 
        {
            switch(Level)
            {
                case 5:
                case 6:
                case 7:
                case 8:
                    return 3;
                case 9:
                case 10:
                    return 4;
                default:
                    return 2;
            }
        }

        int AbilityModifier(StatType statType) 
        {
            int statValue = 10;
            switch(statType)
            {
                case StatType::STRENGTH: 
                    statValue = Strength;
                    break;
                case StatType::DEXTERITY: 
                    statValue = Dexterity;
                    break;                
                case StatType::INTELLIGENCE:
                    statValue = Intelligence;
                    break;                 
                case StatType::INSIGHT: 
                    statValue = Insight;
                    break;                
                case StatType::CONSTITUTION:
                    statValue = Constitution;
                    break;                
            }
            
            return floor((statValue - 10) / 2);
        }

        int AC() { return 10 + AbilityModifier(StatType::DEXTERITY); } //Modify to add bonuses later        

};

#endif // CHARACTER_H