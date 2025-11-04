#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

/*  Roll four six-sided dice, discard the lowest, and
 *  return the sum of the remaining three.                                        */
[[nodiscard]] std::int32_t ability();

/*  Calculate the ability modifier according to the
 *  D&D rule: floor((score − 10) / 2).                                            */
[[nodiscard]] std::int32_t modifier(std::int32_t score);

class Character
{
public:
    Character();

    /*  Public ability scores and hit-points, as required by the tests.          */
    std::int32_t strength{};
    std::int32_t dexterity{};
    std::int32_t constitution{};
    std::int32_t intelligence{};
    std::int32_t wisdom{};
    std::int32_t charisma{};
    std::int32_t hitpoints{};
};

}  // namespace dnd_character
