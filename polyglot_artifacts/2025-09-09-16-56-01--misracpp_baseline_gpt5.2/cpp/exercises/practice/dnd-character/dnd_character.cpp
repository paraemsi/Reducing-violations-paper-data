#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {
    // Thread-local RNG for safe, efficient random number generation.
    thread_local std::mt19937 rng{std::random_device{}()};
    inline int roll_d6() {
        static thread_local std::uniform_int_distribution<int> dist(1, 6);
        return dist(rng);
    }
}  // namespace

int ability() {
    std::array<int, 4> rolls{};
    for (auto& r : rolls) {
        r = roll_d6();
    }
    int total = rolls[0] + rolls[1] + rolls[2] + rolls[3];
    int min_roll = *std::min_element(rolls.begin(), rolls.end());
    return total - min_roll;
}

int modifier(int score) {
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

Character::Character()
    : strength(ability()),
      dexterity(ability()),
      constitution(ability()),
      intelligence(ability()),
      wisdom(ability()),
      charisma(ability()),
      hitpoints(10 + modifier(constitution)) {}

}  // namespace dnd_character
