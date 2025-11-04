#include "yacht.h"

#include <array>
#include <cstddef>
#include <numeric>

namespace yacht {

namespace {
    std::array<int, 7> make_counts(const std::vector<int>& dice) {
        std::array<int, 7> counts{};  // indices 1..6 used
        for (int v : dice) {
            if (v >= 1 && v <= 6) {
                ++counts[static_cast<std::size_t>(v)];
            }
        }
        return counts;
    }

    int sum(const std::vector<int>& dice) {
        return std::accumulate(dice.begin(), dice.end(), 0);
    }
}  // namespace

int score(const std::vector<int>& dice, category cat) {
    const auto counts = make_counts(dice);

    switch (cat) {
        case category::ones:   return counts[1] * 1;
        case category::twos:   return counts[2] * 2;
        case category::threes: return counts[3] * 3;
        case category::fours:  return counts[4] * 4;
        case category::fives:  return counts[5] * 5;
        case category::sixes:  return counts[6] * 6;

        case category::choice:
            return sum(dice);

        case category::yacht: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 5) return 50;
            }
            return 0;
        }

        case category::four_of_a_kind: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] >= 4) return 4 * face;
            }
            return 0;
        }

        case category::full_house: {
            bool has_three = false, has_two = false;
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 3) has_three = true;
                else if (counts[face] == 2) has_two = true;
            }
            return (has_three && has_two) ? sum(dice) : 0;
        }

        case category::little_straight: {
            bool ok = counts[1] == 1 && counts[2] == 1 && counts[3] == 1 &&
                      counts[4] == 1 && counts[5] == 1 && counts[6] == 0;
            return ok ? 30 : 0;
        }

        case category::big_straight: {
            bool ok = counts[1] == 0 && counts[2] == 1 && counts[3] == 1 &&
                      counts[4] == 1 && counts[5] == 1 && counts[6] == 1;
            return ok ? 30 : 0;
        }
    }

    // Should be unreachable, but return 0 to satisfy all control paths
    return 0;
}

int score(const std::vector<int>& dice, const std::string& cat) {
    if (cat == "ones") return score(dice, category::ones);
    if (cat == "twos") return score(dice, category::twos);
    if (cat == "threes") return score(dice, category::threes);
    if (cat == "fours") return score(dice, category::fours);
    if (cat == "fives") return score(dice, category::fives);
    if (cat == "sixes") return score(dice, category::sixes);
    if (cat == "full house") return score(dice, category::full_house);
    if (cat == "four of a kind") return score(dice, category::four_of_a_kind);
    if (cat == "little straight") return score(dice, category::little_straight);
    if (cat == "big straight") return score(dice, category::big_straight);
    if (cat == "choice") return score(dice, category::choice);
    if (cat == "yacht") return score(dice, category::yacht);
    return 0;
}

}  // namespace yacht
