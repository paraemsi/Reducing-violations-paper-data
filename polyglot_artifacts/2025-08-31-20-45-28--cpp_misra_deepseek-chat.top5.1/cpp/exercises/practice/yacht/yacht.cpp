#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <cstdint>
#include <string>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
    // First, map the string to our enum
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
        // Make a copy to sort and process
        std::vector<std::int32_t> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        
        // Count occurrences of each number
        std::map<std::int32_t, std::int32_t> counts;
        for (const auto& die : sorted_dice) {
            counts[die]++;
        }
        
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
        std::vector<std::int32_t> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        
        // Count occurrences of each number
        std::map<std::int32_t, std::int32_t> counts;
        for (const auto& die : sorted_dice) {
            counts[die]++;
        }
        
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                return 4 * pair.first;
            }
        }
        return 0;
    } else if (category == "little straight") {
        std::vector<std::int32_t> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        if (sorted_dice == std::vector<std::int32_t>{1, 2, 3, 4, 5}) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "big straight") {
        std::vector<std::int32_t> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        if (sorted_dice == std::vector<std::int32_t>{2, 3, 4, 5, 6}) {
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
        std::vector<std::int32_t> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        
        // Count occurrences of each number
        std::map<std::int32_t, std::int32_t> counts;
        for (const auto& die : sorted_dice) {
            counts[die]++;
        }
        
        if (counts.size() == 1) {
            return 50;
        } else {
            return 0;
        }
    }
    return 0;
}

}  // namespace yacht
