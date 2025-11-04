#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

/*
 * Roll four six-sided dice, discard the lowest die, and return
 * the total of the remaining three — an ability score.
 */
std::int32_t ability();

/*
 * Compute the ability modifier as defined by the D&D rules.
 */
std::int32_t modifier(std::int32_t score);

class Character {
public:
    Character();

    /* ability scores are public because the tests access them directly */
    std::int32_t strength {};
    std::int32_t dexterity {};
    std::int32_t constitution {};
    std::int32_t intelligence {};
    std::int32_t wisdom {};
    std::int32_t charisma {};

    /* derived hit-points value */
    std::int32_t hitpoints {};
};

}  // namespace dnd_character
