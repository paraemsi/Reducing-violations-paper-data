#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <vector>
#include <numeric>
#include <cstddef>

namespace dnd_character {

namespace {
    // Helper function to roll a single ability score
    dnd_character::ability_t roll_ability() {
        static thread_local std::random_device rd;
        static thread_local std::mt19937 gen(rd());
        static thread_local std::uniform_int_distribution<dnd_character::ability_t> dist(1, 6);

        std::array<dnd_character::ability_t, 4U> rolls{};
        for(std::size_t i = 0U; i < 4U; ++i) {
            rolls[i] = dist(gen);
        }
        // Sort and sum the largest three
        std::sort(rolls.begin(), rolls.end());
        return (rolls[1U] + rolls[2U] + rolls[3U]);
    }
}

Character::Character()
    : abilities_{}
    , hitpoints_{0}
{
    for(std::size_t i = 0U; i < 6U; ++i) {
        abilities_[i] = roll_ability();
    }
    hitpoints_ = (10 + ability_modifier(abilities_[2U]));
}

ability_t Character::ability(std::size_t index) const {
    return abilities_[index];
}

ability_t Character::strength() const {
    return abilities_[0U];
}

ability_t Character::dexterity() const {
    return abilities_[1U];
}

ability_t Character::constitution() const {
    return abilities_[2U];
}

ability_t Character::intelligence() const {
    return abilities_[3U];
}

ability_t Character::wisdom() const {
    return abilities_[4U];
}

ability_t Character::charisma() const {
    return abilities_[5U];
}

ability_t Character::hitpoints() const {
    return hitpoints_;
}

ability_t Character::ability_modifier(ability_t score) const {
    return modifier(score);
}

ability_t modifier(ability_t score) {
    // Constitution modifier: (score - 10) / 2, rounded down
    return static_cast<ability_t>(((score - 10) / 2));
}

}  // namespace dnd_character
