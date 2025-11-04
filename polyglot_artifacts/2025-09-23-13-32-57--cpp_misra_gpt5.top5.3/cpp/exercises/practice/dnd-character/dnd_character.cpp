#include "dnd_character.h"

#include <random>

namespace dnd_character {

namespace {
    inline std::mt19937& rng()
    {
        static thread_local std::mt19937 engine{std::random_device{}()};
        return engine;
    }
}  // namespace

score_t ability()
{
    std::uniform_int_distribution<score_t> dist(static_cast<score_t>(1), static_cast<score_t>(6));

    const score_t a = dist(rng());
    const score_t b = dist(rng());
    const score_t c = dist(rng());
    const score_t d = dist(rng());

    const score_t min_ab = ((a < b) ? a : b);
    const score_t min_cd = ((c < d) ? c : d);
    const score_t min_all = ((min_ab < min_cd) ? min_ab : min_cd);

    const score_t sum_all = ((a + b) + (c + d));
    const score_t result = (sum_all - min_all);

    return result;
}

score_t modifier(score_t score)
{
    const score_t a = (score - static_cast<score_t>(10));
    const score_t div = (a / static_cast<score_t>(2));
    const score_t rem = (a % static_cast<score_t>(2));

    if ((a < static_cast<score_t>(0)) && (rem != static_cast<score_t>(0))) {
        return (div - static_cast<score_t>(1));
    } else {
        return div;
    }
}

Character::Character()
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability())
    , hitpoints(static_cast<score_t>(10) + modifier(constitution))
{
}

}  // namespace dnd_character
