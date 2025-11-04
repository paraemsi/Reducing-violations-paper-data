#include "yacht.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <cstdint>
#include <string>
#include <cstddef>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
    // Make a copy to sort if needed
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
        std::int32_t first_count = it->second;
        it++;
        std::int32_t second_count = it->second;
        if (((first_count == 2) && (second_count == 3)) || ((first_count == 3) && (second_count == 2))) {
            return dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
        } else {
            return 0;
        }
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
        // Check if all numbers from 1 to 5 are present exactly once
        if (sorted_dice[0] == 1 && sorted_dice[1] == 2 && sorted_dice[2] == 3 && 
            sorted_dice[3] == 4 && sorted_dice[4] == 5) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "big straight") {
        // Check if all numbers from 2 to 6 are present exactly once
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
        bool all_same = true;
        for (std::size_t i = 1; i < dice.size(); i++) {
            if (dice[i] != dice[0]) {
                all_same = false;
                break;
            }
        }
        if (all_same) {
            return 50;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

}  // namespace yacht
