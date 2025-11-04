#pragma once

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
Character create();

}  // namespace dnd_character
