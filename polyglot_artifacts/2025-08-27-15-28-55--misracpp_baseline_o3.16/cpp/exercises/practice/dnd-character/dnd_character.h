#pragma once

namespace dnd_character {

// Roll four 6-sided dice, drop the lowest, and return the sum of the rest.
int ability();

// Calculate the ability modifier for a given score.
int modifier(int score);

// Representation of a D&D character with six abilities and hit points.
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
