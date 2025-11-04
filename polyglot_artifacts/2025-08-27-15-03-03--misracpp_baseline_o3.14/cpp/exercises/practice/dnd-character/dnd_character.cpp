#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {
int roll_die(std::mt19937& rng) {
    static std::uniform_int_distribution<int> dist(1, 6);
    return dist(rng);
}
}  // namespace

int modifier(int score) {
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

int ability() {
    return Character::ability();
}

int Character::ability() {
    static thread_local std::mt19937 rng(std::random_device{}());

    std::array<int, 4> rolls;
    std::generate(rolls.begin(), rolls.end(), [&]() { return roll_die(rng); });
    std::sort(rolls.begin(), rolls.end());
    return std::accumulate(rolls.begin() + 1, rolls.end(), 0);  // drop the smallest
}


Character::Character()
    : strength{Character::ability()},
      dexterity{Character::ability()},
      constitution{Character::ability()},
      intelligence{Character::ability()},
      wisdom{Character::ability()},
      charisma{Character::ability()},
      hitpoints{10 + modifier(constitution)} {}


}  // namespace dnd_character
