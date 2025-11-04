#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <random>
#include <cstddef>

namespace dnd_character {

// ---------------------------------------------------------------------------
// Private helper – single instance of PRNG for the entire translation unit.
// ---------------------------------------------------------------------------
namespace
{
    std::mt19937& generator()
    {
        static std::mt19937 gen(std::random_device{}());
        return gen;
    }
} // unnamed namespace

// ---------------------------------------------------------------------------
// Free functions
// ---------------------------------------------------------------------------
score_t ability()
{
    // Uniform distribution for a single six-sided die roll.
    static std::uniform_int_distribution<score_t> dist(
        static_cast<score_t>(1),
        static_cast<score_t>(6));

    std::array<score_t, 4U> rolls {};

    for (auto& r : rolls)
    {
        r = dist(generator());
    }

    std::sort(rolls.begin(), rolls.end());

    // Sum of the largest three dice (skip the first – lowest – element).
    return std::accumulate(
        rolls.begin() + static_cast<std::ptrdiff_t>(1),
        rolls.end(),
        static_cast<score_t>(0));
}

score_t modifier(score_t score)
{
    // Calculate (score - 10) / 2 and round toward minus infinity (D&D rule).
    const score_t diff {score - static_cast<score_t>(10)};
    if (diff >= static_cast<score_t>(0))
    {
        return (diff / static_cast<score_t>(2));
    }
    else
    {
        /* For negative odd numbers C++ truncates toward zero, so adjust by −1
         * before the division to obtain floor-like behaviour.
         * Example: diff = -7  → (-7 - 1) / 2 = -4.
         */
        return ((diff - static_cast<score_t>(1)) / static_cast<score_t>(2));
    }
}

// ---------------------------------------------------------------------------
// Character implementation
// ---------------------------------------------------------------------------
Character::Character()
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability())
    , hitpoints(static_cast<score_t>(10) + modifier(constitution))
{
}

}  // namespace dnd_character
