#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <random>

namespace dnd_character {

namespace {

std::mt19937& get_generator() {
    static std::random_device random_device;
    static std::mt19937 generator(random_device());
    return generator;
}

std::int32_t roll_die() {
    std::uniform_int_distribution<std::int32_t> distribution(1, 6);
    return distribution(get_generator());
}

} // namespace

std::int32_t ability() {
    std::array<std::int32_t, 4> rolls{};
    for (std::int32_t& roll : rolls) {
        roll = roll_die();
    }
    std::sort(rolls.begin(), rolls.end());
    return (rolls[1] + rolls[2]) + rolls[3];
}

Character::Character()
    : strength{ability()},
      dexterity{ability()},
      constitution{ability()},
      intelligence{ability()},
      wisdom{ability()},
      charisma{ability()},
      hitpoints{(10 + modifier(constitution))} {}

}  // namespace dnd_character
