#include "yacht.h"

#include <array>
#include <cstring>
#include <stdexcept>

namespace {
constexpr int kStraightScore = 30;
constexpr int kYachtScore = 50;

using yacht::category;

inline category parse_category(const char* name) {
    if (std::strcmp(name, "ones") == 0) return category::ones;
    if (std::strcmp(name, "twos") == 0) return category::twos;
    if (std::strcmp(name, "threes") == 0) return category::threes;
    if (std::strcmp(name, "fours") == 0) return category::fours;
    if (std::strcmp(name, "fives") == 0) return category::fives;
    if (std::strcmp(name, "sixes") == 0) return category::sixes;
    if (std::strcmp(name, "full house") == 0) return category::full_house;
    if (std::strcmp(name, "four of a kind") == 0) return category::four_of_a_kind;
    if (std::strcmp(name, "little straight") == 0) return category::little_straight;
    if (std::strcmp(name, "big straight") == 0) return category::big_straight;
    if (std::strcmp(name, "choice") == 0) return category::choice;
    if (std::strcmp(name, "yacht") == 0) return category::yacht;
    throw std::invalid_argument("Unknown category");
}
}

namespace yacht {

int score(const std::vector<int>& dice, const char* cat) {
    return score(dice, ::parse_category(cat));
}

int score(const std::vector<int>& dice, category cat) {
    std::array<int, 7> counts{};  // index 1..6 used
    int sum = 0;
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            counts[d]++;
        }
        sum += d;
    }

    switch (cat) {
        case category::ones:
            return 1 * counts[1];
        case category::twos:
            return 2 * counts[2];
        case category::threes:
            return 3 * counts[3];
        case category::fours:
            return 4 * counts[4];
        case category::fives:
            return 5 * counts[5];
        case category::sixes:
            return 6 * counts[6];
        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (int p = 1; p <= 6; ++p) {
                if (counts[p] == 3) {
                    has_three = true;
                } else if (counts[p] == 2) {
                    has_two = true;
                }
            }
            return (has_three && has_two) ? sum : 0;
        }
        case category::four_of_a_kind: {
            for (int p = 1; p <= 6; ++p) {
                if (counts[p] >= 4) {
                    return 4 * p;
                }
            }
            return 0;
        }
        case category::little_straight: {
            bool ok = counts[1] == 1 && counts[2] == 1 && counts[3] == 1 &&
                      counts[4] == 1 && counts[5] == 1 && counts[6] == 0;
            return ok ? kStraightScore : 0;
        }
        case category::big_straight: {
            bool ok = counts[1] == 0 && counts[2] == 1 && counts[3] == 1 &&
                      counts[4] == 1 && counts[5] == 1 && counts[6] == 1;
            return ok ? kStraightScore : 0;
        }
        case category::choice:
            return sum;
        case category::yacht: {
            for (int p = 1; p <= 6; ++p) {
                if (counts[p] == 5) {
                    return kYachtScore;
                }
            }
            return 0;
        }
    }

    return 0;  // Unreachable with valid category
}

}  // namespace yacht
