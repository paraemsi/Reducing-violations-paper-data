#include "yacht.h"
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <string>
#include <cctype>

namespace yacht {

Category category_from_string(const std::string& category) {
    std::string s = category;
    // Remove spaces and convert to lower case for matching
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);

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
    if (s == "yacht") return Category::Yacht;
    throw std::invalid_argument("Unknown category: " + category);
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

}  // namespace yacht
