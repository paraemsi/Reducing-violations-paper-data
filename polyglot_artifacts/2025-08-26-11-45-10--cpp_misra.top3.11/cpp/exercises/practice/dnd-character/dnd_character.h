#pragma once

#include <array>
#include <cstdint>
#include <random>

namespace dnd_character {

// MISRA: Do not use std::int32_t directly in declarations, use an alias type.
using ability_score_t = std::int32_t;
using hitpoint_t = std::int32_t;

// Standalone modifier function as required by tests
ability_score_t modifier(ability_score_t score);

// Standalone ability function as required by tests
ability_score_t ability(void);

class Character {
public:
    Character();

    ability_score_t strength;
    ability_score_t dexterity;
    ability_score_t constitution;
    ability_score_t intelligence;
    ability_score_t wisdom;
    ability_score_t charisma;
    hitpoint_t hitpoints;

private:
    // No private members
};

}  // namespace dnd_character
