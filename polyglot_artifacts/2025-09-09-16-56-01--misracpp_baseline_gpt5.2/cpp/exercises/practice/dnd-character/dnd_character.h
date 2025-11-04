#pragma once

namespace dnd_character {

int ability();
int modifier(int score);

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
