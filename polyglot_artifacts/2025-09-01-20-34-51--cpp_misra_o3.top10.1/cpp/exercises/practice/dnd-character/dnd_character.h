#pragma once

#include <cstdint>

namespace dnd_character {

// Generate an ability score by rolling four 6-sided dice and
// summing the largest three results.
[[nodiscard]] std::int32_t ability();

// Calculate the ability modifier for a given ability score.
// The modifier is floor((score − 10) / 2) and may be negative.
[[nodiscard]] std::int32_t modifier(std::int32_t score);

// A complete D&D character with the six ability scores and hit-points.
class Character {
public:
    Character();

    // Ability scores (range 3–18) and hit-points
    std::int32_t strength{};
    std::int32_t dexterity{};
    std::int32_t constitution{};
    std::int32_t intelligence{};
    std::int32_t wisdom{};
    std::int32_t charisma{};
    std::int32_t hitpoints{};
};

}  // namespace dnd_character
