#pragma once

#include <array>

namespace dnd_character {

int ability();                    // roll 4d6 and drop the lowest
int modifier(int score);          // ability score modifier as per D&D rules

class Character {
public:
    Character();                  // rolls all abilities on construction

    const int strength;
    const int dexterity;
    const int constitution;
    const int intelligence;
    const int wisdom;
    const int charisma;
    const int hitpoints;
};

}  // namespace dnd_character
