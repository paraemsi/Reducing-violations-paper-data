#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <numeric>
#include <set>
#include <string>

namespace yacht {

int score(const std::vector<int>& dice, const std::string& category) {
    if (category == "ones") {
        int count = std::count(dice.begin(), dice.end(), 1);
        return count * 1;
    } else if (category == "twos") {
        int count = std::count(dice.begin(), dice.end(), 2);
        return count * 2;
    } else if (category == "threes") {
        int count = std::count(dice.begin(), dice.end(), 3);
        return count * 3;
    } else if (category == "fours") {
        int count = std::count(dice.begin(), dice.end(), 4);
        return count * 4;
    } else if (category == "fives") {
        int count = std::count(dice.begin(), dice.end(), 5);
        return count * 5;
    } else if (category == "sixes") {
        int count = std::count(dice.begin(), dice.end(), 6);
        return count * 6;
    } else if (category == "full house") {
        std::map<int, int> counts;
        for (int num : dice) {
            counts[num]++;
        }
        bool hasThree = false;
        bool hasTwo = false;
        for (const auto& pair : counts) {
            if (pair.second == 3) hasThree = true;
            if (pair.second == 2) hasTwo = true;
        }
        if (hasThree && hasTwo && counts.size() == 2) {
            return std::accumulate(dice.begin(), dice.end(), 0);
        }
        return 0;
    } else if (category == "four of a kind") {
        std::map<int, int> counts;
        for (int num : dice) {
            counts[num]++;
        }
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                return 4 * pair.first;
            }
        }
        return 0;
    } else if (category == "little straight") {
        std::set<int> unique(dice.begin(), dice.end());
        if (unique.size() == 5 && *unique.rbegin() == 5 && *unique.begin() == 1) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        std::set<int> unique(dice.begin(), dice.end());
        if (unique.size() == 5 && *unique.rbegin() == 6 && *unique.begin() == 2) {
            return 30;
        }
        return 0;
    } else if (category == "choice") {
        return std::accumulate(dice.begin(), dice.end(), 0);
    } else if (category == "yacht") {
        if (std::all_of(dice.begin(), dice.end(), [&](int num) { return num == dice[0]; })) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
