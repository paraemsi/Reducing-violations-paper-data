#include "yacht.h"

#include <algorithm>
#include <numeric>
#include <string>

namespace yacht {

Category string_to_category(const std::string& cat) {
    if (cat == "ones") return Category::Ones;
    if (cat == "twos") return Category::Twos;
    if (cat == "threes") return Category::Threes;
    if (cat == "fours") return Category::Fours;
    if (cat == "fives") return Category::Fives;
    if (cat == "sixes") return Category::Sixes;
    if (cat == "full house") return Category::FullHouse;
    if (cat == "four of a kind") return Category::FourOfAKind;
    if (cat == "little straight") return Category::LittleStraight;
    if (cat == "big straight") return Category::BigStraight;
    if (cat == "choice") return Category::Choice;
    if (cat == "yacht") return Category::Yacht;
    // Default, but shouldn't happen
    return Category::Ones;
}

int score(const std::vector<int>& dice, const std::string& category) {
    Category cat = string_to_category(category);
    if (dice.size() != 5) {
        return 0;  // Invalid input, but per instructions, assume always 5 dice
    }

    std::vector<int> counts(7, 0);
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            counts[d]++;
        }
    }

    switch (cat) {
        case Category::Ones:
            return 1 * counts[1];
        case Category::Twos:
            return 2 * counts[2];
        case Category::Threes:
            return 3 * counts[3];
        case Category::Fours:
            return 4 * counts[4];
        case Category::Fives:
            return 5 * counts[5];
        case Category::Sixes:
            return 6 * counts[6];
        case Category::FullHouse: {
            int three_count = 0, two_count = 0;
            for (int i = 1; i <= 6; ++i) {
                if (counts[i] == 3) three_count++;
                if (counts[i] == 2) two_count++;
            }
            if (three_count == 1 && two_count == 1) {
                return std::accumulate(dice.begin(), dice.end(), 0);
            }
            return 0;
        }
        case Category::FourOfAKind: {
            for (int i = 1; i <= 6; ++i) {
                if (counts[i] >= 4) {
                    return i * 4;
                }
            }
            return 0;
        }
        case Category::LittleStraight: {
            std::vector<int> sorted = dice;
            std::sort(sorted.begin(), sorted.end());
            if (sorted == std::vector<int>{1, 2, 3, 4, 5}) {
                return 30;
            }
            return 0;
        }
        case Category::BigStraight: {
            std::vector<int> sorted = dice;
            std::sort(sorted.begin(), sorted.end());
            if (sorted == std::vector<int>{2, 3, 4, 5, 6}) {
                return 30;
            }
            return 0;
        }
        case Category::Choice:
            return std::accumulate(dice.begin(), dice.end(), 0);
        case Category::Yacht: {
            for (int i = 1; i <= 6; ++i) {
                if (counts[i] == 5) {
                    return 50;
                }
            }
            return 0;
        }
        default:
            return 0;
    }
}

}  // namespace yacht
