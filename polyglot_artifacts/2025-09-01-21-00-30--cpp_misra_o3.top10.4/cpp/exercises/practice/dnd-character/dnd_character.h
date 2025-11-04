#pragma once

#include <cstdint>

namespace dnd_character {

// Roll four six–sided dice and return the sum of the highest three
[[nodiscard]] std::int32_t ability();

// Calculate the ability modifier for a given score
[[nodiscard]] std::int32_t modifier(std::int32_t score);

class Character {
public:
    Character();

    // Ability scores
    std::int32_t strength{};
    std::int32_t dexterity{};
    std::int32_t constitution{};
    std::int32_t intelligence{};
    std::int32_t wisdom{};
    std::int32_t charisma{};

    // Derived attribute
    std::int32_t hitpoints{};
};

}  // namespace dnd_character
