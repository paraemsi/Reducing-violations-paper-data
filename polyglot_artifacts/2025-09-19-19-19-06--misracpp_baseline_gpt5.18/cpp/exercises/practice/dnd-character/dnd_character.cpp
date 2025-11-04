#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {
int roll_die() {
    thread_local std::mt19937 engine{std::random_device{}()};
    static std::uniform_int_distribution<int> dist(1, 6);
    return dist(engine);
}
}  // namespace

int ability() {
    std::array<int, 4> rolls{roll_die(), roll_die(), roll_die(), roll_die()};
    int sum = std::accumulate(rolls.begin(), rolls.end(), 0);
    int min_roll = *std::min_element(rolls.begin(), rolls.end());
    return sum - min_roll;
}

int modifier(int score) {
    const int delta = score - 10;
    int mod = delta / 2;
    if (delta < 0 && (delta % 2 != 0)) {
        --mod;
    }
    return mod;
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
