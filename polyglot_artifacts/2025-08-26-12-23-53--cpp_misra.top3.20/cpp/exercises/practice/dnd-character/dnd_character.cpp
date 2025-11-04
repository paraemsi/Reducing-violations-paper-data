#include "dnd_character.h"

namespace dnd_character {

namespace {
    // Use a single random engine for all rolls
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<std::int32_t> dist(1, 6);
}

// Standalone modifier function
ability_score_t modifier(ability_score_t score) {
    return ((score - 10) / 2);
}

// Standalone ability function
ability_score_t ability(void) {
    std::array<std::int32_t, 4> rolls{};
    for(std::size_t i = 0U; i < 4U; ++i) {
        rolls[i] = dist(engine);
    }
    std::int32_t min_roll = rolls[0];
    for(std::size_t i = 1U; i < 4U; ++i) {
        if(rolls[i] < min_roll) {
            min_roll = rolls[i];
        }
    }
    std::int32_t sum = 0;
    for(std::size_t i = 0U; i < 4U; ++i) {
        sum = (sum + rolls[i]);
    }
    return (sum - min_roll);
}

dnd_character::ability_score_t Character::roll_ability(void) {
    return ability();
}

dnd_character::ability_score_t Character::calculate_modifier(ability_score_t score) {
    return modifier(score);
}

Character::Character()
    : abilities_{}
    , hitpoints_(0)
    , strength(0)
    , dexterity(0)
    , constitution(0)
    , intelligence(0)
    , wisdom(0)
    , charisma(0)
    , hitpoints(0)
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
    hitpoints = (10 + calculate_modifier(constitution));
    hitpoints_ = hitpoints;
}

Character::ability_score_t Character::ability_strength(void) const {
    return abilities_[0];
}

Character::ability_score_t Character::ability_dexterity(void) const {
    return abilities_[1];
}

Character::ability_score_t Character::ability_constitution(void) const {
    return abilities_[2];
}

Character::ability_score_t Character::ability_intelligence(void) const {
    return abilities_[3];
}

Character::ability_score_t Character::ability_wisdom(void) const {
    return abilities_[4];
}

Character::ability_score_t Character::ability_charisma(void) const {
    return abilities_[5];
}

Character::hitpoint_t Character::hitpoints(void) const {
    return hitpoints_;
}

Character::ability_score_t Character::ability_modifier(ability_score_t score) const {
    return calculate_modifier(score);
}

}  // namespace dnd_character
