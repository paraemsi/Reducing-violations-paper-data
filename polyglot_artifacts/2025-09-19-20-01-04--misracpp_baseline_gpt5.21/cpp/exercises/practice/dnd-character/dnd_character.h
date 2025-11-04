#pragma once

namespace dnd_character {

// Roll four 6-sided dice and return the sum of the highest three.
int ability();

 // Compute the ability modifier: floor((score - 10) / 2).
int modifier(int score);

struct Character {
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
    int hitpoints;

    Character();
};

}  // namespace dnd_character
