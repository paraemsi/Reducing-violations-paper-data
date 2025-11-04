#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <cstdint>
#include <string>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
    // Make a copy to sort
    std::vector<std::int32_t> sorted_dice = dice;
    std::sort(sorted_dice.begin(), sorted_dice.end());
    
    // Count occurrences of each number
    std::map<std::int32_t, std::int32_t> counts;
    for (const auto& die : dice) {
        counts[die]++;
    }
    
    if (category == "ones") {
        return 1 * counts[1];
    } else if (category == "twos") {
        return 2 * counts[2];
    } else if (category == "threes") {
        return 3 * counts[3];
    } else if (category == "fours") {
        return 4 * counts[4];
    } else if (category == "fives") {
        return 5 * counts[5];
    } else if (category == "sixes") {
        return 6 * counts[6];
    } else if (category == "full house") {
        bool has_three = false;
        bool has_two = false;
        for (const auto& pair : counts) {
            if (pair.second == 3) {
                has_three = true;
            } else if (pair.second == 2) {
                has_two = true;
            } else if (pair.second != 0) {
                return 0;
            }
        }
        if (has_three && has_two) {
            std::int32_t total = 0;
            for (const auto& die : dice) {
                total += die;
            }
            return total;
        } else {
            return 0;
        }
    } else if (category == "four of a kind") {
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                // Sum all dice that are part of the four of a kind
                // Since there might be five of a kind, we need to pick the right ones
                // Let's find which number has at least 4 occurrences and sum 4 of them
                // But according to the instructions, it's the total of the four dice
                // So for four 6's, it's 6*4=24, which matches the test
                // Wait, the implementation was correct, but the test expects the sum of the four matching dice
                // Which is 4 * value
                return 4 * pair.first;
            }
        }
        return 0;
    } else if (category == "little straight") {
        // Check if all numbers from 1 to 5 are present exactly once
        // Since dice may be in any order, we can use a set
        // But to be efficient, we can check the sorted version
        if (sorted_dice.size() == 5) {
            // Check if numbers are 1,2,3,4,5
            for (int i = 0; i < 5; i++) {
                if (sorted_dice[i] != i + 1) {
                    return 0;
                }
            }
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        // Check if all numbers from 2 to 6 are present exactly once
        if (sorted_dice.size() == 5) {
            // Check if numbers are 2,3,4,5,6
            for (int i = 0; i < 5; i++) {
                if (sorted_dice[i] != i + 2) {
                    return 0;
                }
            }
            return 30;
        }
        return 0;
    } else if (category == "choice") {
        std::int32_t total = 0;
        for (const auto& die : dice) {
            total += die;
        }
        return total;
    } else if (category == "yacht") {
        if (counts.size() == 1) {
            return 50;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

}  // namespace yacht
