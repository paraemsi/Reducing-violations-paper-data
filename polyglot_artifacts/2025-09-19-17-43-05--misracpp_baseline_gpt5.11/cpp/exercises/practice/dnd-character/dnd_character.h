#pragma once

namespace dnd_character {

// Roll four 6-sided dice, drop the lowest, and sum the remaining three.
int ability();

// Compute the ability modifier: floor((score - 10) / 2).
int modifier(int score);

class Character {
public:
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
    int hitpoints;

    // Constructs a character with randomly generated abilities
    // and hitpoints = 10 + modifier(constitution).
    Character();
};

}  // namespace dnd_character
