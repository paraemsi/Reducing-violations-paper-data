#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {
// Roll a single six-sided die.
int roll_die() {
    static std::random_device rd;
    static std::mt19937 engine{rd()};
    static std::uniform_int_distribution<int> dist(1, 6);
    return dist(engine);
}
}  // namespace

// Generate a single ability score by rolling four dice and keeping the highest three.
int ability() {
    std::array<int, 4> rolls{};
    std::generate(rolls.begin(), rolls.end(), roll_die);

    const int lowest = *std::min_element(rolls.begin(), rolls.end());
    const int total = std::accumulate(rolls.begin(), rolls.end(), 0) - lowest;
    return total;
}

// Calculate the ability modifier for a given score.
int modifier(int score) {
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

// -------------------- Character implementation --------------------

Character::Character()
    : strength{ability()},
      dexterity{ability()},
      constitution{ability()},
      intelligence{ability()},
      wisdom{ability()},
      charisma{ability()},
      hitpoints{10 + modifier(constitution)} {}


}  // namespace dnd_character
