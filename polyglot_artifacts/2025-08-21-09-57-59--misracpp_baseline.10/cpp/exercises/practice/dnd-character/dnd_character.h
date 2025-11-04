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
    static int ability();
    static int modifier(int score);

private:
    int m_strength;
    int m_dexterity;
    int m_constitution;
    int m_intelligence;
    int m_wisdom;
    int m_charisma;
    int m_hitpoints;
};

}  // namespace dnd_character
