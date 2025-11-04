#include "yacht.h"

#include <array>
#include <numeric>
#include <string_view>
#include <unordered_map>

namespace yacht {

int score(const std::vector<int>& dice, category cat) {
    std::array<int, 7> counts{}; // index 1..6
    for (int d : dice) {
        if (d < 1 || d > 6) {
            return 0; // safeguard for invalid die values
        }
        ++counts[d];
    }

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            int face = static_cast<int>(cat) + 1;          // enum order matches die faces
            return face * counts[face];
        }

        case category::choice:
            return std::accumulate(dice.begin(), dice.end(), 0);

        case category::yacht:
            for (int v = 1; v <= 6; ++v) {
                if (counts[v] == 5) {
                    return 50;
                }
            }
            return 0;

        case category::four_of_a_kind:
            for (int v = 1; v <= 6; ++v) {
                if (counts[v] >= 4) {
                    return 4 * v;
                }
            }
            return 0;

        case category::full_house: {
            bool has_three = false, has_two = false;
            int total = 0;
            for (int v = 1; v <= 6; ++v) {
                if (counts[v] == 3) has_three = true;
                if (counts[v] == 2) has_two = true;
                total += counts[v] * v;
            }
            return (has_three && has_two) ? total : 0;
        }

        case category::little_straight:
            return (counts[1] == 1 && counts[2] == 1 && counts[3] == 1 &&
                    counts[4] == 1 && counts[5] == 1 && counts[6] == 0)
                       ? 30
                       : 0;

        case category::big_straight:
            return (counts[1] == 0 && counts[2] == 1 && counts[3] == 1 &&
                    counts[4] == 1 && counts[5] == 1 && counts[6] == 1)
                       ? 30
                       : 0;
    }

    return 0; // should be unreachable
}

int score(const std::vector<int>& dice, std::string_view cat) {
    static const std::unordered_map<std::string_view, category> mapping{
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
        {"yacht", category::yacht},
    };
    auto it = mapping.find(cat);
    if (it == mapping.end()) {
        return 0;
    }
    return score(dice, it->second);
}

}  // namespace yacht
