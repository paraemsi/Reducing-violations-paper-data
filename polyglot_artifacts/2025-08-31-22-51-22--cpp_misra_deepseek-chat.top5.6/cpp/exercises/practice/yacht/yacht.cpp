#include "yacht.h"
#include <algorithm>
#include <array>
#include <cctype>
#include <cstdint>
#include <map>
#include <string>
#include <cstring>

namespace yacht {

std::int32_t score(const std::int32_t dice[5], const char* category) {
    std::int32_t result = 0;
    std::array<std::int32_t, 5> dice_arr;
    for (int i = 0; i < 5; i++) {
        dice_arr[i] = dice[i];
    }
    std::sort(dice_arr.begin(), dice_arr.end());
    
    // Convert category to a string for comparison, and make it lowercase
    std::string cat_str(category);
    for (char& c : cat_str) {
        c = std::tolower(c);
    }
    
    if (cat_str == "ones") {
        for (int i = 0; i < 5; i++) {
            if (dice_arr[i] == 1) {
                result += 1;
            }
        }
    } else if (cat_str == "twos") {
        for (int i = 0; i < 5; i++) {
            if (dice_arr[i] == 2) {
                result += 2;
            }
        }
    } else if (cat_str == "threes") {
        for (int i = 0; i < 5; i++) {
            if (dice_arr[i] == 3) {
                result += 3;
            }
        }
    } else if (cat_str == "fours") {
        for (int i = 0; i < 5; i++) {
            if (dice_arr[i] == 4) {
                result += 4;
            }
        }
    } else if (cat_str == "fives") {
        for (int i = 0; i < 5; i++) {
            if (dice_arr[i] == 5) {
                result += 5;
            }
        }
    } else if (cat_str == "sixes") {
        for (int i = 0; i < 5; i++) {
            if (dice_arr[i] == 6) {
                result += 6;
            }
        }
    } else if (cat_str == "full house") {
        // Check if there are exactly two distinct numbers, with counts 3 and 2
        std::map<std::int32_t, std::int32_t> counts;
        for (int i = 0; i < 5; i++) {
            counts[dice_arr[i]]++;
        }
        if (counts.size() == 2) {
            auto it = counts.begin();
            std::int32_t first_count = it->second;
            it++;
            std::int32_t second_count = it->second;
            if (((first_count == 2) && (second_count == 3)) || ((first_count == 3) && (second_count == 2))) {
                for (int i = 0; i < 5; i++) {
                    result += dice_arr[i];
                }
            }
        }
    } else if (cat_str == "four of a kind") {
        std::map<std::int32_t, std::int32_t> counts;
        for (int i = 0; i < 5; i++) {
            counts[dice_arr[i]]++;
        }
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                result = 4 * pair.first;
                break;
            }
        }
    } else if (cat_str == "little straight") {
        // Check if dice are exactly 1,2,3,4,5 when sorted
        // Since they're sorted, we can check directly
        bool is_little_straight = true;
        for (int i = 0; i < 5; i++) {
            if (dice_arr[i] != i + 1) {
                is_little_straight = false;
                break;
            }
        }
        // Also, all must be distinct
        for (int i = 0; i < 4; i++) {
            if (dice_arr[i] == dice_arr[i + 1]) {
                is_little_straight = false;
                break;
            }
        }
        if (is_little_straight) {
            result = 30;
        }
    } else if (cat_str == "big straight") {
        // Check if dice are exactly 2,3,4,5,6 when sorted
        bool is_big_straight = true;
        for (int i = 0; i < 5; i++) {
            if (dice_arr[i] != i + 2) {
                is_big_straight = false;
                break;
            }
        }
        // Also, all must be distinct
        for (int i = 0; i < 4; i++) {
            if (dice_arr[i] == dice_arr[i + 1]) {
                is_big_straight = false;
                break;
            }
        }
        if (is_big_straight) {
            result = 30;
        }
    } else if (cat_str == "choice") {
        for (int i = 0; i < 5; i++) {
            result += dice_arr[i];
        }
    } else if (cat_str == "yacht") {
        // All dice are the same
        bool is_yacht = true;
        for (int i = 1; i < 5; i++) {
            if (dice_arr[i] != dice_arr[0]) {
                is_yacht = false;
                break;
            }
        }
        if (is_yacht) {
            result = 50;
        }
    }
    return result;
}

}  // namespace yacht
