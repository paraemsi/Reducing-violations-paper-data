#include "dnd_character.h"

#include <cmath>
#include <random>

namespace dnd_character {

namespace {
    // Thread-local RNG to avoid reseeding on each call and to be safe in multithreaded contexts
    thread_local std::mt19937 rng{std::random_device{}()};
    thread_local std::uniform_int_distribution<int> d6{1, 6};
}

int ability() {
    int sum = 0;
    int min_roll = 7;
    for (int i = 0; i < 4; ++i) {
        int r = d6(rng);
        sum += r;
        if (r < min_roll) {
            min_roll = r;
        }
    }
    return sum - min_roll;
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
