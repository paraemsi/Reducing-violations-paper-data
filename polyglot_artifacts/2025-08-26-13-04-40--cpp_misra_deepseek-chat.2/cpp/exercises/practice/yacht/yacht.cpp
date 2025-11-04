#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <string>
#include <cstdint>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const char* category) {
    std::string cat(category);
    
    // Make a copy of dice to sort since the original is const
    std::vector<std::int32_t> sorted_dice = dice;
    std::sort(sorted_dice.begin(), sorted_dice.end());
    
    if (cat == "ones") {
        return static_cast<std::int32_t>(1) * static_cast<std::int32_t>(std::count(sorted_dice.begin(), sorted_dice.end(), 1));
    } else if (cat == "twos") {
        return static_cast<std::int32_t>(2) * static_cast<std::int32_t>(std::count(sorted_dice.begin(), sorted_dice.end(), 2));
    } else if (cat == "threes") {
        return static_cast<std::int32_t>(3) * static_cast<std::int32_t>(std::count(sorted_dice.begin(), sorted_dice.end(), 3));
    } else if (cat == "fours") {
        return static_cast<std::int32_t>(4) * static_cast<std::int32_t>(std::count(sorted_dice.begin(), sorted_dice.end(), 4));
    } else if (cat == "fives") {
        return static_cast<std::int32_t>(5) * static_cast<std::int32_t>(std::count(sorted_dice.begin(), sorted_dice.end(), 5));
    } else if (cat == "sixes") {
        return static_cast<std::int32_t>(6) * static_cast<std::int32_t>(std::count(sorted_dice.begin(), sorted_dice.end(), 6));
    } else if (cat == "full house") {
        // Check if there are three of one number and two of another
        std::map<std::int32_t, std::int32_t> counts;
        for (std::int32_t num : sorted_dice) {
            counts[num]++;
        }
        if (counts.size() == 2) {
            auto it = counts.begin();
            std::int32_t first_count = it->second;
            std::int32_t second_count = (++it)->second;
            if (((first_count == 3) && (second_count == 2)) || ((first_count == 2) && (second_count == 3))) {
                std::int32_t total = 0;
                for (std::int32_t num : sorted_dice) total += num;
                return total;
            }
        }
        return 0;
    } else if (cat == "four of a kind") {
        // At least four dice showing the same face
        // Since dice are sorted, the four of a kind must be either the first four or last four
        // Check if first four are equal
        if ((sorted_dice[0] == sorted_dice[1]) && (sorted_dice[1] == sorted_dice[2]) && (sorted_dice[2] == sorted_dice[3])) {
            return static_cast<std::int32_t>(4) * sorted_dice[0];
        }
        // Check if last four are equal
        if ((sorted_dice[1] == sorted_dice[2]) && (sorted_dice[2] == sorted_dice[3]) && (sorted_dice[3] == sorted_dice[4])) {
            return static_cast<std::int32_t>(4) * sorted_dice[1];
        }
        return 0;
    } else if (cat == "little straight") {
        // Check if dice are 1-2-3-4-5
        for (std::int32_t i = 0; i < 5; i++) {
            if (sorted_dice[i] != (i + 1)) {
                return 0;
            }
        }
        return 30;
    } else if (cat == "big straight") {
        // Check if dice are 2-3-4-5-6
        for (std::int32_t i = 0; i < 5; i++) {
            if (sorted_dice[i] != (i + 2)) {
                return 0;
            }
        }
        return 30;
    } else if (cat == "choice") {
        std::int32_t total = 0;
        for (std::int32_t num : sorted_dice) total += num;
        return total;
    } else if (cat == "yacht") {
        // All five dice are the same
        if ((sorted_dice[0] == sorted_dice[1]) && (sorted_dice[1] == sorted_dice[2]) && (sorted_dice[2] == sorted_dice[3]) && (sorted_dice[3] == sorted_dice[4])) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
