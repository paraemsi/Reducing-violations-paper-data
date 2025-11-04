#include "yacht.h"
#include <algorithm>
#include <functional>
#include <map>
#include <cstdint>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
    if (dice.size() != 5) {
        return 0;
    }
    
    // Make a sorted copy to work with
    std::vector<std::int32_t> sorted_dice = dice;
    std::sort(sorted_dice.begin(), sorted_dice.end());
    
    if (category == "ones") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if ((num == 1)) {
                count++;
            }
        }
        return count * 1;
    } else if (category == "twos") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if ((num == 2)) {
                count++;
            }
        }
        return count * 2;
    } else if (category == "threes") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if ((num == 3)) {
                count++;
            }
        }
        return count * 3;
    } else if (category == "fours") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if ((num == 4)) {
                count++;
            }
        }
        return count * 4;
    } else if (category == "fives") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if ((num == 5)) {
                count++;
            }
        }
        return count * 5;
    } else if (category == "sixes") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if ((num == 6)) {
                count++;
            }
        }
        return count * 6;
    } else if (category == "full house") {
        // Check if there are exactly two distinct numbers, with counts 3 and 2
        std::map<std::int32_t, std::int32_t> counts;
        for (std::int32_t num : dice) {
            counts[num]++;
        }
        if ((counts.size() != 2)) {
            return 0;
        }
        auto it = counts.begin();
        std::int32_t count1 = it->second;
        it++;
        std::int32_t count2 = it->second;
        if ((((count1 == 2) && (count2 == 3)) || ((count1 == 3) && (count2 == 2)))) {
            std::int32_t total = 0;
            for (std::int32_t num : dice) {
                total += num;
            }
            return total;
        } else {
            return 0;
        }
    } else if (category == "four of a kind") {
        std::map<std::int32_t, std::int32_t> counts;
        for (std::int32_t num : dice) {
            counts[num]++;
        }
        for (const auto& pair : counts) {
            if ((pair.second >= 4)) {
                return pair.first * 4;
            }
        }
        return 0;
    } else if (category == "little straight") {
        // Check if numbers are 1-5
        std::vector<std::int32_t> expected = {1, 2, 3, 4, 5};
        std::vector<std::int32_t> temp = sorted_dice;
        if ((temp == expected)) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        // Check if numbers are 2-6
        std::vector<std::int32_t> expected = {2, 3, 4, 5, 6};
        std::vector<std::int32_t> temp = sorted_dice;
        if ((temp == expected)) {
            return 30;
        }
        return 0;
    } else if (category == "choice") {
        std::int32_t total = 0;
        for (std::int32_t num : dice) {
            total += num;
        }
        return total;
    } else if (category == "yacht") {
        // Check if all dice are the same
        std::int32_t all_same = 1;
        for (std::int32_t i = 1; i < 5; i++) {
            if ((dice[i] != dice[0])) {
                all_same = 0;
                break;
            }
        }
        if (all_same) {
            return 50;
        } else {
            return 0;
        }
    }
    return 0;
}

}  // namespace yacht
