#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {
std::mt19937& rng() {
    static std::mt19937 engine(std::random_device{}());
    return engine;
}

int roll_d6() {
    static std::uniform_int_distribution<int> dist(1, 6);
    return dist(rng());
}
}  // namespace

int ability() {
    std::array<int, 4> rolls{roll_d6(), roll_d6(), roll_d6(), roll_d6()};
    std::sort(rolls.begin(), rolls.end(), std::greater<int>());
    return rolls[0] + rolls[1] + rolls[2];
}

int modifier(int score) {
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
