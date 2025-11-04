#include "yacht.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <map>

namespace yacht {

std::uint32_t score(const DiceArray& dice, Category category)
{
    // Count occurrences of each die face (1-6)
    std::array<std::uint8_t, 6> counts = {0, 0, 0, 0, 0, 0};
    for(const DieValue die : dice) {
        if((die >= static_cast<DieValue>(1)) && (die <= static_cast<DieValue>(6))) {
            ++counts[static_cast<std::size_t>(die) - 1U];
        }
    }

    switch(category) {
        case Category::Ones:
        case Category::Twos:
        case Category::Threes:
        case Category::Fours:
        case Category::Fives:
        case Category::Sixes:
        {
            // Category index is 0 for Ones, 1 for Twos, etc.
            std::uint8_t idx = static_cast<std::uint8_t>(category);
            return static_cast<std::uint32_t>((idx + 1U) * counts[idx]);
        }
        case Category::FullHouse:
        {
            bool has_three = false;
            bool has_two = false;
            std::uint8_t three_val = 0U;
            std::uint8_t two_val = 0U;
            for(std::uint8_t i = 0U; i < 6U; ++i) {
                if(counts[i] == 3U) {
                    has_three = true;
                    three_val = i + 1U;
                } else if(counts[i] == 2U) {
                    has_two = true;
                    two_val = i + 1U;
                }
            }
            if(has_three && has_two) {
                return static_cast<std::uint32_t>((three_val * 3U) + (two_val * 2U));
            }
            return 0U;
        }
        case Category::FourOfAKind:
        {
            for(std::uint8_t i = 0U; i < 6U; ++i) {
                if(counts[i] >= 4U) {
                    return static_cast<std::uint32_t>((i + 1U) * 4U);
                }
            }
            return 0U;
        }
        case Category::LittleStraight:
        {
            // 1-2-3-4-5
            if((counts[0] == 1U) && (counts[1] == 1U) && (counts[2] == 1U) && (counts[3] == 1U) && (counts[4] == 1U)) {
                return 30U;
            }
            return 0U;
        }
        case Category::BigStraight:
        {
            // 2-3-4-5-6
            if((counts[1] == 1U) && (counts[2] == 1U) && (counts[3] == 1U) && (counts[4] == 1U) && (counts[5] == 1U)) {
                return 30U;
            }
            return 0U;
        }
        case Category::Choice:
        {
            std::uint32_t sum = 0U;
            for(const DieValue die : dice) {
                sum += die;
            }
            return sum;
        }
        case Category::Yacht:
        {
            for(std::uint8_t i = 0U; i < 6U; ++i) {
                if(counts[i] == 5U) {
                    return 50U;
                }
            }
            return 0U;
        }
        default:
            return 0U;
    }
}

std::uint32_t score(const DiceArray& dice, const char* category_name)
{
    // Map string to Category (case-insensitive, ignore spaces/underscores)
    // Accepts: "ones", "twos", ..., "full house", "four of a kind", etc.
    if(category_name == nullptr) {
        return 0U;
    }
    // Lowercase and remove spaces/underscores for matching
    std::string key;
    for(const char* p = category_name; *p != '\0'; ++p) {
        if((*p != ' ') && (*p != '_')) {
            key += static_cast<char>(std::tolower(static_cast<unsigned char>(*p)));
        }
    }
    if(key == "ones") return score(dice, Category::Ones);
    if(key == "twos") return score(dice, Category::Twos);
    if(key == "threes") return score(dice, Category::Threes);
    if(key == "fours") return score(dice, Category::Fours);
    if(key == "fives") return score(dice, Category::Fives);
    if(key == "sixes") return score(dice, Category::Sixes);
    if(key == "fullhouse") return score(dice, Category::FullHouse);
    if(key == "fourofakind") return score(dice, Category::FourOfAKind);
    if(key == "littlestraight") return score(dice, Category::LittleStraight);
    if(key == "bigstraight") return score(dice, Category::BigStraight);
    if(key == "choice") return score(dice, Category::Choice);
    if(key == "yacht") return score(dice, Category::Yacht);
    // Accept also "four of a kind", "full house", etc.
    return 0U;
}

}  // namespace yacht
