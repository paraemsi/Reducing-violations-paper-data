#include "yacht.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <stdexcept>

namespace yacht {

namespace {
constexpr int kYachtScore      = 50;
constexpr int kStraightScore   = 30;
constexpr int kDiceFaces       = 6;
constexpr int kDicePerRoll     = 5;

// Build a frequency table where counts[i] is the number of dice showing face i.
// Index 0 is unused to allow 1-based indexing.
std::array<int, kDiceFaces + 1> make_count_table(const std::vector<int>& dice) {
    std::array<int, kDiceFaces + 1> counts{};
    for (int value : dice) {
        ++counts[value];
    }
    return counts;
}

Category parse_category(const std::string& name) {
    if (name == "ones") return Category::ones;
    if (name == "twos") return Category::twos;
    if (name == "threes") return Category::threes;
    if (name == "fours") return Category::fours;
    if (name == "fives") return Category::fives;
    if (name == "sixes") return Category::sixes;
    if (name == "full house") return Category::full_house;
    if (name == "four of a kind") return Category::four_of_a_kind;
    if (name == "little straight") return Category::little_straight;
    if (name == "big straight") return Category::big_straight;
    if (name == "choice") return Category::choice;
    if (name == "yacht") return Category::yacht;
    throw std::invalid_argument("unknown category");
}
}  // namespace

int score(const std::vector<int>& dice, Category category) {
    const auto counts = make_count_table(dice);

    switch (category) {
        case Category::ones:
        case Category::twos:
        case Category::threes:
        case Category::fours:
        case Category::fives:
        case Category::sixes: {
            const int face = static_cast<int>(category) + 1;  // ones==0 → 1, …
            return counts[face] * face;
        }

        case Category::full_house: {
            const bool has_three = std::any_of(counts.begin(), counts.end(),
                                               [](int c) { return c == 3; });
            const bool has_two =
                std::any_of(counts.begin(), counts.end(), [](int c) { return c == 2; });
            return (has_three && has_two)
                       ? std::accumulate(dice.begin(), dice.end(), 0)
                       : 0;
        }

        case Category::four_of_a_kind: {
            for (int face = 1; face <= kDiceFaces; ++face) {
                if (counts[face] >= 4) {
                    return face * 4;
                }
            }
            return 0;
        }

        case Category::little_straight: {
            static const std::array<int, kDiceFaces + 1> needed{0, 1, 1, 1, 1, 1, 0};
            return std::equal(counts.begin() + 1, counts.end(), needed.begin() + 1)
                       ? kStraightScore
                       : 0;
        }

        case Category::big_straight: {
            static const std::array<int, kDiceFaces + 1> needed{0, 0, 1, 1, 1, 1, 1};
            return std::equal(counts.begin() + 1, counts.end(), needed.begin() + 1)
                       ? kStraightScore
                       : 0;
        }

        case Category::choice:
            return std::accumulate(dice.begin(), dice.end(), 0);

        case Category::yacht: {
            return std::any_of(counts.begin() + 1, counts.end(),
                               [](int c) { return c == kDicePerRoll; })
                       ? kYachtScore
                       : 0;
        }

        default:
            return 0;
    }
}

int score(const std::vector<int>& dice, const std::string& category_str) {
    return score(dice, parse_category(category_str));
}
}  // namespace yacht
