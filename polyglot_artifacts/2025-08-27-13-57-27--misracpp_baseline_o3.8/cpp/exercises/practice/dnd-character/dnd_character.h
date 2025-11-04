#pragma once

#include <cmath>

namespace dnd_character {

// Roll four 6-sided dice, drop the lowest, return the sum of the remaining three.
int ability();

// Calculate the ability modifier for a given score.
int modifier(int score);

class Character {
public:
    Character();

    // Ability scores are exposed as immutable public data members so
    // unit-tests can access them directly (e.g. `character.strength`).
    const int strength;
    const int dexterity;
    const int constitution;
    const int intelligence;
    const int wisdom;
    const int charisma;

    // Pre-computed at construction: 10 + constitution modifier.
    const int hitpoints;
};

}  // namespace dnd_character
