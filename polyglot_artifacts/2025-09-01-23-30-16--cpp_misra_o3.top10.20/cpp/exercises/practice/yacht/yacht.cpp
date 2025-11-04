#include "yacht.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstddef>
#include <numeric>
#include <string_view>

namespace yacht {

[[nodiscard]] auto score(const dice_set& dice, const category cat) -> std::uint32_t
{
    /* Count the occurrences of each face value: indices 1–6 are used */
    std::array<std::uint8_t, 7U> counts{}; /* counts[0] remains unused */

    for(const std::uint8_t die : dice)
    {
        counts[static_cast<std::size_t>(die)] =
            static_cast<std::uint8_t>(
                counts[static_cast<std::size_t>(die)] + static_cast<std::uint8_t>(1U));
    }

    const auto sum_dice = static_cast<std::uint32_t>(std::accumulate(
        dice.begin(),
        dice.end(),
        static_cast<std::uint32_t>(0U),
        [](const std::uint32_t acc, const std::uint8_t value) -> std::uint32_t
        {
            return (acc + static_cast<std::uint32_t>(value));
        }));

    switch(cat)
    {
        case category::ones:
        {
            return (static_cast<std::uint32_t>(counts[1U]) * static_cast<std::uint32_t>(1U));
        }
        case category::twos:
        {
            return (static_cast<std::uint32_t>(counts[2U]) * static_cast<std::uint32_t>(2U));
        }
        case category::threes:
        {
            return (static_cast<std::uint32_t>(counts[3U]) * static_cast<std::uint32_t>(3U));
        }
        case category::fours:
        {
            return (static_cast<std::uint32_t>(counts[4U]) * static_cast<std::uint32_t>(4U));
        }
        case category::fives:
        {
            return (static_cast<std::uint32_t>(counts[5U]) * static_cast<std::uint32_t>(5U));
        }
        case category::sixes:
        {
            return (static_cast<std::uint32_t>(counts[6U]) * static_cast<std::uint32_t>(6U));
        }
        case category::full_house:
        {
            bool has_three {false};
            bool has_two   {false};

            for(std::uint8_t face = static_cast<std::uint8_t>(1U);
                face <= static_cast<std::uint8_t>(6U);
                ++face)
            {
                if(counts[static_cast<std::size_t>(face)] == static_cast<std::uint8_t>(3U))
                {
                    has_three = true;
                }
                else if(counts[static_cast<std::size_t>(face)] == static_cast<std::uint8_t>(2U))
                {
                    has_two = true;
                }
            }

            if((has_three) && (has_two))
            {
                return sum_dice;
            }
            return static_cast<std::uint32_t>(0U);
        }
        case category::four_of_a_kind:
        {
            for(std::uint8_t face = static_cast<std::uint8_t>(1U);
                face <= static_cast<std::uint8_t>(6U);
                ++face)
            {
                if(counts[static_cast<std::size_t>(face)] >= static_cast<std::uint8_t>(4U))
                {
                    return (static_cast<std::uint32_t>(face) * static_cast<std::uint32_t>(4U));
                }
            }
            return static_cast<std::uint32_t>(0U);
        }
        case category::little_straight:
        {
            const bool is_straight =
                (counts[1U] == static_cast<std::uint8_t>(1U)) &&
                (counts[2U] == static_cast<std::uint8_t>(1U)) &&
                (counts[3U] == static_cast<std::uint8_t>(1U)) &&
                (counts[4U] == static_cast<std::uint8_t>(1U)) &&
                (counts[5U] == static_cast<std::uint8_t>(1U)) &&
                (counts[6U] == static_cast<std::uint8_t>(0U));

            if(is_straight)
            {
                return static_cast<std::uint32_t>(30U);
            }
            return static_cast<std::uint32_t>(0U);
        }
        case category::big_straight:
        {
            const bool is_straight =
                (counts[1U] == static_cast<std::uint8_t>(0U)) &&
                (counts[2U] == static_cast<std::uint8_t>(1U)) &&
                (counts[3U] == static_cast<std::uint8_t>(1U)) &&
                (counts[4U] == static_cast<std::uint8_t>(1U)) &&
                (counts[5U] == static_cast<std::uint8_t>(1U)) &&
                (counts[6U] == static_cast<std::uint8_t>(1U));

            if(is_straight)
            {
                return static_cast<std::uint32_t>(30U);
            }
            return static_cast<std::uint32_t>(0U);
        }
        case category::choice:
        {
            return sum_dice;
        }
        case category::yacht:
        {
            for(std::uint8_t face = static_cast<std::uint8_t>(1U);
                face <= static_cast<std::uint8_t>(6U);
                ++face)
            {
                if(counts[static_cast<std::size_t>(face)] == static_cast<std::uint8_t>(5U))
                {
                    return static_cast<std::uint32_t>(50U);
                }
            }
            return static_cast<std::uint32_t>(0U);
        }
        default:
        {
            return static_cast<std::uint32_t>(0U);
        }
    }
}

auto to_category(std::string_view cat) -> category
{
    if(cat == "ones")
    {
        return category::ones;
    }
    else if(cat == "twos")
    {
        return category::twos;
    }
    else if(cat == "threes")
    {
        return category::threes;
    }
    else if(cat == "fours")
    {
        return category::fours;
    }
    else if(cat == "fives")
    {
        return category::fives;
    }
    else if(cat == "sixes")
    {
        return category::sixes;
    }
    else if(cat == "full house")
    {
        return category::full_house;
    }
    else if(cat == "four of a kind")
    {
        return category::four_of_a_kind;
    }
    else if(cat == "little straight")
    {
        return category::little_straight;
    }
    else if(cat == "big straight")
    {
        return category::big_straight;
    }
    else if(cat == "choice")
    {
        return category::choice;
    }
    else    /* default to yacht */
    {
        return category::yacht;
    }
}

[[nodiscard]] auto score(const dice_set& dice, std::string_view cat) -> std::uint32_t
{
    return score(dice, to_category(cat));
}

}  /* namespace yacht */
