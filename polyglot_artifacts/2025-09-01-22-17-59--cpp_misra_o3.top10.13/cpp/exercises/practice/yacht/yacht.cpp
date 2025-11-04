#include "yacht.h"

#include <array>
#include <cstdint>
#include <cstddef>
#include <string_view>

namespace yacht {

auto score(const std::array<std::uint8_t, 5U>& dice, Category category) -> std::uint32_t
{
    /* Count occurrences of each face (1-6). Index 0 is unused. */
    std::array<std::uint8_t, 7U> counts {};
    for (std::uint8_t die : dice) {
        ++counts[static_cast<std::size_t>(die)];
    }

    /* Helper to sum all dice */
    auto sum_dice = [](const std::array<std::uint8_t, 5U>& d) -> std::uint32_t {
        std::uint32_t s { 0U };
        for (std::uint8_t v : d) {
            s += static_cast<std::uint32_t>(v);
        }
        return s;
    };

    switch (category) {
        case Category::Ones:
        case Category::Twos:
        case Category::Threes:
        case Category::Fours:
        case Category::Fives:
        case Category::Sixes:
        {
            const std::uint8_t face { static_cast<std::uint8_t>(
                static_cast<std::uint8_t>(category) + static_cast<std::uint8_t>(1U)) };
            return static_cast<std::uint32_t>(face)
                 * static_cast<std::uint32_t>(counts[static_cast<std::size_t>(face)]);
        }
        case Category::FullHouse:
        {
            bool has_three { false };
            bool has_two { false };
            for (std::uint8_t value { static_cast<std::uint8_t>(1U) };
                 value <= static_cast<std::uint8_t>(6U);
                 ++value) {
                if (counts[static_cast<std::size_t>(value)] == static_cast<std::uint8_t>(3U)) { has_three = true; }
                if (counts[static_cast<std::size_t>(value)] == static_cast<std::uint8_t>(2U)) { has_two  = true; }
            }
            if (has_three && has_two) {
                return sum_dice(dice);
            }
            return 0U;
        }
        case Category::FourOfAKind:
        {
            for (std::uint8_t value { static_cast<std::uint8_t>(1U) };
                 value <= static_cast<std::uint8_t>(6U);
                 ++value) {
                if (counts[static_cast<std::size_t>(value)] >= static_cast<std::uint8_t>(4U)) {
                    return static_cast<std::uint32_t>(value)
                         * static_cast<std::uint32_t>(4U);
                }
            }
            return 0U;
        }
        case Category::LittleStraight:
        {
            if ((counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 0U)) {
                return 30U;
            }
            return 0U;
        }
        case Category::BigStraight:
        {
            if ((counts[1U] == 0U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 1U)) {
                return 30U;
            }
            return 0U;
        }
        case Category::Choice:
        {
            return sum_dice(dice);
        }
        case Category::Yacht:
        {
            for (std::uint8_t value { static_cast<std::uint8_t>(1U) };
                 value <= static_cast<std::uint8_t>(6U);
                 ++value) {
                if (counts[static_cast<std::size_t>(value)] == static_cast<std::uint8_t>(5U)) {
                    return 50U;
                }
            }
            return 0U;
        }
        default:
        {
            return 0U;
        }
    }
}

auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view category) -> std::uint32_t
{
    if (category == "yacht") { 
        return score(dice, Category::Yacht); 
    } else if (category == "ones") { 
        return score(dice, Category::Ones); 
    } else if (category == "twos") { 
        return score(dice, Category::Twos); 
    } else if (category == "threes") { 
        return score(dice, Category::Threes); 
    } else if (category == "fours") { 
        return score(dice, Category::Fours); 
    } else if (category == "fives") { 
        return score(dice, Category::Fives); 
    } else if (category == "sixes") { 
        return score(dice, Category::Sixes); 
    } else if (category == "full house") { 
        return score(dice, Category::FullHouse); 
    } else if (category == "four of a kind") { 
        return score(dice, Category::FourOfAKind); 
    } else if (category == "little straight") { 
        return score(dice, Category::LittleStraight); 
    } else if (category == "big straight") { 
        return score(dice, Category::BigStraight); 
    } else if (category == "choice") { 
        return score(dice, Category::Choice); 
    } else { 
        return static_cast<std::uint32_t>(0U); 
    }
}

}  // namespace yacht
