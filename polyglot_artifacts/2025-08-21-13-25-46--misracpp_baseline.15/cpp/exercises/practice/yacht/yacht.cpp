#include "yacht.h"
#include <algorithm>
#include <numeric>
#include <array>
#include <map>
#include <string>
#include <stdexcept>
#include <cctype>

namespace yacht {

Category parse_category(const std::string& name) {
    std::string n;
    // Lowercase and remove spaces/underscores for matching
    for (char c : name) {
        if (std::isalpha(c))
            n += std::tolower(c);
    }
    if (n == "ones") return Category::Ones;
    if (n == "twos") return Category::Twos;
    if (n == "threes") return Category::Threes;
    if (n == "fours") return Category::Fours;
    if (n == "fives") return Category::Fives;
    if (n == "sixes") return Category::Sixes;
    if (n == "fullhouse") return Category::FullHouse;
    if (n == "fourofakind") return Category::FourOfAKind;
    if (n == "littlestraight") return Category::LittleStraight;
    if (n == "bigstraight") return Category::BigStraight;
    if (n == "choice") return Category::Choice;
    if (n == "yacht") return Category::Yacht;
    throw std::invalid_argument("Unknown category: " + name);
}

int score(const std::vector<int>& dice, const std::string& category_name) {
    return score(dice, parse_category(category_name));
}

int score(const std::vector<int>& dice, Category category) {
    std::array<int, 7> counts{}; // index 1-6
    for (int d : dice) {
        if (d >= 1 && d <= 6)
            counts[d]++;
    }

    switch (category) {
        case Category::Ones:
        case Category::Twos:
        case Category::Threes:
        case Category::Fours:
        case Category::Fives:
        case Category::Sixes: {
            int face = static_cast<int>(category) + 1;
            return face * counts[face];
        }
        case Category::FullHouse: {
            bool has_three = false, has_two = false;
            int three_val = 0, two_val = 0;
            for (int i = 1; i <= 6; ++i) {
                if (counts[i] == 3) {
                    has_three = true;
                    three_val = i;
                }
                if (counts[i] == 2) {
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
        case Category::Choice: {
            return std::accumulate(dice.begin(), dice.end(), 0);
        }
        case Category::Yacht: {
            for (int i = 1; i <= 6; ++i) {
                if (counts[i] == 5)
                    return 50;
            }
            return 0;
        }
    }
    return 0;
}

}  // namespace yacht
