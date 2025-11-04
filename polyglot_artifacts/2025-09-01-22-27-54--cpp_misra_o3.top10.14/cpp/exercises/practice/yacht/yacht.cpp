#include "yacht.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <string_view>

namespace yacht {

// Helper: count occurrences of each face (1-6) in the roll
static auto make_counts(const std::array<std::uint8_t, 5>& dice) -> std::array<std::uint8_t, 7U>
{
    std::array<std::uint8_t, 7U> counts{};
    for (const auto die : dice)
    {
        ++counts[static_cast<std::size_t>(die)];
    }
    return counts;
}

// Convert a textual category name to the strongly-typed enumeration value
static auto category_from_name(std::string_view name) -> category
{
    if (name == "ones")
    {
        return category::ones;
    }
    else if (name == "twos")
    {
        return category::twos;
    }
    else if (name == "threes")
    {
        return category::threes;
    }
    else if (name == "fours")
    {
        return category::fours;
    }
    else if (name == "fives")
    {
        return category::fives;
    }
    else if (name == "sixes")
    {
        return category::sixes;
    }
    else if (name == "full house")
    {
        return category::full_house;
    }
    else if (name == "four of a kind")
    {
        return category::four_of_a_kind;
    }
    else if (name == "little straight")
    {
        return category::little_straight;
    }
    else if (name == "big straight")
    {
        return category::big_straight;
    }
    else if (name == "choice")
    {
        return category::choice;
    }
    else if (name == "yacht")
    {
        return category::yacht;
    }
    else
    {
        /* Unrecognised text – treat as zero-score choice */
        return category::choice;
    }
}

 // Wrapper overload converting textual category name to enum
auto score(const std::array<std::uint8_t, 5>& dice, std::string_view cat_name) -> std::uint32_t
{
    return score(dice, category_from_name(cat_name));
}

// Public API ---------------------------------------------------------------//
auto score(const std::array<std::uint8_t, 5>& dice, category cat) -> std::uint32_t
{
    const auto counts = make_counts(dice);

    switch (cat)
    {
        case category::ones:
        {
            return static_cast<std::uint32_t>(counts[1U]) * static_cast<std::uint32_t>(1U);
        }

        case category::twos:
        {
            return static_cast<std::uint32_t>(counts[2U]) * static_cast<std::uint32_t>(2U);
        }

        case category::threes:
        {
            return static_cast<std::uint32_t>(counts[3U]) * static_cast<std::uint32_t>(3U);
        }

        case category::fours:
        {
            return static_cast<std::uint32_t>(counts[4U]) * static_cast<std::uint32_t>(4U);
        }

        case category::fives:
        {
            return static_cast<std::uint32_t>(counts[5U]) * static_cast<std::uint32_t>(5U);
        }

        case category::sixes:
        {
            return static_cast<std::uint32_t>(counts[6U]) * static_cast<std::uint32_t>(6U);
        }

        case category::full_house:
        {
            bool has_three{false};
            bool has_two{false};
            std::uint32_t total{0U};

            for (std::uint8_t pip = 1U; pip <= 6U; ++pip)
            {
                const std::uint8_t c = counts[static_cast<std::size_t>(pip)];
                if (c == static_cast<std::uint8_t>(3U))
                {
                    has_three = true;
                }
                else if (c == static_cast<std::uint8_t>(2U))
                {
                    has_two = true;
                }
                total += static_cast<std::uint32_t>(pip) * static_cast<std::uint32_t>(c);
            }

            if (has_three && has_two)
            {
                return total;
            }
            return 0U;
        }

        case category::four_of_a_kind:
        {
            for (std::uint8_t pip = 1U; pip <= 6U; ++pip)
            {
                if (counts[static_cast<std::size_t>(pip)] >= static_cast<std::uint8_t>(4U))
                {
                    return static_cast<std::uint32_t>(pip) * static_cast<std::uint32_t>(4U);
                }
            }
            return 0U;
        }

        case category::little_straight:
        {
            /* 1-2-3-4-5 straight requires exactly one of pips 1-5
             * and none of pip 6.  Index 0 is unused. */
            const std::array<std::uint8_t, 7U> want{{0U, 1U, 1U, 1U, 1U, 1U, 0U}};
            if (counts == want)
            {
                return static_cast<std::uint32_t>(30U);
            }
            return 0U;
        }

        case category::big_straight:
        {
            const std::array<std::uint8_t, 7U> want{{0U, 0U, 1U, 1U, 1U, 1U, 1U}};
            if (counts == want)
            {
                return static_cast<std::uint32_t>(30U);
            }
            return 0U;
        }

        case category::choice:
        {
            return std::accumulate(
                dice.begin(),
                dice.end(),
                static_cast<std::uint32_t>(0U),
                [](std::uint32_t acc, std::uint8_t v) { return acc + static_cast<std::uint32_t>(v); });
        }

        case category::yacht:
        {
            for (std::uint8_t pip = 1U; pip <= 6U; ++pip)
            {
                if (counts[static_cast<std::size_t>(pip)] == static_cast<std::uint8_t>(5U))
                {
                    return static_cast<std::uint32_t>(50U);
                }
            }
            return 0U;
        }

        default:
        {
            // Defensive: unreachable with current enum values
            return 0U;
        }
    }
}

}  // namespace yacht
