#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <random>

namespace {
// Thread-local PRNG seeded once per thread.
thread_local std::mt19937 rng{std::random_device{}()};

int roll_die(int sides = 6) {
    std::uniform_int_distribution<int> dist(1, sides);
    return dist(rng);
}
}  // namespace

namespace dnd_character {

int ability() {
    std::array<int, 4> rolls{roll_die(), roll_die(), roll_die(), roll_die()};
    int total = std::accumulate(rolls.begin(), rolls.end(), 0);
    int lowest = *std::min_element(rolls.begin(), rolls.end());
    return total - lowest;
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
      hitpoints(0) {
    hitpoints = 10 + modifier(constitution);
}

}  // namespace dnd_character
