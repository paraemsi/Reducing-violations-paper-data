#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <cstdint>
#include <string>
#include <cstddef>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
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
        std::map<std::int32_t, std::int32_t> counts;
        for (const auto& die : dice) {
            counts[die]++;
        }
        // Check if we have exactly two different numbers
        if (counts.size() != 2) {
            return 0;
        }
        // Check if one appears 3 times and the other 2 times
        auto it = counts.begin();
        std::int32_t first_count = it->second;
        ++it;
        // Make sure we don't access past the end
        if (it == counts.end()) {
            return 0;
        }
        std::int32_t second_count = it->second;
        
        if (((first_count == 3) && (second_count == 2)) || 
            ((first_count == 2) && (second_count == 3))) {
            std::int32_t total = 0;
            for (const auto& die : dice) {
                total += die;
            }
            return total;
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
        std::vector<std::int32_t> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        // Check if all numbers from 1 to 5 are present and unique
        if (sorted_dice.size() == 5) {
            // Check for uniqueness first
            for (std::size_t i = 1; i < sorted_dice.size(); ++i) {
                if (sorted_dice[i] == sorted_dice[i - 1]) {
                    return 0;
                }
            }
            // Check if it's 1-5
            if ((sorted_dice[0] == 1) && (sorted_dice[1] == 2) && 
                (sorted_dice[2] == 3) && (sorted_dice[3] == 4) && 
                (sorted_dice[4] == 5)) {
                return 30;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    } else if (category == "big straight") {
        std::vector<std::int32_t> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        // Check if all numbers from 2 to 6 are present and unique
        if (sorted_dice.size() == 5) {
            // Check for uniqueness first
            for (std::size_t i = 1; i < sorted_dice.size(); ++i) {
                if (sorted_dice[i] == sorted_dice[i - 1]) {
                    return 0;
                }
            }
            // Check if it's 2-6
            if ((sorted_dice[0] == 2) && (sorted_dice[1] == 3) && 
                (sorted_dice[2] == 4) && (sorted_dice[3] == 5) && 
                (sorted_dice[4] == 6)) {
                return 30;
            } else {
                return 0;
            }
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
        bool all_same = true;
        for (std::size_t i = 1; i < dice.size(); ++i) {
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
