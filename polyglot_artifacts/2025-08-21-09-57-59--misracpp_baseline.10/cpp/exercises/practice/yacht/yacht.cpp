#include "yacht.h"
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <string>
#include <cctype>

namespace yacht {

namespace {
    // Helper to convert string to lower case
    std::string to_lower(const std::string& s) {
        std::string out;
        for (char c : s) out += std::tolower(c);
        return out;
    }

    // Helper to map string to Category
    Category category_from_string(const std::string& cat) {
        std::string c = to_lower(cat);
        if (c == "ones") return Category::Ones;
        if (c == "twos") return Category::Twos;
        if (c == "threes") return Category::Threes;
        if (c == "fours") return Category::Fours;
        if (c == "fives") return Category::Fives;
        if (c == "sixes") return Category::Sixes;
        if (c == "full house") return Category::FullHouse;
        if (c == "four of a kind") return Category::FourOfAKind;
        if (c == "little straight") return Category::LittleStraight;
        if (c == "big straight") return Category::BigStraight;
        if (c == "choice") return Category::Choice;
        if (c == "yacht") return Category::Yacht;
        throw std::invalid_argument("Unknown category: " + cat);
    }
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
            std::set<int> ls{1,2,3,4,5};
            if (std::set<int>(dice.begin(), dice.end()) == ls) {
                return 30;
            }
            return 0;
        }
        case Category::BigStraight: {
            std::set<int> bs{2,3,4,5,6};
            if (std::set<int>(dice.begin(), dice.end()) == bs) {
                return 30;
            }
            return 0;
        }
        case Category::Choice: {
            return std::accumulate(dice.begin(), dice.end(), 0);
        }
        case Category::Yacht: {
            if (counts.size() == 1) {
                return 50;
            }
            return 0;
        }
        default:
            return 0;
    }
}

int score(const std::vector<int>& dice, const std::string& category) {
    return score(dice, category_from_string(category));
}

}  // namespace yacht
