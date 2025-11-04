#include "dnd_character.h"

namespace dnd_character {

namespace {
    // Use a single random engine for all rolls
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<std::int32_t> dist(1, 6);
}

// Standalone modifier function as required by tests
ability_score_t modifier(ability_score_t score) {
    return static_cast<ability_score_t>(((score - 10) / 2));
}

// Standalone ability function as required by tests
ability_score_t ability() {
    std::array<std::int32_t, 4U> rolls{};
    for(std::size_t i = 0U; i < 4U; ++i) {
        rolls[i] = dist(engine);
    }
    std::sort(rolls.begin(), rolls.end());
    return (rolls[1U] + rolls[2U] + rolls[3U]);
}

dnd_character::ability_score_t Character::roll_ability() {
    return ability();
}

// Expose public const references for test compatibility
Character::Character()
    : abilities_{}
    , hitpoints_{0}
    , strength(abilities_[0U])
    , dexterity(abilities_[1U])
    , constitution(abilities_[2U])
    , intelligence(abilities_[3U])
    , wisdom(abilities_[4U])
    , charisma(abilities_[5U])
    , hitpoints(hitpoints_)
{
    for(std::size_t i = 0U; i < 6U; ++i) {
        abilities_[i] = roll_ability();
    }
    hitpoints_ = static_cast<hitpoint_t>(10 + modifier(abilities_[2U]));
}

Character::ability_score_t Character::ability_strength() const {
    return abilities_[0U];
}

Character::ability_score_t Character::ability_dexterity() const {
    return abilities_[1U];
}

Character::ability_score_t Character::ability_constitution() const {
    return abilities_[2U];
}

Character::ability_score_t Character::ability_intelligence() const {
    return abilities_[3U];
}

Character::ability_score_t Character::ability_wisdom() const {
    return abilities_[4U];
}

Character::ability_score_t Character::ability_charisma() const {
    return abilities_[5U];
}

Character::hitpoint_t Character::hitpoints() const {
    return hitpoints_;
}

Character::ability_score_t Character::ability_modifier(ability_score_t score) const {
    return modifier(score);
}

}  // namespace dnd_character
