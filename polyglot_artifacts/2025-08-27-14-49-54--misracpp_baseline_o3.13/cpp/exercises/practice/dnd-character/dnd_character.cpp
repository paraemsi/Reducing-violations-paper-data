#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {
// Shared PRNG and distribution for 6-sided dice.
std::random_device rd;
std::mt19937 gen{rd()};
std::uniform_int_distribution<int> d6{1, 6};
}  // namespace

int ability() {
    std::array<int, 4> rolls{};
    for (int& v : rolls) {
        v = d6(gen);
    }
    std::sort(rolls.begin(), rolls.end());
    // Discard the lowest roll and sum the remaining three.
    return std::accumulate(rolls.begin() + 1, rolls.end(), 0);
}

int modifier(int score) {
    // Floor division that works for negative numbers.
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
