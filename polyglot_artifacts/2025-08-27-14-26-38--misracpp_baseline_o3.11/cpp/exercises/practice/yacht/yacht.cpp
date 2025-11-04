#include "yacht.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <string>

namespace yacht {

namespace {

/**
 * Build a histogram of face counts (indices 1..6).
 */
std::array<int, 7> build_histogram(const std::vector<int>& dice) {
    std::array<int, 7> counts{};
    for (int die : dice) {
        ++counts[die];
    }
    return counts;
}

category to_category(const std::string& name) {
    if (name == "ones") return category::ones;
    if (name == "twos") return category::twos;
    if (name == "threes") return category::threes;
    if (name == "fours") return category::fours;
    if (name == "fives") return category::fives;
    if (name == "sixes") return category::sixes;
    if (name == "full house") return category::full_house;
    if (name == "four of a kind") return category::four_of_a_kind;
    if (name == "little straight") return category::little_straight;
    if (name == "big straight") return category::big_straight;
    if (name == "choice") return category::choice;
    if (name == "yacht") return category::yacht;
    return category::choice;  // Fallback
}

}  // namespace

int score(const std::vector<int>& dice, category cat) {
    if (dice.size() != 5) {
        return 0;  // Defensive: invalid input size.
    }

    const auto counts = build_histogram(dice);
    const int total = std::accumulate(dice.begin(), dice.end(), 0);

    switch (cat) {
        case category::ones:   return counts[1] * 1;
        case category::twos:   return counts[2] * 2;
        case category::threes: return counts[3] * 3;
        case category::fours:  return counts[4] * 4;
        case category::fives:  return counts[5] * 5;
        case category::sixes:  return counts[6] * 6;

        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 3) has_three = true;
                if (counts[face] == 2) has_two = true;
            }
            return (has_three && has_two) ? total : 0;
        }

        case category::four_of_a_kind: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] >= 4) {
                    return face * 4;
                }
            }
            return 0;
        }

        case category::little_straight: {
            static const std::array<int, 5> target{1, 2, 3, 4, 5};
            std::array<int, 5> sorted_dice;
            std::copy(dice.begin(), dice.end(), sorted_dice.begin());
            std::sort(sorted_dice.begin(), sorted_dice.end());
            return (sorted_dice == target) ? 30 : 0;
        }

        case category::big_straight: {
            static const std::array<int, 5> target{2, 3, 4, 5, 6};
            std::array<int, 5> sorted_dice;
            std::copy(dice.begin(), dice.end(), sorted_dice.begin());
            std::sort(sorted_dice.begin(), sorted_dice.end());
            return (sorted_dice == target) ? 30 : 0;
        }

        case category::choice:
            return total;

        case category::yacht: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 5) {
                    return 50;
                }
            }
            return 0;
        }
    }
    return 0;  // Should never reach here.
}

int score(const std::vector<int>& dice, const std::string& category_str) {
    return score(dice, to_category(category_str));
}


}  // namespace yacht
