#pragma once

#include <cstdint>

namespace dnd_character {

// Generate a single ability score (sum of the highest 3 out of 4d6).
std::int32_t ability();

// Calculate the ability modifier for a given ability score.
std::int32_t modifier(std::int32_t score);

class Character {
public:
    Character();

    // Public ability scores
    std::int32_t strength;
    std::int32_t dexterity;
    std::int32_t constitution;
    std::int32_t intelligence;
    std::int32_t wisdom;
    std::int32_t charisma;

    // Public hit-point total
    std::int32_t hitpoints;
};

}  // namespace dnd_character
