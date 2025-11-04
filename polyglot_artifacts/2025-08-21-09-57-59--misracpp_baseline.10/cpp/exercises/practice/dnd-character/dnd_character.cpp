#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <vector>
#include <numeric>
#include <cmath>

namespace dnd_character {

namespace {
    // Helper function to get a random number generator
    std::mt19937& rng() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }
}

int Character::ability() {
    std::uniform_int_distribution<int> dist(1, 6);
    std::vector<int> rolls(4);
    for (int& roll : rolls) {
        roll = dist(rng());
    }
    std::sort(rolls.begin(), rolls.end(), std::greater<int>());
    return rolls[0] + rolls[1] + rolls[2];
}

int Character::modifier(int score) {
    return (score - 10) / 2;
}

Character::Character()
    : m_strength(ability()),
      m_dexterity(ability()),
      m_constitution(ability()),
      m_intelligence(ability()),
      m_wisdom(ability()),
      m_charisma(ability())
{
    m_hitpoints = 10 + modifier(m_constitution);
}

int Character::strength() const {
    return m_strength;
}

int Character::dexterity() const {
    return m_dexterity;
}

int Character::constitution() const {
    return m_constitution;
}

int Character::intelligence() const {
    return m_intelligence;
}

int Character::wisdom() const {
    return m_wisdom;
}

int Character::charisma() const {
    return m_charisma;
}

int Character::hitpoints() const {
    return m_hitpoints;
}

}  // namespace dnd_character
