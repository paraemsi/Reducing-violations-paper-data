#pragma once

#include <vector>

namespace dnd_character {

int modifier(int score);
int ability();

class Character {
public:
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
    int hitpoints;

    Character();
};

}  // namespace dnd_character
