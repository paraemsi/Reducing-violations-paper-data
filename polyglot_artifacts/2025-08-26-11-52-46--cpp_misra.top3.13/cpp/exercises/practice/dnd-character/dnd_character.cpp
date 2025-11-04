#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <vector>
#include <numeric>
#include <cmath>

namespace dnd_character {

namespace {
    // Helper function to roll a single ability score
    dnd_character::ability_score_t roll_ability(std::mt19937& rng) {
        std::uniform_int_distribution<dnd_character::ability_score_t> dist(1, 6);
        std::array<dnd_character::ability_score_t, 4> rolls;
        for (std::size_t i = 0U; i < 4U; ++i) {
            rolls[i] = dist(rng);
        }
        std::sort(rolls.begin(), rolls.end());
        // Drop the lowest roll (rolls[0])
        return (rolls[1] + rolls[2] + rolls[3]);
    }
}

// Standalone ability function as required by tests
dnd_character::ability_score_t ability() {
    std::random_device rd;
    std::mt19937 rng(rd());
    return roll_ability(rng);
}

Character::Character() : m_abilities{}, m_hitpoints(0) {
    std::random_device rd;
    std::mt19937 rng(rd());

    for (std::size_t i = 0U; i < 6U; ++i) {
        m_abilities[i] = roll_ability(rng);
    }
    m_hitpoints = (10 + modifier(m_abilities[2]));
}

dnd_character::ability_score_t Character::strength() const {
    return m_abilities[0];
}

dnd_character::ability_score_t Character::dexterity() const {
    return m_abilities[1];
}

dnd_character::ability_score_t Character::constitution() const {
    return m_abilities[2];
}

dnd_character::ability_score_t Character::intelligence() const {
    return m_abilities[3];
}

dnd_character::ability_score_t Character::wisdom() const {
    return m_abilities[4];
}

dnd_character::ability_score_t Character::charisma() const {
    return m_abilities[5];
}

dnd_character::ability_score_t Character::hitpoints() const {
    return m_hitpoints;
}

}  // namespace dnd_character
