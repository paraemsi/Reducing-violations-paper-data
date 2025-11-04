#pragma once

namespace dnd_character {

int ability();
int modifier(int score);

class Character {
public:
    Character();

    const int strength;
    const int dexterity;
    const int constitution;
    const int intelligence;
    const int wisdom;
    const int charisma;
    const int hitpoints;
};

}  // namespace dnd_character
