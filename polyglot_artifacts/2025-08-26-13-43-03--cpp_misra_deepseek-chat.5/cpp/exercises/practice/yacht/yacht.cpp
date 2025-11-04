#include "yacht.h"
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cctype>

namespace yacht {

int score(const std::vector<int>& dice, const std::string& category) {
    // Make a copy to sort
    std::vector<int> sorted_dice = dice;
    std::sort(sorted_dice.begin(), sorted_dice.end());
    
    // Count occurrences of each number
    std::map<int, int> counts;
    for (int num : dice) {
        counts[num]++;
    }
    
    // Convert category to lowercase for case-insensitive comparison
    std::string cat = category;
    std::transform(cat.begin(), cat.end(), cat.begin(), ::tolower);
    
    if (cat == "ones") {
        return counts[1] * 1;
    } else if (cat == "twos") {
        return counts[2] * 2;
    } else if (cat == "threes") {
        return counts[3] * 3;
    } else if (cat == "fours") {
        return counts[4] * 4;
    } else if (cat == "fives") {
        return counts[5] * 5;
    } else if (cat == "sixes") {
        return counts[6] * 6;
    } else if (cat == "full house") {
        // Check if there are exactly two distinct numbers, with counts 3 and 2
        if (counts.size() == 2) {
            auto it = counts.begin();
            int count1 = it->second;
            it++;
            int count2 = it->second;
            if (((count1 == 3) && (count2 == 2)) || ((count1 == 2) && (count2 == 3))) {
                int total = 0;
                for (int num : dice) {
                    total += num;
                }
                return total;
            }
        }
        return 0;
    } else if (cat == "four of a kind") {
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                return pair.first * 4;
            }
        }
        return 0;
    } else if (cat == "little straight") {
        // Check if dice are 1-2-3-4-5
        if (sorted_dice == std::vector<int>{1, 2, 3, 4, 5}) {
            return 30;
        }
        return 0;
    } else if (cat == "big straight") {
        // Check if dice are 2-3-4-5-6
        if (sorted_dice == std::vector<int>{2, 3, 4, 5, 6}) {
            return 30;
        }
        return 0;
    } else if (cat == "choice") {
        int total = 0;
        for (int num : dice) {
            total += num;
        }
        return total;
    } else if (cat == "yacht") {
        // All dice are the same
        if (counts.size() == 1) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
