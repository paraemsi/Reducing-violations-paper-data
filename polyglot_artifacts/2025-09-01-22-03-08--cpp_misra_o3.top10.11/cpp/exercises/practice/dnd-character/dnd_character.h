#pragma once

#include <cstdint>

namespace dnd_character {

// 32-bit signed type alias required by MISRA rules
using score_t = std::int32_t;

/*
 * Calculate the ability modifier that corresponds to an
 * ability score.  The calculation follows the D&D rule:
 *   modifier = floor((score − 10) / 2)
 */
score_t modifier(score_t score);

/*
 * Roll four six-sided dice, discard the lowest roll and
 * return the sum of the remaining three.
 */
score_t ability();

/*
 * A complete D&D character with six ability scores and
 * derived hit-points.
 */
class Character {
public:
    Character();


    // Public data members as required by the Exercism tests
    score_t strength{};
    score_t dexterity{};
    score_t constitution{};
    score_t intelligence{};
    score_t wisdom{};
    score_t charisma{};

    score_t hitpoints{};

    // no private data – abilities are already public to satisfy tests
};

}  // namespace dnd_character
