#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <vector>

namespace dnd_character {

namespace {
    // Helper function to roll 4d6 and sum the highest 3
    ability_t roll_ability(std::mt19937& rng) {
        std::uniform_int_distribution<ability_t> dist(1, 6);
        std::array<ability_t, 4> rolls{};
        for(std::size_t i = 0U; i < 4U; ++i) {
            rolls[i] = dist(rng);
        }
        std::sort(rolls.begin(), rolls.end());
        // sum the highest 3
        return (rolls[1] + rolls[2] + rolls[3]);
    }
}

// Standalone modifier function as required by tests
ability_t modifier(ability_t score) {
    return static_cast<ability_t>(((score - 10) / 2));
}

// Standalone ability function as required by tests
ability_t ability() {
    std::random_device rd;
    std::mt19937 rng(rd());
    return roll_ability(rng);
}

Character::Character() : abilities_{} {
    std::random_device rd;
    std::mt19937 rng(rd());
    for(std::size_t i = 0U; i < 6U; ++i) {
        abilities_[i] = roll_ability(rng);
    }
    strength = abilities_[0];
    dexterity = abilities_[1];
    constitution = abilities_[2];
    intelligence = abilities_[3];
    wisdom = abilities_[4];
    charisma = abilities_[5];
    hitpoints = static_cast<ability_t>(10 + modifier(constitution));
}

ability_t Character::ability_strength() const {
    return abilities_[0];
}

ability_t Character::ability_dexterity() const {
    return abilities_[1];
}

ability_t Character::ability_constitution() const {
    return abilities_[2];
}

ability_t Character::ability_intelligence() const {
    return abilities_[3];
}

ability_t Character::ability_wisdom() const {
    return abilities_[4];
}

ability_t Character::ability_charisma() const {
    return abilities_[5];
}

ability_t Character::ability_modifier(ability_t score) const {
    return modifier(score);
}

ability_t Character::hitpoints() const {
    return static_cast<ability_t>(10 + modifier(ability_constitution()));
}

}  // namespace dnd_character
