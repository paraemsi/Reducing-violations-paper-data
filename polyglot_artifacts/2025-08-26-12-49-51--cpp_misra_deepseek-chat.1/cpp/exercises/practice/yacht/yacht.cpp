#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
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
        for (const auto& pair : counts) {
            if (pair.second == 3) has_three = true;
            if (pair.second == 2) has_two = true;
        }
        if (has_three && has_two && counts.size() == 2) {
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
                return 4 * pair.first;
            }
        }
        return 0;
    } else if (category == "little straight") {
        if (counts[1] == 1 && counts[2] == 1 && counts[3] == 1 && 
            counts[4] == 1 && counts[5] == 1) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
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
        if (counts.size() == 1) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
