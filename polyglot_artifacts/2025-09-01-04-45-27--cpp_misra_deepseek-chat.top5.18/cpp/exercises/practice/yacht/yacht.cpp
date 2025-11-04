#include "yacht.h"
#include <algorithm>
#include <map>
#include <string>
#include <vector>

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
        if ((has_three && has_two) && (counts.size() == 2)) {
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
        // Check if we have 1-5
        if (counts.size() == 5) {
            if ((counts.find(1) != counts.end()) && 
                (counts.find(2) != counts.end()) && 
                (counts.find(3) != counts.end()) && 
                (counts.find(4) != counts.end()) && 
                (counts.find(5) != counts.end())) {
                return 30;
            }
        }
        return 0;
    } else if (category == "big straight") {
        // Check if we have 2-6
        if (counts.size() == 5) {
            if ((counts.find(2) != counts.end()) && 
                (counts.find(3) != counts.end()) && 
                (counts.find(4) != counts.end()) && 
                (counts.find(5) != counts.end()) && 
                (counts.find(6) != counts.end())) {
                return 30;
            }
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
