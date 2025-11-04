#pragma once

#include <cstdint>

namespace dnd_character {

// Fixed-width signed integer used for every ability related value
using ability_t = std::int32_t;

// Generate one ability score by rolling four 6-sided dice
// and summing the largest three rolls.
ability_t ability();

// Compute the D&D ability modifier for a given score.
ability_t modifier(ability_t score);

class Character {
public:
    Character();

    const ability_t strength;
    const ability_t dexterity;
    const ability_t constitution;
    const ability_t intelligence;
    const ability_t wisdom;
    const ability_t charisma;
    const ability_t hitpoints;
};

}  // namespace dnd_character
