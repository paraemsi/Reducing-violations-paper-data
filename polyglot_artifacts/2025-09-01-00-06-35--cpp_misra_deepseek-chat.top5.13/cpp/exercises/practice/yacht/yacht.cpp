#include "yacht.h"
#include <algorithm>
#include <functional>
#include <map>
#include <array>

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
        bool hasThree = false;
        bool hasTwo = false;
        for (const auto& pair : counts) {
            if (pair.second == 3) {
                hasThree = true;
            } else if (pair.second == 2) {
                hasTwo = true;
            } else if (pair.second != 0) {
                // If there's any other count, it's invalid
                return 0;
            }
        }
        if (hasThree && hasTwo) {
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
        // Check if all numbers are unique and form 1-5
        std::array<std::int32_t, 5> sortedDice;
        for (std::int32_t i = 0; i < 5; ++i) {
            sortedDice[i] = dice[i];
        }
        std::sort(sortedDice.begin(), sortedDice.end());
        // Check for duplicates
        for (std::int32_t i = 0; i < 4; ++i) {
            if (sortedDice[i] == sortedDice[i + 1]) {
                return 0;
            }
        }
        // Check if it's exactly 1-5
        if (sortedDice[0] == 1 && sortedDice[1] == 2 && sortedDice[2] == 3 && 
            sortedDice[3] == 4 && sortedDice[4] == 5) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        // Check if all numbers are unique and form 2-6
        std::array<std::int32_t, 5> sortedDice;
        for (std::int32_t i = 0; i < 5; ++i) {
            sortedDice[i] = dice[i];
        }
        std::sort(sortedDice.begin(), sortedDice.end());
        // Check for duplicates
        for (std::int32_t i = 0; i < 4; ++i) {
            if (sortedDice[i] == sortedDice[i + 1]) {
                return 0;
            }
        }
        // Check if it's exactly 2-6
        if (sortedDice[0] == 2 && sortedDice[1] == 3 && sortedDice[2] == 4 && 
            sortedDice[3] == 5 && sortedDice[4] == 6) {
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
        // Check if all dice are the same
        for (std::int32_t i = 1; i < 5; ++i) {
            if (dice[i] != dice[0]) {
                return 0;
            }
        }
        return 50;
    } else {
        return 0;
    }
}

}  // namespace yacht
