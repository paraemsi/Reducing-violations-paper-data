#pragma once

#include <cstdint>

namespace dnd_character {

// Fixed-width signed integer used for all numeric values.
using score_t = std::int32_t;

// Roll four 6-sided dice, drop the lowest, and return the sum of the rest.
score_t ability();

// Calculate the ability modifier: floor((score − 10) / 2).
inline constexpr score_t modifier(score_t score)
{
    const score_t delta { (static_cast<score_t>(score) - static_cast<score_t>(10)) };
    score_t result { (delta / static_cast<score_t>(2)) };

    if ((delta < static_cast<score_t>(0)) && ((delta % static_cast<score_t>(2)) != static_cast<score_t>(0))) {
        --result;
    }

    return result;
}

// A randomly generated D-and-D character.
class Character {
public:
    Character();

    // Public, read-only ability scores and hit-points that the tests access
    const score_t strength;
    const score_t dexterity;
    const score_t constitution;
    const score_t intelligence;
    const score_t wisdom;
    const score_t charisma;
    const score_t hitpoints;
};

}  // namespace dnd_character
