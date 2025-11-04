#include "yacht.h"
#include <array>
#include <string>

namespace yacht {

int score(const std::vector<int>& dice, category cat)
{
    std::array<int, 7> counts{};   // counts[1]..counts[6]
    int total = 0;
    for (int d : dice) {
        ++counts[d];
        total += d;
    }

    switch (cat) {
        case category::ones:   return counts[1] * 1;
        case category::twos:   return counts[2] * 2;
        case category::threes: return counts[3] * 3;
        case category::fours:  return counts[4] * 4;
        case category::fives:  return counts[5] * 5;
        case category::sixes:  return counts[6] * 6;

        case category::full_house: {
            bool has_three = false, has_two = false;
            int sum = 0;
            for (int v = 1; v <= 6; ++v) {
                if (counts[v] == 3) {
                    has_three = true;
                    sum += v * 3;
                } else if (counts[v] == 2) {
                    has_two = true;
                    sum += v * 2;
                }
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
            return total;

        case category::yacht:
            for (int v = 1; v <= 6; ++v) {
                if (counts[v] == 5) {
                    return 50;
                }
            }
            return 0;
    }

    // Should never reach here.
    return 0;
}

int score(const std::vector<int>& dice, const std::string& cat_str)
{
    category cat;
    if      (cat_str == "ones")             cat = category::ones;
    else if (cat_str == "twos")             cat = category::twos;
    else if (cat_str == "threes")           cat = category::threes;
    else if (cat_str == "fours")            cat = category::fours;
    else if (cat_str == "fives")            cat = category::fives;
    else if (cat_str == "sixes")            cat = category::sixes;
    else if (cat_str == "full house")       cat = category::full_house;
    else if (cat_str == "four of a kind")   cat = category::four_of_a_kind;
    else if (cat_str == "little straight")  cat = category::little_straight;
    else if (cat_str == "big straight")     cat = category::big_straight;
    else if (cat_str == "choice")           cat = category::choice;
    else if (cat_str == "yacht")            cat = category::yacht;
    else                                    return 0;   // unknown category

    return score(dice, cat);
}

}  // namespace yacht
