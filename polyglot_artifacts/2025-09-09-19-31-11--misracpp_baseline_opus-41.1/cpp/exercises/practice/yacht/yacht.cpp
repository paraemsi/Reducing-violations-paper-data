#include "yacht.h"
#include <algorithm>
#include <unordered_map>

namespace yacht {

int score(const std::vector<int>& dice, const std::string& category) {
    // Count occurrences of each die value
    std::unordered_map<int, int> counts;
    for (int die : dice) {
        counts[die]++;
    }
    
    if (category == "ones") {
        return counts[1] * 1;
    }
    else if (category == "twos") {
        return counts[2] * 2;
    }
    else if (category == "threes") {
        return counts[3] * 3;
    }
    else if (category == "fours") {
        return counts[4] * 4;
    }
    else if (category == "fives") {
        return counts[5] * 5;
    }
    else if (category == "sixes") {
        return counts[6] * 6;
    }
    else if (category == "full house") {
        // Need exactly 3 of one number and 2 of another
        bool hasThree = false;
        bool hasTwo = false;
        for (auto it = counts.begin(); it != counts.end(); ++it) {
            if (it->second == 3) hasThree = true;
            if (it->second == 2) hasTwo = true;
        }
        if (hasThree && hasTwo) {
            int sum = 0;
            for (int die : dice) {
                sum += die;
            }
            return sum;
        }
        return 0;
    }
    else if (category == "four of a kind") {
        // At least four dice showing the same face
        for (auto it = counts.begin(); it != counts.end(); ++it) {
            if (it->second >= 4) {
                return it->first * 4;
            }
        }
        return 0;
    }
    else if (category == "little straight") {
        // Must be exactly 1-2-3-4-5
        std::vector<int> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        if (sorted_dice == std::vector<int>{1, 2, 3, 4, 5}) {
            return 30;
        }
        return 0;
    }
    else if (category == "big straight") {
        // Must be exactly 2-3-4-5-6
        std::vector<int> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        if (sorted_dice == std::vector<int>{2, 3, 4, 5, 6}) {
            return 30;
        }
        return 0;
    }
    else if (category == "choice") {
        // Sum of all dice
        int sum = 0;
        for (int die : dice) {
            sum += die;
        }
        return sum;
    }
    else if (category == "yacht") {
        // All five dice showing the same face
        for (auto it = counts.begin(); it != counts.end(); ++it) {
            if (it->second == 5) {
                return 50;
            }
        }
        return 0;
    }
    
    return 0;
}

}  // namespace yacht
