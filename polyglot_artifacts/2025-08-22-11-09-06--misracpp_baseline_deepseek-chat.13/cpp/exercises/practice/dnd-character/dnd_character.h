#pragma once
#include <random>

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
int modifier(int constitution);

}  // namespace dnd_character
