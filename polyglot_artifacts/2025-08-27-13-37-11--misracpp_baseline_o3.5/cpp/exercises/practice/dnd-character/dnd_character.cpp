#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <random>

namespace dnd_character {

// ---------------------------------------------------------------------------
// Internal helpers
// ---------------------------------------------------------------------------
namespace {
    int roll_die(std::mt19937 &gen) {
        static std::uniform_int_distribution<int> dist(1, 6);
        return dist(gen);
    }

    std::mt19937 &rng() {
        static std::random_device rd;
        static std::mt19937       gen(rd());
        return gen;
    }
}  // namespace

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------
int ability() {
    auto &gen = rng();

    std::array<int, 4> rolls{};
    std::generate(rolls.begin(), rolls.end(), [&]() { return roll_die(gen); });

    // Drop the lowest roll and sum the rest.
    const int total = std::accumulate(rolls.begin(), rolls.end(), 0);
    const int lowest = *std::min_element(rolls.begin(), rolls.end());
    return total - lowest;
}

int modifier(int score) {
    // Using floor division to ensure negative values round toward −∞.
    const int diff = score - 10;
    return diff >= 0 ? diff / 2 : (diff - 1) / 2;
}

// ---------------------------------------------------------------------------
// Character implementation
// ---------------------------------------------------------------------------
Character::Character()
    : strength(ability()),
      dexterity(ability()),
      constitution(ability()),
      intelligence(ability()),
      wisdom(ability()),
      charisma(ability()),
      hitpoints(10 + modifier(constitution)) {}

}  // namespace dnd_character
