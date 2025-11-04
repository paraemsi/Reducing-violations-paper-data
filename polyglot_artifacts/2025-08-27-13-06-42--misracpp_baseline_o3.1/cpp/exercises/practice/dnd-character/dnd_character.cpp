#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <random>

namespace {

// single RNG instance shared by all rolls
std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution<int> d6(1, 6);

}  // namespace

namespace dnd_character {

int ability() {
    std::array<int, 4> rolls{};
    for (int& r : rolls) {
        r = d6(rng);
    }
    std::sort(rolls.begin(), rolls.end());  // ascending
    // drop the lowest roll (index 0)
    return rolls[1] + rolls[2] + rolls[3];
}

int modifier(int score) {
    // floor((score - 10) / 2.0)
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

// Character implementation
Character::Character()
    : strength{ability()},
      dexterity{ability()},
      constitution{ability()},
      intelligence{ability()},
      wisdom{ability()},
      charisma{ability()},
      hitpoints{10 + modifier(constitution)} {}


}  // namespace dnd_character
