#include "yacht.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <numeric>
#include <string>

namespace yacht {

static category parse_category(const std::string& name) {
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
    return category::choice;  // default fallback
}

int score(const std::vector<int>& dice, const char* cat) noexcept {
    return score(dice, parse_category(std::string(cat)));
}

int score(const std::vector<int>& dice, category cat) noexcept {
    std::array<int, 7> counts{};  // index 1..6 used
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            counts[static_cast<std::size_t>(d)]++;
        }
    }

    const int sum = std::accumulate(dice.begin(), dice.end(), 0);

    switch (cat) {
        case category::ones:   return counts[1] * 1;
        case category::twos:   return counts[2] * 2;
        case category::threes: return counts[3] * 3;
        case category::fours:  return counts[4] * 4;
        case category::fives:  return counts[5] * 5;
        case category::sixes:  return counts[6] * 6;

        case category::choice:
            return sum;

        case category::yacht: {
            auto max_count = *std::max_element(counts.begin() + 1, counts.end());
            return (max_count == 5) ? 50 : 0;
        }

        case category::four_of_a_kind: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[static_cast<std::size_t>(face)] >= 4) {
                    return face * 4;
                }
            }
            return 0;
        }

        case category::full_house: {
            bool has_three = false, has_two = false;
            for (int face = 1; face <= 6; ++face) {
                if (counts[static_cast<std::size_t>(face)] == 3) has_three = true;
                else if (counts[static_cast<std::size_t>(face)] == 2) has_two = true;
            }
            return (has_three && has_two) ? sum : 0;
        }

        case category::little_straight: {
            const bool ok = counts[1] == 1 && counts[2] == 1 && counts[3] == 1 &&
                            counts[4] == 1 && counts[5] == 1 && counts[6] == 0;
            return ok ? 30 : 0;
        }

        case category::big_straight: {
            const bool ok = counts[1] == 0 && counts[2] == 1 && counts[3] == 1 &&
                            counts[4] == 1 && counts[5] == 1 && counts[6] == 1;
            return ok ? 30 : 0;
        }
    }

    return 0;  // Fallback, should be unreachable
}

}  // namespace yacht
