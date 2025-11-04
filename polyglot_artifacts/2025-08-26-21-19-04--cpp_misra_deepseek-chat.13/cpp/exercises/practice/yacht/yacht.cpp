#include "yacht.h"
#include <algorithm>
#include <map>
#include <functional>
#include <cstdint>
#include <vector>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
    // Count occurrences of each number
    std::map<std::int32_t, std::int32_t> counts;
    for (const auto& die : dice) {
        counts[die]++;
    }
    
    if (category == "ones") {
        std::int32_t sum = 0;
        for (const auto& die : dice) {
            if (die == 1) {
                sum += 1;
            }
        }
        return sum;
    } else if (category == "twos") {
        std::int32_t sum = 0;
        for (const auto& die : dice) {
            if (die == 2) {
                sum += 2;
            }
        }
        return sum;
    } else if (category == "threes") {
        std::int32_t sum = 0;
        for (const auto& die : dice) {
            if (die == 3) {
                sum += 3;
            }
        }
        return sum;
    } else if (category == "fours") {
        std::int32_t sum = 0;
        for (const auto& die : dice) {
            if (die == 4) {
                sum += 4;
            }
        }
        return sum;
    } else if (category == "fives") {
        std::int32_t sum = 0;
        for (const auto& die : dice) {
            if (die == 5) {
                sum += 5;
            }
        }
        return sum;
    } else if (category == "sixes") {
        std::int32_t sum = 0;
        for (const auto& die : dice) {
            if (die == 6) {
                sum += 6;
            }
        }
        return sum;
    } else if (category == "full house") {
        bool has_three = false;
        bool has_two = false;
        for (const auto& pair : counts) {
            if (pair.second == 3) {
                has_three = true;
            } else if (pair.second == 2) {
                has_two = true;
            } else {
                // Any other count makes it invalid
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
                // Total of the four dice
                return 4 * pair.first;
            }
        }
        return 0;
    } else if (category == "little straight") {
        // Check if all numbers from 1 to 5 are present exactly once
        if (counts.size() == 5 && counts.find(6) == counts.end()) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "big straight") {
        // Check if all numbers from 2 to 6 are present exactly once
        if (counts.size() == 5 && counts.find(1) == counts.end()) {
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
    } else {
        return 0;
    }
}

}  // namespace yacht
