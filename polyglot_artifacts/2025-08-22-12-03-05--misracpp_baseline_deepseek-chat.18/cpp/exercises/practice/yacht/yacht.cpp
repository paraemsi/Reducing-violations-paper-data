#include "yacht.h"
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <unordered_map>

namespace yacht {

int score(const std::vector<int>& dice, const std::string& category) {
    // Make a copy of dice to sort
    std::vector<int> sorted_dice = dice;
    std::sort(sorted_dice.begin(), sorted_dice.end());
    
    // Count occurrences of each number
    std::map<int, int> counts;
    for (int num : sorted_dice) {
        counts[num]++;
    }
    
    // Check each category - use lowercase to match the tests
    if (category == "ones") {
        return counts[1] * 1;
    } else if (category == "twos") {
        return counts[2] * 2;
    } else if (category == "threes") {
        return counts[3] * 3;
    } else if (category == "fours") {
        return counts[4] * 4;
    } else if (category == "fives") {
        return counts[5] * 5;
    } else if (category == "sixes") {
        return counts[6] * 6;
    } else if (category == "full house") {
        // Check if there's exactly a three of a kind and a two of a kind
        // And no other counts
        bool has_three = false;
        bool has_two = false;
        for (const auto& pair : counts) {
            if (pair.second == 3) has_three = true;
            else if (pair.second == 2) has_two = true;
            else if (pair.second != 0) return 0; // Any other count makes it invalid
        }
        if (has_three && has_two) {
            int total = 0;
            for (int num : sorted_dice) total += num;
            return total;
        } else {
            return 0;
        }
    } else if (category == "four of a kind") {
        // Check if any number appears at least 4 times
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                return pair.first * 4;
            }
        }
        return 0;
    } else if (category == "little straight") {
        // Check if all dice are unique and form a sequence 1-2-3-4-5
        // Since the dice are sorted, we can check if they're exactly 1,2,3,4,5
        // All must be distinct
        for (int i = 0; i < 4; i++) {
            if (sorted_dice[i] == sorted_dice[i + 1]) {
                return 0;
            }
        }
        if (sorted_dice[0] == 1 && sorted_dice[4] == 5) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "big straight") {
        // Check if all dice are unique and form a sequence 2-3-4-5-6
        for (int i = 0; i < 4; i++) {
            if (sorted_dice[i] == sorted_dice[i + 1]) {
                return 0;
            }
        }
        if (sorted_dice[0] == 2 && sorted_dice[4] == 6) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "choice") {
        int total = 0;
        for (int num : sorted_dice) total += num;
        return total;
    } else if (category == "yacht") {
        // Check if all dice are the same
        if (counts.size() == 1) {
            return 50;
        } else {
            return 0;
        }
    }
    return 0;
}

}  // namespace yacht
