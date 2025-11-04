#pragma once

#include <array>
#include <cstdint>
#include <random>

namespace dnd_character {

using ability_t = std::int32_t;

struct character
{
    ability_t strength;
    ability_t dexterity;
    ability_t constitution;
    ability_t intelligence;
    ability_t wisdom;
    ability_t charisma;
    ability_t hitpoints;
};

character generate();

ability_t ability();
ability_t modifier(ability_t score);

}  // namespace dnd_character
