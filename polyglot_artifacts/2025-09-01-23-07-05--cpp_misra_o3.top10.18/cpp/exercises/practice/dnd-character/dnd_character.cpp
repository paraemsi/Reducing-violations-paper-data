#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <random>
#include <iterator>

namespace
{
    // Thread-local RNG components to stay race-free under parallel tests.
    thread_local std::random_device rd{};
    thread_local std::mt19937 engine{ rd() };
    thread_local std::uniform_int_distribution<std::int32_t> dist{ 1, 6 };
} // unnamed namespace

namespace dnd_character
{

auto ability() -> std::int32_t
{
    std::array<std::int32_t, 4U> rolls{};

    for (std::int32_t& value : rolls)
    {
        value = dist(engine);
    }

    std::sort(rolls.begin(), rolls.end());

    const std::int32_t score{
        std::accumulate(std::next(rolls.begin()), rolls.end(), std::int32_t{ 0 })
    };

    return score;
}

auto modifier(std::int32_t score) noexcept -> std::int32_t
{
    if (score < 10)
    {
        return ((score - 11) / 2);
    }

    return ((score - 10) / 2);
}

Character::Character()
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability())
    , hitpoints(static_cast<std::int32_t>(10 + modifier(constitution)))
{
}

character::character()
    : m_strength(ability())
    , m_dexterity(ability())
    , m_constitution(ability())
    , m_intelligence(ability())
    , m_wisdom(ability())
    , m_charisma(ability())
{
}

auto character::strength() const noexcept -> std::int32_t
{
    return m_strength;
}

auto character::dexterity() const noexcept -> std::int32_t
{
    return m_dexterity;
}

auto character::constitution() const noexcept -> std::int32_t
{
    return m_constitution;
}

auto character::intelligence() const noexcept -> std::int32_t
{
    return m_intelligence;
}

auto character::wisdom() const noexcept -> std::int32_t
{
    return m_wisdom;
}

auto character::charisma() const noexcept -> std::int32_t
{
    return m_charisma;
}

auto character::modifier(std::int32_t score) noexcept -> std::int32_t
{
    if (score < 10)
    {
        return (score - 11) / 2;
    }

    return (score - 10) / 2;
}

auto character::hitpoints() const noexcept -> std::int32_t
{
    return (10 + modifier(m_constitution));
}

} // namespace dnd_character
