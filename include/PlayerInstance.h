#ifndef PLAYERINSTANCE_H
#define PLAYERINSTANCE_H

#include <vector>
#include "Character.h"

class PlayerInstance
{
    public:
        PlayerInstance();
        virtual ~PlayerInstance();
        std::vector<Character> Party;
};

#endif // PLAYERINSTANCE_H
