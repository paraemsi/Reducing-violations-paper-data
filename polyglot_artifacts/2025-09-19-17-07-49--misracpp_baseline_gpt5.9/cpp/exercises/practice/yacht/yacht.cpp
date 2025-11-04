#include "yacht.h"

#include <array>
#include <numeric>
#include <cstddef>
#include <string>
#include <algorithm>
#include <cctype>

namespace yacht {

namespace {
std::array<int, 7> counts_of(const std::vector<int>& dice) {
    std::array<int, 7> counts{};
    counts.fill(0);
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            counts[static_cast<std::size_t>(d)]++;
        }
    }
    return counts;
}
category parse_category(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    if (s == "ones") return category::ones;
    if (s == "twos") return category::twos;
    if (s == "threes") return category::threes;
    if (s == "fours") return category::fours;
    if (s == "fives") return category::fives;
    if (s == "sixes") return category::sixes;
    if (s == "full house") return category::full_house;
    if (s == "four of a kind") return category::four_of_a_kind;
    if (s == "little straight") return category::little_straight;
    if (s == "big straight") return category::big_straight;
    if (s == "choice") return category::choice;
    if (s == "yacht") return category::yacht;
    return category::choice;
}
}  // namespace

int score(const std::vector<int>& dice, const std::string& cat) {
    return score(dice, parse_category(cat));
}

int score(const std::vector<int>& dice, category cat) {
    const auto counts = counts_of(dice);
    const int total = std::accumulate(dice.begin(), dice.end(), 0);

    switch (cat) {
        case category::ones:   return counts[1] * 1;
        case category::twos:   return counts[2] * 2;
        case category::threes: return counts[3] * 3;
        case category::fours:  return counts[4] * 4;
        case category::fives:  return counts[5] * 5;
        case category::sixes:  return counts[6] * 6;

        case category::full_house: {
            bool has_two = false;
            bool has_three = false;
            for (std::size_t i = 1; i <= 6; ++i) {
                if (counts[i] == 2) has_two = true;
                if (counts[i] == 3) has_three = true;
            }
            return (has_two && has_three) ? total : 0;
        }

        case category::four_of_a_kind: {
            for (std::size_t i = 1; i <= 6; ++i) {
                if (counts[i] >= 4) {
                    return static_cast<int>(i) * 4;
                }
            }
            return 0;
        }

        case category::little_straight: {
            // 1,2,3,4,5 exactly
            return (counts[1] == 1 && counts[2] == 1 && counts[3] == 1 &&
                    counts[4] == 1 && counts[5] == 1 && counts[6] == 0)
                       ? 30
                       : 0;
        }

        case category::big_straight: {
            // 2,3,4,5,6 exactly
            return (counts[1] == 0 && counts[2] == 1 && counts[3] == 1 &&
                    counts[4] == 1 && counts[5] == 1 && counts[6] == 1)
                       ? 30
                       : 0;
        }

        case category::choice:
            return total;

        case category::yacht: {
            for (std::size_t i = 1; i <= 6; ++i) {
                if (counts[i] == 5) return 50;
            }
            return 0;
        }
    }

    return 0;
}

int score(const std::vector<int>& dice, const char* cat) {
    return score(dice, std::string{cat});
}

}  // namespace yacht
