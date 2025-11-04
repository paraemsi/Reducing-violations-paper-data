#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {

/*  Roll a single six-sided die (1-6). */
Score roll_die(std::mt19937& engine)
{
    static constexpr Score min_val { static_cast<Score>(1) };
    static constexpr Score max_val { static_cast<Score>(6) };
    std::uniform_int_distribution<Score> dist(min_val, max_val);
    return static_cast<Score>(dist(engine));
}

/*  Thread-local random engine. */
std::mt19937& rng()
{
    thread_local std::mt19937 engine { std::random_device{}() };
    return engine;
}

}  // unnamed namespace

Score ability()
{
    std::array<Score, 4U> rolls {};

    for(std::size_t i { 0U }; i < rolls.size(); ++i)
    {
        rolls[i] = roll_die(rng());
    }

    /*  Discard the lowest roll and sum the remaining three. */
    const auto lowest_iter { std::min_element(rolls.cbegin(), rolls.cend()) };
    const Score sum { static_cast<Score>(std::accumulate(rolls.cbegin(),
                                                         rolls.cend(),
                                                         static_cast<Score>(0))) - *lowest_iter };

    return sum;
}

Score modifier(Score score)
{
    /*  floor((score - 10) / 2) with only integral arithmetic. */
    const Score delta { score - static_cast<Score>(10) };

    if(delta >= static_cast<Score>(0))
    {
        return delta / static_cast<Score>(2);
    }
    else
    {
        /*  For negative numbers, adjust to obtain floor semantics. */
        return (delta - static_cast<Score>(1)) / static_cast<Score>(2);
    }
}

Character::Character()
    : strength      { ability() }
    , dexterity     { ability() }
    , constitution  { ability() }
    , intelligence  { ability() }
    , wisdom        { ability() }
    , charisma      { ability() }
    , hitpoints     { static_cast<Score>(10) + modifier(constitution) }
{
}


}  // namespace dnd_character
