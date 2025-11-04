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
                total += static_cast<std::uint32_t>(counts[i]) * static_cast<std::uint32_t>(i + 1U);
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
            std::uint32_t sum = 0U;
            for(std::size_t i = 0U; i < 5U; ++i) {
                sum += static_cast<std::uint32_t>(dice[i]);
            }
            return sum;
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
        return Category::Choice; // fallback, shouldn't happen
    }
    // Yacht
    if((std::strcmp(name, "yacht") == 0)) {
        return Category::Yacht;
    }
    // Ones
    if((std::strcmp(name, "ones") == 0)) {
        return Category::Ones;
    }
    // Twos
    if((std::strcmp(name, "twos") == 0)) {
        return Category::Twos;
    }
    // Threes
    if((std::strcmp(name, "threes") == 0)) {
        return Category::Threes;
    }
    // Fours
    if((std::strcmp(name, "fours") == 0)) {
        return Category::Fours;
    }
    // Fives
    if((std::strcmp(name, "fives") == 0)) {
        return Category::Fives;
    }
    // Sixes
    if((std::strcmp(name, "sixes") == 0)) {
        return Category::Sixes;
    }
    // Full House
    if((std::strcmp(name, "full house") == 0)) {
        return Category::FullHouse;
    }
    // Four of a Kind
    if((std::strcmp(name, "four of a kind") == 0)) {
        return Category::FourOfAKind;
    }
    // Little Straight
    if((std::strcmp(name, "little straight") == 0)) {
        return Category::LittleStraight;
    }
    // Big Straight
    if((std::strcmp(name, "big straight") == 0)) {
        return Category::BigStraight;
    }
    // Choice
    if((std::strcmp(name, "choice") == 0)) {
        return Category::Choice;
    }
    // fallback
    return Category::Choice;
}

std::uint32_t score(const DiceArray& dice, const char* category_name)
{
    return score(dice, category_from_string(category_name));
}

}  // namespace yacht
