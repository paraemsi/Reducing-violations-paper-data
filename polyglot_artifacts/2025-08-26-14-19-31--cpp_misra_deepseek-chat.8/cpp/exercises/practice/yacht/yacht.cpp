#include "yacht.h"
#include <algorithm>
#include <functional>
#include <map>
#include <array>
#include <cstdint>
#include <cstring>

namespace yacht {

std::int32_t score(const int dice[5], const char* category) {
    // Map the category string to our enum
    Category cat;
    if (strcmp(category, "ones") == 0) {
        cat = Category::Ones;
    } else if (strcmp(category, "twos") == 0) {
        cat = Category::Twos;
    } else if (strcmp(category, "threes") == 0) {
        cat = Category::Threes;
    } else if (strcmp(category, "fours") == 0) {
        cat = Category::Fours;
    } else if (strcmp(category, "fives") == 0) {
        cat = Category::Fives;
    } else if (strcmp(category, "sixes") == 0) {
        cat = Category::Sixes;
    } else if (strcmp(category, "full house") == 0) {
        cat = Category::FullHouse;
    } else if (strcmp(category, "four of a kind") == 0) {
        cat = Category::FourOfAKind;
    } else if (strcmp(category, "little straight") == 0) {
        cat = Category::LittleStraight;
    } else if (strcmp(category, "big straight") == 0) {
        cat = Category::BigStraight;
    } else if (strcmp(category, "choice") == 0) {
        cat = Category::Choice;
    } else if (strcmp(category, "yacht") == 0) {
        cat = Category::Yacht;
    } else {
        return 0;
    }
    
    // Convert dice to a more manageable form
    std::array<std::int32_t, 5> dice_arr;
    for (std::int32_t i = 0; i < 5; i++) {
        dice_arr[i] = static_cast<std::int32_t>(dice[i]);
    }
    std::sort(dice_arr.begin(), dice_arr.end());
    
    switch (cat) {
        case Category::Ones:
        case Category::Twos:
        case Category::Threes:
        case Category::Fours:
        case Category::Fives:
        case Category::Sixes: {
            std::int32_t target = static_cast<std::int32_t>(cat) + 1;
            std::int32_t sum = 0;
            for (std::int32_t i = 0; i < 5; i++) {
                if (dice_arr[i] == target) {
                    sum += target;
                }
            }
            return sum;
        }
        case Category::FullHouse: {
            // Check if it's a full house: three of one and two of another
            bool condition1 = ((dice_arr[0] == dice_arr[1]) && (dice_arr[1] == dice_arr[2]) && 
                               (dice_arr[3] == dice_arr[4]) && (dice_arr[2] != dice_arr[3]));
            bool condition2 = ((dice_arr[0] == dice_arr[1]) && 
                               (dice_arr[2] == dice_arr[3]) && (dice_arr[3] == dice_arr[4]) && 
                               (dice_arr[1] != dice_arr[2]));
            if (condition1 || condition2) {
                std::int32_t sum = 0;
                for (std::int32_t i = 0; i < 5; i++) {
                    sum += dice_arr[i];
                }
                return sum;
            } else {
                return 0;
            }
        }
        case Category::FourOfAKind: {
            // Check for at least four of the same number
            if ((dice_arr[0] == dice_arr[3])) {
                return 4 * dice_arr[0];
            } else if ((dice_arr[1] == dice_arr[4])) {
                return 4 * dice_arr[1];
            } else {
                return 0;
            }
        }
        case Category::LittleStraight: {
            // Check if the sorted dice are exactly 1,2,3,4,5
            if ((dice_arr[0] == 1) && (dice_arr[1] == 2) && (dice_arr[2] == 3) && 
                (dice_arr[3] == 4) && (dice_arr[4] == 5)) {
                return 30;
            } else {
                return 0;
            }
        }
        case Category::BigStraight: {
            // Check if the sorted dice are exactly 2,3,4,5,6
            if ((dice_arr[0] == 2) && (dice_arr[1] == 3) && (dice_arr[2] == 4) && 
                (dice_arr[3] == 5) && (dice_arr[4] == 6)) {
                return 30;
            } else {
                return 0;
            }
        }
        case Category::Choice: {
            std::int32_t sum = 0;
            for (std::int32_t i = 0; i < 5; i++) {
                sum += dice_arr[i];
            }
            return sum;
        }
        case Category::Yacht: {
            // All dice must be the same
            if (dice_arr[0] == dice_arr[4]) {
                return 50;
            } else {
                return 0;
            }
        }
        default:
            return 0;
    }
}

}  // namespace yacht
