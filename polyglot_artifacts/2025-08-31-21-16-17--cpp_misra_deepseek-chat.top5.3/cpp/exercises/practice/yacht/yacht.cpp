#include "yacht.h"
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <cstdint>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
    if (category == "ones") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if (num == 1) {
                count++;
            }
        }
        return (count * 1);
    } else if (category == "twos") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if (num == 2) {
                count++;
            }
        }
        return (count * 2);
    } else if (category == "threes") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if (num == 3) {
                count++;
            }
        }
        return (count * 3);
    } else if (category == "fours") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if (num == 4) {
                count++;
            }
        }
        return (count * 4);
    } else if (category == "fives") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if (num == 5) {
                count++;
            }
        }
        return (count * 5);
    } else if (category == "sixes") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if (num == 6) {
                count++;
            }
        }
        return (count * 6);
    } else if (category == "full house") {
        std::map<std::int32_t, std::int32_t> counts;
        for (std::int32_t num : dice) {
            counts[num]++;
        }
        if (counts.size() != 2) {
            return 0;
        }
        auto it = counts.begin();
        std::int32_t first_count = it->second;
        it++;
        std::int32_t second_count = it->second;
        if ((((first_count == 2) && (second_count == 3)) || ((first_count == 3) && (second_count == 2)))) {
            std::int32_t sum = 0;
            for (std::int32_t num : dice) {
                sum += num;
            }
            return sum;
        } else {
            return 0;
        }
    } else if (category == "four of a kind") {
        std::map<std::int32_t, std::int32_t> counts;
        for (std::int32_t num : dice) {
            counts[num]++;
        }
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                return (pair.first * 4);
            }
        }
        return 0;
    } else if (category == "little straight") {
        std::vector<std::int32_t> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        // Check if all are unique and in sequence 1-5
        bool is_valid = true;
        for (std::int32_t i = 0; i < 4; i++) {
            if ((sorted_dice[i] + 1) != sorted_dice[i + 1]) {
                is_valid = false;
                break;
            }
        }
        if (is_valid && (sorted_dice[0] == 1) && (sorted_dice[4] == 5)) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "big straight") {
        std::vector<std::int32_t> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        // Check if all are unique and in sequence 2-6
        bool is_valid = true;
        for (std::int32_t i = 0; i < 4; i++) {
            if ((sorted_dice[i] + 1) != sorted_dice[i + 1]) {
                is_valid = false;
                break;
            }
        }
        if (is_valid && (sorted_dice[0] == 2) && (sorted_dice[4] == 6)) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "choice") {
        std::int32_t sum = 0;
        for (std::int32_t num : dice) {
            sum += num;
        }
        return sum;
    } else if (category == "yacht") {
        std::int32_t first = dice[0];
        for (std::int32_t num : dice) {
            if (num != first) {
                return 0;
            }
        }
        return 50;
    }
    return 0;
}

}  // namespace yacht
