#pragma once

#include <array>

namespace dnd_character {

// Ability modifier is floor((score - 10) / 2).
int modifier(int score);

// Roll four six-sided dice and return the sum of the largest three.
int ability();

// A randomly generated D&D character.
class Character {
public:
    Character();

    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
    int hitpoints;
};

}  // namespace dnd_character
