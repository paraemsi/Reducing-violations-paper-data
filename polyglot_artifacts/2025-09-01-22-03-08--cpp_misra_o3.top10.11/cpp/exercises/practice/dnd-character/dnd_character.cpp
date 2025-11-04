#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <random>

namespace dnd_character {

// ----------------------------------------------------------------------------
// internal helpers
// ----------------------------------------------------------------------------
namespace {

/* roll a single six-sided die                                                      */
score_t roll_die()
{
    static std::random_device rd{};
    /* mt19937 has 32-bit result type – matches score_t exactly                     */
    static std::mt19937 engine{rd()};
    static std::uniform_int_distribution<score_t> dist{static_cast<score_t>(1),
                                                       static_cast<score_t>(6)};

    return dist(engine);
}

/* roll four d6, drop the lowest                                                    */
score_t roll_four_drop_lowest()
{
    std::array<score_t, static_cast<std::size_t>(4U)> dice{};

    for (auto &d : dice) {
        d = roll_die();
    }

    const score_t total =
        std::accumulate(dice.begin(), dice.end(), static_cast<score_t>(0));

    const score_t lowest = *std::min_element(dice.begin(), dice.end());

    return total - lowest;
}

} // unnamed namespace

// ----------------------------------------------------------------------------
// public API
// ----------------------------------------------------------------------------
score_t modifier(score_t score)
{
    const score_t diff = score - static_cast<score_t>(10);

    if (diff >= static_cast<score_t>(0)) {
        return diff / static_cast<score_t>(2);
    } else {
        /* adjust by −1 before integer division to obtain floor() behaviour        */
        return (diff - static_cast<score_t>(1)) / static_cast<score_t>(2);
    }
}

score_t ability()
{
    return roll_four_drop_lowest();
}

// ----------------------------------------------------------------------------
// Character implementation
// ----------------------------------------------------------------------------
Character::Character()
    : strength{ability()},
      dexterity{ability()},
      constitution{ability()},
      intelligence{ability()},
      wisdom{ability()},
      charisma{ability()},
      hitpoints{static_cast<score_t>(10) + modifier(constitution)}
{
}









}  // namespace dnd_character
