#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

using score_t = std::int32_t;

// Generate one ability score by rolling four 6-sided dice and summing the best three rolls
score_t ability();

// Compute the ability-score modifier as ⌊(score − 10) / 2⌋
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
