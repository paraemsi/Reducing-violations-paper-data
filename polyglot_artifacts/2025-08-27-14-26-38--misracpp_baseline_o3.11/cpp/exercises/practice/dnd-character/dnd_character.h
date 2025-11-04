#pragma once

#include <cmath>

namespace dnd_character {

/* Generate an ability score by rolling 4d6 and summing the highest three. */
int ability();

/* Calculate the ability modifier for a given ability score. */
int modifier(int score);

/* A fully-rolled D&D character. */
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
