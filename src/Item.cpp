#include "Item.h"

std::vector<Item> Item::readItemData(const std::string& filename) 
{
    std::vector<Item> items;
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "Error: Failed to open JSON file " << filename << std::endl;
        return items;
    }

    std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    json::jobject itemList;
    try { itemList = json::jobject::parse(jsonString); }
    catch (const json::parsing_error& e)
    {
        std::cerr << "Error: Failed to parse JSON file " << filename << ": " << e.what() << std::endl;
        return items; 
    }

    for (int i = 0; i < itemList.size(); i++)
    {        
        Item newItem;
        json::jobject currentItem = itemList.array(i).as_object();        
        newItem.setName(currentItem["name"].as_string());
        newItem.setValue(currentItem["value"]);

        std::string itemType = currentItem["type"].as_string();
        if (itemType == "Weapon") {
            newItem.setType(ItemType::Weapon);
            newItem.setWeaponType(ItemEnumUtils::toWeaponType(currentItem["weaponType"].as_string()));
            newItem.setDamageDice({ currentItem["damageDice"]["numDice"], currentItem["damageDice"]["sides"] });
            newItem.setFinesseProperty((strcasecmp("true",currentItem["hasFinesse"].as_string().c_str()) == 0));
            newItem.setReachProperty((strcasecmp("true",currentItem["hasReach"].as_string().c_str()) == 0));
        } else if (itemType == "Armor") {
            newItem.setType(ItemType::Armor);
            newItem.setArmorType(ItemEnumUtils::toArmorType(currentItem["armorType"].as_string()));
            newItem.setDefense(currentItem["defense"]);             
            for(int aff = 0; aff < currentItem["affinity"].as_object().size(); aff++)
            {
                newItem.setAffinity(newItem.getAffinity() | ItemEnumUtils::toAffinityType(currentItem["affinity"].array(aff).as_string()));                
            }            
        } else if (itemType == "Consumable") {
            newItem.setType(ItemType::Consumable);
            newItem.setConsumableType(ItemEnumUtils::toConsumableType(currentItem["consumableType"].as_string()));
        }

        items.push_back(newItem);
    }

    // Close the file
    file.close();

    return items;
}

namespace ItemEnumUtils 
{
    WeaponProperty toWeaponPropertyType(std::string value)
    {
        if(value == "Melee") 
            return WeaponProperty::Melee;
        else if(value == "Ranged") 
            return WeaponProperty::Ranged;            
        return WeaponProperty::MagicalCatalyst;     
    }

    ElementAffinity toAffinityType(std::string value)
    {
        if(value == "Fire") 
            return ElementAffinity::Fire;
        else if(value == "Water") 
            return ElementAffinity::Water;
        else if(value == "Earth") 
            return ElementAffinity::Earth;   
        else if(value == "Air") 
            return ElementAffinity::Air;                      
        return ElementAffinity::None;    
    }

    ItemType toItemType(std::string value)
    {
        if(value == "Weapon") 
            return ItemType::Weapon;
        else if(value == "Armor") 
            return ItemType::Armor;            
        return ItemType::Consumable;     
    }

    WeaponType toWeaponType(std::string value)
    {
        if(value == "Sword") 
            return WeaponType::Sword;           
        else if(value == "Axe") 
            return WeaponType::Axe;
        return WeaponType::Bow;     
    }

    ArmorType toArmorType(std::string value)
    {
        if(value == "Helmet") 
            return ArmorType::Helmet;           
        else if(value == "Chestplate") 
            return ArmorType::Chestplate;
        return ArmorType::Leggings;     
    }

    ConsumableType toConsumableType(std::string value)
    {
        if(value == "Potion") 
            return ConsumableType::Potion;            
        return ConsumableType::Scroll;     
    }
}