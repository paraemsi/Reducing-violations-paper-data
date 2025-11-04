#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <random>

namespace dnd_character {

namespace {
    // Pseudo-random generator encapsulated in a function to ensure single initialization.
    std::mt19937& rng()
    {
        static std::random_device rd;
        static std::mt19937 eng(rd());
        return eng;
    }

    score_type roll_die(score_type sides)
    {
        // Roll a single die with the given number of sides (inclusive range [1, sides]).
        std::uniform_int_distribution<score_type> dist(static_cast<score_type>(1), sides);
        return dist(rng());
    }
}

score_type ability()
{
    std::array<score_type, 4U> rolls{};

    for (std::size_t i = 0U; i < 4U; ++i)
    {
        rolls[i] = roll_die(static_cast<score_type>(6));
    }

    std::sort(rolls.begin(), rolls.end());

    // Sum the largest three dice (indices 1, 2, 3 after ascending sort).
    const score_type sum = (rolls[1U] + rolls[2U]) + rolls[3U];
    return sum;
}

score_type modifier(score_type score)
{
    const score_type diff = score - static_cast<score_type>(10);

    // Compute floor(diff / 2) for both positive and negative diff
    return (diff >= static_cast<score_type>(0))
        ? (diff / static_cast<score_type>(2))
        : ((diff - static_cast<score_type>(1)) / static_cast<score_type>(2));
}

Character::Character()
    : strength{ability()}
    , dexterity{ability()}
    , constitution{ability()}
    , intelligence{ability()}
    , wisdom{ability()}
    , charisma{ability()}
    , hitpoints{static_cast<score_type>(10) + modifier(constitution)}
{
}








}  // namespace dnd_character
