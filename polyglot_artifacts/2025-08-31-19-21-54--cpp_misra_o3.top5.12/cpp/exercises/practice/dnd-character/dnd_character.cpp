#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <random>

namespace dnd_character {

std::uint32_t ability()
{
    static thread_local std::mt19937 generator{ std::random_device{}() };
    std::uniform_int_distribution<std::uint32_t> distribution(1U, 6U);

    std::array<std::uint32_t, 4U> rolls{};

    for (std::uint32_t & value : rolls) {
        value = distribution(generator);
    }

    const std::uint32_t total_roll =
        std::accumulate(rolls.begin(), rolls.end(), static_cast<std::uint32_t>(0U));

    const std::uint32_t min_roll =
        *std::min_element(rolls.begin(), rolls.end());

    return (total_roll - min_roll);
}

std::int32_t modifier(std::uint32_t score)
{
    if (score >= 10U) {
        return static_cast<std::int32_t>((score - 10U) / 2U);
    } else {
        return -static_cast<std::int32_t>((11U - score) / 2U);
    }
}

Character::Character()
    : strength(ability()),
      dexterity(ability()),
      constitution(ability()),
      intelligence(ability()),
      wisdom(ability()),
      charisma(ability()),
      hitpoints(static_cast<std::int32_t>(10) + modifier(constitution))
{
    /* all members initialised */
}




}  // namespace dnd_character
