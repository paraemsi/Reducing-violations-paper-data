#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

typedef std::int32_t ability_t;

struct Character
{
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
Character generate();

}  // namespace dnd_character
