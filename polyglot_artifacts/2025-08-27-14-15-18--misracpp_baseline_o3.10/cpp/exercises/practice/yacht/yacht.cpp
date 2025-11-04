#include "yacht.h"

#include <array>
#include <numeric>
#include <string>
#include <algorithm>
#include <cctype>

namespace yacht {

namespace {
constexpr int yacht_score   = 50;
constexpr int straight_score = 30;

// Helper: build a histogram of die face counts (index 1-6).
std::array<int, 7> build_histogram(const std::vector<int>& dice) {
    std::array<int, 7> counts{0, 0, 0, 0, 0, 0, 0};
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            ++counts[d];
        }
    }
    return counts;
}

/* Convert user-supplied category string (lower-case, may contain spaces)
 * to the corresponding enum value.
 */
category string_to_category(std::string name) {
    std::transform(name.begin(), name.end(), name.begin(),
                   [](unsigned char ch) { return std::tolower(ch); });

    if (name == "ones")              return category::ones;
    if (name == "twos")              return category::twos;
    if (name == "threes")            return category::threes;
    if (name == "fours")             return category::fours;
    if (name == "fives")             return category::fives;
    if (name == "sixes")             return category::sixes;
    if (name == "full house")        return category::full_house;
    if (name == "four of a kind")    return category::four_of_a_kind;
    if (name == "little straight")   return category::little_straight;
    if (name == "big straight")      return category::big_straight;
    if (name == "choice")            return category::choice;
    if (name == "yacht")             return category::yacht;

    // Unknown string – treat as a category that always scores zero.
    return category::choice; // Choice with empty dice would yield 0.
}
}  // namespace

int score(category cat, const std::vector<int>& dice) {
    const auto counts = build_histogram(dice);
    const int  sum    = std::accumulate(dice.begin(), dice.end(), 0);

    switch (cat) {
        case category::ones:   return counts[1] * 1;
        case category::twos:   return counts[2] * 2;
        case category::threes: return counts[3] * 3;
        case category::fours:  return counts[4] * 4;
        case category::fives:  return counts[5] * 5;
        case category::sixes:  return counts[6] * 6;

        case category::full_house: {
            bool has_three = false, has_two = false;
            for (int v = 1; v <= 6; ++v) {
                if (counts[v] == 3) has_three = true;
                if (counts[v] == 2) has_two   = true;
            }
            return (has_three && has_two) ? sum : 0;
        }

        case category::four_of_a_kind: {
            for (int v = 1; v <= 6; ++v) {
                if (counts[v] >= 4) {
                    return v * 4;
                }
            }
            return 0;
        }

        case category::little_straight:
            return (counts[1] == 1 && counts[2] == 1 && counts[3] == 1 &&
                    counts[4] == 1 && counts[5] == 1 && counts[6] == 0)
                       ? straight_score
                       : 0;

        case category::big_straight:
            return (counts[1] == 0 && counts[2] == 1 && counts[3] == 1 &&
                    counts[4] == 1 && counts[5] == 1 && counts[6] == 1)
                       ? straight_score
                       : 0;

        case category::choice:
            return sum;

        case category::yacht:
            for (int v = 1; v <= 6; ++v) {
                if (counts[v] == 5) {
                    return yacht_score;
                }
            }
            return 0;
    }

    return 0; // Should be unreachable.
}

/* Public overload that matches the order used in the tests:
 * dice first, category as string second.
 */
int score(const std::vector<int>& dice, const std::string& category_name) {
    return score(string_to_category(category_name), dice);
}

}  // namespace yacht
