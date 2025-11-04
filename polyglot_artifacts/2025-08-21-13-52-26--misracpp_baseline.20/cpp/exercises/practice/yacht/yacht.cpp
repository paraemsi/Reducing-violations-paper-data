#include "yacht.h"
#include <algorithm>
#include <numeric>
#include <map>
#include <array>
#include <string>
#include <cctype>

namespace yacht {

Category parse_category(const std::string& category) {
    std::string s;
    // Lowercase and remove spaces/underscores for robust matching
    for (char c : category) {
        if (std::isalpha(c))
            s += std::tolower(c);
    }
    if (s == "yacht") return Category::Yacht;
    if (s == "ones") return Category::Ones;
    if (s == "twos") return Category::Twos;
    if (s == "threes") return Category::Threes;
    if (s == "fours") return Category::Fours;
    if (s == "fives") return Category::Fives;
    if (s == "sixes") return Category::Sixes;
    if (s == "fullhouse") return Category::FullHouse;
    if (s == "fourofakind") return Category::FourOfAKind;
    if (s == "littlestraight") return Category::LittleStraight;
    if (s == "bigstraight") return Category::BigStraight;
    if (s == "choice") return Category::Choice;
    throw std::invalid_argument("Unknown category: " + category);
}

int score(const std::vector<int>& dice, const std::string& category) {
    return score(dice, parse_category(category));
}

int score(const std::vector<int>& dice, Category category) {
    std::array<int, 7> counts{}; // index 1-6
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            counts[d]++;
        }
    }

    switch (category) {
        case Category::Ones:
            return counts[1] * 1;
        case Category::Twos:
            return counts[2] * 2;
        case Category::Threes:
            return counts[3] * 3;
        case Category::Fours:
            return counts[4] * 4;
        case Category::Fives:
            return counts[5] * 5;
        case Category::Sixes:
            return counts[6] * 6;
        case Category::FullHouse: {
            bool has_three = false, has_two = false;
            int three_val = 0, two_val = 0;
            for (int i = 1; i <= 6; ++i) {
                if (counts[i] == 3) {
                    has_three = true;
                    three_val = i;
                } else if (counts[i] == 2) {
                    has_two = true;
                    two_val = i;
                }
            }
            if (has_three && has_two)
                return three_val * 3 + two_val * 2;
            return 0;
        }
        case Category::FourOfAKind: {
            for (int i = 1; i <= 6; ++i) {
                if (counts[i] >= 4)
                    return i * 4;
            }
            return 0;
        }
        case Category::LittleStraight: {
            // 1,2,3,4,5
            for (int i = 1; i <= 5; ++i) {
                if (counts[i] != 1)
                    return 0;
            }
            if (counts[6] == 0)
                return 30;
            return 0;
        }
        case Category::BigStraight: {
            // 2,3,4,5,6
            for (int i = 2; i <= 6; ++i) {
                if (counts[i] != 1)
                    return 0;
            }
            if (counts[1] == 0)
                return 30;
            return 0;
        }
        case Category::Choice:
            return std::accumulate(dice.begin(), dice.end(), 0);
        case Category::Yacht: {
            for (int i = 1; i <= 6; ++i) {
                if (counts[i] == 5)
                    return 50;
            }
            return 0;
        }
        default:
            return 0;
    }
}

}  // namespace yacht
