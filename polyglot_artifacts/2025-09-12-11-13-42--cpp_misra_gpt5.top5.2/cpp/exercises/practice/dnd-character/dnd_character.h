#pragma once

#include <cstdint>

namespace dnd_character {

using score_t = std::int32_t;
using hp_t = std::int32_t;

// Roll four 6-sided dice, drop the lowest, and sum the top three.
auto ability() -> score_t;

// Compute the ability modifier: floor((score - 10) / 2)
auto modifier(score_t score) -> score_t;

class Character {
public:
    Character();

    // Ability scores
    score_t strength;
    score_t dexterity;
    score_t constitution;
    score_t intelligence;
    score_t wisdom;
    score_t charisma;

    // Hit points: 10 + constitution modifier
    hp_t hitpoints;
};

}  // namespace dnd_character
