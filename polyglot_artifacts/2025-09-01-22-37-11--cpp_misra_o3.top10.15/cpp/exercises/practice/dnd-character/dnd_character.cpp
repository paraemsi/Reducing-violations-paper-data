#include "dnd_character.h"

#include <random>
#include <numeric>
#include <cstddef>

namespace dnd_character {

/* ------------------------------------------------------------- */
/*  Internal helpers                                             */
/* ------------------------------------------------------------- */

/*  Roll a single six-sided die (1-6 inclusive). */
static auto roll_die() -> Score
{
    static std::random_device rd {};
    static std::mt19937 engine { rd() };
    static std::uniform_int_distribution<Score> dist(static_cast<Score>(1),
                                                     static_cast<Score>(6));

    return dist(engine);
}

/* ------------------------------------------------------------- */
/*  Free functions                                               */
/* ------------------------------------------------------------- */

auto ability() -> Score
{
    std::array<Score, 4U> rolls {};

    for (auto & r : rolls)
    {
        r = roll_die();
    }

    std::sort(rolls.begin(), rolls.end());

    constexpr std::uint32_t kLowestIndex { 1U };

    const Score sum { std::accumulate(rolls.begin() + static_cast<std::ptrdiff_t>(kLowestIndex),
                                      rolls.end(),
                                      static_cast<Score>(0)) };

    return sum;
}

auto modifier(Score score) -> Score
{
    Score diff { score - static_cast<Score>(10) };

    if ((diff < static_cast<Score>(0)) && ((diff % static_cast<Score>(2)) != static_cast<Score>(0)))
    {
        return (diff / static_cast<Score>(2)) - static_cast<Score>(1);
    }

    return diff / static_cast<Score>(2);
}

/* ------------------------------------------------------------- */
/*  Character implementation                                     */
/* ------------------------------------------------------------- */

Character::Character()
    : strength{ ability() }
    , dexterity{ ability() }
    , constitution{ ability() }
    , intelligence{ ability() }
    , wisdom{ ability() }
    , charisma{ ability() }
    , hitpoints{ static_cast<Score>(10) + modifier(constitution) }
{
}


}  // namespace dnd_character
