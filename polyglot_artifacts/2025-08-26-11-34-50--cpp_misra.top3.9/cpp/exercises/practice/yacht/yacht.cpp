#include "yacht.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>

namespace yacht {

std::uint32_t score(const Dice& dice, Category category)
{
    // Count occurrences of each die face (1-6)
    std::array<std::uint8_t, 6U> counts = {0U, 0U, 0U, 0U, 0U, 0U};
    for(const Die d : dice)
    {
        if((d >= 1U) && (d <= 6U))
        {
            ++counts[d - 1U];
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
            std::uint32_t total = 0U;
            for(std::uint8_t i = 0U; i < 6U; ++i)
            {
                if(counts[i] == 3U)
                {
                    has_three = true;
                }
                else if(counts[i] == 2U)
                {
                    has_two = true;
                }
            }
            if(has_three && has_two)
            {
                for(const Die d : dice)
                {
                    total += static_cast<std::uint32_t>(d);
                }
                return total;
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
            if((counts[0U] == 1U) && (counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) && (counts[4U] == 1U))
            {
                return 30U;
            }
            return 0U;
        }
        case Category::BigStraight:
        {
            // 2-3-4-5-6
            if((counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) && (counts[4U] == 1U) && (counts[5U] == 1U))
            {
                return 30U;
            }
            return 0U;
        }
        case Category::Choice:
        {
            std::uint32_t total = 0U;
            for(const Die d : dice)
            {
                total += static_cast<std::uint32_t>(d);
            }
            return total;
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

Category parse_category(const char* name)
{
    // Accepts lower case, with or without spaces/underscores
    // e.g. "yacht", "ones", "full house", "big straight"
    if(name == nullptr)
    {
        return Category::Yacht; // fallback, will always score 0
    }
    std::string s(name);
    // Remove underscores
    s.erase(std::remove(s.begin(), s.end(), '_'), s.end());
    // Convert to lower case
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); });

    if(s == "yacht") return Category::Yacht;
    if(s == "ones") return Category::Ones;
    if(s == "twos") return Category::Twos;
    if(s == "threes") return Category::Threes;
    if(s == "fours") return Category::Fours;
    if(s == "fives") return Category::Fives;
    if(s == "sixes") return Category::Sixes;
    if(s == "fullhouse" || s == "full house") return Category::FullHouse;
    if(s == "fourofakind" || s == "four of a kind") return Category::FourOfAKind;
    if(s == "littlestraight" || s == "little straight") return Category::LittleStraight;
    if(s == "bigstraight" || s == "big straight") return Category::BigStraight;
    if(s == "choice") return Category::Choice;
    // fallback: treat as Yacht, will always score 0
    return Category::Yacht;
}

std::uint32_t score(const Dice& dice, const char* category_name)
{
    return score(dice, parse_category(category_name));
}

}  // namespace yacht
