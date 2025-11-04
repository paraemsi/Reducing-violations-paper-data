#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <random>

namespace dnd_character {

namespace {
    // Thread-local RNG to be safe in multi-threaded contexts and avoid reseeding.
    thread_local std::mt19937 rng{std::random_device{}()};
    inline int roll_d6() {
        static thread_local std::uniform_int_distribution<int> dist(1, 6);
        return dist(rng);
    }
}  // namespace

int ability() {
    // Roll 4d6, drop the lowest, sum the rest.
    std::array<int, 4> rolls{roll_d6(), roll_d6(), roll_d6(), roll_d6()};
    int sum = rolls[0] + rolls[1] + rolls[2] + rolls[3];
    int lowest = *std::min_element(rolls.begin(), rolls.end());
    return sum - lowest;
}

int modifier(int score) {
    // Floor division for negatives: use std::floor on a double.
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

Character::Character()
    : strength{ability()},
      dexterity{ability()},
      constitution{ability()},
      intelligence{ability()},
      wisdom{ability()},
      charisma{ability()},
      hitpoints{10 + modifier(constitution)} {}


}  // namespace dnd_character
