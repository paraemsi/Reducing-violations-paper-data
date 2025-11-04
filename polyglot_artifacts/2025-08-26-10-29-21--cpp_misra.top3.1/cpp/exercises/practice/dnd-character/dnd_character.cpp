#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <string>
#include <array>
#include <cstdint>

namespace dnd_character {

namespace {
    // Helper function to get a random number generator
    std::mt19937& rng() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }
}

Character::Character()
    : abilities_{}
    , hitpoints_{0}
{
    for(std::size_t i = 0U; i < static_cast<std::size_t>(6); ++i) {
        abilities_[i] = roll_ability();
    }
    hitpoints_ = static_cast<ability_score_t>(10 + modifier(abilities_[2]));
}

Character::ability_score_t Character::roll_ability() {
    std::uniform_int_distribution<std::int32_t> dist(1, 6);
    std::array<std::int32_t, 4> rolls{};
    for(std::size_t i = 0U; i < static_cast<std::size_t>(4); ++i) {
        rolls[i] = dist(rng());
    }
    std::sort(rolls.begin(), rolls.end());
    // sum the largest three dice
    return static_cast<ability_score_t>((rolls[1] + rolls[2]) + rolls[3]);
}

Character::ability_score_t Character::ability(const char* ability_name) const {
    if(std::string(ability_name) == "strength") {
        return strength();
    } else if(std::string(ability_name) == "dexterity") {
        return dexterity();
    } else if(std::string(ability_name) == "constitution") {
        return constitution();
    } else if(std::string(ability_name) == "intelligence") {
        return intelligence();
    } else if(std::string(ability_name) == "wisdom") {
        return wisdom();
    } else if(std::string(ability_name) == "charisma") {
        return charisma();
    }
    return static_cast<ability_score_t>(0);
}

Character::ability_score_t Character::strength() const {
    return abilities_[0];
}

Character::ability_score_t Character::dexterity() const {
    return abilities_[1];
}

Character::ability_score_t Character::constitution() const {
    return abilities_[2];
}

Character::ability_score_t Character::intelligence() const {
    return abilities_[3];
}

Character::ability_score_t Character::wisdom() const {
    return abilities_[4];
}

Character::ability_score_t Character::charisma() const {
    return abilities_[5];
}

Character::ability_score_t Character::modifier(ability_score_t score) {
    // ((score - 10) / 2) rounded down
    return static_cast<ability_score_t>(((score - 10) / 2));
}

Character::ability_score_t Character::hitpoints() const {
    return hitpoints_;
}

ability_score_t ability() {
    std::uniform_int_distribution<std::int32_t> dist(1, 6);
    std::array<std::int32_t, 4> rolls{};
    for(std::size_t i = 0U; i < static_cast<std::size_t>(4); ++i) {
        rolls[i] = dist(rng());
    }
    std::sort(rolls.begin(), rolls.end());
    return static_cast<ability_score_t>((rolls[1] + rolls[2]) + rolls[3]);
}

}  // namespace dnd_character
