#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {
    std::mt19937& prng() {
        static std::mt19937 engine(std::random_device{}());
        return engine;
    }

    int roll_die(int sides = 6) {
        std::uniform_int_distribution<int> dist(1, sides);
        return dist(prng());
    }
}

int ability() {
    std::array<int, 4> rolls{roll_die(), roll_die(), roll_die(), roll_die()};
    int lowest = *std::min_element(rolls.begin(), rolls.end());
    int total = std::accumulate(rolls.begin(), rolls.end(), 0) - lowest;
    return total;
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
