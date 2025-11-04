#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <numeric>
#include <random>

namespace {
using score_t = dnd_character::score_t;

/* roll a single six-sided die */
score_t roll_die()
{
    static std::random_device rd{};
    static std::mt19937 generator{ rd() };
    static std::uniform_int_distribution<score_t> distribution(
        static_cast<score_t>(1),
        static_cast<score_t>(6));

    return distribution(generator);
}
}  // unnamed namespace

namespace dnd_character {

score_t ability() noexcept
{
    std::array<score_t, 4U> rolls{};

    for (auto & roll : rolls)
    {
        roll = roll_die();
    }

    const score_t total{ std::accumulate(rolls.begin(), rolls.end(), static_cast<score_t>(0)) };
    const score_t min_roll{ *std::min_element(rolls.begin(), rolls.end()) };

    return (total - min_roll);  // sum of the highest three rolls
}

Character::Character()
    : strength{ ability() }
    , dexterity{ ability() }
    , constitution{ ability() }
    , intelligence{ ability() }
    , wisdom{ ability() }
    , charisma{ ability() }
    , hitpoints{ static_cast<score_t>(10) + modifier(constitution) }
{
    // constructor body intentionally left empty
}







score_t modifier(score_t ability_score) noexcept
{
    const score_t delta{ ability_score - static_cast<score_t>(10) };

    if (delta >= static_cast<score_t>(0))
    {
        return (delta / static_cast<score_t>(2));
    }
    else
    {
        /* floor division for negatives */
        return ((delta - static_cast<score_t>(1)) / static_cast<score_t>(2));
    }
}


}  // namespace dnd_character
