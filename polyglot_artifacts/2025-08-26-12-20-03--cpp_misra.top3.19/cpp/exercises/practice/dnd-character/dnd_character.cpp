#include "dnd_character.h"

#include <algorithm>
#include <vector>
#include <numeric>
#include <cmath>

namespace dnd_character {

namespace {
    // Use a single random engine for all rolls
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int32_t> dist(1, 6);
}

// Standalone modifier function as required by tests
auto modifier(ability_score_t score) -> ability_score_t {
    // (score - 10) / 2, rounded down
    return static_cast<ability_score_t>(std::floor(static_cast<double>(score - 10) / 2.0));
}

// Standalone ability function as required by tests
auto ability() -> ability_score_t {
    std::vector<ability_score_t> rolls;
    for(std::size_t i = 0U; i < 4U; ++i) {
        rolls.push_back(dist(gen));
    }
    std::sort(rolls.begin(), rolls.end());
    return (rolls[1] + rolls[2] + rolls[3]);
}

dnd_character::ability_score_t Character::roll_ability() {
    std::vector<ability_score_t> rolls;
    for(std::size_t i = 0U; i < 4U; ++i) {
        rolls.push_back(dist(gen));
    }
    std::sort(rolls.begin(), rolls.end());
    return (rolls[1] + rolls[2] + rolls[3]);
}

Character::Character()
    : abilities_{}, strength(0), dexterity(0), constitution(0), intelligence(0), wisdom(0), charisma(0), hitpoints(0)
{
    for(std::size_t i = 0U; i < 6U; ++i) {
        abilities_[i] = roll_ability();
    }
    strength = abilities_[0];
    dexterity = abilities_[1];
    constitution = abilities_[2];
    intelligence = abilities_[3];
    wisdom = abilities_[4];
    charisma = abilities_[5];
    hitpoints = static_cast<hitpoint_t>(10 + modifier(constitution));
}

auto Character::ability_strength() const -> ability_score_t {
    return strength;
}

auto Character::ability_dexterity() const -> ability_score_t {
    return dexterity;
}

auto Character::ability_constitution() const -> ability_score_t {
    return constitution;
}

auto Character::ability_intelligence() const -> ability_score_t {
    return intelligence;
}

auto Character::ability_wisdom() const -> ability_score_t {
    return wisdom;
}

auto Character::ability_charisma() const -> ability_score_t {
    return charisma;
}

}  // namespace dnd_character
