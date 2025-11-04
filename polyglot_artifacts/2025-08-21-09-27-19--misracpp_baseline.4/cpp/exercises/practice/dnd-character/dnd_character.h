#pragma once

#include <array>

namespace dnd_character {

class Character {
public:
    Character();

    static int ability();
    static int modifier(int score);

    int strength();
    int dexterity();
    int constitution();
    int intelligence();
    int wisdom();
    int charisma();
    int hitpoints() const;

private:
    std::array<int, 6> abilities_;
    int hitpoints_;
};

}  // namespace dnd_character
