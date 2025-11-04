#include "yacht.h"

#include <array>
#include <string>

namespace yacht {

static bool to_category(const std::string& name, category& out) {
    if (name == "ones") { out = category::ones; return true; }
    if (name == "twos") { out = category::twos; return true; }
    if (name == "threes") { out = category::threes; return true; }
    if (name == "fours") { out = category::fours; return true; }
    if (name == "fives") { out = category::fives; return true; }
    if (name == "sixes") { out = category::sixes; return true; }
    if (name == "full house") { out = category::full_house; return true; }
    if (name == "four of a kind") { out = category::four_of_a_kind; return true; }
    if (name == "little straight") { out = category::little_straight; return true; }
    if (name == "big straight") { out = category::big_straight; return true; }
    if (name == "choice") { out = category::choice; return true; }
    if (name == "yacht") { out = category::yacht; return true; }
    return false;
}

int score(const std::vector<int>& dice, const std::string& cat_name) {
    category c;
    if (!to_category(cat_name, c)) return 0;
    return score(dice, c);
}

int score(const std::vector<int>& dice, const char* cat_name) {
    return score(dice, std::string(cat_name ? cat_name : ""));
}

int score(const std::vector<int>& dice, category cat) {
    std::array<int, 7> counts{};  // counts[1..6]
    int sum = 0;
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            counts[d]++;
            sum += d;
        }
    }

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            int face = 0;
            switch (cat) {
                case category::ones:   face = 1; break;
                case category::twos:   face = 2; break;
                case category::threes: face = 3; break;
                case category::fours:  face = 4; break;
                case category::fives:  face = 5; break;
                case category::sixes:  face = 6; break;
                default: break;
            }
            return face * counts[face];
        }

        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 3) has_three = true;
                else if (counts[face] == 2) has_two = true;
            }
            return (has_three && has_two) ? sum : 0;
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
            for (int face = 1; face <= 5; ++face) {
                if (counts[face] != 1) return 0;
            }
            return counts[6] == 0 ? 30 : 0;
        }

        case category::big_straight: {
            for (int face = 2; face <= 6; ++face) {
                if (counts[face] != 1) return 0;
            }
            return counts[1] == 0 ? 30 : 0;
        }

        case category::choice:
            return sum;

        case category::yacht: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 5) return 50;
            }
            return 0;
        }
    }

    return 0;
}

}  // namespace yacht
