#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <random>

namespace dnd_character {

namespace {
std::mt19937& rng() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

int roll_d6() {
    static thread_local std::uniform_int_distribution<int> dist(1, 6);
    return dist(rng());
}
}  // namespace

int ability() {
    std::array<int, 4> rolls{};
    for (auto& r : rolls) {
        r = roll_d6();
    }
    std::sort(rolls.begin(), rolls.end());
    // Sum the highest three dice.
    return rolls[1] + rolls[2] + rolls[3];
}

int modifier(int score) {
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

Character::Character() noexcept
    : strength{ability()},
      dexterity{ability()},
      constitution{ability()},
      intelligence{ability()},
      wisdom{ability()},
      charisma{ability()},
      hitpoints{10 + modifier(constitution)} {}

}  // namespace dnd_character
