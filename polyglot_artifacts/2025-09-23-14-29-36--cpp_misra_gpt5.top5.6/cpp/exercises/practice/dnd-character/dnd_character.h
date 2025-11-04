#pragma once

#include <cstdint>

namespace dnd_character {

using score_t = std::int32_t;

// Roll four 6-sided dice and return the sum of the highest three.
auto ability() -> score_t;

// Compute the ability modifier as floor((score - 10) / 2).
auto modifier(score_t score) -> score_t;

class Character {
public:
    Character();

    // Public fields (commonly expected by D&D character kata/tests)
    score_t strength{};
    score_t dexterity{};
    score_t constitution{};
    score_t intelligence{};
    score_t wisdom{};
    score_t charisma{};
    score_t hitpoints{};
};

}  // namespace dnd_character
