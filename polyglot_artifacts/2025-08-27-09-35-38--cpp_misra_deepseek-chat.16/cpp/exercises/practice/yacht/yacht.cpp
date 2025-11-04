#include "yacht.h"
#include <algorithm>
#include <map>
#include <array>
#include <set>
#include <string>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
    // Map the string to our enum
    if (category == "ones") {
        return 1 * std::count(dice.begin(), dice.end(), 1);
    } else if (category == "twos") {
        return 2 * std::count(dice.begin(), dice.end(), 2);
    } else if (category == "threes") {
        return 3 * std::count(dice.begin(), dice.end(), 3);
    } else if (category == "fours") {
        return 4 * std::count(dice.begin(), dice.end(), 4);
    } else if (category == "fives") {
        return 5 * std::count(dice.begin(), dice.end(), 5);
    } else if (category == "sixes") {
        return 6 * std::count(dice.begin(), dice.end(), 6);
    } else if (category == "full house") {
        // Always have 5 dice according to the note
        // Count occurrences of each number
        std::map<std::int32_t, std::int32_t> counts;
        for (const auto& die : dice) {
            counts[die]++;
        }
        
        bool hasThree = false;
        bool hasTwo = false;
        for (const auto& pair : counts) {
            if (pair.second == 3) {
                hasThree = true;
            } else if (pair.second == 2) {
                hasTwo = true;
            }
        }
        if (hasThree && hasTwo) {
            std::int32_t total = 0;
            for (const auto& die : dice) {
                total += die;
            }
            return total;
        }
        return 0;
    } else if (category == "four of a kind") {
        std::map<std::int32_t, std::int32_t> counts;
        for (const auto& die : dice) {
            counts[die]++;
        }
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                return 4 * pair.first;
            }
        }
        return 0;
    } else if (category == "little straight") {
        std::set<std::int32_t> uniqueDice(dice.begin(), dice.end());
        if (uniqueDice.size() == 5) {
            // Check if it contains 1 through 5
            if (uniqueDice.find(1) != uniqueDice.end() &&
                uniqueDice.find(2) != uniqueDice.end() &&
                uniqueDice.find(3) != uniqueDice.end() &&
                uniqueDice.find(4) != uniqueDice.end() &&
                uniqueDice.find(5) != uniqueDice.end()) {
                return 30;
            }
        }
        return 0;
    } else if (category == "big straight") {
        std::set<std::int32_t> uniqueDice(dice.begin(), dice.end());
        if (uniqueDice.size() == 5) {
            // Check if it contains 2 through 6
            if (uniqueDice.find(2) != uniqueDice.end() &&
                uniqueDice.find(3) != uniqueDice.end() &&
                uniqueDice.find(4) != uniqueDice.end() &&
                uniqueDice.find(5) != uniqueDice.end() &&
                uniqueDice.find(6) != uniqueDice.end()) {
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
        std::map<std::int32_t, std::int32_t> counts;
        for (const auto& die : dice) {
            counts[die]++;
        }
        if (counts.size() == 1) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
