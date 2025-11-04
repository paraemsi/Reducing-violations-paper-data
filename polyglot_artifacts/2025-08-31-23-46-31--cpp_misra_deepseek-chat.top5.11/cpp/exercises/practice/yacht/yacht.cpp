#include "yacht.h"
#include <algorithm>
#include <map>
#include <vector>
#include <string>

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
        std::vector<std::int32_t> little_straight = {1, 2, 3, 4, 5};
        if (sorted_dice == little_straight) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "big straight") {
        std::vector<std::int32_t> big_straight = {2, 3, 4, 5, 6};
        if (sorted_dice == big_straight) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "choice") {
        return dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
    } else if (category == "yacht") {
        bool all_same = true;
        for (std::int32_t i = 1; i < 5; i++) {
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
