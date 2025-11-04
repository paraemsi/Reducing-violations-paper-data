#include "dnd_character.h"

#include <random>

namespace dnd_character {

namespace {
    inline auto floor_div2(score_t a) -> score_t
    {
        score_t q = (a / static_cast<score_t>(2));
        score_t r = (a % static_cast<score_t>(2));
        if ((r != static_cast<score_t>(0)) && (a < static_cast<score_t>(0))) {
            q = (q - static_cast<score_t>(1));
        }
        return q;
    }

    inline auto rng_engine() -> std::mt19937&
    {
        static thread_local std::mt19937 eng{std::random_device{}()};
        return eng;
    }
}  // namespace

auto ability() -> score_t
{
    std::uniform_int_distribution<score_t> dist(static_cast<score_t>(1), static_cast<score_t>(6));

    score_t total = static_cast<score_t>(0);
    score_t min_val = static_cast<score_t>(7);

    for (score_t i = static_cast<score_t>(0); (i < static_cast<score_t>(4)); ++i) {
        score_t roll = dist(rng_engine());
        total = (total + roll);
        if (roll < min_val) {
            min_val = roll;
        }
    }

    return (total - min_val);
}

auto modifier(score_t score) -> score_t
{
    const score_t delta = (score - static_cast<score_t>(10));
    return floor_div2(delta);
}

Character::Character()
    : strength(static_cast<score_t>(0))
    , dexterity(static_cast<score_t>(0))
    , constitution(static_cast<score_t>(0))
    , intelligence(static_cast<score_t>(0))
    , wisdom(static_cast<score_t>(0))
    , charisma(static_cast<score_t>(0))
    , hitpoints(static_cast<score_t>(0))
{
    strength = ability();
    dexterity = ability();
    constitution = ability();
    intelligence = ability();
    wisdom = ability();
    charisma = ability();

    hitpoints = (static_cast<score_t>(10) + modifier(constitution));
}



}  // namespace dnd_character
