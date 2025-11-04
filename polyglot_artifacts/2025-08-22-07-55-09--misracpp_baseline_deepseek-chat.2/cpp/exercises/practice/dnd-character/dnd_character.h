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
int generate_hitpoints(int constitution);
Character generate();

}  // namespace dnd_character
