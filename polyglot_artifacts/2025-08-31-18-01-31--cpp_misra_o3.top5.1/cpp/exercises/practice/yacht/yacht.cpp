#include "yacht.h"

#include <algorithm>
#include <numeric>
#include <cstddef>  // for std::size_t
#include <string_view>
#include <initializer_list>

namespace yacht {

/* Count how many times a particular face value appears in the dice set */
static auto count_die(const std::array<std::int32_t, 5>& dice,
                      std::int32_t                          value) -> std::int32_t
{
    return static_cast<std::int32_t>(std::count(dice.begin(), dice.end(), value));
}

/* Determine whether all dice show the same face value */
static auto is_yacht(const std::array<std::int32_t, 5>& dice) -> bool
{
    return (count_die(dice, dice[0]) == static_cast<std::int32_t>(5));
}

auto score(const std::array<std::int32_t, 5>& dice, category cat) -> std::int32_t
{
    switch (cat)
    {
        case category::ones:
            return (count_die(dice, static_cast<std::int32_t>(1)) * static_cast<std::int32_t>(1));

        case category::twos:
            return (count_die(dice, static_cast<std::int32_t>(2)) * static_cast<std::int32_t>(2));

        case category::threes:
            return (count_die(dice, static_cast<std::int32_t>(3)) * static_cast<std::int32_t>(3));

        case category::fours:
            return (count_die(dice, static_cast<std::int32_t>(4)) * static_cast<std::int32_t>(4));

        case category::fives:
            return (count_die(dice, static_cast<std::int32_t>(5)) * static_cast<std::int32_t>(5));

        case category::sixes:
            return (count_die(dice, static_cast<std::int32_t>(6)) * static_cast<std::int32_t>(6));

        case category::full_house:
        {
            /* Count each face (indices 1-6) */
            std::array<std::int32_t, 7> counts{};
            for (auto v : dice)
            {
                ++counts[static_cast<std::size_t>(v)];
            }

            bool has_three {false};
            bool has_two   {false};

            for (std::int32_t i = 1; i <= static_cast<std::int32_t>(6); ++i)
            {
                if (counts[static_cast<std::size_t>(i)] == static_cast<std::int32_t>(3))
                {
                    has_three = true;
                }
                else if (counts[static_cast<std::size_t>(i)] == static_cast<std::int32_t>(2))
                {
                    has_two = true;
                }
            }

            if (has_three && has_two)
            {
                return static_cast<std::int32_t>(
                    std::accumulate(dice.begin(), dice.end(), static_cast<std::int32_t>(0)));
            }
            return static_cast<std::int32_t>(0);
        }

        case category::four_of_a_kind:
        {
            for (std::int32_t face = static_cast<std::int32_t>(1);
                 face <= static_cast<std::int32_t>(6);
                 ++face)
            {
                if (count_die(dice, face) >= static_cast<std::int32_t>(4))
                {
                    return (face * static_cast<std::int32_t>(4));
                }
            }
            return static_cast<std::int32_t>(0);
        }

        case category::little_straight:
        {
            const std::array<std::int32_t, 5> target {1, 2, 3, 4, 5};
            auto                              sorted {dice};
            std::sort(sorted.begin(), sorted.end());
            return ((sorted == target) ? static_cast<std::int32_t>(30) : static_cast<std::int32_t>(0));
        }

        case category::big_straight:
        {
            const std::array<std::int32_t, 5> target {2, 3, 4, 5, 6};
            auto                              sorted {dice};
            std::sort(sorted.begin(), sorted.end());
            return ((sorted == target) ? static_cast<std::int32_t>(30) : static_cast<std::int32_t>(0));
        }

        case category::choice:
            return static_cast<std::int32_t>(
                std::accumulate(dice.begin(), dice.end(), static_cast<std::int32_t>(0)));

        case category::yacht:
            return (is_yacht(dice) ? static_cast<std::int32_t>(50) : static_cast<std::int32_t>(0));

        default:
            /* Defensive default: zero score */
            return static_cast<std::int32_t>(0);
    }
}

/* Translate the textual category names provided by the Exercism
 * tests into the strongly-typed enumeration.
 */
static auto to_category(std::string_view name) -> category
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
    /* Defensive fallback */
    return category::choice;
}

/* Helper to transform an initializer_list into the fixed-size dice array. */
static auto to_array(const std::initializer_list<std::int32_t>& dice_il) -> std::array<std::int32_t, 5>
{
    std::array<std::int32_t, 5> result {};
    if (dice_il.size() == static_cast<std::size_t>(5))
    {
        auto it {dice_il.begin()};
        for (std::size_t idx = 0U; idx < static_cast<std::size_t>(5); ++idx, ++it)
        {
            result[idx] = static_cast<std::int32_t>(*it);
        }
    }
    return result;
}

auto score(const std::array<std::int32_t, 5>& dice, std::string_view cat) -> std::int32_t
{
    return score(dice, to_category(cat));
}

auto score(const std::initializer_list<std::int32_t>& dice_il, category cat) -> std::int32_t
{
    return score(to_array(dice_il), cat);
}

auto score(const std::initializer_list<std::int32_t>& dice_il, std::string_view cat) -> std::int32_t
{
    return score(to_array(dice_il), to_category(cat));
}

}  // namespace yacht
