#pragma once

#include <cstdint>

namespace dnd_character {

using score_t = int32_t;

/*  Generate a single ability score by rolling four six-sided dice,
 *  discarding the lowest roll and summing the remaining three. */
score_t ability();

/*  Calculate the ability modifier for a given score.
 *  The result is ⌊(score − 10) / 2⌋. */
score_t modifier(score_t score);

class Character
{
public:
    Character();

    /*  Public, read-only ability scores and hit-points expected by the tests. */
    const score_t strength;
    const score_t dexterity;
    const score_t constitution;
    const score_t intelligence;
    const score_t wisdom;
    const score_t charisma;
    const score_t hitpoints;
};

} // namespace dnd_character
