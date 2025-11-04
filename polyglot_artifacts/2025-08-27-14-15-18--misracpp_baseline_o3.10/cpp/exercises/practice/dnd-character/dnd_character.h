#pragma once

namespace dnd_character {

// Roll four six-sided dice, discard the lowest and
// return the sum of the remaining three.
int ability();

// Calculate the ability modifier for a given score.
int modifier(int score);

// A complete D&D character with six abilities and hit-points.
class Character {
public:
    Character();

    // Abilities
    const int strength;
    const int dexterity;
    const int constitution;
    const int intelligence;
    const int wisdom;
    const int charisma;

    // Hit points
    const int hitpoints;
};

}  // namespace dnd_character
