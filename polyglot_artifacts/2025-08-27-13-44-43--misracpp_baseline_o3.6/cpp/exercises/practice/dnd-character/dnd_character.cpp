#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {
// Thread-local random number generator to ensure independent rolls
thread_local std::mt19937 rng{std::random_device{}()};

/**
 * Roll a single six-sided die.
 */
int roll_die() {
    static std::uniform_int_distribution<int> dist(1, 6);
    return dist(rng);
}
}  // namespace

int modifier(int score) {
    // Ensure we round down (floor) for negative numbers.
    const int diff = score - 10;
    return diff >= 0 ? diff / 2 : (diff - 1) / 2;
}

int ability() {
    std::array<int, 4> rolls{};
    std::generate(rolls.begin(), rolls.end(), roll_die);
    std::sort(rolls.begin(), rolls.end());                 // ascending
    return std::accumulate(rolls.begin() + 1, rolls.end(), 0); // drop lowest
}

// ---- Character -------------------------------------------------------------

Character::Character()
    : strength{ability()},
      dexterity{ability()},
      constitution{ability()},
      intelligence{ability()},
      wisdom{ability()},
      charisma{ability()},
      hitpoints{10 + modifier(constitution)} {}



}  // namespace dnd_character
