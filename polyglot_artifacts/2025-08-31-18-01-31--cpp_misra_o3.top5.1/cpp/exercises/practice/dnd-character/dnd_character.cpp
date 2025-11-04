#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <random>

namespace dnd_character {

namespace
{
    /*  Return a reference to a static Mersenne Twister engine.
        Use a function-scope static to ensure thread-safe initialisation
        and to avoid the static-initialisation-order fiasco. */
    std::mt19937 & random_engine()
    {
        static std::random_device rd;
        static std::mt19937 eng(rd());
        return eng;
    }

    /*  Roll a single six-sided die. */
    std::int32_t roll_die()
    {
        static std::uniform_int_distribution<std::int32_t> dist(1, 6);
        return dist(random_engine());
    }
} // unnamed namespace

/*  Roll four dice, drop the lowest, and sum the remaining three. */
static std::int32_t roll_ability()
{
    std::array<std::int32_t, 4U> rolls{};

    for (std::uint32_t i = 0U; i < 4U; ++i)
    {
        rolls[i] = roll_die();
    }

    std::sort(rolls.begin(), rolls.end());

    /*  Sum the three highest values (indices 1-3 after sorting). */
    return (rolls[1] + rolls[2]) + rolls[3];
}

Character::Character()
    : strength(roll_ability()),
      dexterity(roll_ability()),
      constitution(roll_ability()),
      intelligence(roll_ability()),
      wisdom(roll_ability()),
      charisma(roll_ability()),
      hitpoints(10 + modifier(constitution))
{
}








/*  Compute the ability modifier with correct rounding
    (floor division for negative results). */
std::int32_t modifier(const std::int32_t ability_score) noexcept
{
    const std::int32_t diff = ability_score - 10;

    if ((diff < 0) && ((diff % 2) != 0))
    {
        return (diff / 2) - 1;
    }

    return diff / 2;
}

/*  Expose the roll_ability algorithm as a free function. */
std::int32_t ability() noexcept
{
    return roll_ability();
}

}  // namespace dnd_character
