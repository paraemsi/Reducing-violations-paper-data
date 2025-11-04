#include "yacht.h"

#include <array>
#include <numeric>

namespace yacht {

int score(const std::vector<int>& dice, const std::string& cat) {
    category c;
    if (cat == "ones") c = category::ones;
    else if (cat == "twos") c = category::twos;
    else if (cat == "threes") c = category::threes;
    else if (cat == "fours") c = category::fours;
    else if (cat == "fives") c = category::fives;
    else if (cat == "sixes") c = category::sixes;
    else if (cat == "full house") c = category::full_house;
    else if (cat == "four of a kind") c = category::four_of_a_kind;
    else if (cat == "little straight") c = category::little_straight;
    else if (cat == "big straight") c = category::big_straight;
    else if (cat == "choice") c = category::choice;
    else if (cat == "yacht") c = category::yacht;
    else return 0;

    return score(dice, c);
}

int score(const std::vector<int>& dice, const char* cat) {
    return score(dice, std::string{cat});
}

int score(const std::vector<int>& dice, category cat) {
    std::array<int, 7> counts{};  // 1..6 used
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            counts[d]++;
        }
    }

    const int total = std::accumulate(dice.begin(), dice.end(), 0);

    switch (cat) {
        case category::ones:   return counts[1] * 1;
        case category::twos:   return counts[2] * 2;
        case category::threes: return counts[3] * 3;
        case category::fours:  return counts[4] * 4;
        case category::fives:  return counts[5] * 5;
        case category::sixes:  return counts[6] * 6;

        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 3) has_three = true;
                else if (counts[face] == 2) has_two = true;
            }
            return (has_three && has_two) ? total : 0;
        }

        case category::four_of_a_kind: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] >= 4) {
                    return 4 * face;
                }
            }
            return 0;
        }

        case category::little_straight: {
            bool ok = counts[6] == 0;
            for (int face = 1; face <= 5 && ok; ++face) {
                ok = counts[face] == 1;
            }
            return ok ? 30 : 0;
        }

        case category::big_straight: {
            bool ok = counts[1] == 0;
            for (int face = 2; face <= 6 && ok; ++face) {
                ok = counts[face] == 1;
            }
            return ok ? 30 : 0;
        }

        case category::choice:
            return total;

        case category::yacht: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 5) return 50;
            }
            return 0;
        }
    }

    return 0;  // Fallback (should be unreachable)
}

}  // namespace yacht
