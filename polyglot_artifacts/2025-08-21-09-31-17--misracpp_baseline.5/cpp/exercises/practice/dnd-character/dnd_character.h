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
    static int modifier(int ability_score);

private:
    // std::array<int, 6> abilities_; // Remove unused member
};

int ability();
int modifier(int ability_score);

}  // namespace dnd_character
