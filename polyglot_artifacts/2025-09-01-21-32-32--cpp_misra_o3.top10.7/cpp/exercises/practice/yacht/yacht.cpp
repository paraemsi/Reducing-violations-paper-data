#include "yacht.h"

#include <algorithm>
#include <numeric>
#include <string_view>

namespace yacht {

auto score(const std::array<std::uint8_t, 5U>& dice,
           const category cat) -> std::uint32_t
{
    /* Count occurrences of each possible face (1-6). Index 0 is unused. */
    std::array<std::uint8_t, 7U> counts{};
    counts.fill(static_cast<std::uint8_t>(0U));

    for (std::uint8_t die : dice)
    {
        /* The face value is guaranteed to be 1-6 by the exercise description. */
        ++counts[static_cast<std::size_t>(die)];
    }

    switch (cat)
    {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes:
        {
            const std::uint8_t face_value =
                static_cast<std::uint8_t>(cat); /* 1-6 for these entries */
            const std::uint32_t result =
                (static_cast<std::uint32_t>(face_value) *
                 static_cast<std::uint32_t>(counts[face_value]));
            return result;
        }

        case category::full_house:
        {
            bool has_three {false};
            bool has_two   {false};

            for (std::uint8_t face = 1U; face <= 6U; ++face)
            {
                if (counts[face] == 3U)
                {
                    has_three = true;
                }
                else if (counts[face] == 2U)
                {
                    has_two = true;
                }
            }

            if (has_three && has_two)
            {
                const std::uint32_t total =
                    std::accumulate(dice.begin(),
                                    dice.end(),
                                    static_cast<std::uint32_t>(0),
                                    [](std::uint32_t sum, std::uint8_t value)
                                    {
                                        return (sum + static_cast<std::uint32_t>(value));
                                    });
                return total;
            }
            else
            {
                return 0;
            }
        }

        case category::four_of_a_kind:
        {
            for (std::uint8_t face = 1U; face <= 6U; ++face)
            {
                if (counts[face] >= 4U)
                {
                    const std::uint32_t result =
                        (static_cast<std::uint32_t>(face) * static_cast<std::uint32_t>(4));
                    return result;
                }
            }
            return 0;
        }

        case category::little_straight:
        {
            if ((counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 0U))
            {
                return static_cast<std::uint32_t>(30);
            }
            return 0;
        }

        case category::big_straight:
        {
            if ((counts[1U] == 0U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 1U))
            {
                return static_cast<std::uint32_t>(30);
            }
            return 0;
        }

        case category::choice:
        {
            const std::uint32_t total =
                std::accumulate(dice.begin(),
                                dice.end(),
                                static_cast<std::uint32_t>(0),
                                [](std::uint32_t sum, std::uint8_t value)
                                {
                                    return (sum + static_cast<std::uint32_t>(value));
                                });
            return total;
        }

        case category::yacht:
        {
            for (std::uint8_t face = 1U; face <= 6U; ++face)
            {
                if (counts[face] == 5U)
                {
                    return static_cast<std::uint32_t>(50);
                }
            }
            return 0;
        }

        default:
        {
            /* Should be unreachable; return zero as a safe fallback. */
            return 0;
        }
    }
}

/*  Convert a textual category into its enum representation. */
static auto to_category(std::string_view sv) -> category
{
    if (sv == "ones")
    {
        return category::ones;
    }
    else if (sv == "twos")
    {
        return category::twos;
    }
    else if (sv == "threes")
    {
        return category::threes;
    }
    else if (sv == "fours")
    {
        return category::fours;
    }
    else if (sv == "fives")
    {
        return category::fives;
    }
    else if (sv == "sixes")
    {
        return category::sixes;
    }
    else if (sv == "full house")
    {
        return category::full_house;
    }
    else if (sv == "four of a kind")
    {
        return category::four_of_a_kind;
    }
    else if (sv == "little straight")
    {
        return category::little_straight;
    }
    else if (sv == "big straight")
    {
        return category::big_straight;
    }
    else if (sv == "choice")
    {
        return category::choice;
    }
    else if (sv == "yacht")
    {
        return category::yacht;
    }
    else
    {
        return static_cast<category>(0U); /* Invalid string → zero score. */
    }
}

/*  Overload accepting the textual category names used by the tests. */
auto score(const std::array<std::uint8_t, 5U>& dice,
           std::string_view cat) -> std::uint32_t
{
    const category cat_enum = to_category(cat);
    return score(dice, cat_enum);
}

}  // namespace yacht
