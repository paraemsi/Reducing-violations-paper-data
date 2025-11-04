#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <cstdint>
#include <string>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
    // Make a copy of dice to sort
    std::vector<std::int32_t> sorted_dice = dice;
    std::sort(sorted_dice.begin(), sorted_dice.end());
    
    // Count occurrences of each number
    std::map<std::int32_t, std::int32_t> counts;
    for (std::int32_t num : sorted_dice) {
        counts[num]++;
    }
    
    if (category == "ones") {
        std::int32_t sum = 0;
        for (std::int32_t num : sorted_dice) {
            if (num == 1) {
                sum += 1;
            }
        }
        return sum;
    } else if (category == "twos") {
        std::int32_t sum = 0;
        for (std::int32_t num : sorted_dice) {
            if (num == 2) {
                sum += 2;
            }
        }
        return sum;
    } else if (category == "threes") {
        std::int32_t sum = 0;
        for (std::int32_t num : sorted_dice) {
            if (num == 3) {
                sum += 3;
            }
        }
        return sum;
    } else if (category == "fours") {
        std::int32_t sum = 0;
        for (std::int32_t num : sorted_dice) {
            if (num == 4) {
                sum += 4;
            }
        }
        return sum;
    } else if (category == "fives") {
        std::int32_t sum = 0;
        for (std::int32_t num : sorted_dice) {
            if (num == 5) {
                sum += 5;
            }
        }
        return sum;
    } else if (category == "sixes") {
        std::int32_t sum = 0;
        for (std::int32_t num : sorted_dice) {
            if (num == 6) {
                sum += 6;
            }
        }
        return sum;
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
        if ((has_three) && (has_two)) {
            std::int32_t total = 0;
            for (std::int32_t num : sorted_dice) {
                total += num;
            }
            return total;
        }
        return 0;
    } else if (category == "four of a kind") {
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                return 4 * pair.first;
            }
        }
        return 0;
    } else if (category == "little straight") {
        // Check if all numbers are unique and exactly 1 through 5
        if (counts.size() == 5) {
            if ((sorted_dice[0] == 1) && (sorted_dice[1] == 2) && (sorted_dice[2] == 3) && 
                (sorted_dice[3] == 4) && (sorted_dice[4] == 5)) {
                return 30;
            }
        }
        return 0;
    } else if (category == "big straight") {
        // Check if all numbers are unique and exactly 2 through 6
        if (counts.size() == 5) {
            if ((sorted_dice[0] == 2) && (sorted_dice[1] == 3) && (sorted_dice[2] == 4) && 
                (sorted_dice[3] == 5) && (sorted_dice[4] == 6)) {
                return 30;
            }
        }
        return 0;
    } else if (category == "choice") {
        std::int32_t total = 0;
        for (std::int32_t num : sorted_dice) {
            total += num;
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
