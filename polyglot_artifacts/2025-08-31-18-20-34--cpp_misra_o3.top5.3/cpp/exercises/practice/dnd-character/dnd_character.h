#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

// fixed-width integral type for all abilities
using ability_t = std::int32_t;

// roll 4d6 and return the sum of the highest three dice
ability_t ability();

// compute the ability modifier as described by the D&D rules
ability_t modifier(ability_t score);

class Character {
public:
    Character();

    /* ability scores (3 – 18) */
    ability_t strength{};
    ability_t dexterity{};
    ability_t constitution{};
    ability_t intelligence{};
    ability_t wisdom{};
    ability_t charisma{};

    /* derived attribute */
    ability_t hitpoints{};
};

}  // namespace dnd_character
