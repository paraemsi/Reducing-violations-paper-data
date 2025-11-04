#pragma once

namespace dnd_character {

int modifier(int score);
int ability();

struct Character {
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
