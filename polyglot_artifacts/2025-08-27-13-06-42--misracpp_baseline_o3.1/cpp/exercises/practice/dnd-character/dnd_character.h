#pragma once


namespace dnd_character {

// Roll 4d6 and return the sum of the highest three dice
int ability();

// Calculate the ability modifier for a given ability score
int modifier(int score);

class Character {
public:
    Character();

    // ability scores (3-18) – accessed directly by the tests
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;

    // derived attribute – 10 + constitution modifier
    int hitpoints;
};

}  // namespace dnd_character
