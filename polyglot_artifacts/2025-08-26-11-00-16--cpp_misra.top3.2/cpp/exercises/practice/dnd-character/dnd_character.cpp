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
        static thread_local std::uniform_int_distribution<std::int32_t> dist(1, 6);

        std::array<std::int32_t, 4U> rolls{};
        for(std::size_t i = 0U; i < 4U; ++i) {
            rolls[i] = dist(gen);
        }
        std::sort(rolls.begin(), rolls.end());
        // Drop the lowest roll (rolls[0])
        return (rolls[1] + rolls[2] + rolls[3]);
    }
}

Character::Character()
    : abilities_{}
    , hitpoints_{0}
{
    for(std::size_t i = 0U; i < 6U; ++i) {
        abilities_[i] = roll_ability();
    }
    hitpoints_ = (10 + modifier(abilities_[2]));
}

dnd_character::ability_t Character::ability(std::size_t index) const {
    return abilities_.at(index);
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

// Remove the member function modifier; not needed for tests

dnd_character::ability_t modifier(dnd_character::ability_t score) {
    // ((score - 10) / 2), rounded down
    return static_cast<dnd_character::ability_t>(((score - 10) / 2));
}

}  // namespace dnd_character
