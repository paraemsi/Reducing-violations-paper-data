#pragma once

#include <random>

namespace dnd_character {

// Generate a single ability score by rolling four six-sided dice and
// summing the highest three results.
int ability();

// Calculate the modifier for the supplied ability score.
int modifier(int score);

class Character {
public:
    // Constructs a fully generated D&D character.
    Character();

    // Rolled ability scores and hit-points are exposed publicly to satisfy the
    // Exercism test-suite access pattern (e.g. `character.strength`).
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
    int hitpoints;
};

}  // namespace dnd_character
