#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <random>
#include <cmath>

namespace dnd_character {

namespace {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 6);
}

int ability() {
    std::array<int, 4> rolls;
    int total = 0;
    int min_roll = 6;

    for (auto &roll : rolls) {
        roll = dist(gen);
        total += roll;
        if (roll < min_roll) {
            min_roll = roll;
        }
    }
    return total - min_roll;
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
