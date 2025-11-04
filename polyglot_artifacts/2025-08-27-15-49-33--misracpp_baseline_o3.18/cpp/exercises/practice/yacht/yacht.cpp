#include "yacht.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <unordered_map>
#include <string>

namespace yacht {

namespace {

constexpr int kLittleStraightScore = 30;
constexpr int kBigStraightScore    = 30;
constexpr int kYachtScore          = 50;

}  // namespace

int score(const std::vector<int>& dice, Category category) {
    if (dice.size() != 5) {
        return 0;  // Defensive – spec guarantees five dice but avoid UB.
    }

    // Count occurrences of each face (1..6)
    std::array<int, 7> counts{};  // index 0 unused
    for (int die : dice) {
        if (die < 1 || die > 6) {
            return 0;  // Invalid die value, defensive.
        }
        ++counts[die];
    }

    auto all_equal = [&](int count) {
        return std::any_of(counts.begin() + 1, counts.end(),
                           [=](int c) { return c == count; });
    };

    switch (category) {
        case Category::ones:
        case Category::twos:
        case Category::threes:
        case Category::fours:
        case Category::fives:
        case Category::sixes: {
            int face = static_cast<int>(category) + 1;  // ones==0 maps to 1, etc.
            return face * counts[face];
        }

        case Category::full_house: {
            bool has_three = false, has_two = false;
            for (int c : counts) {
                if (c == 3) has_three = true;
                if (c == 2) has_two   = true;
            }
            if (has_three && has_two) {
                return std::accumulate(dice.begin(), dice.end(), 0);
            }
            return 0;
        }

        case Category::four_of_a_kind: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] >= 4) {
                    return face * 4;
                }
            }
            return 0;
        }

        case Category::little_straight: {
            bool matches =
                counts[1] == 1 && counts[2] == 1 && counts[3] == 1 &&
                counts[4] == 1 && counts[5] == 1 && counts[6] == 0;
            return matches ? kLittleStraightScore : 0;
        }

        case Category::big_straight: {
            bool matches =
                counts[1] == 0 && counts[2] == 1 && counts[3] == 1 &&
                counts[4] == 1 && counts[5] == 1 && counts[6] == 1;
            return matches ? kBigStraightScore : 0;
        }

        case Category::choice:
            return std::accumulate(dice.begin(), dice.end(), 0);

        case Category::yacht:
            return all_equal(5) ? kYachtScore : 0;
    }

    return 0;  // Should be unreachable.
}

int score(const std::vector<int>& dice, const std::string& category_str) {
    static const std::unordered_map<std::string, Category> kLookup{
        {"ones", Category::ones},
        {"twos", Category::twos},
        {"threes", Category::threes},
        {"fours", Category::fours},
        {"fives", Category::fives},
        {"sixes", Category::sixes},
        {"full house", Category::full_house},
        {"four of a kind", Category::four_of_a_kind},
        {"little straight", Category::little_straight},
        {"big straight", Category::big_straight},
        {"choice", Category::choice},
        {"yacht", Category::yacht},
    };

    auto it = kLookup.find(category_str);
    if (it == kLookup.end()) {
        return 0;  // Unknown category name supplied.
    }
    return score(dice, it->second);
}


}  // namespace yacht
