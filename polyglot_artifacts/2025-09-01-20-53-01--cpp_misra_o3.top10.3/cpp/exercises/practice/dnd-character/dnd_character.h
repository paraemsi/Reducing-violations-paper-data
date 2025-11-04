#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <random>

namespace dnd_character {

//  Fixed-width signed integer used for all numeric values in this module.
using score_t = std::int32_t;

/**
 * Roll four 6-sided dice and return the sum of the largest three.
 */
[[nodiscard]] auto ability() -> score_t;

/**
 * Calculate the ability modifier for a given ability score.
 * The modifier is floor((score − 10) / 2).
 */
[[nodiscard]] auto modifier(score_t score) -> score_t;

/**
 * A generator for a complete D&D character.
 */
class Character {
public:
    Character();

    //  Ability scores and hit-points are exposed as public data members
    //  because the supplied unit-tests access them directly.
    //  Getters remain available for additional, test-independent use.
    score_t strength{};
    score_t dexterity{};
    score_t constitution{};
    score_t intelligence{};
    score_t wisdom{};
    score_t charisma{};
    score_t hitpoints{};
};

}  // namespace dnd_character
