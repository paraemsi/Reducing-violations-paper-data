#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <functional>
#include <random>

namespace dnd_character {

namespace
{
    // Roll a single six-sided die
    std::int32_t roll_die(std::mt19937& gen)
    {
        std::uniform_int_distribution<std::int32_t> dist(static_cast<std::int32_t>(1),
                                                         static_cast<std::int32_t>(6));
        return dist(gen);
    }

    // Roll four dice, drop the lowest, and sum the rest
    std::int32_t roll_ability(std::mt19937& gen)
    {
        std::array<std::int32_t, 4U> rolls {};
        for(std::int32_t& value : rolls)
        {
            value = roll_die(gen);
        }

        std::sort(rolls.begin(), rolls.end(), std::greater<std::int32_t>());

        const std::int32_t ability_score { (rolls[0] + rolls[1]) + rolls[2] }; // explicit precedence
        return ability_score;
    }
} // anonymous namespace

std::int32_t ability()
{
    std::random_device rd {};
    std::mt19937 gen { rd() };
    return roll_ability(gen);
}

Character::Character()
{
    std::random_device rd {};
    std::mt19937 gen { rd() };

    strength     = roll_ability(gen);
    dexterity    = roll_ability(gen);
    constitution = roll_ability(gen);
    intelligence = roll_ability(gen);
    wisdom       = roll_ability(gen);
    charisma     = roll_ability(gen);

    hitpoints = static_cast<std::int32_t>(10) + modifier(constitution);
}


std::int32_t modifier(std::int32_t ability_score) noexcept
{
    /*  Calculate the difference from the baseline (10) first so that the logic
     *  stays clear and all arithmetic operates on the same fixed-width type.
     *  Integer division in C++ truncates toward zero, but the D&D rules require
     *  the result to be rounded down (toward negative infinity).  Therefore, if
     *  the difference is negative and odd, the truncated result is one greater
     *  than the mathematical floor; adjust by subtracting one.
     */
    const std::int32_t diff { ability_score - static_cast<std::int32_t>(10) };

    std::int32_t modifier { diff / static_cast<std::int32_t>(2) };

    if((diff < static_cast<std::int32_t>(0)) &&
       ((diff % static_cast<std::int32_t>(2)) != static_cast<std::int32_t>(0)))
    {
        --modifier;
    }

    return modifier;
}

}  // namespace dnd_character
