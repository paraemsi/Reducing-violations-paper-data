#pragma once

#include <cstdint>
#include <array>

namespace dnd_character {

// 32-bit signed integer is sufficient for every score and modifier we need.
using score_t = std::int32_t;

// Generate one ability score (sum of the highest three out of four d6 rolls).
score_t ability();

// Calculate the modifier for a given ability score.
score_t modifier(score_t score);

class Character {
public:
    Character();

    const score_t strength;
    const score_t dexterity;
    const score_t constitution;
    const score_t intelligence;
    const score_t wisdom;
    const score_t charisma;
    const score_t hitpoints;
};

}  // namespace dnd_character
