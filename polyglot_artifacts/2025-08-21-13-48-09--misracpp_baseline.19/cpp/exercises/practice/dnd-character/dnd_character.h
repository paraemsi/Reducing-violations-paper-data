#pragma once

#include <array>
#include <random>

namespace dnd_character {

class Character {
public:
    Character();

    static int ability();
    int strength() const;
    int dexterity() const;
    int constitution() const;
    int intelligence() const;
    int wisdom() const;
    int charisma() const;
    int hitpoints() const;

// No duplicate private section or member variables here
};

 // Provide free functions in the dnd_character namespace
int modifier(int ability_score);

}  // namespace dnd_character
