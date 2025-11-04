#include "yacht.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <map>

namespace yacht {

namespace
{
    // Helper: count occurrences of each die face (1-6)
    std::array<std::uint8_t, 6U> count_faces(const Dice& dice)
    {
        std::array<std::uint8_t, 6U> counts = {0U, 0U, 0U, 0U, 0U, 0U};
        for(const DieValue value : dice)
        {
            if((value >= 1U) && (value <= 6U))
            {
                ++counts[static_cast<std::size_t>(value - 1U)];
            }
        }
        return counts;
    }
}

std::uint32_t score(const Dice& dice, Category category)
{
    const std::array<std::uint8_t, 6U> counts = count_faces(dice);

    switch(category)
    {
        case Category::Ones:
        case Category::Twos:
        case Category::Threes:
        case Category::Fours:
        case Category::Fives:
        case Category::Sixes:
        {
            const std::uint8_t face = static_cast<std::uint8_t>(category) + 1U;
            return (static_cast<std::uint32_t>(face) * static_cast<std::uint32_t>(counts[face - 1U]));
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
                total += (static_cast<std::uint32_t>(counts[i]) * static_cast<std::uint32_t>(i + 1U));
            }
            if(has_three && has_two)
            {
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
            std::uint32_t total = 0U;
            for(std::uint8_t i = 0U; i < 6U; ++i)
            {
                total += (static_cast<std::uint32_t>(counts[i]) * static_cast<std::uint32_t>(i + 1U));
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

ScoreType score(const Dice& dice, const char* category)
{
    // Map lower-case string to Category
    // Accepts: "ones", "twos", ..., "sixes", "full house", "four of a kind", "little straight", "big straight", "choice", "yacht"
    if(category == nullptr)
    {
        return 0U;
    }
    std::string cat_str(category);
    // Remove spaces and convert to lower case for matching
    std::string cat_trim;
    for(char c : cat_str)
    {
        if((c >= 'A') && (c <= 'Z'))
        {
            cat_trim += static_cast<char>(c + ('a' - 'A'));
        }
        else if(c != ' ')
        {
            cat_trim += c;
        }
    }

    if(cat_trim == "ones") return score(dice, Category::Ones);
    if(cat_trim == "twos") return score(dice, Category::Twos);
    if(cat_trim == "threes") return score(dice, Category::Threes);
    if(cat_trim == "fours") return score(dice, Category::Fours);
    if(cat_trim == "fives") return score(dice, Category::Fives);
    if(cat_trim == "sixes") return score(dice, Category::Sixes);
    if(cat_trim == "fullhouse") return score(dice, Category::FullHouse);
    if(cat_trim == "fourofakind") return score(dice, Category::FourOfAKind);
    if(cat_trim == "littlestraight") return score(dice, Category::LittleStraight);
    if(cat_trim == "bigstraight") return score(dice, Category::BigStraight);
    if(cat_trim == "choice") return score(dice, Category::Choice);
    if(cat_trim == "yacht") return score(dice, Category::Yacht);

    // If not recognized, return 0
    return 0U;
}

}  // namespace yacht
