#include "dnd_character.h"

#include <cmath>
#include <random>

namespace dnd_character {

namespace {
    // Thread-local RNG to avoid contention in multi-threaded environments
    thread_local std::mt19937 rng{std::random_device{}()};
}

int ability() {
    std::uniform_int_distribution<int> dist(1, 6);
    int sum = 0;
    int min_roll = 6;

    for (int i = 0; i < 4; ++i) {
        int r = dist(rng);
        sum += r;
        if (r < min_roll) {
            min_roll = r;
        }
    }
    return sum - min_roll; // sum of the highest three rolls
}

int modifier(int score) {
    // floor((score - 10) / 2)
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
