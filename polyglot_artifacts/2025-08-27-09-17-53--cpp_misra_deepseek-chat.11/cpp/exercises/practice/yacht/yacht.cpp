#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <cstdint>
#include <string>
#include <cctype>
#include <functional>
#include <algorithm>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
    // Convert category to lowercase for case-insensitive comparison
    std::string lower_category;
    for (char c : category) {
        lower_category += std::tolower(c);
    }
    
    // Count occurrences of each number
    std::map<std::int32_t, std::int32_t> counts;
    for (const auto& die : dice) {
        counts[die]++;
    }
    
    if (lower_category == "ones") {
        std::int32_t sum = 0;
        for (const auto& die : dice) {
            if (die == 1) {
                sum += 1;
            }
        }
        return sum;
    } else if (lower_category == "twos") {
        std::int32_t sum = 0;
        for (const auto& die : dice) {
            if (die == 2) {
                sum += 2;
            }
        }
        return sum;
    } else if (lower_category == "threes") {
        std::int32_t sum = 0;
        for (const auto& die : dice) {
            if (die == 3) {
                sum += 3;
            }
        }
        return sum;
    } else if (lower_category == "fours") {
        std::int32_t sum = 0;
        for (const auto& die : dice) {
            if (die == 4) {
                sum += 4;
            }
        }
        return sum;
    } else if (lower_category == "fives") {
        std::int32_t sum = 0;
        for (const auto& die : dice) {
            if (die == 5) {
                sum += 5;
            }
        }
        return sum;
    } else if (lower_category == "sixes") {
        std::int32_t sum = 0;
        for (const auto& die : dice) {
            if (die == 6) {
                sum += 6;
            }
        }
        return sum;
    } else if (lower_category == "full house") {
        bool has_three = false;
        bool has_two = false;
        for (const auto& pair : counts) {
            if (pair.second == 3) {
                has_three = true;
            } else if (pair.second == 2) {
                has_two = true;
            } else if (pair.second != 0) {
                // If there's any other count, it's not a full house
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
    } else if (lower_category == "four of a kind") {
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                return 4 * pair.first;
            }
        }
        return 0;
    } else if (lower_category == "little straight") {
        // Check if we have 1-5
        if (counts[1] == 1 && counts[2] == 1 && counts[3] == 1 && 
            counts[4] == 1 && counts[5] == 1) {
            return 30;
        }
        return 0;
    } else if (lower_category == "big straight") {
        // Check if we have 2-6
        if (counts[2] == 1 && counts[3] == 1 && counts[4] == 1 && 
            counts[5] == 1 && counts[6] == 1) {
            return 30;
        }
        return 0;
    } else if (lower_category == "choice") {
        std::int32_t total = 0;
        for (const auto& die : dice) {
            total += die;
        }
        return total;
    } else if (lower_category == "yacht") {
        // All dice are the same
        if (counts.size() == 1) {
            return 50;
        }
        return 0;
    } else {
        return 0;
    }
}

}  // namespace yacht
