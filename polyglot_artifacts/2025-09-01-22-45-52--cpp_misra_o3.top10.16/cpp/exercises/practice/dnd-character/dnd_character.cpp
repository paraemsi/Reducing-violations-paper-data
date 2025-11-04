#include "dnd_character.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <cstddef>

namespace dnd_character {

//------------------------------------------------------------------------------
//  Helper: obtain a single pseudo-random engine instance.
//------------------------------------------------------------------------------
static std::mt19937& rng()
{
    static std::mt19937 engine{ std::random_device{}() };
    return engine;
}

//------------------------------------------------------------------------------
//  ability – generate a single ability score.
//------------------------------------------------------------------------------
std::int32_t ability()
{
    /*  Uniform distribution in the closed interval [1,6]                        */
    static std::uniform_int_distribution<std::uint32_t> dist(1U, 6U);

    std::array<std::int32_t, 4U> rolls{};

    for (std::int32_t& r : rolls)
    {
        /*  Cast is explicit to comply with MISRA rules regarding conversions.   */
        r = static_cast<std::int32_t>(dist(rng()));
    }

    std::sort(rolls.begin(), rolls.end());

    /*  Discard the smallest (index 0) and sum the remaining three.              */
    const std::int32_t sum =
        std::accumulate(rolls.begin() + static_cast<std::ptrdiff_t>(1),
                        rolls.end(),
                        static_cast<std::int32_t>(0));

    return sum;
}

//------------------------------------------------------------------------------
//  ability_modifier – floor((score – 10) / 2) with integral arithmetic.
//------------------------------------------------------------------------------
std::int32_t modifier(std::int32_t score)
{
    const std::int32_t diff = score - static_cast<std::int32_t>(10);
    std::int32_t modifier   = diff / static_cast<std::int32_t>(2);

    if ((diff < static_cast<std::int32_t>(0)) &&
        ((diff % static_cast<std::int32_t>(2)) != static_cast<std::int32_t>(0)))
    {
        --modifier;
    }

    return modifier;
}

//------------------------------------------------------------------------------
//  Character – constructor rolls all abilities and computes hit-points.
//------------------------------------------------------------------------------
Character::Character()
    : strength(ability()),
      dexterity(ability()),
      constitution(ability()),
      intelligence(ability()),
      wisdom(ability()),
      charisma(ability()),
      hitpoints(static_cast<std::int32_t>(10) + modifier(constitution))
{
}

//------------------------------------------------------------------------------
//  Accessors
//------------------------------------------------------------------------------

}  // namespace dnd_character
