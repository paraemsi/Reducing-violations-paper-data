#pragma once

#include <cstdint>

namespace dnd_character {

using ability_t = int32_t;

class Character {
public:
    Character();

    ability_t strength;
    ability_t dexterity;
    ability_t constitution;
    ability_t intelligence;
    ability_t wisdom;
    ability_t charisma;
    ability_t hitpoints;
};

ability_t ability();
ability_t modifier(ability_t score);

}  // namespace dnd_character
