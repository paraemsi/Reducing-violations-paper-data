#pragma once

namespace dnd_character {

// Roll four six-sided dice and sum the highest three.
int ability();

// Compute the ability modifier: floor((score - 10) / 2).
int modifier(int score);

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
