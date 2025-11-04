#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cstdint>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
    // Make a sorted copy of the dice
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
        if (((count1 == 2) && (count2 == 3)) || ((count1 == 3) && (count2 == 2))) {
            return dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
        }
        return 0;
    } else if (category == "four of a kind") {
        // Since dice are sorted, check if first 4 or last 4 are the same
        if (sorted_dice[0] == sorted_dice[3]) {
            return 4 * sorted_dice[0];
        }
        if (sorted_dice[1] == sorted_dice[4]) {
            return 4 * sorted_dice[1];
        }
        return 0;
    } else if (category == "little straight") {
        // Check if sorted dice are exactly 1,2,3,4,5
        if (sorted_dice[0] == 1 && sorted_dice[1] == 2 && sorted_dice[2] == 3 && 
            sorted_dice[3] == 4 && sorted_dice[4] == 5) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        // Check if sorted dice are exactly 2,3,4,5,6
        if (sorted_dice[0] == 2 && sorted_dice[1] == 3 && sorted_dice[2] == 4 && 
            sorted_dice[3] == 5 && sorted_dice[4] == 6) {
            return 30;
        }
        return 0;
    } else if (category == "choice") {
        return dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
    } else if (category == "yacht") {
        if (sorted_dice[0] == sorted_dice[4]) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
