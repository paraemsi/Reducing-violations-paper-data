#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cstdint>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
    // Make a copy and sort to make some checks easier
    std::vector<std::int32_t> sorted_dice = dice;
    std::sort(sorted_dice.begin(), sorted_dice.end());
    
    if (category == "ones") {
        std::int32_t count = 0;
        for (const auto& die : dice) {
            if (die == 1) {
                count++;
            }
        }
        return count * 1;
    } else if (category == "twos") {
        std::int32_t count = 0;
        for (const auto& die : dice) {
            if (die == 2) {
                count++;
            }
        }
        return count * 2;
    } else if (category == "threes") {
        std::int32_t count = 0;
        for (const auto& die : dice) {
            if (die == 3) {
                count++;
            }
        }
        return count * 3;
    } else if (category == "fours") {
        std::int32_t count = 0;
        for (const auto& die : dice) {
            if (die == 4) {
                count++;
            }
        }
        return count * 4;
    } else if (category == "fives") {
        std::int32_t count = 0;
        for (const auto& die : dice) {
            if (die == 5) {
                count++;
            }
        }
        return count * 5;
    } else if (category == "sixes") {
        std::int32_t count = 0;
        for (const auto& die : dice) {
            if (die == 6) {
                count++;
            }
        }
        return count * 6;
    } else if (category == "full house") {
        // Check if there are exactly two distinct numbers, with counts 3 and 2
        std::map<std::int32_t, std::int32_t> counts;
        for (const auto& die : dice) {
            counts[die]++;
        }
        if (counts.size() != 2) {
            return 0;
        }
        auto it = counts.begin();
        std::int32_t count1 = it->second;
        std::int32_t count2 = (++it)->second;
        // Check if one count is 3 and the other is 2
        if ((count1 == 3 && count2 == 2) || (count1 == 2 && count2 == 3)) {
            // Sum all dice
            std::int32_t total = 0;
            for (const auto& die : dice) {
                total += die;
            }
            return total;
        } else {
            return 0;
        }
    } else if (category == "four of a kind") {
        // Check if at least four dice are the same
        // Since the dice are sorted, the four of a kind must be either the first four or last four
        if (sorted_dice[0] == sorted_dice[3]) {
            return 4 * sorted_dice[0];
        } else if (sorted_dice[1] == sorted_dice[4]) {
            return 4 * sorted_dice[1];
        } else {
            return 0;
        }
    } else if (category == "little straight") {
        // Check if the dice are 1-2-3-4-5 in any order
        // After sorting, they should be exactly 1,2,3,4,5
        // Also, all must be distinct
        for (int i = 0; i < 4; i++) {
            if (sorted_dice[i] == sorted_dice[i + 1]) {
                return 0;
            }
        }
        if (sorted_dice[0] == 1 && sorted_dice[1] == 2 && sorted_dice[2] == 3 && 
            sorted_dice[3] == 4 && sorted_dice[4] == 5) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "big straight") {
        // Check if the dice are 2-3-4-5-6 in any order
        // After sorting, they should be exactly 2,3,4,5,6
        // Also, all must be distinct
        for (int i = 0; i < 4; i++) {
            if (sorted_dice[i] == sorted_dice[i + 1]) {
                return 0;
            }
        }
        if (sorted_dice[0] == 2 && sorted_dice[1] == 3 && sorted_dice[2] == 4 && 
            sorted_dice[3] == 5 && sorted_dice[4] == 6) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "choice") {
        std::int32_t sum = 0;
        for (const auto& die : dice) {
            sum += die;
        }
        return sum;
    } else if (category == "yacht") {
        if (sorted_dice[0] == sorted_dice[4]) {
            return 50;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

}  // namespace yacht
