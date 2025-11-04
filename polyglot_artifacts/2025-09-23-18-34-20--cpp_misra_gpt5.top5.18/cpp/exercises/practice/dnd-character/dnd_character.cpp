#include "dnd_character.h"

#include <array>
#include <random>

namespace dnd_character {

namespace {
    std::mt19937& rng()
    {
        static std::mt19937 gen(std::random_device{}());
        return gen;
    }

    score_t roll_die_1_6()
    {
        static std::uniform_int_distribution<score_t> dist(static_cast<score_t>(1), static_cast<score_t>(6));
        return dist(rng());
    }
}  // namespace

score_t ability()
{
    std::array<score_t, 4U> rolls{};
    for (score_t& r : rolls) {
        r = roll_die_1_6();
    }

    score_t sum = static_cast<score_t>(0);
    score_t min_val = rolls[0];
    for (const score_t& r : rolls) {
        sum = (sum + r);
        if ((r < min_val)) {
            min_val = r;
        }
    }
    return (sum - min_val);
}

score_t modifier(score_t score)
{
    // Using floor(score / 2) - 5 is equivalent to floor((score - 10) / 2) for all valid ability scores.
    return ((score / static_cast<score_t>(2)) - static_cast<score_t>(5));
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
