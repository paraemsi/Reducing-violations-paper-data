#pragma once

#include <array>

namespace dnd_character {

// Roll four six-sided dice and return the sum of the highest three.
int ability();

// Calculate the ability modifier for a given ability score.
int modifier(int score);

// A Dungeons & Dragons character with six ability scores and hit points.
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
