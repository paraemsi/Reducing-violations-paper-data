#include "yacht.h"
#include <algorithm>
#include <numeric>
#include <map>
#include <string>
#include <cctype>

namespace yacht {

Category category_from_string(const std::string& name) {
    std::string n;
    // Remove spaces and convert to lower case for matching
    for (char c : name) {
        if (!std::isspace(static_cast<unsigned char>(c)))
            n += std::tolower(static_cast<unsigned char>(c));
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

int score(const std::vector<int>& dice, const std::string& category) {
    return score(dice, category_from_string(category));
}

int score(const std::vector<int>& dice, Category category) {
    std::map<int, int> counts;
    for (int d : dice) {
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
            if (counts.size() == 2) {
                bool found_three = false, found_two = false;
                for (const auto& kv : counts) {
                    if (kv.second == 3) found_three = true;
                    if (kv.second == 2) found_two = true;
                }
                if (found_three && found_two) {
                    return std::accumulate(dice.begin(), dice.end(), 0);
                }
            }
            return 0;
        }
        case Category::FourOfAKind: {
            for (const auto& kv : counts) {
                if (kv.second >= 4) {
                    return kv.first * 4;
                }
            }
            return 0;
        }
        case Category::LittleStraight: {
            std::vector<int> ls = {1,2,3,4,5};
            std::vector<int> sorted = dice;
            std::sort(sorted.begin(), sorted.end());
            if (sorted == ls) return 30;
            return 0;
        }
        case Category::BigStraight: {
            std::vector<int> bs = {2,3,4,5,6};
            std::vector<int> sorted = dice;
            std::sort(sorted.begin(), sorted.end());
            if (sorted == bs) return 30;
            return 0;
        }
        case Category::Choice: {
            return std::accumulate(dice.begin(), dice.end(), 0);
        }
        case Category::Yacht: {
            if (counts.size() == 1) return 50;
            return 0;
        }
        default:
            return 0;
    }
}

}  // namespace yacht
