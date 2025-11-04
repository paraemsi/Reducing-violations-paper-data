#include "yacht.h"

#include <array>
#include <numeric>

namespace yacht {

namespace {
    // Count occurrences of each die face 1..6
    std::array<int, 7> counts_for(const std::vector<int>& dice) {
        std::array<int, 7> cnt{};
        for (int d : dice) {
            if (d >= 1 && d <= 6) {
                ++cnt[d];
            }
        }
        return cnt;
    }
}  // namespace

int score(const std::vector<int>& dice, category cat) {
    const auto cnt = counts_for(dice);
    const int sum = std::accumulate(dice.begin(), dice.end(), 0);

    switch (cat) {
        case category::ones:   return 1 * cnt[1];
        case category::twos:   return 2 * cnt[2];
        case category::threes: return 3 * cnt[3];
        case category::fours:  return 4 * cnt[4];
        case category::fives:  return 5 * cnt[5];
        case category::sixes:  return 6 * cnt[6];

        case category::choice:
            return sum;

        case category::yacht: {
            for (int p = 1; p <= 6; ++p) {
                if (cnt[p] == 5) {
                    return 50;
                }
            }
            return 0;
        }

        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (int p = 1; p <= 6; ++p) {
                if (cnt[p] == 3) has_three = true;
                else if (cnt[p] == 2) has_two = true;
            }
            return (has_three && has_two) ? sum : 0;
        }

        case category::four_of_a_kind: {
            for (int p = 1; p <= 6; ++p) {
                if (cnt[p] >= 4) {
                    // Yacht (5 of a kind) also qualifies as four of a kind
                    return 4 * p;
                }
            }
            return 0;
        }

        case category::little_straight:
            // 1-2-3-4-5 exactly
            return (cnt[1] == 1 && cnt[2] == 1 && cnt[3] == 1 && cnt[4] == 1 && cnt[5] == 1 && cnt[6] == 0) ? 30 : 0;

        case category::big_straight:
            // 2-3-4-5-6 exactly
            return (cnt[1] == 0 && cnt[2] == 1 && cnt[3] == 1 && cnt[4] == 1 && cnt[5] == 1 && cnt[6] == 1) ? 30 : 0;
    }

    return 0; // Fallback (should be unreachable)
}

int score(const std::vector<int>& dice, const std::string& cat) {
    category c;

    if (cat == "ones") c = category::ones;
    else if (cat == "twos") c = category::twos;
    else if (cat == "threes") c = category::threes;
    else if (cat == "fours") c = category::fours;
    else if (cat == "fives") c = category::fives;
    else if (cat == "sixes") c = category::sixes;
    else if (cat == "full house") c = category::full_house;
    else if (cat == "four of a kind") c = category::four_of_a_kind;
    else if (cat == "little straight") c = category::little_straight;
    else if (cat == "big straight") c = category::big_straight;
    else if (cat == "choice") c = category::choice;
    else if (cat == "yacht") c = category::yacht;
    else return 0; // Unknown category string

    return score(dice, c);
}

}  // namespace yacht
