#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <random>
#include <vector>

namespace dnd_character {
namespace {
// Returns a single roll of a 6-sided die.
int roll_die() {
    static std::random_device rd;
    static std::mt19937 gen{rd()};
    static std::uniform_int_distribution<int> dist{1, 6};
    return dist(gen);
}
}  // namespace

int ability() {
    std::array<int, 4> rolls{};
    for (int& r : rolls) {
        r = roll_die();
    }
    std::sort(rolls.begin(), rolls.end());           // ascending
    return rolls[1] + rolls[2] + rolls[3];            // drop the lowest
}

int modifier(int score) {
    // Floor division for negatives: use std::floor on double.
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

// ---------------- Character implementation ----------------
Character::Character()
    : strength{ability()},
      dexterity{ability()},
      constitution{ability()},
      intelligence{ability()},
      wisdom{ability()},
      charisma{ability()},
      hitpoints{10 + modifier(constitution)} {}


}  // namespace dnd_character
