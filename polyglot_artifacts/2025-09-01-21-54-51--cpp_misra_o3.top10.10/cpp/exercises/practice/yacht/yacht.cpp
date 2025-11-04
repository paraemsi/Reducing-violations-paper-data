#include "yacht.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <string_view>

namespace yacht {

namespace {

/* Sum all dice values */
auto sum_dice(const std::array<std::uint8_t, 5U>& dice) -> std::uint32_t
{
    auto const total = std::accumulate(
        dice.begin(),
        dice.end(),
        static_cast<std::uint32_t>(0),
        [](std::uint32_t acc, std::uint8_t val) -> std::uint32_t
        {
            return (acc + static_cast<std::uint32_t>(val));
        });
    return total;
}

/* Build a frequency table indexed by face value (1‥6) */
auto build_counts(const std::array<std::uint8_t, 5U>& dice) -> std::array<std::uint8_t, 7U>
{
    auto counts = std::array<std::uint8_t, 7U>{};
    counts.fill(static_cast<std::uint8_t>(0));

    for (auto const value : dice)
    {
        ++counts[static_cast<std::size_t>(value)];
    }

    return counts;
}

}  // unnamed namespace

auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint32_t
{
    auto const counts = build_counts(dice);

    switch (cat)
    {
        case category::ones:
        {
            return (static_cast<std::uint32_t>(counts[1U]) *
                    static_cast<std::uint32_t>(1U));
        }
        case category::twos:
        {
            return (static_cast<std::uint32_t>(counts[2U]) *
                    static_cast<std::uint32_t>(2U));
        }
        case category::threes:
        {
            return (static_cast<std::uint32_t>(counts[3U]) *
                    static_cast<std::uint32_t>(3U));
        }
        case category::fours:
        {
            return (static_cast<std::uint32_t>(counts[4U]) *
                    static_cast<std::uint32_t>(4U));
        }
        case category::fives:
        {
            return (static_cast<std::uint32_t>(counts[5U]) *
                    static_cast<std::uint32_t>(5U));
        }
        case category::sixes:
        {
            return (static_cast<std::uint32_t>(counts[6U]) *
                    static_cast<std::uint32_t>(6U));
        }
        case category::full_house:
        {
            auto has_three = false;
            auto has_two   = false;

            for (std::size_t face = 1U; face <= 6U; ++face)
            {
                auto const c = static_cast<std::uint32_t>(counts[face]);

                if (c == 3U)
                {
                    has_three = true;
                }
                else if (c == 2U)
                {
                    has_two = true;
                }
            }

            if ((has_three) && (has_two))
            {
                return sum_dice(dice);
            }
            return static_cast<std::uint32_t>(0);
        }
        case category::four_of_a_kind:
        {
            for (std::size_t face = 1U; face <= 6U; ++face)
            {
                if (static_cast<std::uint32_t>(counts[face]) >= 4U)
                {
                    return (static_cast<std::uint32_t>(face) *
                            static_cast<std::uint32_t>(4U));
                }
            }
            return static_cast<std::uint32_t>(0);
        }
        case category::little_straight:
        {
            if ((static_cast<std::uint32_t>(counts[1U]) == 1U) &&
                (static_cast<std::uint32_t>(counts[2U]) == 1U) &&
                (static_cast<std::uint32_t>(counts[3U]) == 1U) &&
                (static_cast<std::uint32_t>(counts[4U]) == 1U) &&
                (static_cast<std::uint32_t>(counts[5U]) == 1U))
            {
                return static_cast<std::uint32_t>(30U);
            }
            return static_cast<std::uint32_t>(0);
        }
        case category::big_straight:
        {
            if ((static_cast<std::uint32_t>(counts[2U]) == 1U) &&
                (static_cast<std::uint32_t>(counts[3U]) == 1U) &&
                (static_cast<std::uint32_t>(counts[4U]) == 1U) &&
                (static_cast<std::uint32_t>(counts[5U]) == 1U) &&
                (static_cast<std::uint32_t>(counts[6U]) == 1U))
            {
                return static_cast<std::uint32_t>(30U);
            }
            return static_cast<std::uint32_t>(0);
        }
        case category::choice:
        {
            return sum_dice(dice);
        }
        case category::yacht:
        {
            for (std::size_t face = 1U; face <= 6U; ++face)
            {
                if (static_cast<std::uint32_t>(counts[face]) == 5U)
                {
                    return static_cast<std::uint32_t>(50U);
                }
            }
            return static_cast<std::uint32_t>(0);
        }
        default:
        {
            return static_cast<std::uint32_t>(0);
        }
    }
}

auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view cat_name) -> std::uint32_t
{
    if (cat_name == "ones")
    {
        return score(dice, category::ones);
    }
    else if (cat_name == "twos")
    {
        return score(dice, category::twos);
    }
    else if (cat_name == "threes")
    {
        return score(dice, category::threes);
    }
    else if (cat_name == "fours")
    {
        return score(dice, category::fours);
    }
    else if (cat_name == "fives")
    {
        return score(dice, category::fives);
    }
    else if (cat_name == "sixes")
    {
        return score(dice, category::sixes);
    }
    else if (cat_name == "full house")
    {
        return score(dice, category::full_house);
    }
    else if (cat_name == "four of a kind")
    {
        return score(dice, category::four_of_a_kind);
    }
    else if (cat_name == "little straight")
    {
        return score(dice, category::little_straight);
    }
    else if (cat_name == "big straight")
    {
        return score(dice, category::big_straight);
    }
    else if (cat_name == "choice")
    {
        return score(dice, category::choice);
    }
    else if (cat_name == "yacht")
    {
        return score(dice, category::yacht);
    }

    return static_cast<std::uint32_t>(0);
}

}  // namespace yacht
