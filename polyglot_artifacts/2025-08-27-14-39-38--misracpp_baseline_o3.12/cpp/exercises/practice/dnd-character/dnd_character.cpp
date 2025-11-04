#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <random>

namespace dnd_character {

namespace {
// Shared random engine & distribution for the translation unit.
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(1, 6);
}  // namespace

int ability() {
    std::array<int, 4> rolls{};
    for (int &v : rolls) {
        v = dist(gen);
    }
    std::sort(rolls.begin(), rolls.end());               // ascending
    return rolls[1] + rolls[2] + rolls[3];               // drop the lowest
}

int modifier(int score) {
    // Floor division for negatives: use floating-point and std::floor.
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

// ---------- Character -------------------------------------------------------

Character::Character()
    : strength{ability()},
      dexterity{ability()},
      constitution{ability()},
      intelligence{ability()},
      wisdom{ability()},
      charisma{ability()},
      hitpoints{10 + modifier(constitution)} {}


}  // namespace dnd_character
