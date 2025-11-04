#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <random>

namespace dnd_character {

namespace {
/*  Roll a single six-sided die.                                        */
ability_score_t roll_die()
{
    static std::random_device rd {};
    static std::mt19937 generator { rd() };
    static std::uniform_int_distribution<ability_score_t> distribution(
        static_cast<ability_score_t>(1),
        static_cast<ability_score_t>(6));

    return distribution(generator);
}
} // unnamed namespace

ability_score_t ability()
{
    std::array<ability_score_t, 4U> rolls {};

    for (ability_score_t & value : rolls) {
        value = roll_die();
    }

    std::sort(rolls.begin(), rolls.end());

    /*  Sum the highest three dice (elements 1, 2, 3 after sort).      */
    return (rolls.at(1U) + rolls.at(2U)) + rolls.at(3U);
}

ability_score_t modifier(ability_score_t score)
{
    /*  delta = score − 10                                               */
    const ability_score_t delta {
        score - static_cast<ability_score_t>(10)
    };

    if (delta >= static_cast<ability_score_t>(0)) {
        /*  Non-negative values round down naturally with integer div.   */
        return delta / static_cast<ability_score_t>(2);
    }

    /*  For negative numbers, adjust by −1 to obtain floor division.     */
    return (delta - static_cast<ability_score_t>(1)) /
           static_cast<ability_score_t>(2);
}

Character::Character()
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability())
    , hitpoints(static_cast<ability_score_t>(10) +
                modifier(constitution))
{
}


}  // namespace dnd_character
