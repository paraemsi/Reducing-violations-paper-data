#include "dnd_character.h"

#include <array>
#include <algorithm>
#include <random>

namespace dnd_character {

namespace
{
    /*  Roll a single six-sided die (1-6). */
    score_t roll_die()
    {
        static thread_local std::mt19937 generator { std::random_device{}() };
        static thread_local std::uniform_int_distribution<std::int32_t> distribution(
            static_cast<std::int32_t>(1), static_cast<std::int32_t>(6));

        return static_cast<score_t>(distribution(generator));
    }
} // unnamed namespace

score_t ability()
{
    std::array<score_t, 4U> rolls {};
    for(std::size_t i {0U}; i < rolls.size(); ++i)
    {
        rolls[i] = roll_die();
    }

    std::sort(rolls.begin(), rolls.end());

    const score_t sum_top_three =
        static_cast<score_t>((rolls[1U] + rolls[2U]) + rolls[3U]);

    return sum_top_three;
}

score_t modifier(score_t score)
{
    const score_t delta { score - static_cast<score_t>(10) };
    score_t mod { delta / static_cast<score_t>(2) };

    if((delta < static_cast<score_t>(0)) && ((delta % static_cast<score_t>(2)) != static_cast<score_t>(0)))
    {
        --mod;
    }

    return mod;
}

Character::Character() :
    strength{ ability() },
    dexterity{ ability() },
    constitution{ ability() },
    intelligence{ ability() },
    wisdom{ ability() },
    charisma{ ability() },
    hitpoints{ static_cast<score_t>(10) + modifier(constitution) }
{
}








} // namespace dnd_character
