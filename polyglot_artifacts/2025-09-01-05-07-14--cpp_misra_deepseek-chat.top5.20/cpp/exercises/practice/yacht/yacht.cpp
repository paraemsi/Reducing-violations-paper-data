#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <cstdint>
#include <string>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
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
        bool hasThree = false;
        bool hasTwo = false;
        for (const auto& pair : counts) {
            if (pair.second == 3) {
                hasThree = true;
            } else if (pair.second == 2) {
                hasTwo = true;
            } else {
                // If any count is not 2 or 3, it's invalid
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
        std::vector<std::int32_t> sorted = dice;
        std::sort(sorted.begin(), sorted.end());
        // Check if all are unique and in sequence 1-5
        bool isUnique = true;
        for (std::int32_t i = 1; i < 5; i++) {
            if (sorted[i] == sorted[i-1]) {
                isUnique = false;
                break;
            }
        }
        if (isUnique && 
            sorted[0] == 1 && 
            sorted[1] == 2 && 
            sorted[2] == 3 && 
            sorted[3] == 4 && 
            sorted[4] == 5) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        std::vector<std::int32_t> sorted = dice;
        std::sort(sorted.begin(), sorted.end());
        // Check if all are unique and in sequence 2-6
        bool isUnique = true;
        for (std::int32_t i = 1; i < 5; i++) {
            if (sorted[i] == sorted[i-1]) {
                isUnique = false;
                break;
            }
        }
        if (isUnique && 
            sorted[0] == 2 && 
            sorted[1] == 3 && 
            sorted[2] == 4 && 
            sorted[3] == 5 && 
            sorted[4] == 6) {
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
        bool allSame = true;
        for (std::int32_t i = 1; i < static_cast<std::int32_t>(dice.size()); i++) {
            if (dice[i] != dice[0]) {
                allSame = false;
                break;
            }
        }
        if (allSame) {
            return 50;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

}  // namespace yacht
