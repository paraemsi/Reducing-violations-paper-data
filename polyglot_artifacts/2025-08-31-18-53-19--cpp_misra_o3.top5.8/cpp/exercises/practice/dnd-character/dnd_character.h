#pragma once

#include <array>
#include <cstdint>
#include <random>

namespace dnd_character {

std::int32_t ability();
std::int32_t modifier(std::int32_t score);

/*
 * A Dungeons & Dragons character.
 * Generates six ability scores using the “4d6 drop lowest” rule
 * and provides accessors for every ability, as well as hit-points.
 *
 * All integers use fixed-width signed types to comply with MISRA C++.
 */
class Character {
public:
    Character();

    /* ability scores */
    std::int32_t strength{};
    std::int32_t dexterity{};
    std::int32_t constitution{};
    std::int32_t intelligence{};
    std::int32_t wisdom{};
    std::int32_t charisma{};

    /* derived statistic */
    std::int32_t hitpoints{};
};

}  // namespace dnd_character
