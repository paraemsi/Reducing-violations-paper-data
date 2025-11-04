#include "yacht.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <map>

namespace yacht {

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
            return (static_cast<std::uint32_t>(counts[face - 1U]) * static_cast<std::uint32_t>(face));
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
                    three_val = static_cast<std::uint8_t>(i + 1U);
                }
                else if(counts[i] == 2U)
                {
                    has_two = true;
                    two_val = static_cast<std::uint8_t>(i + 1U);
                }
            }
            if(has_three && has_two)
            {
                std::uint32_t sum = 0U;
                for(const DieValue value : dice)
                {
                    sum += static_cast<std::uint32_t>(value);
                }
                return sum;
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
            // 1,2,3,4,5
            for(std::uint8_t i = 0U; i < 5U; ++i)
            {
                if(counts[i] != 1U)
                {
                    return 0U;
                }
            }
            if(counts[5U] == 0U)
            {
                return 30U;
            }
            return 0U;
        }
        case Category::BigStraight:
        {
            // 2,3,4,5,6
            if(counts[0U] == 0U)
            {
                for(std::uint8_t i = 1U; i < 6U; ++i)
                {
                    if(counts[i] != 1U)
                    {
                        return 0U;
                    }
                }
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

std::uint32_t score(const Dice& dice, const char* category_name)
{
    // Map string to Category (case-insensitive, spaces ignored)
    // Accepts: "ones", "twos", ..., "full house", "four of a kind", "little straight", "big straight", "choice", "yacht"
    if(category_name == nullptr)
    {
        return 0U;
    }
    std::string s(category_name);
    // Remove spaces and convert to lower case
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); });

    if(s == "ones") return score(dice, Category::Ones);
    if(s == "twos") return score(dice, Category::Twos);
    if(s == "threes") return score(dice, Category::Threes);
    if(s == "fours") return score(dice, Category::Fours);
    if(s == "fives") return score(dice, Category::Fives);
    if(s == "sixes") return score(dice, Category::Sixes);
    if(s == "fullhouse") return score(dice, Category::FullHouse);
    if(s == "fourofakind") return score(dice, Category::FourOfAKind);
    if(s == "littlestraight") return score(dice, Category::LittleStraight);
    if(s == "bigstraight") return score(dice, Category::BigStraight);
    if(s == "choice") return score(dice, Category::Choice);
    if(s == "yacht") return score(dice, Category::Yacht);

    return 0U;
}

}  // namespace yacht
