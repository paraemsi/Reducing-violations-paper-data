#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {
    // Thread-local PRNG seeded once per thread.
    thread_local std::mt19937 rng{std::random_device{}()};
}

int ability() {
    std::uniform_int_distribution<int> dist(1, 6);
    std::array<int, 4> rolls{};
    for (auto& r : rolls) {
        r = dist(rng);
    }
    int sum = std::accumulate(rolls.begin(), rolls.end(), 0);
    int minv = *std::min_element(rolls.begin(), rolls.end());
    return sum - minv;
}

int modifier(int score) {
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

Character::Character() noexcept
    : strength(ability()),
      dexterity(ability()),
      constitution(ability()),
      intelligence(ability()),
      wisdom(ability()),
      charisma(ability()),
      hitpoints(10 + modifier(constitution)) {}

}  // namespace dnd_character
