#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <random>

namespace {
// single die roll helper (1‒6)
int roll_die(std::mt19937& gen) {
    static std::uniform_int_distribution<int> dist(1, 6);
    return dist(gen);
}
}  // namespace

namespace dnd_character {

int ability() {
    static thread_local std::mt19937 gen(std::random_device{}());

    std::array<int, 4> rolls{};
    std::generate(rolls.begin(), rolls.end(), [&] { return roll_die(gen); });

    auto smallest = std::min_element(rolls.begin(), rolls.end());
    int sum = std::accumulate(rolls.begin(), rolls.end(), 0);
    return sum - *smallest;           // drop the lowest roll
}

int modifier(int score) {
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

// -------- Character implementation --------
Character::Character()
    : strength{ability()},
      dexterity{ability()},
      constitution{ability()},
      intelligence{ability()},
      wisdom{ability()},
      charisma{ability()},
      hitpoints{10 + modifier(constitution)} {}


}  // namespace dnd_character
