#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <random>

namespace dnd_character {

int modifier(int score) {
    // floor((score - 10) / 2)
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

int ability() {
    static thread_local std::mt19937 rng{std::random_device{}()};
    static thread_local std::uniform_int_distribution<int> dist(1, 6);

    std::array<int, 4> rolls{};
    for (auto& r : rolls) {
        r = dist(rng);
    }

    // Sum the top three rolls
    std::sort(rolls.begin(), rolls.end(), std::greater<int>());
    return rolls[0] + rolls[1] + rolls[2];
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
