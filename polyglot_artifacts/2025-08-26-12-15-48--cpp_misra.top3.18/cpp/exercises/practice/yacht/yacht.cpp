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
    for(const Die d : dice) {
        if((d >= 1U) && (d <= 6U)) {
            ++counts[d - 1U];
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
            std::uint32_t total = 0U;
            for(std::uint8_t i = 0U; i < 6U; ++i) {
                if(counts[i] == 3U) {
                    has_three = true;
                    total += (static_cast<std::uint32_t>(i + 1U) * 3U);
                } else if(counts[i] == 2U) {
                    has_two = true;
                    total += (static_cast<std::uint32_t>(i + 1U) * 2U);
                }
            }
            if(has_three && has_two) {
                return total;
            }
            return 0U;
        }
        case Category::FourOfAKind: {
            for(std::uint8_t i = 0U; i < 6U; ++i) {
                if(counts[i] >= 4U) {
                    return (static_cast<std::uint32_t>(i + 1U) * 4U);
                }
            }
            return 0U;
        }
        case Category::LittleStraight: {
            // 1-2-3-4-5
            for(std::uint8_t i = 0U; i < 5U; ++i) {
                if(counts[i] != 1U) {
                    return 0U;
                }
            }
            if(counts[5U] == 0U) {
                return 30U;
            }
            return 0U;
        }
        case Category::BigStraight: {
            // 2-3-4-5-6
            if((counts[0U] == 0U) &&
               (counts[1U] == 1U) &&
               (counts[2U] == 1U) &&
               (counts[3U] == 1U) &&
               (counts[4U] == 1U) &&
               (counts[5U] == 1U)) {
                return 30U;
            }
            return 0U;
        }
        case Category::Choice: {
            std::uint32_t sum = 0U;
            for(const Die d : dice) {
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

std::uint32_t score(const Dice& dice, const char* category_name)
{
    // Map string to Category (case-insensitive, ignore underscores and spaces)
    if(category_name == nullptr) {
        return 0U;
    }
    std::string name(category_name);
    // Convert to lower case and remove spaces/underscores
    std::string norm;
    for(char c : name) {
        if((c >= 'A') && (c <= 'Z')) {
            norm += static_cast<char>(c + ('a' - 'A'));
        } else if((c >= 'a') && (c <= 'z')) {
            norm += c;
        } else if((c >= '0') && (c <= '9')) {
            norm += c;
        }
        // skip spaces and underscores
    }

    if(norm == "yacht") {
        return score(dice, Category::Yacht);
    } else if(norm == "ones") {
        return score(dice, Category::Ones);
    } else if(norm == "twos") {
        return score(dice, Category::Twos);
    } else if(norm == "threes") {
        return score(dice, Category::Threes);
    } else if(norm == "fours") {
        return score(dice, Category::Fours);
    } else if(norm == "fives") {
        return score(dice, Category::Fives);
    } else if(norm == "sixes") {
        return score(dice, Category::Sixes);
    } else if(norm == "fullhouse") {
        return score(dice, Category::FullHouse);
    } else if(norm == "fourofakind") {
        return score(dice, Category::FourOfAKind);
    } else if(norm == "littlestraight") {
        return score(dice, Category::LittleStraight);
    } else if(norm == "bigstraight") {
        return score(dice, Category::BigStraight);
    } else if(norm == "choice") {
        return score(dice, Category::Choice);
    }
    // Try with spaces/underscores removed
    if(norm == "fullhouse") {
        return score(dice, Category::FullHouse);
    } else if(norm == "fourofakind") {
        return score(dice, Category::FourOfAKind);
    } else if(norm == "littlestraight") {
        return score(dice, Category::LittleStraight);
    } else if(norm == "bigstraight") {
        return score(dice, Category::BigStraight);
    }
    return 0U;
}

}  // namespace yacht
