#include "yacht.h"

#include <array>
#include <string>
#include <stdexcept>
#include <vector>

namespace yacht {

static category parse_category(const std::string& s) {
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
    throw std::invalid_argument("Unknown category: " + s);
}

int score(const std::vector<int>& dice, const std::string& cat) {
    return score(dice, parse_category(cat));
}

int score(const std::vector<int>& dice, category cat) {
    std::array<int, 7> counts{};
    int sum = 0;
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            counts[d]++;
            sum += d;
        }
    }

    switch (cat) {
        case category::ones:   return counts[1] * 1;
        case category::twos:   return counts[2] * 2;
        case category::threes: return counts[3] * 3;
        case category::fours:  return counts[4] * 4;
        case category::fives:  return counts[5] * 5;
        case category::sixes:  return counts[6] * 6;

        case category::choice:
            return sum;

        case category::yacht:
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 5) {
                    return 50;
                }
            }
            return 0;

        case category::four_of_a_kind:
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] >= 4) {
                    return face * 4;
                }
            }
            return 0;

        case category::full_house: {
            bool has_three = false, has_two = false;
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 3) {
                    has_three = true;
                } else if (counts[face] == 2) {
                    has_two = true;
                } else if (counts[face] == 5) {
                    // A yacht is not a full house
                    return 0;
                }
            }
            return (has_three && has_two) ? sum : 0;
        }

        case category::little_straight:
            if (counts[6] != 0) return 0;
            for (int face = 1; face <= 5; ++face) {
                if (counts[face] != 1) return 0;
            }
            return 30;

        case category::big_straight:
            if (counts[1] != 0) return 0;
            for (int face = 2; face <= 6; ++face) {
                if (counts[face] != 1) return 0;
            }
            return 30;
    }

    return 0;
}

}  // namespace yacht
