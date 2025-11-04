#include "yacht.h"

#include <array>
#include <algorithm>
#include <numeric>
#include <string>
#include <unordered_map>

namespace yacht {

namespace {

constexpr int kStraightScore = 30;
constexpr int kYachtScore    = 50;

bool is_little_straight(const std::array<int, 7>& freq) {
    // 1-2-3-4-5 means one of each of the first five faces.
    return std::all_of(freq.begin() + 1, freq.begin() + 6,
                       [](int f) { return f == 1; }) &&
           freq[6] == 0;
}

bool is_big_straight(const std::array<int, 7>& freq) {
    // 2-3-4-5-6 means one of each of faces 2-6.
    return freq[1] == 0 &&
           std::all_of(freq.begin() + 2, freq.end(),
                       [](int f) { return f == 1; });
}

}  // namespace

int score(const std::vector<int>& dice, Category category) {
    if (dice.size() != 5) {
        return 0;
    }

    std::array<int, 7> freq{};  // index 0 unused
    for (int die : dice) {
        if (die < 1 || die > 6) {
            return 0;
        }
        ++freq[die];
    }

    const int total = std::accumulate(dice.begin(), dice.end(), 0);

    switch (category) {
        case Category::Ones:
        case Category::Twos:
        case Category::Threes:
        case Category::Fours:
        case Category::Fives:
        case Category::Sixes: {
            int face = static_cast<int>(category) + 1;  // Ones=0 … Sixes=5
            return freq[face] * face;
        }

        case Category::FullHouse: {
            bool has_three = false;
            bool has_two   = false;
            for (int face = 1; face <= 6; ++face) {
                if (freq[face] == 3) has_three = true;
                if (freq[face] == 2) has_two   = true;
            }
            return (has_three && has_two) ? total : 0;
        }

        case Category::FourOfAKind: {
            for (int face = 1; face <= 6; ++face) {
                if (freq[face] >= 4) {
                    return face * 4;
                }
            }
            return 0;
        }

        case Category::LittleStraight:
            return is_little_straight(freq) ? kStraightScore : 0;

        case Category::BigStraight:
            return is_big_straight(freq) ? kStraightScore : 0;

        case Category::Choice:
            return total;

        case Category::Yacht:
            return std::any_of(freq.begin(), freq.end(),
                               [](int f) { return f == 5; })
                       ? kYachtScore
                       : 0;
    }

    // Should never reach here.
    return 0;
}

int score(const std::vector<int>& dice, const std::string& category_str) {
    static const std::unordered_map<std::string, Category> mapping{
        {"ones", Category::Ones},
        {"twos", Category::Twos},
        {"threes", Category::Threes},
        {"fours", Category::Fours},
        {"fives", Category::Fives},
        {"sixes", Category::Sixes},
        {"full house", Category::FullHouse},
        {"four of a kind", Category::FourOfAKind},
        {"little straight", Category::LittleStraight},
        {"big straight", Category::BigStraight},
        {"choice", Category::Choice},
        {"yacht", Category::Yacht},
    };

    auto it = mapping.find(category_str);
    if (it == mapping.end()) {
        return 0;  // Unknown category string.
    }
    return score(dice, it->second);
}

}  // namespace yacht
