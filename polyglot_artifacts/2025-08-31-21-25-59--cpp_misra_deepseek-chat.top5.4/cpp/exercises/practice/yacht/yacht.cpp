#include "yacht.h"
#include <algorithm>
#include <array>
#include <functional>
#include <map>
#include <cstdint>
#include <string>

namespace yacht {

std::int32_t score(const std::int32_t dice[5], const std::string& category) {
    // Make a copy of the dice to work with
    std::array<std::int32_t, 5> dice_arr;
    for (std::int32_t i = 0; i < 5; i++) {
        dice_arr[i] = dice[i];
    }
    std::sort(dice_arr.begin(), dice_arr.end());
    
    if (category == "ones") {
        std::int32_t sum = 0;
        for (std::int32_t i = 0; i < 5; i++) {
            if (dice_arr[i] == 1) {
                sum += 1;
            }
        }
        return sum;
    } else if (category == "twos") {
        std::int32_t sum = 0;
        for (std::int32_t i = 0; i < 5; i++) {
            if (dice_arr[i] == 2) {
                sum += 2;
            }
        }
        return sum;
    } else if (category == "threes") {
        std::int32_t sum = 0;
        for (std::int32_t i = 0; i < 5; i++) {
            if (dice_arr[i] == 3) {
                sum += 3;
            }
        }
        return sum;
    } else if (category == "fours") {
        std::int32_t sum = 0;
        for (std::int32_t i = 0; i < 5; i++) {
            if (dice_arr[i] == 4) {
                sum += 4;
            }
        }
        return sum;
    } else if (category == "fives") {
        std::int32_t sum = 0;
        for (std::int32_t i = 0; i < 5; i++) {
            if (dice_arr[i] == 5) {
                sum += 5;
            }
        }
        return sum;
    } else if (category == "sixes") {
        std::int32_t sum = 0;
        for (std::int32_t i = 0; i < 5; i++) {
            if (dice_arr[i] == 6) {
                sum += 6;
            }
        }
        return sum;
    } else if (category == "full house") {
        // Check if there are exactly two distinct numbers, with counts of 3 and 2
        std::map<std::int32_t, std::int32_t> counts;
        for (std::int32_t i = 0; i < 5; i++) {
            counts[dice_arr[i]]++;
        }
        if (counts.size() != 2) {
            return 0;
        }
        auto it = counts.begin();
        std::int32_t first_count = it->second;
        it++;
        std::int32_t second_count = it->second;
        if (((first_count == 2) && (second_count == 3)) || ((first_count == 3) && (second_count == 2))) {
            return dice_arr[0] + dice_arr[1] + dice_arr[2] + dice_arr[3] + dice_arr[4];
        } else {
            return 0;
        }
    } else if (category == "four of a kind") {
        // At least four dice are the same
        // Since the array is sorted, the four of a kind must be either the first four or last four
        if (dice_arr[0] == dice_arr[3]) {
            return 4 * dice_arr[0];
        } else if (dice_arr[1] == dice_arr[4]) {
            return 4 * dice_arr[1];
        } else {
            return 0;
        }
    } else if (category == "little straight") {
        // Check if the sorted dice are exactly 1,2,3,4,5
        // All must be distinct and in order
        if ((dice_arr[0] == 1) && (dice_arr[1] == 2) && (dice_arr[2] == 3) && 
            (dice_arr[3] == 4) && (dice_arr[4] == 5)) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "big straight") {
        // Check if the sorted dice are exactly 2,3,4,5,6
        if ((dice_arr[0] == 2) && (dice_arr[1] == 3) && (dice_arr[2] == 4) && 
            (dice_arr[3] == 5) && (dice_arr[4] == 6)) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "choice") {
        return dice_arr[0] + dice_arr[1] + dice_arr[2] + dice_arr[3] + dice_arr[4];
    } else if (category == "yacht") {
        // All dice are the same
        if (dice_arr[0] == dice_arr[4]) {
            return 50;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

}  // namespace yacht
