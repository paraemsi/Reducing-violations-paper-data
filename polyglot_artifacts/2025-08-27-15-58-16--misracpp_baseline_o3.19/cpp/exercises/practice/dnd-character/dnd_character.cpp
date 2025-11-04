#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {
    // Shared PRNG resources for the entire translation unit.
    std::random_device rd;
    std::mt19937 engine{rd()};
    std::uniform_int_distribution<int> d6{1, 6};
} // namespace

int ability() {
    std::array<int, 4> rolls{};
    std::generate(rolls.begin(), rolls.end(), [] { return d6(engine); });
    std::sort(rolls.begin(), rolls.end());
    return std::accumulate(rolls.begin() + 1, rolls.end(), 0);
}

int modifier(int score) {
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

// Character ------------------------------------------------------------------

Character::Character()
    : strength{ability()},
      dexterity{ability()},
      constitution{ability()},
      intelligence{ability()},
      wisdom{ability()},
      charisma{ability()},
      hitpoints{10 + modifier(constitution)} {}

}  // namespace dnd_character
