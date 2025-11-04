#include "dnd_character.h"

#include <array>
#include <algorithm>
#include <random>

namespace dnd_character {

ability_t ability()
{
    static thread_local std::mt19937 generator{ std::random_device{}() };
    std::uniform_int_distribution<std::int32_t> distribution(
        static_cast<std::int32_t>(1),
        static_cast<std::int32_t>(6));

    std::array<std::int32_t, 4U> rolls{ };

    for (std::size_t i{ 0U }; i < rolls.size(); ++i)
    {
        rolls[i] = distribution(generator);
    }

    std::sort(rolls.begin(), rolls.end());

    return ((rolls[1U] + rolls[2U]) + rolls[3U]);
}

ability_t modifier(ability_t score)
{
    std::int32_t diff{ score - static_cast<std::int32_t>(10) };

    if (diff >= static_cast<std::int32_t>(0))
    {
        return diff / static_cast<std::int32_t>(2);
    }
    else
    {
        return (diff - static_cast<std::int32_t>(1)) / static_cast<std::int32_t>(2);
    }
}

Character::Character() :
    strength{ ability() },
    dexterity{ ability() },
    constitution{ ability() },
    intelligence{ ability() },
    wisdom{ ability() },
    charisma{ ability() },
    hitpoints{ static_cast<ability_t>(10) + modifier(constitution) }
{
}


}  // namespace dnd_character
