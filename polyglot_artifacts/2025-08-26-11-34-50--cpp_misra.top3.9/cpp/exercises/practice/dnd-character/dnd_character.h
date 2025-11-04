#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

using ability_t = std::int32_t;

// Returns the ability modifier for a given ability score
ability_t modifier(ability_t score);

ability_t ability();

struct Character
{
    std::array<ability_t, 6U> abilities;
    ability_t hitpoints;

    ability_t strength;
    ability_t dexterity;
    ability_t constitution;
    ability_t intelligence;
    ability_t wisdom;
    ability_t charisma;

    Character();
};

Character generate();

}  // namespace dnd_character
