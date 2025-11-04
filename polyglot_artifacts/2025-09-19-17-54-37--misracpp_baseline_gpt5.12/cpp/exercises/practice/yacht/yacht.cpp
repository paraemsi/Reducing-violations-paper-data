#include "yacht.h"

#include <array>
#include <numeric>
#include <string>

namespace yacht {

int score(const std::vector<int>& dice, category cat) {
    // Frequency of faces 1..6
    std::array<int, 7> freq{};  // index 0 unused
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            ++freq[d];
        }
    }

    const int total = std::accumulate(dice.begin(), dice.end(), 0);

    switch (cat) {
        case category::ones:   return 1 * freq[1];
        case category::twos:   return 2 * freq[2];
        case category::threes: return 3 * freq[3];
        case category::fours:  return 4 * freq[4];
        case category::fives:  return 5 * freq[5];
        case category::sixes:  return 6 * freq[6];

        case category::yacht: {
            for (int face = 1; face <= 6; ++face) {
                if (freq[face] == 5) return 50;
            }
            return 0;
        }

        case category::choice:
            return total;

        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (int face = 1; face <= 6; ++face) {
                if (freq[face] == 3) has_three = true;
                else if (freq[face] == 2) has_two = true;
            }
            return (has_three && has_two) ? total : 0;
        }

        case category::four_of_a_kind: {
            for (int face = 1; face <= 6; ++face) {
                if (freq[face] >= 4) {
                    return 4 * face;  // only the four dice count, even if five are the same
                }
            }
            return 0;
        }

        case category::little_straight: {
            // 1-2-3-4-5: each appears exactly once
            for (int face = 1; face <= 5; ++face) {
                if (freq[face] != 1) return 0;
            }
            // Implicitly ensures face 6 is not present (must be zero for total count to be 5)
            return 30;
        }

        case category::big_straight: {
            // 2-3-4-5-6: each appears exactly once
            for (int face = 2; face <= 6; ++face) {
                if (freq[face] != 1) return 0;
            }
            // Ensures face 1 is not present
            return 30;
        }
    }

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
