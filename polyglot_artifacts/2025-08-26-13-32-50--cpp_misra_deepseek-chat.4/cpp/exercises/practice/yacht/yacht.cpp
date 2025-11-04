#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <cstdint>
#include <string>

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
        // Check if we have exactly two distinct numbers, one appearing 3 times and the other 2 times
        if (counts.size() != 2) {
            return 0;
        }
        bool has_three = false;
        bool has_two = false;
        for (const auto& pair : counts) {
            if (pair.second == 3) {
                has_three = true;
            } else if (pair.second == 2) {
                has_two = true;
            } else {
                return 0;
            }
        }
        if (has_three && has_two) {
            std::int32_t total = 0;
            for (const auto& die : dice) {
                total += die;
            }
            return total;
        }
        return 0;
    } else if (category == "four of a kind") {
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                // For cases where there are 5 of a kind, we still only score 4 * the number
                return 4 * pair.first;
            }
        }
        return 0;
    } else if (category == "little straight") {
        std::vector<std::int32_t> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        if (sorted_dice == std::vector<std::int32_t>{1, 2, 3, 4, 5}) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        std::vector<std::int32_t> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        if (sorted_dice == std::vector<std::int32_t>{2, 3, 4, 5, 6}) {
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
