#include "yacht.h"

#include <array>
#include <cstddef>
#include <string>

namespace yacht {


int score(const std::vector<int>& dice, const char* cat) {
    return score(dice, std::string{cat ? cat : ""});
}

int score(const std::vector<int>& dice, const std::string& cat) {
    std::array<int, 7> counts{};  // indices 1..6 used
    int sum = 0;
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            ++counts[static_cast<std::size_t>(d)];
            sum += d;
        }
    }

    category cat_enum{};
    if (cat == "ones") cat_enum = category::ones;
    else if (cat == "twos") cat_enum = category::twos;
    else if (cat == "threes") cat_enum = category::threes;
    else if (cat == "fours") cat_enum = category::fours;
    else if (cat == "fives") cat_enum = category::fives;
    else if (cat == "sixes") cat_enum = category::sixes;
    else if (cat == "full house") cat_enum = category::full_house;
    else if (cat == "four of a kind") cat_enum = category::four_of_a_kind;
    else if (cat == "little straight") cat_enum = category::little_straight;
    else if (cat == "big straight") cat_enum = category::big_straight;
    else if (cat == "choice") cat_enum = category::choice;
    else if (cat == "yacht") cat_enum = category::yacht;
    else return 0;

    switch (cat_enum) {
        case category::ones:   return counts[1] * 1;
        case category::twos:   return counts[2] * 2;
        case category::threes: return counts[3] * 3;
        case category::fours:  return counts[4] * 4;
        case category::fives:  return counts[5] * 5;
        case category::sixes:  return counts[6] * 6;

        case category::choice:
            return sum;

        case category::yacht: {
            for (std::size_t face = 1; face <= 6; ++face) {
                if (counts[face] == 5) return 50;
            }
            return 0;
        }

        case category::four_of_a_kind: {
            for (std::size_t face = 1; face <= 6; ++face) {
                if (counts[face] >= 4) {
                    return static_cast<int>(face) * 4;
                }
            }
            return 0;
        }

        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (std::size_t face = 1; face <= 6; ++face) {
                if (counts[face] == 3) has_three = true;
                else if (counts[face] == 2) has_two = true;
                else if (counts[face] == 5) return 0;  // five of a kind is not a full house
            }
            return (has_three && has_two) ? sum : 0;
        }

        case category::little_straight: {
            if (counts[1] == 1 && counts[2] == 1 && counts[3] == 1 &&
                counts[4] == 1 && counts[5] == 1 && counts[6] == 0) {
                return 30;
            }
            return 0;
        }

        case category::big_straight: {
            if (counts[1] == 0 && counts[2] == 1 && counts[3] == 1 &&
                counts[4] == 1 && counts[5] == 1 && counts[6] == 1) {
                return 30;
            }
            return 0;
        }
    }

    return 0;  // Unreachable for valid enum values
}

}  // namespace yacht
