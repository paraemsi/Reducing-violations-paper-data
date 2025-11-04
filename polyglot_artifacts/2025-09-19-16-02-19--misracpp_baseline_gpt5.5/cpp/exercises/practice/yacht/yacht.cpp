#include "yacht.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <numeric>
#include <string>

namespace yacht {

namespace {
std::array<int, 7> count_faces(const std::vector<int>& dice) {
    std::array<int, 7> counts{};
    counts.fill(0);
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

category parse_category(const std::string& s) {
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
    return category::choice;
}
}  // namespace

int score(const std::vector<int>& dice, category cat) {
    const auto counts = count_faces(dice);

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
            return face * counts[static_cast<std::size_t>(face)];
        }

        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (std::size_t face = 1; face <= 6; ++face) {
                if (counts[face] == 3) has_three = true;
                else if (counts[face] == 2) has_two = true;
            }
            return (has_three && has_two) ? sum(dice) : 0;
        }

        case category::four_of_a_kind: {
            for (std::size_t face = 1; face <= 6; ++face) {
                if (counts[face] >= 4) {
                    return static_cast<int>(4 * face);
                }
            }
            return 0;
        }

        case category::little_straight: {
            // Exactly 1,2,3,4,5
            if (counts[1] == 1 && counts[2] == 1 && counts[3] == 1 &&
                counts[4] == 1 && counts[5] == 1 && counts[6] == 0) {
                return 30;
            }
            return 0;
        }

        case category::big_straight: {
            // Exactly 2,3,4,5,6
            if (counts[1] == 0 && counts[2] == 1 && counts[3] == 1 &&
                counts[4] == 1 && counts[5] == 1 && counts[6] == 1) {
                return 30;
            }
            return 0;
        }

        case category::choice:
            return sum(dice);

        case category::yacht: {
            for (std::size_t face = 1; face <= 6; ++face) {
                if (counts[face] == 5) {
                    return 50;
                }
            }
            return 0;
        }
    }

    return 0;  // Fallback, should not be reached.
}

int score(const std::vector<int>& dice, const std::string& cat) {
    return score(dice, parse_category(cat));
}

int score(const std::vector<int>& dice, const char* cat) {
    if (cat == nullptr) {
        return score(dice, category::choice);
    }
    return score(dice, std::string{cat});
}

}  // namespace yacht
