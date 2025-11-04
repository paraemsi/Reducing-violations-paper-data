#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cstdint>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
    if (category == "ones") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if (num == 1) count++;
        }
        return count * 1;
    } else if (category == "twos") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if (num == 2) count++;
        }
        return count * 2;
    } else if (category == "threes") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if (num == 3) count++;
        }
        return count * 3;
    } else if (category == "fours") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if (num == 4) count++;
        }
        return count * 4;
    } else if (category == "fives") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if (num == 5) count++;
        }
        return count * 5;
    } else if (category == "sixes") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if (num == 6) count++;
        }
        return count * 6;
    } else if (category == "full house") {
        std::map<std::int32_t, std::int32_t> counts;
        for (std::int32_t num : dice) counts[num]++;
        if (counts.size() != 2) return 0;
        bool hasThree = false;
        bool hasTwo = false;
        for (const auto& pair : counts) {
            if (pair.second == 3) hasThree = true;
            else if (pair.second == 2) hasTwo = true;
            else return 0;
        }
        if (hasThree && hasTwo) {
            std::int32_t total = 0;
            for (std::int32_t num : dice) total += num;
            return total;
        }
        return 0;
    } else if (category == "four of a kind") {
        std::map<std::int32_t, std::int32_t> counts;
        for (std::int32_t num : dice) counts[num]++;
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                return pair.first * 4;
            }
        }
        return 0;
    } else if (category == "little straight") {
        std::vector<std::int32_t> sorted = dice;
        std::sort(sorted.begin(), sorted.end());
        // Check if all numbers are unique and in order 1-5
        for (int i = 0; i < 4; i++) {
            if (sorted[i] + 1 != sorted[i + 1]) {
                return 0;
            }
        }
        // Check if it starts with 1 and ends with 5
        if (sorted[0] == 1 && sorted[4] == 5) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        std::vector<std::int32_t> sorted = dice;
        std::sort(sorted.begin(), sorted.end());
        // Check if all numbers are unique and in order 2-6
        for (int i = 0; i < 4; i++) {
            if (sorted[i] + 1 != sorted[i + 1]) {
                return 0;
            }
        }
        // Check if it starts with 2 and ends with 6
        if (sorted[0] == 2 && sorted[4] == 6) {
            return 30;
        }
        return 0;
    } else if (category == "choice") {
        std::int32_t total = 0;
        for (std::int32_t num : dice) total += num;
        return total;
    } else if (category == "yacht") {
        std::int32_t first = dice[0];
        for (std::int32_t num : dice) {
            if (num != first) return 0;
        }
        return 50;
    }
    return 0;
}

}  // namespace yacht
