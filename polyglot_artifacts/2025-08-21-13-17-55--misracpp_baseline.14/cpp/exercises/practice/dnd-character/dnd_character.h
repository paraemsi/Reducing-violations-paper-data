#pragma once

#include <array>
#include <random>

namespace dnd_character {

class Character {
public:
    Character();

    static int ability();
    static int modifier(int score);

    int strength() const;
    int dexterity() const;
    int constitution() const;
    int intelligence() const;
    int wisdom() const;
    int charisma() const;
    int hitpoints() const;

private:
    std::array<int, 6> abilities_;
};

}  // namespace dnd_character
