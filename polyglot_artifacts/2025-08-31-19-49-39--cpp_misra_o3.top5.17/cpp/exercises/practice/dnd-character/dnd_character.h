#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

// Alias for all integral values used by this module.
// 32-bit signed is more than enough to hold any value we generate.
using ability_score_t = std::int32_t;

// Generate a single ability score by rolling four 6-sided dice,
// discarding the lowest die and summing the remaining three.
ability_score_t ability();

// Ability score modifier as defined by D&D rules.
ability_score_t modifier(ability_score_t score);

class Character {
public:
    Character();

    // Public, read-only ability scores.
    const ability_score_t strength;
    const ability_score_t dexterity;
    const ability_score_t constitution;
    const ability_score_t intelligence;
    const ability_score_t wisdom;
    const ability_score_t charisma;

    // Initial hit-points are 10 + constitution modifier.
    const ability_score_t hitpoints;
};

}  // namespace dnd_character
