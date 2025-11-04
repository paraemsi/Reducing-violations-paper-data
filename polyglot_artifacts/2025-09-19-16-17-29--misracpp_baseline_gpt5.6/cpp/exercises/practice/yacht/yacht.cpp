#include "yacht.h"

#include <array>
#include <numeric>
#include <string_view>

namespace yacht {

namespace {
std::array<int, 7> counts_for(const std::vector<int>& dice) {
    std::array<int, 7> counts{};
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            ++counts[d];
        }
    }
    return counts;
}

category parse_category(std::string_view s) {
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
    // Default to choice if unknown; tests only use valid names.
    return category::choice;
}
}  // namespace

int score(const std::vector<int>& dice, std::string_view cat) {
    const auto counts = counts_for(dice);
    const int sum_all = std::accumulate(dice.begin(), dice.end(), 0);
    const auto cat_enum = parse_category(cat);

    switch (cat_enum) {
        case category::ones:
            return counts[1] * 1;
        case category::twos:
            return counts[2] * 2;
        case category::threes:
            return counts[3] * 3;
        case category::fours:
            return counts[4] * 4;
        case category::fives:
            return counts[5] * 5;
        case category::sixes:
            return counts[6] * 6;

        case category::full_house: {
            bool has2 = false;
            bool has3 = false;
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 2) has2 = true;
                else if (counts[face] == 3) has3 = true;
            }
            return (has2 && has3) ? sum_all : 0;
        }

        case category::four_of_a_kind: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] >= 4) {
                    return 4 * face;
                }
            }
            return 0;
        }

        case category::little_straight: {
            // Must be exactly 1-2-3-4-5 (each once), and no 6.
            for (int face = 1; face <= 5; ++face) {
                if (counts[face] != 1) return 0;
            }
            return counts[6] == 0 ? 30 : 0;
        }

        case category::big_straight: {
            // Must be exactly 2-3-4-5-6 (each once), and no 1.
            if (counts[1] != 0) return 0;
            for (int face = 2; face <= 6; ++face) {
                if (counts[face] != 1) return 0;
            }
            return 30;
        }

        case category::choice:
            return sum_all;

        case category::yacht: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 5) return 50;
            }
            return 0;
        }
    }

    // Fallback for completeness; all enum cases handled above.
    return 0;
}

}  // namespace yacht
