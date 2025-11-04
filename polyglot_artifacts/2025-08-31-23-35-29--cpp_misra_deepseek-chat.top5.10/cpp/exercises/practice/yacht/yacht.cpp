#include "yacht.h"
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <functional>
#include <cstdint>

namespace yacht {

std::int32_t score(const std::vector<std::int8_t>& dice, const std::string& category) {
    // Make a copy of dice to sort
    std::vector<std::int8_t> sorted_dice = dice;
    std::sort(sorted_dice.begin(), sorted_dice.end());
    
    if (category == "ones") {
        std::int32_t count = 0;
        for (std::int8_t num : sorted_dice) {
            if (num == 1) {
                count++;
            }
        }
        return count * 1;
    } else if (category == "twos") {
        std::int32_t count = 0;
        for (std::int8_t num : sorted_dice) {
            if (num == 2) {
                count++;
            }
        }
        return count * 2;
    } else if (category == "threes") {
        std::int32_t count = 0;
        for (std::int8_t num : sorted_dice) {
            if (num == 3) {
                count++;
            }
        }
        return count * 3;
    } else if (category == "fours") {
        std::int32_t count = 0;
        for (std::int8_t num : sorted_dice) {
            if (num == 4) {
                count++;
            }
        }
        return count * 4;
    } else if (category == "fives") {
        std::int32_t count = 0;
        for (std::int8_t num : sorted_dice) {
            if (num == 5) {
                count++;
            }
        }
        return count * 5;
    } else if (category == "sixes") {
        std::int32_t count = 0;
        for (std::int8_t num : sorted_dice) {
            if (num == 6) {
                count++;
            }
        }
        return count * 6;
    } else if (category == "full house") {
        // Check if first three are equal and last two are equal and different from first three
        // Or first two are equal and last three are equal and different from first two
        bool condition1 = ((sorted_dice[0] == sorted_dice[1]) && (sorted_dice[1] == sorted_dice[2]) && 
                          (sorted_dice[3] == sorted_dice[4]) && (sorted_dice[2] != sorted_dice[3]));
        bool condition2 = ((sorted_dice[0] == sorted_dice[1]) && 
                          (sorted_dice[2] == sorted_dice[3]) && (sorted_dice[3] == sorted_dice[4]) && 
                          (sorted_dice[1] != sorted_dice[2]));
        if (condition1 || condition2) {
            std::int32_t sum = 0;
            for (std::int8_t num : sorted_dice) {
                sum += static_cast<std::int32_t>(num);
            }
            return sum;
        } else {
            return 0;
        }
    } else if (category == "four of a kind") {
        // Check if first four are equal or last four are equal
        if ((sorted_dice[0] == sorted_dice[1]) && (sorted_dice[1] == sorted_dice[2]) && (sorted_dice[2] == sorted_dice[3])) {
            return 4 * static_cast<std::int32_t>(sorted_dice[0]);
        } else if ((sorted_dice[1] == sorted_dice[2]) && (sorted_dice[2] == sorted_dice[3]) && (sorted_dice[3] == sorted_dice[4])) {
            return 4 * static_cast<std::int32_t>(sorted_dice[1]);
        } else {
            return 0;
        }
    } else if (category == "little straight") {
        // Check if dice are 1,2,3,4,5
        for (std::int32_t i = 0; i < 5; i++) {
            if (sorted_dice[i] != (static_cast<std::int8_t>(i) + 1)) {
                return 0;
            }
        }
        return 30;
    } else if (category == "big straight") {
        // Check if dice are 2,3,4,5,6
        for (std::int32_t i = 0; i < 5; i++) {
            if (sorted_dice[i] != (static_cast<std::int8_t>(i) + 2)) {
                return 0;
            }
        }
        return 30;
    } else if (category == "choice") {
        std::int32_t sum = 0;
        for (std::int8_t num : sorted_dice) {
            sum += static_cast<std::int32_t>(num);
        }
        return sum;
    } else if (category == "yacht") {
        // All dice must be the same
        if ((sorted_dice[0] == sorted_dice[1]) && (sorted_dice[1] == sorted_dice[2]) && 
            (sorted_dice[2] == sorted_dice[3]) && (sorted_dice[3] == sorted_dice[4])) {
            return 50;
        } else {
            return 0;
        }
    }
    return 0;
}

}  // namespace yacht
