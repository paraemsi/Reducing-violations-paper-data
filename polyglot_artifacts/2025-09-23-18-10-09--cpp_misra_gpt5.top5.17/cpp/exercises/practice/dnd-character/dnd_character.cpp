#include "dnd_character.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <random>

namespace dnd_character {

// Internal RNG accessor
static std::mt19937& rng_engine() {
    static thread_local std::mt19937 engine{std::random_device{}()};
    return engine;
}

std::int32_t ability() {
    std::uniform_int_distribution<std::int32_t> dist(static_cast<std::int32_t>(1), static_cast<std::int32_t>(6));

    std::int32_t sum = static_cast<std::int32_t>(0);
    std::int32_t min_roll = static_cast<std::int32_t>(6);

    for (std::size_t i = static_cast<std::size_t>(0); i < static_cast<std::size_t>(4); ++i) {
        const std::int32_t roll = dist(rng_engine());
        sum = sum + roll;
        if (roll < min_roll) {
            min_roll = roll;
        } else {
            // no-op
        }
    }

    return (sum - min_roll);
}

std::int32_t modifier(std::int32_t score) {
    return ((score / 2) - 5);
}

Character::Character()
    : strength(ability()),
      dexterity(ability()),
      constitution(ability()),
      intelligence(ability()),
      wisdom(ability()),
      charisma(ability()),
      hitpoints(static_cast<std::int32_t>(10) + modifier(constitution)) {}

}  // namespace dnd_character
