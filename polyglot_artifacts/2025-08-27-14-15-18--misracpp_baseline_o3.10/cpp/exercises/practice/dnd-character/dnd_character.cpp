#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <random>
#include <cmath>

namespace {
// Roll a single six-sided die.
int roll_die() {
    static std::random_device               rd;
    static std::mt19937                     gen{rd()};
    static std::uniform_int_distribution<>  dist{1, 6};
    return dist(gen);
}
}  // namespace

namespace dnd_character {

int ability() {
    std::array<int, 4> rolls;
    std::generate(rolls.begin(), rolls.end(), roll_die);
    std::sort(rolls.begin(), rolls.end());                // ascending
    return std::accumulate(rolls.begin() + 1, rolls.end(), 0);
}

int modifier(int score) {
    // Use mathematical floor to ensure negative modifiers round down.
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
