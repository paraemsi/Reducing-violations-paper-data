#include "yacht.h"

#include <algorithm>
#include <numeric>
#include <vector>
#include <cstddef>
#include <string_view>

namespace yacht {

/* Helper: count occurrences of each face (index 1-6) */
static auto make_histogram(const std::array<DieValue, 5U>& dice) -> std::array<std::uint8_t, 7U>
{
    std::array<std::uint8_t, 7U> counts{};           /* element [0] left unused  */
    for(const DieValue face : dice)
    {
        /* face is in the range 1-6 per problem statement */
        ++counts[static_cast<std::size_t>(face)];
    }
    return counts;
}

/*---------------------------------------------------------------------------*/
/*  Convert text category name used by tests into the Category enumeration   */
/*---------------------------------------------------------------------------*/
static auto parse_category(std::string_view name) -> Category
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
    else /* name == "yacht" */
    {
        return Category::yacht;
    }
}

auto score(const std::array<DieValue, 5U>& dice, Category category) -> Score
{
    const auto counts = make_histogram(dice);

    switch(category)
    {
        case Category::ones:
        {
            return static_cast<Score>(counts[1U]) * static_cast<Score>(1U);
        }
        case Category::twos:
        {
            return static_cast<Score>(counts[2U]) * static_cast<Score>(2U);
        }
        case Category::threes:
        {
            return static_cast<Score>(counts[3U]) * static_cast<Score>(3U);
        }
        case Category::fours:
        {
            return static_cast<Score>(counts[4U]) * static_cast<Score>(4U);
        }
        case Category::fives:
        {
            return static_cast<Score>(counts[5U]) * static_cast<Score>(5U);
        }
        case Category::sixes:
        {
            return static_cast<Score>(counts[6U]) * static_cast<Score>(6U);
        }
        case Category::full_house:
        {
            bool has_three {false};
            bool has_two   {false};

            for(std::size_t i {1U}; i <= 6U; ++i)
            {
                if(counts[i] == static_cast<std::uint8_t>(3U))
                {
                    has_three = true;
                }
                else if(counts[i] == static_cast<std::uint8_t>(2U))
                {
                    has_two = true;
                }
            }

            if(has_three && has_two)
            {
                /* sum of all dice */
                const Score total = std::accumulate(dice.begin(),
                                                    dice.end(),
                                                    static_cast<Score>(0U),
                                                    [](Score acc, DieValue v)
                                                    {
                                                        return acc + static_cast<Score>(v);
                                                    });
                return total;
            }
            return static_cast<Score>(0U);
        }
        case Category::four_of_a_kind:
        {
            for(std::size_t i {1U}; i <= 6U; ++i)
            {
                if(counts[i] >= static_cast<std::uint8_t>(4U))
                {
                    return static_cast<Score>(i) * static_cast<Score>(4U);
                }
            }
            return static_cast<Score>(0U);
        }
        case Category::little_straight:
        {
            if((counts[1U] == static_cast<std::uint8_t>(1U)) &&
               (counts[2U] == static_cast<std::uint8_t>(1U)) &&
               (counts[3U] == static_cast<std::uint8_t>(1U)) &&
               (counts[4U] == static_cast<std::uint8_t>(1U)) &&
               (counts[5U] == static_cast<std::uint8_t>(1U)) &&
               (counts[6U] == static_cast<std::uint8_t>(0U)))
            {
                return static_cast<Score>(30U);
            }
            return static_cast<Score>(0U);
        }
        case Category::big_straight:
        {
            if((counts[1U] == static_cast<std::uint8_t>(0U)) &&
               (counts[2U] == static_cast<std::uint8_t>(1U)) &&
               (counts[3U] == static_cast<std::uint8_t>(1U)) &&
               (counts[4U] == static_cast<std::uint8_t>(1U)) &&
               (counts[5U] == static_cast<std::uint8_t>(1U)) &&
               (counts[6U] == static_cast<std::uint8_t>(1U)))
            {
                return static_cast<Score>(30U);
            }
            return static_cast<Score>(0U);
        }
        case Category::choice:
        {
            const Score total = std::accumulate(dice.begin(),
                                                dice.end(),
                                                static_cast<Score>(0U),
                                                [](Score acc, DieValue v)
                                                {
                                                    return acc + static_cast<Score>(v);
                                                });
            return total;
        }
        case Category::yacht:
        {
            for(std::size_t i {1U}; i <= 6U; ++i)
            {
                if(counts[i] == static_cast<std::uint8_t>(5U))
                {
                    return static_cast<Score>(50U);
                }
            }
            return static_cast<Score>(0U);
        }
        /* default cannot be reached but silences compiler warnings */
        default:
        {
            return static_cast<Score>(0U);
        }
    }
}

/*---------------------------------------------------------------------------*/
/*  Convenience overload matching the original Exercism test signature       */
/*---------------------------------------------------------------------------*/
auto score(const std::vector<int>& dice, Category category) -> Score
{
    /* Pre-condition: dice.size() should be 5U */
    std::array<DieValue, 5U> arr{};
    for(std::size_t i {0U}; i < 5U; ++i)
    {
        arr[i] = static_cast<DieValue>(dice.at(i));
    }
    return score(arr, category);
}

/*---------------------------------------------------------------------------*/
/*  Public overloads that accept the category as text                         */
/*---------------------------------------------------------------------------*/
auto score(const std::array<DieValue, 5U>& dice, std::string_view category) -> Score
{
    return score(dice, parse_category(category));
}

auto score(const std::vector<int>& dice, std::string_view category) -> Score
{
    return score(dice, parse_category(category));
}

/*  C-string overloads are now provided as inline functions in the header   */

}  // namespace yacht
