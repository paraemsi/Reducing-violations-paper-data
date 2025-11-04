#include "yacht.h"
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <string>
#include <stdexcept>

namespace yacht {

Category category_from_string(const std::string& name) {
    if (name == "ones") return Category::Ones;
    if (name == "twos") return Category::Twos;
    if (name == "threes") return Category::Threes;
    if (name == "fours") return Category::Fours;
    if (name == "fives") return Category::Fives;
    if (name == "sixes") return Category::Sixes;
    if (name == "full house") return Category::FullHouse;
    if (name == "four of a kind") return Category::FourOfAKind;
    if (name == "little straight") return Category::LittleStraight;
    if (name == "big straight") return Category::BigStraight;
    if (name == "choice") return Category::Choice;
    if (name == "yacht") return Category::Yacht;
    throw std::invalid_argument("Unknown category: " + name);
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
