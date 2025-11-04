#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <vector>
#include <numeric>
#include <cmath>

namespace dnd_character {

namespace {
    // Use a static random engine for all dice rolls
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int32_t> dist(1, 6);

    std::int32_t roll_die() {
        return dist(gen);
    }
}

dnd_character::ability_t Character::ability() {
    std::vector<std::int32_t> rolls;
    for(std::int32_t i = 0; i < 4; ++i) {
        rolls.push_back(roll_die());
    }
    std::sort(rolls.begin(), rolls.end());
    // Drop the lowest roll (first element)
    return static_cast<dnd_character::ability_t>((rolls[1] + rolls[2]) + rolls[3]);
}

dnd_character::ability_t ability() {
    return Character::ability();
}

dnd_character::ability_t Character::modifier(dnd_character::ability_t score) {
    // Constitution modifier: floor((score - 10) / 2)
    return static_cast<dnd_character::ability_t>(std::floor(static_cast<double>(score - 10) / 2.0));
}

Character::Character() : abilities_{}, hitpoints_(0) {
    for(std::size_t i = 0U; i < abilities_.size(); ++i) {
        abilities_[i] = ability();
    }
    hitpoints_ = static_cast<dnd_character::ability_t>(10 + modifier(abilities_[2]));
}

dnd_character::ability_t Character::strength() const {
    return abilities_[0];
}

dnd_character::ability_t Character::dexterity() const {
    return abilities_[1];
}

dnd_character::ability_t Character::constitution() const {
    return abilities_[2];
}

dnd_character::ability_t Character::intelligence() const {
    return abilities_[3];
}

dnd_character::ability_t Character::wisdom() const {
    return abilities_[4];
}

dnd_character::ability_t Character::charisma() const {
    return abilities_[5];
}

dnd_character::ability_t Character::hitpoints() const {
    return hitpoints_;
}

}  // namespace dnd_character
