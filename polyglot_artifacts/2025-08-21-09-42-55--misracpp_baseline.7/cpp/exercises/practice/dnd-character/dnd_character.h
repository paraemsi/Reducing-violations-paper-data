#pragma once

#include <array>

namespace dnd_character {

class Character {
public:
    Character();

    // Returns the character's strength ability score (for backward compatibility)
    int ability() const;
    int strength() const;
    int dexterity() const;
    int constitution() const;
    int intelligence() const;
    int wisdom() const;
    int charisma() const;
    int hitpoints() const;

    static int modifier(int score);

private:
    std::array<int, 6> abilities_{};
    int hitpoints_{};
};

// Provide free function for modifier in the dnd_character namespace
int modifier(int score);

}  // namespace dnd_character
