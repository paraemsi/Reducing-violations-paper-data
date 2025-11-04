#pragma once
#include <random>

namespace dnd_character {

struct Character {
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
Character generate();

}  // namespace dnd_character
