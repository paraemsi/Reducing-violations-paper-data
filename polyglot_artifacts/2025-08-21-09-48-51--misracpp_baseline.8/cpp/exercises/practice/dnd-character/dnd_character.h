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
    // int modifier(int ability_score) const; // Remove this member function declaration

private:
};

int ability();
int modifier(int ability_score);

}  // namespace dnd_character
