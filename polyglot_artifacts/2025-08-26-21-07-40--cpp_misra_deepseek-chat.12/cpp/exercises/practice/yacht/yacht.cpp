#include "yacht.h"
#include <vector>
#include <map>
#include <algorithm>
#include <cstdint>
#include <string>
#include <functional>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
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
            }
        }
        // Check if we have exactly one three and one two, and no other counts
        if (has_three && has_two && counts.size() == 2) {
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
                return 4 * pair.first;
            }
        }
        return 0;
    } else if (category == "little straight") {
        // Check if all numbers are unique and exactly 1-5
        if (counts.size() == 5) {
            // Sort the dice and check if they're 1,2,3,4,5
            std::vector<std::int32_t> sorted_dice = dice;
            std::sort(sorted_dice.begin(), sorted_dice.end());
            for (std::int32_t i = 0; i < 5; i++) {
                if (sorted_dice[i] != i + 1) {
                    return 0;
                }
            }
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        // Check if all numbers are unique and exactly 2-6
        if (counts.size() == 5) {
            // Sort the dice and check if they're 2,3,4,5,6
            std::vector<std::int32_t> sorted_dice = dice;
            std::sort(sorted_dice.begin(), sorted_dice.end());
            for (std::int32_t i = 0; i < 5; i++) {
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
        }
        return 0;
    } else {
        return 0;
    }
}

}  // namespace yacht
