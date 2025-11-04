#pragma once


namespace dnd_character {

// Generate a single ability score by rolling four 6-sided dice,
// discarding the lowest roll and summing the remaining three.
int ability();

// Calculate the ability modifier for a given score.
// Modifier = floor((score − 10) / 2).
int modifier(int score);

// A complete D&D character with six ability scores and hit points.
class Character {
public:
    Character();

    // Ability scores
    int strength{};
    int dexterity{};
    int constitution{};
    int intelligence{};
    int wisdom{};
    int charisma{};

    // Derived attribute
    int hitpoints{};
};

}  // namespace dnd_character
