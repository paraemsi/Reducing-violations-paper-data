#include "dnd_character.h"
#include <array>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <random>

namespace dnd_character {

// Roll four 6-sided dice, drop the lowest, sum the rest.
std::int32_t ability()
{
    static std::random_device rd;
    static std::mt19937 engine{ rd() };
    static std::uniform_int_distribution<std::int32_t> dist(
        static_cast<std::int32_t>(1),
        static_cast<std::int32_t>(6));

    std::array<std::int32_t, 4U> rolls{};

    for (std::int32_t& value : rolls)
    {
        value = dist(engine);
    }

    std::sort(rolls.begin(), rolls.end());

    const std::int32_t sum = std::accumulate(
        std::next(rolls.begin()),
        rolls.end(),
        static_cast<std::int32_t>(0));

    return sum;
}

std::int32_t modifier(std::int32_t score)
{
    /*  D&D ability modifier is the floor of (score - 10) / 2.
        In C++ integer arithmetic, division truncates toward zero, so we adjust
        negative values by subtracting one before dividing to achieve flooring. */
    const std::int32_t diff{ score - static_cast<std::int32_t>(10) };

    if(diff >= static_cast<std::int32_t>(0))
    {
        return diff / static_cast<std::int32_t>(2);
    }
    else
    {
        /* Ensure arithmetic floors toward minus infinity for negatives */
        return (diff - static_cast<std::int32_t>(1)) / static_cast<std::int32_t>(2);
    }
}

Character::Character()
    : strength{ ability() }
    , dexterity{ ability() }
    , constitution{ ability() }
    , intelligence{ ability() }
    , wisdom{ ability() }
    , charisma{ ability() }
    , hitpoints{ static_cast<std::int32_t>(10) + modifier(constitution) }
{
}


}  // namespace dnd_character
