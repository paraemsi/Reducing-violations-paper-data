#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cstdint>

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
        // Check if we have exactly two different numbers: one with count 3 and one with count 2
        if (counts.size() == 2) {
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
        }
        return 0;
    } else if (category == "four of a kind") {
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                return 4 * pair.first;
            }
        }
        return 0;
    } else if (category == "little straight") {
        // Check if all numbers from 1 to 5 are present
        if (counts[1] == 1 && counts[2] == 1 && counts[3] == 1 && 
            counts[4] == 1 && counts[5] == 1) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        // Check if all numbers from 2 to 6 are present
        if (counts[2] == 1 && counts[3] == 1 && counts[4] == 1 && 
            counts[5] == 1 && counts[6] == 1) {
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
        // All dice must be the same
        if (counts.size() == 1) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
