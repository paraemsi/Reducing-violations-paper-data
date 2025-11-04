#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <random>

namespace {
// Shared random number generator, seeded once.
std::mt19937& rng() {
    static std::mt19937 engine{std::random_device{}()};
    return engine;
}
}  // namespace

namespace dnd_character {

int ability() {
    std::uniform_int_distribution<int> dist(1, 6);
    std::array<int, 4> rolls{};
    std::generate(rolls.begin(), rolls.end(), [&] { return dist(rng()); });

    int total = std::accumulate(rolls.begin(), rolls.end(), 0);
    int lowest = *std::min_element(rolls.begin(), rolls.end());
    return total - lowest;
}

int modifier(int score) {
    // Use floating-point division then floor to handle negatives correctly.
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
