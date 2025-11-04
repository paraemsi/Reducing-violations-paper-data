#pragma once


namespace dnd_character {

// Roll four six-sided dice, drop the lowest, return the sum of the rest.
int ability();

// Ability-score modifier, rounded toward −∞.
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
