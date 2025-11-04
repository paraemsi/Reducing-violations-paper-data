#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <numeric>

namespace dnd_character {


namespace {
    /* random number generator – single instance */
    std::mt19937& generator()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }
}  // unnamed namespace

std::int32_t ability()
{
    std::array<std::int32_t, DICE_COUNT> rolls {};
    std::uniform_int_distribution<std::int32_t> dist(DICE_MIN, DICE_MAX);

    for (std::int32_t& roll : rolls) {
        roll = dist(generator());
    }

    const auto min_it = std::min_element(rolls.begin(), rolls.end());
    const std::int32_t sum_all = std::accumulate(
        rolls.begin(),
        rolls.end(),
        static_cast<std::int32_t>(0)
    );

    const std::int32_t sum = (sum_all - *min_it);

    return sum;
}

std::int32_t modifier(std::int32_t score)
{
    const std::int32_t delta = score - static_cast<std::int32_t>(10);
    std::int32_t mod = (delta / static_cast<std::int32_t>(2));

    if ((delta < static_cast<std::int32_t>(0)) && ((delta % static_cast<std::int32_t>(2)) != static_cast<std::int32_t>(0))) {
        --mod;
    }

    return mod;
}

Character::Character() :
    strength(ability()),
    dexterity(ability()),
    constitution(ability()),
    intelligence(ability()),
    wisdom(ability()),
    charisma(ability()),
    hitpoints((static_cast<std::int32_t>(10) + modifier(constitution)))
{
}

}  // namespace dnd_character
