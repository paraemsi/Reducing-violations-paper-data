#pragma once

#include <cstdint>

namespace dnd_character {

    // Fixed-width aliases per MISRA guidance
using i32 = std::int32_t;

// Roll 4d6 and sum the highest three dice
i32 ability();

// Compute the ability modifier: floor((score - 10) / 2)
i32 modifier(i32 score);

class Character {
public:
    i32 strength;
    i32 dexterity;
    i32 constitution;
    i32 intelligence;
    i32 wisdom;
    i32 charisma;
    i32 hitpoints;

    Character();

};

}  // namespace dnd_character
