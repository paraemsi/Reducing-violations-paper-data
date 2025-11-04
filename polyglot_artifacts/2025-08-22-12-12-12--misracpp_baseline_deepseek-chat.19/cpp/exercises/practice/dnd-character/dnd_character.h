#pragma once

namespace dnd_character {

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

int ability();
int modifier(int constitution);

}  // namespace dnd_character
