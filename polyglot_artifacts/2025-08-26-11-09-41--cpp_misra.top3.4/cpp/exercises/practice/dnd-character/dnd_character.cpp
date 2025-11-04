#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <string>
#include <array>
#include <cstdint>

namespace dnd_character {

namespace {
    // Helper function to roll 4d6 and sum the highest 3
    ability_score_t roll_ability(std::mt19937& rng) {
        std::uniform_int_distribution<int32_t> dist(1, 6);
        std::array<int32_t, 4> rolls{};
        for(std::size_t i = 0U; i < 4U; ++i) {
            rolls[i] = dist(rng);
        }
        std::sort(rolls.begin(), rolls.end());
        // sum the highest 3
        return (rolls[1] + rolls[2] + rolls[3]);
    }
}

ability_score_t ability() {
    static thread_local std::random_device rd;
    static thread_local std::mt19937 rng(rd());
    return roll_ability(rng);
}

ability_score_t modifier(ability_score_t score) {
    return static_cast<ability_score_t>(((score - 10) / 2));
}

Character::Character()
    : abilities_{ability(), ability(), ability(), ability(), ability(), ability()},
      hitpoints_{static_cast<hitpoint_t>(10 + modifier(abilities_[2]))},
      strength(abilities_[0]),
      dexterity(abilities_[1]),
      constitution(abilities_[2]),
      intelligence(abilities_[3]),
      wisdom(abilities_[4]),
      charisma(abilities_[5]),
      hitpoints(hitpoints_)
{
}

Character::ability_score_t Character::ability(const char* ability_name) const {
    // Order: strength, dexterity, constitution, intelligence, wisdom, charisma
    if(std::string(ability_name) == "strength") {
        return abilities_[0];
    } else if(std::string(ability_name) == "dexterity") {
        return abilities_[1];
    } else if(std::string(ability_name) == "constitution") {
        return abilities_[2];
    } else if(std::string(ability_name) == "intelligence") {
        return abilities_[3];
    } else if(std::string(ability_name) == "wisdom") {
        return abilities_[4];
    } else if(std::string(ability_name) == "charisma") {
        return abilities_[5];
    }
    // Invalid ability name
    return 0;
}

Character::hitpoint_t Character::hitpoints() const {
    return hitpoints_;
}

Character::ability_score_t Character::modifier(Character::ability_score_t score) {
    return static_cast<ability_score_t>(((score - 10) / 2));
}

}  // namespace dnd_character
