#include "yacht.h"

#include <array>
#include <numeric>
#include <string>

namespace yacht {

namespace {
std::array<int, 7> tally(const std::vector<int>& dice) {
    std::array<int, 7> counts{};
    counts.fill(0);
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            counts[d]++;
        }
    }
    return counts;
}

int sum_dice(const std::vector<int>& dice) {
    return std::accumulate(dice.begin(), dice.end(), 0);
}

bool is_little_straight(const std::array<int, 7>& c) {
    return c[1] == 1 && c[2] == 1 && c[3] == 1 && c[4] == 1 && c[5] == 1 && c[6] == 0;
}

bool is_big_straight(const std::array<int, 7>& c) {
    return c[1] == 0 && c[2] == 1 && c[3] == 1 && c[4] == 1 && c[5] == 1 && c[6] == 1;
}
}  // namespace

int score(const std::vector<int>& dice, category cat) {
    auto counts = tally(dice);

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            int face = (cat == category::ones) ? 1
                     : (cat == category::twos) ? 2
                     : (cat == category::threes) ? 3
                     : (cat == category::fours) ? 4
                     : (cat == category::fives) ? 5
                     : 6;
            return face * counts[face];
        }
        case category::full_house: {
            bool has2 = false, has3 = false;
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 2) {
                    has2 = true;
                } else if (counts[face] == 3) {
                    has3 = true;
                } else if (counts[face] == 1 || counts[face] == 4 || counts[face] == 5) {
                    return 0;
                }
            }
            return (has2 && has3) ? sum_dice(dice) : 0;
        }
        case category::four_of_a_kind: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] >= 4) {
                    return 4 * face;
                }
            }
            return 0;
        }
        case category::little_straight:
            return is_little_straight(counts) ? 30 : 0;
        case category::big_straight:
            return is_big_straight(counts) ? 30 : 0;
        case category::choice:
            return sum_dice(dice);
        case category::yacht: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 5) {
                    return 50;
                }
            }
            return 0;
        }
    }

    return 0;
}

 

int score(const std::vector<int>& dice, const char* cat) {
    if (cat == nullptr) {
        return 0;
    }
    std::string s(cat);
    if (s == "ones") return score(dice, category::ones);
    if (s == "twos") return score(dice, category::twos);
    if (s == "threes") return score(dice, category::threes);
    if (s == "fours") return score(dice, category::fours);
    if (s == "fives") return score(dice, category::fives);
    if (s == "sixes") return score(dice, category::sixes);
    if (s == "full house") return score(dice, category::full_house);
    if (s == "four of a kind") return score(dice, category::four_of_a_kind);
    if (s == "little straight") return score(dice, category::little_straight);
    if (s == "big straight") return score(dice, category::big_straight);
    if (s == "choice") return score(dice, category::choice);
    if (s == "yacht") return score(dice, category::yacht);
    return 0;
}

}  // namespace yacht
