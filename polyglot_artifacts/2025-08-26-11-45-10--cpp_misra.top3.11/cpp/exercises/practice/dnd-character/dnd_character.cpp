#include "dnd_character.h"

namespace dnd_character {

namespace {
    // Use a single random engine for all rolls
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<std::int32_t> dist(1, 6);
}

// Standalone ability function
dnd_character::ability_score_t ability(void) {
    std::array<std::int32_t, 4U> rolls{};
    for(std::size_t i = 0U; i < 4U; ++i) {
        rolls[i] = dist(engine);
    }
    std::sort(rolls.begin(), rolls.end());
    return (rolls[1] + rolls[2] + rolls[3]);
}

// Standalone modifier function
dnd_character::ability_score_t modifier(dnd_character::ability_score_t score) {
    return static_cast<dnd_character::ability_score_t>(((score - 10) / 2));
}

// Class static method for rolling ability
dnd_character::ability_score_t Character::roll_ability(void) {
    return ability();
}

Character::Character()
    : abilities_{}
    , hitpoints_{}
{
    for(std::size_t i = 0U; i < 6U; ++i) {
        abilities_[i] = roll_ability();
    }
    hitpoints_ = static_cast<hitpoint_t>(10 + modifier(abilities_[2U]));
}

Character::ability_score_t Character::ability_strength(void) const {
    return abilities_[0U];
}

Character::ability_score_t Character::ability_dexterity(void) const {
    return abilities_[1U];
}

Character::ability_score_t Character::ability_constitution(void) const {
    return abilities_[2U];
}

Character::ability_score_t Character::ability_intelligence(void) const {
    return abilities_[3U];
}

Character::ability_score_t Character::ability_wisdom(void) const {
    return abilities_[4U];
}

Character::ability_score_t Character::ability_charisma(void) const {
    return abilities_[5U];
}

Character::hitpoint_t Character::hitpoints(void) const {
    return hitpoints_;
}

}  // namespace dnd_character
