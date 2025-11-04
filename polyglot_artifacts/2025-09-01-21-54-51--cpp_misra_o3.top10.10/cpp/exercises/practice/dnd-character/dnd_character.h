#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

/* Roll four 6-sided dice, discard the lowest, return the sum of the remaining
 * three dice. The result is always in the range [3, 18]. */
std::int32_t ability();

/* Calculate the ability modifier for a given ability score.
 * The modifier is ⌊(score − 10)/2⌋. */
std::int32_t modifier(std::int32_t score);

/* A randomly generated D&D character. */
class Character
{
public:
    Character();

    const std::int32_t strength;
    const std::int32_t dexterity;
    const std::int32_t constitution;
    const std::int32_t intelligence;
    const std::int32_t wisdom;
    const std::int32_t charisma;

    const std::int32_t hitpoints;
};

}  // namespace dnd_character
