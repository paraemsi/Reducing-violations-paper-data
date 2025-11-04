#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <random>

namespace dnd_character {
namespace {

// Shared random-number generator.
inline std::mt19937& rng() {
    static std::mt19937 gen{std::random_device{}()};
    return gen;
}

}  // namespace

int ability() {
    std::uniform_int_distribution<int> dist(1, 6);
    std::array<int, 4> rolls{};
    for (int& r : rolls) {
        r = dist(rng());
    }
    std::sort(rolls.begin(), rolls.end());                    // ascending
    return std::accumulate(rolls.begin() + 1, rolls.end(), 0); // sum highest three
}

int modifier(int score) {
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

Character::Character() {
    strength     = ability(); // STR
    dexterity    = ability(); // DEX
    constitution = ability(); // CON
    intelligence = ability(); // INT
    wisdom       = ability(); // WIS
    charisma     = ability(); // CHA

    hitpoints = 10 + modifier(constitution);
}

}  // namespace dnd_character
