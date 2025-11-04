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
            if((value >= static_cast<DieValue>(1)) && (value <= static_cast<DieValue>(6))) {
                ++counts[static_cast<std::size_t>(value) - 1U];
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
            return static_cast<std::uint32_t>(counts[0]) * static_cast<std::uint32_t>(1U);
        case Category::Twos:
            return static_cast<std::uint32_t>(counts[1]) * static_cast<std::uint32_t>(2U);
        case Category::Threes:
            return static_cast<std::uint32_t>(counts[2]) * static_cast<std::uint32_t>(3U);
        case Category::Fours:
            return static_cast<std::uint32_t>(counts[3]) * static_cast<std::uint32_t>(4U);
        case Category::Fives:
            return static_cast<std::uint32_t>(counts[4]) * static_cast<std::uint32_t>(5U);
        case Category::Sixes:
            return static_cast<std::uint32_t>(counts[5]) * static_cast<std::uint32_t>(6U);
        case Category::FullHouse: {
            bool has_three = false;
            bool has_two = false;
            std::uint32_t total = 0U;
            for(std::size_t i = 0U; i < counts.size(); ++i) {
                if(counts[i] == static_cast<std::uint8_t>(3U)) {
                    has_three = true;
                    total += static_cast<std::uint32_t>(counts[i]) * static_cast<std::uint32_t>(i + 1U);
                } else if(counts[i] == static_cast<std::uint8_t>(2U)) {
                    has_two = true;
                    total += static_cast<std::uint32_t>(counts[i]) * static_cast<std::uint32_t>(i + 1U);
                }
            }
            if(has_three && has_two) {
                return total;
            }
            return 0U;
        }
        case Category::FourOfAKind: {
            for(std::size_t i = 0U; i < counts.size(); ++i) {
                if(counts[i] >= static_cast<std::uint8_t>(4U)) {
                    return static_cast<std::uint32_t>(4U) * static_cast<std::uint32_t>(i + 1U);
                }
            }
            return 0U;
        }
        case Category::LittleStraight: {
            // 1-2-3-4-5
            if((counts[0] == static_cast<std::uint8_t>(1U)) &&
               (counts[1] == static_cast<std::uint8_t>(1U)) &&
               (counts[2] == static_cast<std::uint8_t>(1U)) &&
               (counts[3] == static_cast<std::uint8_t>(1U)) &&
               (counts[4] == static_cast<std::uint8_t>(1U)) &&
               (counts[5] == static_cast<std::uint8_t>(0U))) {
                return 30U;
            }
            return 0U;
        }
        case Category::BigStraight: {
            // 2-3-4-5-6
            if((counts[0] == static_cast<std::uint8_t>(0U)) &&
               (counts[1] == static_cast<std::uint8_t>(1U)) &&
               (counts[2] == static_cast<std::uint8_t>(1U)) &&
               (counts[3] == static_cast<std::uint8_t>(1U)) &&
               (counts[4] == static_cast<std::uint8_t>(1U)) &&
               (counts[5] == static_cast<std::uint8_t>(1U))) {
                return 30U;
            }
            return 0U;
        }
        case Category::Choice: {
            std::uint32_t sum = 0U;
            for(const DieValue value : dice) {
                sum += static_cast<std::uint32_t>(value);
            }
            return sum;
        }
        case Category::Yacht: {
            for(std::size_t i = 0U; i < counts.size(); ++i) {
                if(counts[i] == static_cast<std::uint8_t>(5U)) {
                    return 50U;
                }
            }
            return 0U;
        }
        default:
            return 0U;
    }
}

std::uint32_t score(const DiceArray& dice, const char* category)
{
    // Map lower-case string to Category
    // Accepts: "ones", "twos", ..., "full house", "four of a kind", "little straight", "big straight", "choice", "yacht"
    if(category == nullptr) {
        return 0U;
    }
    std::string catstr(category);
    // Remove spaces and convert to lower case for matching
    std::string s;
    for(char c : catstr) {
        if(c != ' ') {
            s += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
    }
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
