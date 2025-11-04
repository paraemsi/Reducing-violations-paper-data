#pragma once

#include <cstdint>

namespace dnd_character {

// Roll four d6, drop the lowest, and return the sum of the highest three.
auto ability() -> std::int32_t;

// Compute the D&D ability modifier for a given ability score.
auto modifier(std::int32_t score) -> std::int32_t;

class Character {
public:
    Character();

    // Public ability scores and hit points to satisfy test expectations.
    std::int32_t strength{};
    std::int32_t dexterity{};
    std::int32_t constitution{};
    std::int32_t intelligence{};
    std::int32_t wisdom{};
    std::int32_t charisma{};
    std::int32_t hitpoints{};
};

}  // namespace dnd_character
