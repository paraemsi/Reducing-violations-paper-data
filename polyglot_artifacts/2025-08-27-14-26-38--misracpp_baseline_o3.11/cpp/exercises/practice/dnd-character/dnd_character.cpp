#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <random>

namespace dnd_character {

namespace {
/* Thread-local random engine so that every thread gets its own generator
   while keeping the generator static for performance. */
thread_local std::mt19937& rng() {
    static thread_local std::mt19937 eng{std::random_device{}()};
    return eng;
}
}  // namespace

int ability() {
    std::uniform_int_distribution<int> dist(1, 6);

    std::array<int, 4> rolls{};
    for (int& r : rolls) {
        r = dist(rng());
    }

    std::sort(rolls.begin(), rolls.end());          // ascending
    return rolls[1] + rolls[2] + rolls[3];          // highest three
}

int modifier(int score) {
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

/* ---------- Character --------------------------------------------------- */

Character::Character()
    : strength{ability()},
      dexterity{ability()},
      constitution{ability()},
      intelligence{ability()},
      wisdom{ability()},
      charisma{ability()},
      hitpoints{10 + modifier(constitution)} {}

}  // namespace dnd_character
