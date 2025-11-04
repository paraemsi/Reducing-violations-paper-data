#include "dnd_character.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

namespace dnd_character {

// Single, lazily-initialised random engine shared by all rolls.
static std::mt19937& rng() {
    static std::random_device rd;
    static std::mt19937 gen{rd()};
    return gen;
}

int ability() {
    std::uniform_int_distribution<int> dist(1, 6);
    std::vector<int> rolls;
    rolls.reserve(4);
    for (int i = 0; i < 4; ++i) {
        rolls.push_back(dist(rng()));
    }
    std::sort(rolls.begin(), rolls.end());
    // discard the smallest die (first element after sort)
    return std::accumulate(rolls.begin() + 1, rolls.end(), 0);
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
