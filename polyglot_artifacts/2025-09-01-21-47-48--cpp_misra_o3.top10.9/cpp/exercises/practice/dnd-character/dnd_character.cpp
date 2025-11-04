#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <random>
#include <cstdint>

namespace dnd_character {

namespace
{
    std::int32_t roll_die() noexcept
    {
        static std::random_device seed_device{};
        static std::mt19937 engine{seed_device()};
        static std::uniform_int_distribution<std::int32_t> distribution(1, 6);

        return distribution(engine);
    }

    std::int32_t roll_ability_score() noexcept
    {
        std::array<std::int32_t, 4U> rolls{};
        for (std::uint32_t i{0U}; i < static_cast<std::uint32_t>(rolls.size()); ++i)
        {
            rolls[i] = roll_die();
        }

        std::sort(rolls.begin(), rolls.end());

        /* Sum the highest three dice (indices 1, 2, and 3) */
        const std::int32_t sum_highest_three{(rolls[1] + rolls[2]) + rolls[3]};
        return sum_highest_three;
    }
}  // unnamed namespace

std::int32_t DndCharacter::ability() noexcept
{
    return roll_ability_score();
}

std::int32_t DndCharacter::modifier(std::int32_t score) noexcept
{
    const std::int32_t diff{score - 10};
    if (diff >= 0)
    {
        return diff / 2;
    }
    else
    {
        return (diff - 1) / 2;
    }
}

DndCharacter::DndCharacter()
    : m_strength{DndCharacter::ability()},
      m_dexterity{DndCharacter::ability()},
      m_constitution{DndCharacter::ability()},
      m_intelligence{DndCharacter::ability()},
      m_wisdom{DndCharacter::ability()},
      m_charisma{DndCharacter::ability()},
      m_hitpoints{10 + DndCharacter::modifier(m_constitution)}
{
}

std::int32_t DndCharacter::strength() const noexcept
{
    return m_strength;
}

std::int32_t DndCharacter::dexterity() const noexcept
{
    return m_dexterity;
}

std::int32_t DndCharacter::constitution() const noexcept
{
    return m_constitution;
}

std::int32_t DndCharacter::intelligence() const noexcept
{
    return m_intelligence;
}

std::int32_t DndCharacter::wisdom() const noexcept
{
    return m_wisdom;
}

std::int32_t DndCharacter::charisma() const noexcept
{
    return m_charisma;
}

std::int32_t DndCharacter::hitpoints() const noexcept
{
    return m_hitpoints;
}

std::int32_t ability() noexcept
{
    return DndCharacter::ability();
}

std::int32_t modifier(std::int32_t score) noexcept
{
    return DndCharacter::modifier(score);
}

}  // namespace dnd_character
