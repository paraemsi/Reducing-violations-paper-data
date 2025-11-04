#include "yacht.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <map>

namespace yacht {

// Helper function to map string to Category
Category category_from_string(const char* category_name)
{
    // Use only lowercase and exact match as per test cases
    if(category_name == nullptr)
    {
        return Category::Choice; // fallback, shouldn't happen
    }
    // Single word categories
    if(std::strcmp(category_name, "ones") == 0)
    {
        return Category::Ones;
    }
    if(std::strcmp(category_name, "twos") == 0)
    {
        return Category::Twos;
    }
    if(std::strcmp(category_name, "threes") == 0)
    {
        return Category::Threes;
    }
    if(std::strcmp(category_name, "fours") == 0)
    {
        return Category::Fours;
    }
    if(std::strcmp(category_name, "fives") == 0)
    {
        return Category::Fives;
    }
    if(std::strcmp(category_name, "sixes") == 0)
    {
        return Category::Sixes;
    }
    if(std::strcmp(category_name, "choice") == 0)
    {
        return Category::Choice;
    }
    if(std::strcmp(category_name, "yacht") == 0)
    {
        return Category::Yacht;
    }
    // Multi-word categories
    if(std::strcmp(category_name, "full house") == 0)
    {
        return Category::FullHouse;
    }
    if(std::strcmp(category_name, "four of a kind") == 0)
    {
        return Category::FourOfAKind;
    }
    if(std::strcmp(category_name, "little straight") == 0)
    {
        return Category::LittleStraight;
    }
    if(std::strcmp(category_name, "big straight") == 0)
    {
        return Category::BigStraight;
    }
    // fallback
    return Category::Choice;
}

std::uint32_t score(const Dice& dice, const char* category_name)
{
    return score(dice, category_from_string(category_name));
}

std::uint32_t score(const Dice& dice, Category category)
{
    // Count occurrences of each die face (1-6)
    std::array<std::uint8_t, 6U> counts = {0U, 0U, 0U, 0U, 0U, 0U};
    for(const DieValue value : dice)
    {
        if((value >= 1U) && (value <= 6U))
        {
            ++counts[static_cast<std::size_t>(value - 1U)];
        }
    }

    switch(category)
    {
        case Category::Ones:
        case Category::Twos:
        case Category::Threes:
        case Category::Fours:
        case Category::Fives:
        case Category::Sixes:
        {
            std::uint8_t face = static_cast<std::uint8_t>(category) + 1U;
            return (static_cast<std::uint32_t>(face) * static_cast<std::uint32_t>(counts[face - 1U]));
        }
        case Category::FullHouse:
        {
            bool has_three = false;
            bool has_two = false;
            std::uint8_t three_val = 0U;
            std::uint8_t two_val = 0U;
            for(std::uint8_t i = 0U; i < 6U; ++i)
            {
                if(counts[i] == 3U)
                {
                    has_three = true;
                    three_val = i + 1U;
                }
                else if(counts[i] == 2U)
                {
                    has_two = true;
                    two_val = i + 1U;
                }
            }
            if(has_three && has_two)
            {
                return (static_cast<std::uint32_t>(three_val) * 3U) + (static_cast<std::uint32_t>(two_val) * 2U);
            }
            return 0U;
        }
        case Category::FourOfAKind:
        {
            for(std::uint8_t i = 0U; i < 6U; ++i)
            {
                if(counts[i] >= 4U)
                {
                    return (static_cast<std::uint32_t>(i + 1U) * 4U);
                }
            }
            return 0U;
        }
        case Category::LittleStraight:
        {
            // 1-2-3-4-5
            if((counts[0] == 1U) && (counts[1] == 1U) && (counts[2] == 1U) && (counts[3] == 1U) && (counts[4] == 1U))
            {
                return 30U;
            }
            return 0U;
        }
        case Category::BigStraight:
        {
            // 2-3-4-5-6
            if((counts[1] == 1U) && (counts[2] == 1U) && (counts[3] == 1U) && (counts[4] == 1U) && (counts[5] == 1U))
            {
                return 30U;
            }
            return 0U;
        }
        case Category::Choice:
        {
            std::uint32_t sum = 0U;
            for(const DieValue value : dice)
            {
                sum += static_cast<std::uint32_t>(value);
            }
            return sum;
        }
        case Category::Yacht:
        {
            for(std::uint8_t i = 0U; i < 6U; ++i)
            {
                if(counts[i] == 5U)
                {
                    return 50U;
                }
            }
            return 0U;
        }
        default:
            return 0U;
    }
}

}  // namespace yacht
