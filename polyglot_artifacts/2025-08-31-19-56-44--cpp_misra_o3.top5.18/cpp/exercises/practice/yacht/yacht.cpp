#include "yacht.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

namespace yacht {

auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint32_t
{
    std::array<std::uint8_t, 7U> counts{};
    std::uint32_t total{0U};

    for (auto value : dice)
    {
        /* value is in range 1..6 by problem statement */
        ++counts[static_cast<std::size_t>(value)];
        total += static_cast<std::uint32_t>(value);
    }

    switch (cat)
    {
        case category::ones:
        {
            return static_cast<std::uint32_t>(counts[1U]) * 1U;
        }
        case category::twos:
        {
            return static_cast<std::uint32_t>(counts[2U]) * 2U;
        }
        case category::threes:
        {
            return static_cast<std::uint32_t>(counts[3U]) * 3U;
        }
        case category::fours:
        {
            return static_cast<std::uint32_t>(counts[4U]) * 4U;
        }
        case category::fives:
        {
            return static_cast<std::uint32_t>(counts[5U]) * 5U;
        }
        case category::sixes:
        {
            return static_cast<std::uint32_t>(counts[6U]) * 6U;
        }
        case category::full_house:
        {
            bool has_three{false};
            bool has_two{false};
            for (std::uint8_t face{1U}; face <= 6U; ++face)
            {
                auto const count_val{counts[static_cast<std::size_t>(face)]};
                if (static_cast<std::uint32_t>(count_val) == 3U)
                {
                    has_three = true;
                }
                else if (static_cast<std::uint32_t>(count_val) == 2U)
                {
                    has_two = true;
                }
            }
            if ((has_three) && (has_two))
            {
                return total;
            }
            return 0U;
        }
        case category::four_of_a_kind:
        {
            for (std::uint8_t face{1U}; face <= 6U; ++face)
            {
                if (static_cast<std::uint32_t>(counts[static_cast<std::size_t>(face)]) >= 4U)
                {
                    return static_cast<std::uint32_t>(face) * 4U;
                }
            }
            return 0U;
        }
        case category::little_straight:
        {
            if (   (static_cast<std::uint32_t>(counts[1U]) == 1U)
                && (static_cast<std::uint32_t>(counts[2U]) == 1U)
                && (static_cast<std::uint32_t>(counts[3U]) == 1U)
                && (static_cast<std::uint32_t>(counts[4U]) == 1U)
                && (static_cast<std::uint32_t>(counts[5U]) == 1U)
                && (static_cast<std::uint32_t>(counts[6U]) == 0U))
            {
                return 30U;
            }
            return 0U;
        }
        case category::big_straight:
        {
            if (   (static_cast<std::uint32_t>(counts[1U]) == 0U)
                && (static_cast<std::uint32_t>(counts[2U]) == 1U)
                && (static_cast<std::uint32_t>(counts[3U]) == 1U)
                && (static_cast<std::uint32_t>(counts[4U]) == 1U)
                && (static_cast<std::uint32_t>(counts[5U]) == 1U)
                && (static_cast<std::uint32_t>(counts[6U]) == 1U))
            {
                return 30U;
            }
            return 0U;
        }
        case category::choice:
        {
            return total;
        }
        case category::yacht:
        {
            for (auto count_value : counts)
            {
                if (static_cast<std::uint32_t>(count_value) == 5U)
                {
                    return 50U;
                }
            }
            return 0U;
        }
        default:
        {
            return 0U;
        }
    }
}

auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view cat_str) -> std::uint32_t
{
    category cat_enum{category::choice};

    if (cat_str == "ones")
    {
        cat_enum = category::ones;
    }
    else if (cat_str == "twos")
    {
        cat_enum = category::twos;
    }
    else if (cat_str == "threes")
    {
        cat_enum = category::threes;
    }
    else if (cat_str == "fours")
    {
        cat_enum = category::fours;
    }
    else if (cat_str == "fives")
    {
        cat_enum = category::fives;
    }
    else if (cat_str == "sixes")
    {
        cat_enum = category::sixes;
    }
    else if (cat_str == "full house")
    {
        cat_enum = category::full_house;
    }
    else if (cat_str == "four of a kind")
    {
        cat_enum = category::four_of_a_kind;
    }
    else if (cat_str == "little straight")
    {
        cat_enum = category::little_straight;
    }
    else if (cat_str == "big straight")
    {
        cat_enum = category::big_straight;
    }
    else if (cat_str == "choice")
    {
        cat_enum = category::choice;
    }
    else if (cat_str == "yacht")
    {
        cat_enum = category::yacht;
    }

    return score(dice, cat_enum);
}


}  // namespace yacht
