#include "dnd_character.h"

#include <cmath>
#include <random>

namespace {

 // Thread-local RNG to ensure good randomness in multi-threaded contexts.
std::mt19937& rng() {
    static thread_local std::mt19937 gen{std::random_device{}()};
    return gen;
}

int roll_d6() {
    static thread_local std::uniform_int_distribution<int> dist(1, 6);
    return dist(rng());
}

}  // namespace

namespace dnd_character {

int ability() {
    // Roll 4d6, drop the lowest.
    int sum = 0;
    int lowest = 7;  // higher than any d6 roll
    for (int i = 0; i < 4; ++i) {
        const int r = roll_d6();
        sum += r;
        if (r < lowest) lowest = r;
    }
    return sum - lowest;
}

int modifier(int score) {
    return static_cast<int>(std::floor((score - 10.0) / 2.0));
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
