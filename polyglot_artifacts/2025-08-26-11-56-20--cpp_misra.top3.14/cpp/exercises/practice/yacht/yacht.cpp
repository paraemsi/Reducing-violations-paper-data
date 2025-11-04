#include "yacht.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <map>

namespace yacht {

namespace {
    // Helper: count occurrences of each die face (1-6)
    std::array<std::uint8_t, 6> count_faces(const DiceArray& dice)
    {
        std::array<std::uint8_t, 6> counts = {0, 0, 0, 0, 0, 0};
        for(const DieValue value : dice) {
            if((value >= 1U) && (value <= 6U)) {
                ++counts[static_cast<std::size_t>(value - 1U)];
            }
        }
        return counts;
    }
}

std::uint32_t score(const DiceArray& dice, Category category)
{
    const std::array<std::uint8_t, 6> counts = count_faces(dice);

    switch(category) {
        case Category::Ones:
            return (static_cast<std::uint32_t>(counts[0]) * 1U);
        case Category::Twos:
            return (static_cast<std::uint32_t>(counts[1]) * 2U);
        case Category::Threes:
            return (static_cast<std::uint32_t>(counts[2]) * 3U);
        case Category::Fours:
            return (static_cast<std::uint32_t>(counts[3]) * 4U);
        case Category::Fives:
            return (static_cast<std::uint32_t>(counts[4]) * 5U);
        case Category::Sixes:
            return (static_cast<std::uint32_t>(counts[5]) * 6U);
        case Category::FullHouse: {
            bool has_three = false;
            bool has_two = false;
            std::uint32_t total = 0U;
            for(std::size_t i = 0U; i < 6U; ++i) {
                if(counts[i] == 3U) {
                    has_three = true;
                }
                if(counts[i] == 2U) {
                    has_two = true;
                }
                total = (total + (static_cast<std::uint32_t>(counts[i]) * static_cast<std::uint32_t>(i + 1U)));
            }
            if(has_three && has_two) {
                return total;
            }
            return 0U;
        }
        case Category::FourOfAKind: {
            for(std::size_t i = 0U; i < 6U; ++i) {
                if(counts[i] >= 4U) {
                    return (static_cast<std::uint32_t>(i + 1U) * 4U);
                }
            }
            return 0U;
        }
        case Category::LittleStraight:
            // 1-2-3-4-5
            if((counts[0] == 1U) && (counts[1] == 1U) && (counts[2] == 1U) && (counts[3] == 1U) && (counts[4] == 1U)) {
                return 30U;
            }
            return 0U;
        case Category::BigStraight:
            // 2-3-4-5-6
            if((counts[1] == 1U) && (counts[2] == 1U) && (counts[3] == 1U) && (counts[4] == 1U) && (counts[5] == 1U)) {
                return 30U;
            }
            return 0U;
        case Category::Choice: {
            std::uint32_t total = 0U;
            for(std::size_t i = 0U; i < 5U; ++i) {
                total = (total + static_cast<std::uint32_t>(dice[i]));
            }
            return total;
        }
        case Category::Yacht:
            for(std::size_t i = 0U; i < 6U; ++i) {
                if(counts[i] == 5U) {
                    return 50U;
                }
            }
            return 0U;
        default:
            return 0U;
    }
}

std::uint32_t score(const DiceArray& dice, const char* category_name)
{
    // Map lower-case category names to enum values
    // Accepts both "full house" and "fullhouse", "four of a kind" and "fourofakind", etc.
    if(category_name == nullptr) {
        return 0U;
    }
    std::string name(category_name);
    // Remove spaces and convert to lower case
    name.erase(std::remove(name.begin(), name.end(), ' '), name.end());
    std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); });

    if(name == "ones") return score(dice, Category::Ones);
    if(name == "twos") return score(dice, Category::Twos);
    if(name == "threes") return score(dice, Category::Threes);
    if(name == "fours") return score(dice, Category::Fours);
    if(name == "fives") return score(dice, Category::Fives);
    if(name == "sixes") return score(dice, Category::Sixes);
    if(name == "fullhouse") return score(dice, Category::FullHouse);
    if(name == "fourofakind") return score(dice, Category::FourOfAKind);
    if(name == "littlestraight") return score(dice, Category::LittleStraight);
    if(name == "bigstraight") return score(dice, Category::BigStraight);
    if(name == "choice") return score(dice, Category::Choice);
    if(name == "yacht") return score(dice, Category::Yacht);

    // Unknown category
    return 0U;
}

}  // namespace yacht
