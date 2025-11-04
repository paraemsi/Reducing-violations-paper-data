#pragma once

#include <array>

namespace dnd_character {

// Roll 4d6, drop the lowest die, and sum the rest.
int ability();

// Calculate the ability modifier, rounding down.
int modifier(int score);

class Character {
public:
    Character();

    const int strength;
    const int dexterity;
    const int constitution;
    const int intelligence;
    const int wisdom;
    const int charisma;

    const int hitpoints;
};

}  // namespace dnd_character
