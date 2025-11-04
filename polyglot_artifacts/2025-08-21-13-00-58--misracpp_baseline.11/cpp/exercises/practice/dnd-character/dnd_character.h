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

};

int ability();
int modifier(int ability_score);

}  // namespace dnd_character
