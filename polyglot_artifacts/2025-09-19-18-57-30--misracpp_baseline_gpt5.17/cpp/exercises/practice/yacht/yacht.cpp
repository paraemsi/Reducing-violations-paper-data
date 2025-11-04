#include "yacht.h"

#include <array>
#include <numeric>

namespace yacht {

namespace {
std::array<int, 7> make_counts(const std::vector<int>& dice) {
    std::array<int, 7> counts{};  // 0..6, ignore index 0
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            ++counts[d];
        }
    }
    return counts;
}
}  // namespace

int score(const std::vector<int>& dice, category cat) {
    const auto counts = make_counts(dice);
    const int sum_all = std::accumulate(dice.begin(), dice.end(), 0);

    switch (cat) {
        case category::ones:   return counts[1] * 1;
        case category::twos:   return counts[2] * 2;
        case category::threes: return counts[3] * 3;
        case category::fours:  return counts[4] * 4;
        case category::fives:  return counts[5] * 5;
        case category::sixes:  return counts[6] * 6;

        case category::full_house: {
            bool has_three = false, has_two = false;
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 3) has_three = true;
                if (counts[face] == 2) has_two = true;
            }
            return (has_three && has_two) ? sum_all : 0;
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
            if (counts[6] != 0) return 0;
            for (int face = 1; face <= 5; ++face) {
                if (counts[face] != 1) return 0;
            }
            return 30;
        }

        case category::big_straight: {
            if (counts[1] != 0) return 0;
            for (int face = 2; face <= 6; ++face) {
                if (counts[face] != 1) return 0;
            }
            return 30;
        }

        case category::choice:
            return sum_all;

        case category::yacht:
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 5) return 50;
            }
            return 0;
    }

    return 0;
}

int score(const std::vector<int>& dice, std::string_view category_name) {
    if (category_name == "ones")            return score(dice, category::ones);
    if (category_name == "twos")            return score(dice, category::twos);
    if (category_name == "threes")          return score(dice, category::threes);
    if (category_name == "fours")           return score(dice, category::fours);
    if (category_name == "fives")           return score(dice, category::fives);
    if (category_name == "sixes")           return score(dice, category::sixes);
    if (category_name == "full house")      return score(dice, category::full_house);
    if (category_name == "four of a kind")  return score(dice, category::four_of_a_kind);
    if (category_name == "little straight") return score(dice, category::little_straight);
    if (category_name == "big straight")    return score(dice, category::big_straight);
    if (category_name == "choice")          return score(dice, category::choice);
    if (category_name == "yacht")           return score(dice, category::yacht);
    return 0;  // Unknown category name
}

}  // namespace yacht
