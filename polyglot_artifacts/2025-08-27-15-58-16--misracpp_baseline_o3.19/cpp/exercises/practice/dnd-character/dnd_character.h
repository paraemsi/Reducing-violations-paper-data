#pragma once

#include <cmath>

namespace dnd_character {

// Generate an ability score by rolling four 6-sided dice and summing the
// highest three rolls.
int ability();

// Calculate the ability modifier for the given ability score.
int modifier(int score);

// A fully-generated D&D character with six abilities and hit points.
class Character {
public:
    Character();

    // Public ability scores and hit points, matching test expectations.
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;

    int hitpoints;
};

}  // namespace dnd_character
