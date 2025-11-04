#include "dnd_character.h"

#include <array>
#include <algorithm>
#include <random>
#include <cmath>

namespace {
    thread_local std::mt19937 rng{std::random_device{}()};
    thread_local std::uniform_int_distribution<int> d6{1, 6};

    int roll_d6() {
        return d6(rng);
    }
}

namespace dnd_character {

int ability() {
    std::array<int, 4> rolls{ roll_d6(), roll_d6(), roll_d6(), roll_d6() };
    int sum = rolls[0] + rolls[1] + rolls[2] + rolls[3];
    int lowest = *std::min_element(rolls.begin(), rolls.end());
    return sum - lowest;
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
