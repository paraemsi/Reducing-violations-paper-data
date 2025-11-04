#pragma once

namespace dnd_character {

int modifier(int score);
int ability();

class Character {
public:
    Character();

    static int ability();

    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;

    int hitpoints;
};

}  // namespace dnd_character
