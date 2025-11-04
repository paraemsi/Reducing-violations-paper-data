#include "yacht.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <string>
#include <unordered_map>

namespace yacht {

int score(const std::vector<int>& dice, category cat) {
    // counts[face] gives how many times the die face appears; index 0 unused
    std::array<int, 7> counts{};

    for (int d : dice) {
        if (d < 1 || d > 6) {
            return 0;  // invalid die face value
        }
        counts[d]++;
    }

    switch (cat) {
        case category::ones:   return counts[1] * 1;
        case category::twos:   return counts[2] * 2;
        case category::threes: return counts[3] * 3;
        case category::fours:  return counts[4] * 4;
        case category::fives:  return counts[5] * 5;
        case category::sixes:  return counts[6] * 6;

        case category::full_house: {
            bool has_three = false;
            bool has_two   = false;
            int total = 0;

            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 3) has_three = true;
                else if (counts[face] == 2) has_two = true;
                total += counts[face] * face;
            }
            return (has_three && has_two) ? total : 0;
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
            return std::accumulate(dice.begin(), dice.end(), 0);

        case category::yacht:
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 5) return 50;
            }
            return 0;
    }

    return 0;  // should never reach here
}

int score(const std::vector<int>& dice, const std::string& cat_str) {
    static const std::unordered_map<std::string, category> lookup{
        {"ones", category::ones},
        {"twos", category::twos},
        {"threes", category::threes},
        {"fours", category::fours},
        {"fives", category::fives},
        {"sixes", category::sixes},
        {"full house", category::full_house},
        {"four of a kind", category::four_of_a_kind},
        {"little straight", category::little_straight},
        {"big straight", category::big_straight},
        {"choice", category::choice},
        {"yacht", category::yacht}
    };

    auto it = lookup.find(cat_str);
    if (it == lookup.end()) {
        return 0;  // unknown category string
    }
    return score(dice, it->second);
}

}  // namespace yacht
