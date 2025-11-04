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

    // Expose member variable-like access for tests
    const int& strength;
    const int& dexterity;
    const int& constitution;
    const int& intelligence;
    const int& wisdom;
    const int& charisma;
    const int& hitpoints;

    static const int strength_idx;
    static const int dexterity_idx;
    static const int constitution_idx;
    static const int intelligence_idx;
    static const int wisdom_idx;
    static const int charisma_idx;

private:
    std::array<int, 6> abilities_;
    int hitpoints_;
};

int ability();
int modifier(int ability_score);

}  // namespace dnd_character
