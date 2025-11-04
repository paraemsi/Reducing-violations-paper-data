#include "yacht.h"
#include <numeric>
#include <algorithm>
#include <array>
#include <string_view>

namespace yacht {

int score(const std::vector<int>& dice, category cat) {
    std::array<int, 7> counts{};  // index 1..6
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            counts[d]++;
        }
    }

    int sum = std::accumulate(dice.begin(), dice.end(), 0);

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
                has_three = has_three || counts[v] == 3;
                has_two   = has_two   || counts[v] == 2;
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
                    counts[4] == 1 && counts[5] == 1 && counts[6] == 0) ? 30 : 0;

        case category::big_straight:
            return (counts[1] == 0 && counts[2] == 1 && counts[3] == 1 &&
                    counts[4] == 1 && counts[5] == 1 && counts[6] == 1) ? 30 : 0;

        case category::choice:
            return sum;

        case category::yacht:
            for (int v = 1; v <= 6; ++v) {
                if (counts[v] == 5) {
                    return 50;
                }
            }
            return 0;
    }

    return 0;  // Fallback, should never hit.
}

int score(const std::vector<int>& dice, std::string_view cat_str) {
    category cat_enum{};
    if      (cat_str == "ones")            cat_enum = category::ones;
    else if (cat_str == "twos")            cat_enum = category::twos;
    else if (cat_str == "threes")          cat_enum = category::threes;
    else if (cat_str == "fours")           cat_enum = category::fours;
    else if (cat_str == "fives")           cat_enum = category::fives;
    else if (cat_str == "sixes")           cat_enum = category::sixes;
    else if (cat_str == "full house")      cat_enum = category::full_house;
    else if (cat_str == "four of a kind")  cat_enum = category::four_of_a_kind;
    else if (cat_str == "little straight") cat_enum = category::little_straight;
    else if (cat_str == "big straight")    cat_enum = category::big_straight;
    else if (cat_str == "choice")          cat_enum = category::choice;
    else if (cat_str == "yacht")           cat_enum = category::yacht;
    else                                   return 0;  // Unknown category

    return score(dice, cat_enum);
}

}  // namespace yacht
