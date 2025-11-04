#pragma once

#include <array>

namespace dnd_character {

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

private:
    // No private members needed
};

int modifier(int ability_score);
int ability();

}  // namespace dnd_character
