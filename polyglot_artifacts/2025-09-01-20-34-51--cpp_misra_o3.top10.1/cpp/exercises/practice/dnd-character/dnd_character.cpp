#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <random>

namespace dnd_character {

// ---------------------------------------------------------------------
// Internal helpers
// ---------------------------------------------------------------------
namespace {

// Obtain a single (thread-local) PRNG instance.
[[nodiscard]] std::mt19937& generator()
{
    static std::random_device rd{};
    static std::mt19937 gen{rd()};
    return gen;
}

// Roll one 6-sided die and return the result [1,6].
[[nodiscard]] std::int32_t roll_die()
{
    static std::uniform_int_distribution<std::int32_t> dist(1, 6);
    return dist(generator());
}

}  // unnamed namespace

// ---------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------
std::int32_t ability()
{
    std::array<std::int32_t, 4U> rolls{};
    for (std::int32_t& r : rolls)
    {
        r = roll_die();
    }

    std::sort(rolls.begin(), rolls.end());

    // Discard the smallest die (rolls[0]) and sum the rest.
    std::int32_t sum{0};
    for (std::size_t i{1U}; i < rolls.size(); ++i)
    {
        sum += rolls[i];
    }

    return sum;
}

std::int32_t modifier(std::int32_t score)
{
    const std::int32_t diff{score - 10};

    if (diff >= 0)
    {
        return diff / 2;
    }
    else
    {
        // Ensure mathematical floor for negative values.
        return (diff - 1) / 2;
    }
}

// ---------------------------------------------------------------------
// Character implementation
// ---------------------------------------------------------------------
Character::Character()
    : strength{ability()},
      dexterity{ability()},
      constitution{ability()},
      intelligence{ability()},
      wisdom{ability()},
      charisma{ability()}
{
    hitpoints = 10 + modifier(constitution);
}


}  // namespace dnd_character
