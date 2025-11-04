#pragma once

#include <array>

namespace dnd_character {

class Character {
public:
    Character();

    int strength() const;
    int dexterity() const;
    int constitution() const;
    int intelligence() const;
    int wisdom() const;
    int charisma() const;
    int hitpoints() const;
    int modifier(int ability_score) const;

private:
    std::array<int, 6> abilities_;
    int hitpoints_;
};

int ability();
int modifier(int ability_score);

}  // namespace dnd_character
