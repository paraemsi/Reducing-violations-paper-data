#pragma once

namespace dnd_character {

// Generate a single ability score by rolling four 6-sided dice,
// dropping the lowest roll, and summing the rest.
int ability();

// Calculate the ability modifier for a given score.
// (score − 10) / 2 rounded down.
int modifier(int score);

// A fully-generated D&D character.
class Character {
public:
    Character();

    // ability scores and hit points are accessed directly by the tests
    int strength{};
    int dexterity{};
    int constitution{};
    int intelligence{};
    int wisdom{};
    int charisma{};
    int hitpoints{};
};

}  // namespace dnd_character
