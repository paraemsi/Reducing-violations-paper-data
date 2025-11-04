#include "dnd_character.h"

#include <algorithm>   // std::min_element
#include <numeric>     // std::accumulate
#include <random>
#include <array>

namespace dnd_character
{
namespace
{
    // Roll one six-sided die
    [[nodiscard]] ability_score_t roll_die(std::mt19937& engine)
    {
        static constexpr std::int32_t MIN_DIE_VALUE = 1;
        static constexpr std::int32_t MAX_DIE_VALUE = 6;

        std::uniform_int_distribution<std::int32_t> distribution(MIN_DIE_VALUE, MAX_DIE_VALUE);
        return static_cast<ability_score_t>(distribution(engine));
    }
} // unnamed namespace

ability_score_t ability()
{
    static std::random_device random_device;
    static std::mt19937       engine(random_device());

    std::array<ability_score_t, 4U> rolls{};

    for(std::size_t i = 0U; i < 4U; ++i)
    {
        rolls[i] = roll_die(engine);
    }

    const ability_score_t smallest = *std::min_element(rolls.cbegin(), rolls.cend());
    std::int32_t total = static_cast<std::int32_t>(0);
    for(const ability_score_t val : rolls)
    {
        total += static_cast<std::int32_t>(val);
    }

    const ability_score_t score = static_cast<ability_score_t>(total - static_cast<std::int32_t>(smallest));
    return score;
}

modifier_t modifier(const ability_score_t score)
{
    const std::int32_t diff = static_cast<std::int32_t>(score) - static_cast<std::int32_t>(10);

    modifier_t result{};

    if(diff >= 0)
    {
        result = static_cast<modifier_t>(diff / 2);
    }
    else
    {
        /* Subtract 1 before division to obtain floor() semantics for negatives */
        result = static_cast<modifier_t>((diff - 1) / 2);
    }

    return result;
}

Character::Character()
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability())
    , hitpoints(
          static_cast<hit_point_t>(
              static_cast<hit_point_t>(10)
              + static_cast<hit_point_t>(modifier(constitution))))
{
}







} // namespace dnd_character
