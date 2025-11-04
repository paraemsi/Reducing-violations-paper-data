#include "yacht.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>

namespace yacht {

namespace
{
    using CountArray = std::array<std::uint8_t, 6U>;

    auto count_faces(const Dice& dice) -> CountArray
    {
        CountArray counts = {0U, 0U, 0U, 0U, 0U, 0U};
        for(const auto die : dice)
        {
            if((die >= 1U) && (die <= 6U))
            {
                ++counts[static_cast<std::size_t>(die - 1U)];
            }
        }
        return counts;
    }
}

auto score(const Dice& dice, Category category) -> std::uint32_t
{
    const CountArray counts = count_faces(dice);

    switch(category)
    {
        case Category::Ones:
            return (1U * static_cast<std::uint32_t>(counts[0U]));
        case Category::Twos:
            return (2U * static_cast<std::uint32_t>(counts[1U]));
        case Category::Threes:
            return (3U * static_cast<std::uint32_t>(counts[2U]));
        case Category::Fours:
            return (4U * static_cast<std::uint32_t>(counts[3U]));
        case Category::Fives:
            return (5U * static_cast<std::uint32_t>(counts[4U]));
        case Category::Sixes:
            return (6U * static_cast<std::uint32_t>(counts[5U]));
        case Category::FullHouse:
        {
            bool has_three = false;
            bool has_two = false;
            std::uint32_t total = 0U;
            for(std::size_t i = 0U; i < 6U; ++i)
            {
                if(counts[i] == 3U)
                {
                    has_three = true;
                    total += static_cast<std::uint32_t>((i + 1U) * 3U);
                }
                else if(counts[i] == 2U)
                {
                    has_two = true;
                    total += static_cast<std::uint32_t>((i + 1U) * 2U);
                }
            }
            if(has_three && has_two)
            {
                return total;
            }
            return 0U;
        }
        case Category::FourOfAKind:
        {
            for(std::size_t i = 0U; i < 6U; ++i)
            {
                if(counts[i] >= 4U)
                {
                    return static_cast<std::uint32_t>((i + 1U) * 4U);
                }
            }
            return 0U;
        }
        case Category::LittleStraight:
            if((counts[0U] == 1U) && (counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) && (counts[4U] == 1U))
            {
                return 30U;
            }
            return 0U;
        case Category::BigStraight:
            if((counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) && (counts[4U] == 1U) && (counts[5U] == 1U))
            {
                return 30U;
            }
            return 0U;
        case Category::Choice:
            return std::accumulate(dice.begin(), dice.end(), 0U, [](std::uint32_t sum, Die d) { return (sum + static_cast<std::uint32_t>(d)); });
        case Category::Yacht:
            for(std::size_t i = 0U; i < 6U; ++i)
            {
                if(counts[i] == 5U)
                {
                    return 50U;
                }
            }
            return 0U;
        default:
            return 0U;
    }
}

auto yacht::score(const Dice& dice, const char* category) -> std::uint32_t
{
    // Map lower-case and space-insensitive category strings to enum
    // Accepts: "ones", "twos", ..., "full house", "four of a kind", etc.
    if(category == nullptr)
    {
        return 0U;
    }
    std::string cat{category};
    // Remove spaces and convert to lower case
    cat.erase(std::remove(cat.begin(), cat.end(), ' '), cat.end());
    std::transform(cat.begin(), cat.end(), cat.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); });

    if(cat == "ones") return score(dice, Category::Ones);
    if(cat == "twos") return score(dice, Category::Twos);
    if(cat == "threes") return score(dice, Category::Threes);
    if(cat == "fours") return score(dice, Category::Fours);
    if(cat == "fives") return score(dice, Category::Fives);
    if(cat == "sixes") return score(dice, Category::Sixes);
    if(cat == "fullhouse") return score(dice, Category::FullHouse);
    if(cat == "fourofakind") return score(dice, Category::FourOfAKind);
    if(cat == "littlestraight") return score(dice, Category::LittleStraight);
    if(cat == "bigstraight") return score(dice, Category::BigStraight);
    if(cat == "choice") return score(dice, Category::Choice);
    if(cat == "yacht") return score(dice, Category::Yacht);

    return 0U;
}

}  // namespace yacht
