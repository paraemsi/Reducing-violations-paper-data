#include "yacht.h"
#include <algorithm>
#include <map>
#include <numeric>

namespace yacht {

std::uint32_t score(const DiceArray& dice, Category category)
{
    // Count occurrences of each die value (1-6)
    std::array<std::uint8_t, 6> counts = {0, 0, 0, 0, 0, 0};
    for(const DieValue d : dice) {
        if((d >= 1U) && (d <= 6U)) {
            ++(counts[static_cast<std::size_t>(d) - 1U]);
        }
    }

    switch(category) {
        case Category::Ones:
        case Category::Twos:
        case Category::Threes:
        case Category::Fours:
        case Category::Fives:
        case Category::Sixes: {
            std::uint8_t face = static_cast<std::uint8_t>(category) + 1U;
            return (face * static_cast<std::uint32_t>(counts[face - 1U]));
        }
        case Category::FullHouse: {
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
                return (three_val * 3U + two_val * 2U);
            }
            return 0U;
        }
        case Category::FourOfAKind: {
            for(std::uint8_t i = 0U; i < 6U; ++i) {
                if(counts[i] >= 4U) {
                    return ((i + 1U) * 4U);
                }
            }
            return 0U;
        }
        case Category::LittleStraight: {
            // 1,2,3,4,5
            if((counts[0] == 1U) && (counts[1] == 1U) && (counts[2] == 1U) && (counts[3] == 1U) && (counts[4] == 1U)) {
                return 30U;
            }
            return 0U;
        }
        case Category::BigStraight: {
            // 2,3,4,5,6
            if((counts[1] == 1U) && (counts[2] == 1U) && (counts[3] == 1U) && (counts[4] == 1U) && (counts[5] == 1U)) {
                return 30U;
            }
            return 0U;
        }
        case Category::Choice: {
            std::uint32_t sum = 0U;
            for(const DieValue d : dice) {
                sum += d;
            }
            return sum;
        }
        case Category::Yacht: {
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
    // Map string to Category
    if(category_name == nullptr) {
        return 0U;
    }
    // Lowercase and remove spaces for robust matching
    std::string name(category_name);
    std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    name.erase(std::remove(name.begin(), name.end(), ' '), name.end());

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

    return 0U;
}

}  // namespace yacht
