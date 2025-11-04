#include "yacht.h"
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <cstdint>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
    if (dice.size() != 5) {
        return 0;
    }
    
    // Count occurrences of each number
    std::map<std::int32_t, std::int32_t> counts;
    for (const auto& die : dice) {
        counts[die]++;
    }
    
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
        bool has_three = false;
        bool has_two = false;
        for (const auto& pair : counts) {
            if (pair.second == 3) {
                has_three = true;
            } else if (pair.second == 2) {
                has_two = true;
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
                return pair.first * 4;
            }
        }
        return 0;
    } else if (category == "little straight") {
        // Check if all numbers from 1 to 5 are present
        // Sort and check if they're consecutive
        std::vector<std::int32_t> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        // Check for 1,2,3,4,5
        bool is_little_straight = true;
        for (int i = 0; i < 5; i++) {
            if (sorted_dice[i] != i + 1) {
                is_little_straight = false;
                break;
            }
        }
        if (is_little_straight) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "big straight") {
        // Check if all numbers from 2 to 6 are present
        // Sort and check if they're consecutive
        std::vector<std::int32_t> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        // Check for 2,3,4,5,6
        bool is_big_straight = true;
        for (int i = 0; i < 5; i++) {
            if (sorted_dice[i] != i + 2) {
                is_big_straight = false;
                break;
            }
        }
        if (is_big_straight) {
            return 30;
        } else {
            return 0;
        }
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
    }
    return 0;
}

}  // namespace yacht
