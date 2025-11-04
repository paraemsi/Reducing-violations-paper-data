#pragma once

#include <array>
#include <random>

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
    int ability() const; // Rolls 4d6, drops the lowest, returns sum

    // Expose modifier and ability as required by the tests
    static int modifier(int score);
    static int ability();

private:
    std::array<int, 6> abilities_;
    int hitpoints_;
};

}  // namespace dnd_character
