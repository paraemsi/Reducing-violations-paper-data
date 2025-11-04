#include "yacht.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <map>

namespace yacht {

namespace {
    // Helper: count occurrences of each die face (1-6)
    std::array<std::uint8_t, 6> count_faces(const DiceArray& dice) {
        std::array<std::uint8_t, 6> counts = {0, 0, 0, 0, 0, 0};
        for (const DieValue value : dice) {
            if ((value >= 1U) && (value <= 6U)) {
                ++counts[static_cast<std::size_t>(value - 1U)];
            }
        }
        return counts;
    }
}

std::uint32_t score(const DiceArray& dice, Category category) {
    const std::array<std::uint8_t, 6> counts = count_faces(dice);
    std::uint32_t result = 0U;

    switch (category) {
        case Category::Ones:
            result = static_cast<std::uint32_t>(counts[0]) * 1U;
            break;
        case Category::Twos:
            result = static_cast<std::uint32_t>(counts[1]) * 2U;
            break;
        case Category::Threes:
            result = static_cast<std::uint32_t>(counts[2]) * 3U;
            break;
        case Category::Fours:
            result = static_cast<std::uint32_t>(counts[3]) * 4U;
            break;
        case Category::Fives:
            result = static_cast<std::uint32_t>(counts[4]) * 5U;
            break;
        case Category::Sixes:
            result = static_cast<std::uint32_t>(counts[5]) * 6U;
            break;
        case Category::FullHouse: {
            bool has_three = false;
            bool has_two = false;
            for (std::uint8_t c : counts) {
                if (c == 3U) {
                    has_three = true;
                } else if (c == 2U) {
                    has_two = true;
                }
            }
            if (has_three && has_two) {
                for (std::size_t i = 0U; i < 6U; ++i) {
                    result += static_cast<std::uint32_t>(counts[i]) * static_cast<std::uint32_t>(i + 1U);
                }
            }
            break;
        }
        case Category::FourOfAKind: {
            for (std::size_t i = 0U; i < 6U; ++i) {
                if (counts[i] >= 4U) {
                    result = static_cast<std::uint32_t>(i + 1U) * 4U;
                    break;
                }
            }
            break;
        }
        case Category::LittleStraight:
            if ((counts[0] == 1U) && (counts[1] == 1U) && (counts[2] == 1U) && (counts[3] == 1U) && (counts[4] == 1U)) {
                result = 30U;
            }
            break;
        case Category::BigStraight:
            if ((counts[1] == 1U) && (counts[2] == 1U) && (counts[3] == 1U) && (counts[4] == 1U) && (counts[5] == 1U)) {
                result = 30U;
            }
            break;
        case Category::Choice:
            for (std::size_t i = 0U; i < 5U; ++i) {
                result += static_cast<std::uint32_t>(dice[i]);
            }
            break;
        case Category::Yacht:
            for (std::uint8_t c : counts) {
                if (c == 5U) {
                    result = 50U;
                    break;
                }
            }
            break;
        default:
            // No action needed
            break;
    }
    return result;
}

Category category_from_string(const char* name) {
    // Accepts lower-case and space-separated category names as in the test cases
    if (name == nullptr) {
        return Category::Choice; // fallback, shouldn't happen
    }
    // Use only lower-case comparisons for simplicity
    if (std::strcmp(name, "ones") == 0) return Category::Ones;
    if (std::strcmp(name, "twos") == 0) return Category::Twos;
    if (std::strcmp(name, "threes") == 0) return Category::Threes;
    if (std::strcmp(name, "fours") == 0) return Category::Fours;
    if (std::strcmp(name, "fives") == 0) return Category::Fives;
    if (std::strcmp(name, "sixes") == 0) return Category::Sixes;
    if (std::strcmp(name, "full house") == 0) return Category::FullHouse;
    if (std::strcmp(name, "four of a kind") == 0) return Category::FourOfAKind;
    if (std::strcmp(name, "little straight") == 0) return Category::LittleStraight;
    if (std::strcmp(name, "big straight") == 0) return Category::BigStraight;
    if (std::strcmp(name, "choice") == 0) return Category::Choice;
    if (std::strcmp(name, "yacht") == 0) return Category::Yacht;
    // fallback
    return Category::Choice;
}

std::uint32_t score(const DiceArray& dice, const char* category_name) {
    return score(dice, category_from_string(category_name));
}

}  // namespace yacht
