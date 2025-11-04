#pragma once

#include <cstdint>

namespace dnd_character {

// Fixed-width signed integer type for ability scores (MISRA: avoid plain int)
using score_t = std::int32_t;

score_t ability();
score_t modifier(score_t score);

struct Character {
    score_t strength;
    score_t dexterity;
    score_t constitution;
    score_t intelligence;
    score_t wisdom;
    score_t charisma;
    score_t hitpoints;

    // Default constructor rolls abilities and computes hitpoints
    Character();
};

}  // namespace dnd_character
