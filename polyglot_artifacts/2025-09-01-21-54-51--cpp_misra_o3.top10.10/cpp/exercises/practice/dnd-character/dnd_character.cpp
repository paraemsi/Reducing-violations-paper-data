#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <random>

namespace dnd_character {

namespace
{
/* Shared random-number generator – initialised once per program run. */
std::mt19937& rng()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}
}  // unnamed namespace

std::int32_t ability()
{
    /* Roll four 6-sided dice and discard the lowest roll. */
    std::uniform_int_distribution<std::int32_t> dist(
        1,
        6);

    std::array<std::int32_t, 4> dice{};
    for (std::int32_t& die : dice)
    {
        die = dist(rng());
    }

    const std::int32_t lowest = *std::min_element(dice.begin(), dice.end());

    std::int32_t sum = 0;
    for (const std::int32_t die : dice)
    {
        sum += die;
    }
    sum -= lowest;

    return sum;
}

std::int32_t modifier(std::int32_t score)
{
    if (score >= 10)
    {
        return (score - 10) / 2;
    }
    else
    {
        return (score - 11) / 2;
    }
}

Character::Character() :
    strength(ability()),
    dexterity(ability()),
    constitution(ability()),
    intelligence(ability()),
    wisdom(ability()),
    charisma(ability()),
    hitpoints(static_cast<std::int32_t>(10) + modifier(constitution))
{
}


}  // namespace dnd_character
