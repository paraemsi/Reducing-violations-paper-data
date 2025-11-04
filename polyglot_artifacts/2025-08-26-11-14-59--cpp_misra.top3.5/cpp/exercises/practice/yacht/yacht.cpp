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
            return static_cast<std::uint32_t>(counts[0]) * 1U;
        case Category::Twos:
            return static_cast<std::uint32_t>(counts[1]) * 2U;
        case Category::Threes:
            return static_cast<std::uint32_t>(counts[2]) * 3U;
        case Category::Fours:
            return static_cast<std::uint32_t>(counts[3]) * 4U;
        case Category::Fives:
            return static_cast<std::uint32_t>(counts[4]) * 5U;
        case Category::Sixes:
            return static_cast<std::uint32_t>(counts[5]) * 6U;
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
                total = total + (static_cast<std::uint32_t>(counts[i]) * static_cast<std::uint32_t>(i + 1U));
            }
            if(has_three && has_two) {
                return total;
            }
            return 0U;
        }
        case Category::FourOfAKind: {
            for(std::size_t i = 0U; i < 6U; ++i) {
                if(counts[i] >= 4U) {
                    return static_cast<std::uint32_t>(i + 1U) * 4U;
                }
            }
            return 0U;
        }
        case Category::LittleStraight:
            if((counts[0] == 1U) && (counts[1] == 1U) && (counts[2] == 1U) && (counts[3] == 1U) && (counts[4] == 1U)) {
                return 30U;
            }
            return 0U;
        case Category::BigStraight:
            if((counts[1] == 1U) && (counts[2] == 1U) && (counts[3] == 1U) && (counts[4] == 1U) && (counts[5] == 1U)) {
                return 30U;
            }
            return 0U;
        case Category::Choice: {
            std::uint32_t total = 0U;
            for(std::size_t i = 0U; i < 6U; ++i) {
                total = total + (static_cast<std::uint32_t>(counts[i]) * static_cast<std::uint32_t>(i + 1U));
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

Category category_from_string(const char* name)
{
    // Accepts lower-case and space-separated category names as in the test cases
    if(name == nullptr) {
        return Category::Yacht; // fallback, shouldn't happen
    }
    // Use only lower-case comparisons
    std::string s(name);
    // Remove leading/trailing spaces
    s.erase(0, s.find_first_not_of(' '));
    s.erase(s.find_last_not_of(' ') + 1);
    // Lowercase
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); });

    if(s == "ones") return Category::Ones;
    if(s == "twos") return Category::Twos;
    if(s == "threes") return Category::Threes;
    if(s == "fours") return Category::Fours;
    if(s == "fives") return Category::Fives;
    if(s == "sixes") return Category::Sixes;
    if(s == "full house") return Category::FullHouse;
    if(s == "four of a kind") return Category::FourOfAKind;
    if(s == "little straight") return Category::LittleStraight;
    if(s == "big straight") return Category::BigStraight;
    if(s == "choice") return Category::Choice;
    if(s == "yacht") return Category::Yacht;
    // fallback
    return Category::Yacht;
}

// Overload for const char* category argument
std::uint32_t score(const DiceArray& dice, const char* category)
{
    return score(dice, category_from_string(category));
}

}  // namespace yacht
