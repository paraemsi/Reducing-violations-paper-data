#pragma once

#include <cstdint>

namespace dnd_character {

struct Character final {
    // Ability scores (3..18) generated per 4d6 drop-lowest
    std::int32_t strength;
    std::int32_t dexterity;
    std::int32_t constitution;
    std::int32_t intelligence;
    std::int32_t wisdom;
    std::int32_t charisma;
    // Hit points = 10 + modifier(constitution)
    std::int32_t hitpoints;

    Character();
};

 // Roll four six-sided dice, drop the lowest, and sum the rest.
std::int32_t ability() noexcept;
// Compute ability modifier: floor((score - 10) / 2)
std::int32_t modifier(std::int32_t score) noexcept;

}  // namespace dnd_character
