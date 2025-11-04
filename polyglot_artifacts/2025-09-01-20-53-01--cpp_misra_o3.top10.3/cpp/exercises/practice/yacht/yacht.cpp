#include "yacht.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <string_view>
#include <initializer_list>

namespace yacht {

auto score(const DiceArray& dice, Category category) -> std::uint32_t
{
    // Frequency table: counts[index] holds how many dice show face (index + 1).
    std::array<std::uint8_t, 6U> counts {};
    for(const dice_value_t value : dice)
    {
        // Dice values are 1-6; convert to zero-based index.
        const std::uint8_t idx {
            static_cast<std::uint8_t>(
                static_cast<std::uint32_t>(value) - static_cast<std::uint32_t>(1U))
        };
        ++counts[idx];
    }

    // Helper lambda: sum of all dice.
    const auto total_sum =
        static_cast<std::uint32_t>(std::accumulate(dice.cbegin(),
                                                   dice.cend(),
                                                   static_cast<std::uint32_t>(0U)));

    // Determine score based on category.
    switch(category)
    {
        case Category::ones:
        case Category::twos:
        case Category::threes:
        case Category::fours:
        case Category::fives:
        case Category::sixes:
        {
            const std::uint8_t face { static_cast<std::uint8_t>(static_cast<std::uint8_t>(category) + static_cast<std::uint8_t>(1U)) };
            const std::uint32_t multiplier { static_cast<std::uint32_t>(face) };
            return static_cast<std::uint32_t>(counts[face - static_cast<std::uint8_t>(1U)]) * multiplier;
        }

        case Category::full_house:
        {
            bool has_three { false };
            bool has_two   { false };
            for(const std::uint8_t c : counts)
            {
                if(c == static_cast<std::uint8_t>(3U))
                {
                    has_three = true;
                }
                else if(c == static_cast<std::uint8_t>(2U))
                {
                    has_two = true;
                }
            }
            if(has_three && has_two)
            {
                return total_sum;
            }
            return static_cast<std::uint32_t>(0U);
        }

        case Category::four_of_a_kind:
        {
            for(std::size_t i { 0U }; i < counts.size(); ++i)
            {
                if(counts[i] >= static_cast<std::uint8_t>(4U))
                {
                    const std::uint32_t face { static_cast<std::uint32_t>(i + 1U) };
                    return face * static_cast<std::uint32_t>(4U);
                }
            }
            return static_cast<std::uint32_t>(0U);
        }

        case Category::little_straight:
        {
            const bool is_match { (counts[0U] == static_cast<std::uint8_t>(1U)) &&
                                  (counts[1U] == static_cast<std::uint8_t>(1U)) &&
                                  (counts[2U] == static_cast<std::uint8_t>(1U)) &&
                                  (counts[3U] == static_cast<std::uint8_t>(1U)) &&
                                  (counts[4U] == static_cast<std::uint8_t>(1U)) &&
                                  (counts[5U] == static_cast<std::uint8_t>(0U)) };
            return is_match ? static_cast<std::uint32_t>(30U) : static_cast<std::uint32_t>(0U);
        }

        case Category::big_straight:
        {
            const bool is_match { (counts[0U] == static_cast<std::uint8_t>(0U)) &&
                                  (counts[1U] == static_cast<std::uint8_t>(1U)) &&
                                  (counts[2U] == static_cast<std::uint8_t>(1U)) &&
                                  (counts[3U] == static_cast<std::uint8_t>(1U)) &&
                                  (counts[4U] == static_cast<std::uint8_t>(1U)) &&
                                  (counts[5U] == static_cast<std::uint8_t>(1U)) };
            return is_match ? static_cast<std::uint32_t>(30U) : static_cast<std::uint32_t>(0U);
        }

        case Category::choice:
        {
            return total_sum;
        }

        case Category::yacht:
        {
            for(const std::uint8_t c : counts)
            {
                if(c == static_cast<std::uint8_t>(5U))
                {
                    return static_cast<std::uint32_t>(50U);
                }
            }
            return static_cast<std::uint32_t>(0U);
        }

        default:
            // All enum values are handled; default is unreachable but included
            // to satisfy MISRA switch-exhaustiveness guidelines.
            return static_cast<std::uint32_t>(0U);
    }
}

static auto score(const DiceArray& dice, std::string_view category) -> std::uint32_t
{
    if(category == "ones")
    {
        return score(dice, Category::ones);
    }
    else if(category == "twos")
    {
        return score(dice, Category::twos);
    }
    else if(category == "threes")
    {
        return score(dice, Category::threes);
    }
    else if(category == "fours")
    {
        return score(dice, Category::fours);
    }
    else if(category == "fives")
    {
        return score(dice, Category::fives);
    }
    else if(category == "sixes")
    {
        return score(dice, Category::sixes);
    }
    else if(category == "full house")
    {
        return score(dice, Category::full_house);
    }
    else if(category == "four of a kind")
    {
        return score(dice, Category::four_of_a_kind);
    }
    else if(category == "little straight")
    {
        return score(dice, Category::little_straight);
    }
    else if(category == "big straight")
    {
        return score(dice, Category::big_straight);
    }
    else if(category == "choice")
    {
        return score(dice, Category::choice);
    }
    else if(category == "yacht")
    {
        return score(dice, Category::yacht);
    }
    else
    {
        return static_cast<std::uint32_t>(0U);
    }
}

auto score(std::initializer_list<dice_value_t> dice_list, Category category) -> std::uint32_t
{
    DiceArray dice {};
    std::size_t idx { 0U };
    for(const dice_value_t value : dice_list)
    {
        if(idx < dice.size())
        {
            dice[idx] = value;
            ++idx;
        }
    }
    return score(dice, category);
}

auto score(std::initializer_list<dice_value_t> dice_list, std::string_view category) -> std::uint32_t
{
    DiceArray dice {};
    std::size_t idx { 0U };
    for(const dice_value_t value : dice_list)
    {
        if(idx < dice.size())
        {
            dice[idx] = value;
            ++idx;
        }
    }
    return score(dice, category);
}

}  // namespace yacht
