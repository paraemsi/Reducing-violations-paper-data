#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <set>
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
        return 1 * (counts.count(1) ? counts.at(1) : 0);
    } else if (category == "twos") {
        return 2 * (counts.count(2) ? counts.at(2) : 0);
    } else if (category == "threes") {
        return 3 * (counts.count(3) ? counts.at(3) : 0);
    } else if (category == "fours") {
        return 4 * (counts.count(4) ? counts.at(4) : 0);
    } else if (category == "fives") {
        return 5 * (counts.count(5) ? counts.at(5) : 0);
    } else if (category == "sixes") {
        return 6 * (counts.count(6) ? counts.at(6) : 0);
    } else if (category == "full house") {
        // Check if there are exactly two different numbers
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
                // Always score 4 times the number, even if there are 5
                return 4 * pair.first;
            }
        }
        return 0;
    } else if (category == "little straight") {
        std::set<std::int32_t> unique_dice(dice.begin(), dice.end());
        if (unique_dice.size() == 5) {
            // Check if it contains 1 through 5
            if (unique_dice.find(1) != unique_dice.end() &&
                unique_dice.find(2) != unique_dice.end() &&
                unique_dice.find(3) != unique_dice.end() &&
                unique_dice.find(4) != unique_dice.end() &&
                unique_dice.find(5) != unique_dice.end()) {
                return 30;
            }
        }
        return 0;
    } else if (category == "big straight") {
        std::set<std::int32_t> unique_dice(dice.begin(), dice.end());
        if (unique_dice.size() == 5) {
            // Check if it contains 2 through 6
            if (unique_dice.find(2) != unique_dice.end() &&
                unique_dice.find(3) != unique_dice.end() &&
                unique_dice.find(4) != unique_dice.end() &&
                unique_dice.find(5) != unique_dice.end() &&
                unique_dice.find(6) != unique_dice.end()) {
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
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
