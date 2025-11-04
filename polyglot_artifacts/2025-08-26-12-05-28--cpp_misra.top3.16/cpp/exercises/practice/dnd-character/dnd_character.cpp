#include "dnd_character.h"

namespace dnd_character {

namespace {
    // Use a single random engine for all rolls
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<std::int32_t> dist(1, 6);
}

dnd_character::ability_score_t Character::roll_ability() {
    // Roll four 6-sided dice, drop the lowest, sum the rest
    std::array<std::int32_t, 4> rolls{};
    for(std::size_t i = 0U; i < 4U; ++i) {
        rolls[i] = dist(engine);
    }
    // Find the minimum roll
    std::size_t min_index = 0U;
    for(std::size_t i = 1U; i < 4U; ++i) {
        if(rolls[i] < rolls[min_index]) {
            min_index = i;
        }
    }
    // Sum all except the minimum
    std::int32_t sum = 0;
    for(std::size_t i = 0U; i < 4U; ++i) {
        if(i != min_index) {
            sum = (sum + rolls[i]);
        }
    }
    return sum;
}

// Standalone function for ability() as required by tests
ability_score_t ability() {
    return Character::roll_ability();
}

Character::Character() : abilities_{}, hitpoints_{0} {
    for(std::size_t i = 0U; i < 6U; ++i) {
        abilities_[i] = roll_ability();
    }
    hitpoints_ = (10 + ability_modifier(abilities_[2]));
}

dnd_character::ability_score_t Character::ability_strength() const {
    return abilities_[0];
}

dnd_character::ability_score_t Character::ability_dexterity() const {
    return abilities_[1];
}

dnd_character::ability_score_t Character::ability_constitution() const {
    return abilities_[2];
}

dnd_character::ability_score_t Character::ability_intelligence() const {
    return abilities_[3];
}

dnd_character::ability_score_t Character::ability_wisdom() const {
    return abilities_[4];
}

dnd_character::ability_score_t Character::ability_charisma() const {
    return abilities_[5];
}

dnd_character::hitpoint_t Character::hitpoints() const {
    return hitpoints_;
}

dnd_character::ability_score_t Character::ability_modifier(ability_score_t score) {
    // (score - 10) / 2, rounded down
    return static_cast<ability_score_t>(((score - 10) / 2));
}

// Standalone function for modifier as required by tests
ability_score_t modifier(ability_score_t score) {
    return Character::ability_modifier(score);
}

}  // namespace dnd_character
