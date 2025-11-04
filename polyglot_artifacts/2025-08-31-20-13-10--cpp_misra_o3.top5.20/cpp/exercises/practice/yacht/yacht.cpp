#include "yacht.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <cstddef>
#include <string_view>

namespace yacht {

/* Helper: frequency count of dice faces 1-6 */
static auto get_frequencies(const std::vector<dice_value_t>& dice)
    -> std::array<std::uint8_t, 6U>
{
    std::array<std::uint8_t, 6U> freq { };
    for(const dice_value_t value : dice)
    {
        /* index is (value − 1); dice values guaranteed 1-6 */
        freq.at(static_cast<std::size_t>(value - static_cast<dice_value_t>(1U)))++;
    }
    return freq;
}

/* Map external string names used by the tests to the internal Category enum */
static auto to_category(std::string_view name) -> Category
{
    if(name == "ones")
    {
        return Category::ones;
    }
    else if(name == "twos")
    {
        return Category::twos;
    }
    else if(name == "threes")
    {
        return Category::threes;
    }
    else if(name == "fours")
    {
        return Category::fours;
    }
    else if(name == "fives")
    {
        return Category::fives;
    }
    else if(name == "sixes")
    {
        return Category::sixes;
    }
    else if(name == "full house")
    {
        return Category::full_house;
    }
    else if(name == "four of a kind")
    {
        return Category::four_of_a_kind;
    }
    else if(name == "little straight")
    {
        return Category::little_straight;
    }
    else if(name == "big straight")
    {
        return Category::big_straight;
    }
    else if(name == "choice")
    {
        return Category::choice;
    }
    else /* default to "yacht" */
    {
        return Category::yacht;
    }
}

/* Public convenience overload expected by the tests */
auto score(const std::vector<dice_value_t>& dice, std::string_view category) -> score_t
{
    return score(dice, to_category(category));
}

auto score(const std::vector<dice_value_t>& dice, Category category) -> score_t
{
    /* Expect exactly five dice; behaviour is undefined otherwise */
    const std::array<std::uint8_t, 6U> freq { get_frequencies(dice) };

    switch(category)
    {
        case Category::ones:
        case Category::twos:
        case Category::threes:
        case Category::fours:
        case Category::fives:
        case Category::sixes:
        {
            const dice_value_t face { static_cast<dice_value_t>(static_cast<std::uint8_t>(category) + static_cast<std::uint8_t>(1U)) };
            return static_cast<score_t>(face * static_cast<dice_value_t>(freq.at(static_cast<std::size_t>(face - static_cast<dice_value_t>(1U)))) );
        }

        case Category::full_house:
        {
            bool has_three { false };
            bool has_two   { false };
            for(const std::uint8_t f : freq)
            {
                if(f == static_cast<std::uint8_t>(3U))
                {
                    has_three = true;
                }
                else if(f == static_cast<std::uint8_t>(2U))
                {
                    has_two = true;
                }
            }
            if(has_three && has_two)
            {
                return static_cast<score_t>(std::accumulate(dice.cbegin(), dice.cend(), static_cast<dice_value_t>(0U)));
            }
            return static_cast<score_t>(0U);
        }

        case Category::four_of_a_kind:
        {
            for(std::size_t i = 0U; i < freq.size(); ++i)
            {
                if(freq.at(i) >= static_cast<std::uint8_t>(4U))
                {
                    const dice_value_t face { static_cast<dice_value_t>(i + 1U) };
                    return static_cast<score_t>(face * static_cast<dice_value_t>(4U));
                }
            }
            return static_cast<score_t>(0U);
        }

        case Category::little_straight:
        {
            const bool is_little { std::equal(freq.cbegin(), freq.cbegin() + 5U,
                                               std::array<std::uint8_t, 5U>{1U, 1U, 1U, 1U, 1U}.cbegin()) &&
                                   (freq.at(5U) == static_cast<std::uint8_t>(0U)) };
            return is_little ? static_cast<score_t>(30U) : static_cast<score_t>(0U);
        }

        case Category::big_straight:
        {
            const bool is_big { (freq.at(0U) == static_cast<std::uint8_t>(0U)) &&
                                std::equal(freq.cbegin() + 1U, freq.cend(),
                                           std::array<std::uint8_t, 5U>{1U, 1U, 1U, 1U, 1U}.cbegin()) };
            return is_big ? static_cast<score_t>(30U) : static_cast<score_t>(0U);
        }

        case Category::choice:
        {
            return static_cast<score_t>(std::accumulate(dice.cbegin(), dice.cend(), static_cast<dice_value_t>(0U)));
        }

        case Category::yacht:
        {
            for(const std::uint8_t f : freq)
            {
                if(f == static_cast<std::uint8_t>(5U))
                {
                    return static_cast<score_t>(50U);
                }
            }
            return static_cast<score_t>(0U);
        }

        default:
        {
            /* Unreachable with current enum values */
            return static_cast<score_t>(0U);
        }
    }
}

}  // namespace yacht
