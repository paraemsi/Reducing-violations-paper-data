#pragma once


namespace dnd_character {

// Calculate the ability modifier for a given ability score
int modifier(int score);

// Roll four six-sided dice, discard the lowest roll, and return the sum of the
// remaining three rolls.
int ability();

// A simple aggregate representing a freshly rolled D&D character
struct Character {
    Character();

    int strength{};
    int dexterity{};
    int constitution{};
    int intelligence{};
    int wisdom{};
    int charisma{};
    int hitpoints{};
};

}  // namespace dnd_character
