#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {
// Thread-local PRNG: seeded once per thread
thread_local std::mt19937 rng{std::random_device{}()};
std::uniform_int_distribution<int> d6{1, 6};

// Roll a single six-sided die
inline int roll_die() {
    return d6(rng);
}
}  // namespace

int ability() {
    std::array<int, 4> rolls{};
    std::generate(rolls.begin(), rolls.end(), roll_die);

    std::sort(rolls.begin(), rolls.end());
    // Discard the lowest roll (index 0) and sum the rest
    return std::accumulate(rolls.begin() + 1, rolls.end(), 0);
}

int modifier(int score) {
    // floor((score − 10) / 2)
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
