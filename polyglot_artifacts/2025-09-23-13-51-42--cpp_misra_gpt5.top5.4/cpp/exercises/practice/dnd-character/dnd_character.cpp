#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <random>

namespace dnd_character {

namespace {
    score_t roll_die_six()
    {
        static std::mt19937 engine{ std::random_device{}() };
        static std::uniform_int_distribution<score_t> distribution(
            static_cast<score_t>(1),
            static_cast<score_t>(6));
        return distribution(engine);
    }
}  // namespace

score_t ability()
{
    std::array<score_t, 4U> rolls{};
    for (score_t& r : rolls)
    {
        r = roll_die_six();
    }

    std::sort(rolls.begin(), rolls.end());
    const score_t total = ((rolls[1] + rolls[2]) + rolls[3]);
    return total;
}

score_t modifier(score_t score)
{
    const score_t diff = (score - static_cast<score_t>(10));
    if (diff >= static_cast<score_t>(0))
    {
        return (diff / static_cast<score_t>(2));
    }
    else
    {
        const score_t neg = (-diff);
        return (-( (neg + static_cast<score_t>(1)) / static_cast<score_t>(2) ));
    }
}

Character::Character()
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability())
    , hitpoints((static_cast<score_t>(10) + modifier(constitution)))
{
}


}  // namespace dnd_character
