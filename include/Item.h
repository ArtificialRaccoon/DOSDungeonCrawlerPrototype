#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include "json.h"

enum class ItemType {
    Weapon,
    Armor,
    Consumable
};

enum class WeaponType {
    Sword,
    Axe,
    Bow
};

enum class ArmorType {
    Helmet,
    Chestplate,
    Leggings
};

enum class ConsumableType {
    Potion,
    Scroll
};

enum class ElementAffinity {
    None = 0,
    Fire = 1,
    Water = 2,
    Earth = 4,
    Air = 8
};

enum class WeaponProperty {
    Melee,
    Ranged,
    MagicalCatalyst
};

// Struct to represent damage dice
struct DamageDice {
    int numDice; // Number of dice
    int sides;   // Sides of each die
};

// Overloading bitwise OR operator to combine elemental affinities
inline ElementAffinity operator|(ElementAffinity lhs, ElementAffinity rhs) {
    return static_cast<ElementAffinity>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

// Overloading bitwise AND operator to check if an item has a specific elemental affinity
inline bool operator&(ElementAffinity lhs, ElementAffinity rhs) {
    return (static_cast<int>(lhs) & static_cast<int>(rhs)) != 0;
}

namespace ItemEnumUtils 
{
    WeaponProperty toWeaponPropertyType(std::string value);
    ElementAffinity toAffinityType(std::string value);
    ItemType toItemType(std::string value);
    WeaponType toWeaponType(std::string value);
    ArmorType toArmorType(std::string value);
    ConsumableType toConsumableType(std::string value);
}

// Class to represent items in the game
class Item {
    public:
        Item() {};            

        // Constructor for weapons
        Item(std::string name, WeaponType weaponType, int value, DamageDice damageDice, bool hasFinesse = false, bool hasReach = false) 
            : name(name), type(ItemType::Weapon), value(value), weaponType(weaponType), damageDice(damageDice), hasFinesse(hasFinesse), hasReach(hasReach), defense(0), weaponProperty(WeaponProperty::Melee), affinity(ElementAffinity::None) {}

        // Constructor for armors
        Item(std::string name, ArmorType armorType, int value, int defense, ElementAffinity affinity = ElementAffinity::None) 
            : name(name), type(ItemType::Armor), value(value), armorType(armorType), defense(defense), affinity(affinity), weaponProperty(WeaponProperty::Melee), hasFinesse(false), hasReach(false), damageDice({0, 0}) {}

        // Constructor for consumables
        Item(std::string name, ConsumableType consumableType, int value) 
            : name(name), type(ItemType::Consumable), value(value), consumableType(consumableType), defense(0), weaponProperty(WeaponProperty::Melee), affinity(ElementAffinity::None), hasFinesse(false), hasReach(false), damageDice({0, 0}) {}


        // Getters and setters for item properties
        std::string getName() const { return name; }
        void setName(const std::string& newName) { name = newName; }
        ItemType getType() const { return type; }
        void setType(ItemType newType) { type = newType; }        
        int getValue() const { return value; }
        void setValue(int newValue) { value = newValue; }

        // Functions specific to weapon type
        WeaponType getWeaponType() const { return weaponType; }
        void setWeaponType(WeaponType type) { weaponType = type; }

        // Functions specific to armor type
        ArmorType getArmorType() const { return armorType; }
        void setArmorType(ArmorType type) { armorType = type; }

        // Functions specific to consumable type
        ConsumableType getConsumableType() const { return consumableType; }
        void setConsumableType(ConsumableType type) { consumableType = type; }

        // Getter and setter for elemental affinity
        ElementAffinity getAffinity() const { return affinity; }
        void setAffinity(ElementAffinity aff) { affinity = aff; }

        // Getter and setter for defense (Armour Class)
        int getDefense() const { return defense; }
        void setDefense(int def) { defense = def; }

        // Getter and setter for weapon property
        WeaponProperty getWeaponProperty() const { return weaponProperty; }
        void setWeaponProperty(WeaponProperty prop) { weaponProperty = prop; }

        // Getter and setter for damage dice
        DamageDice getDamageDice() const { return damageDice; }
        void setDamageDice(DamageDice dice) { damageDice = dice; }

        // Getter and setter for finesse property
        bool hasFinesseProperty() const { return hasFinesse; }
        void setFinesseProperty(bool finesse) { hasFinesse = finesse; }

        // Getter and setter for reach property
        bool hasReachProperty() const { return hasReach; }
        void setReachProperty(bool reach) { hasReach = reach; }

        static std::vector<Item> readItemData(const std::string& filename);
    private:
        std::string name;
        ItemType type;
        int value; 
        union {
            WeaponType weaponType;
            ArmorType armorType;
            ConsumableType consumableType;
        };
        ElementAffinity affinity; 
        int defense; 
        WeaponProperty weaponProperty; 
        DamageDice damageDice; 
        bool hasFinesse; 
        bool hasReach;   
};

#endif // ITEM_H