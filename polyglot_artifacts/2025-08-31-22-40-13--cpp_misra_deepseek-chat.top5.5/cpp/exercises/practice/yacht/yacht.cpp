#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cstdint>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
    // Always 5 dice according to the note
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
        bool has_three = false;
        bool has_two = false;
        for (const auto& pair : counts) {
            if (pair.second == 3) {
                has_three = true;
            } else if (pair.second == 2) {
                has_two = true;
            } else if (pair.second != 2 && pair.second != 3) {
                return 0;
            }
        }
        if (has_three && has_two) {
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
        std::vector<std::int32_t> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        if (sorted_dice[0] == 1 && 
            sorted_dice[1] == 2 && 
            sorted_dice[2] == 3 && 
            sorted_dice[3] == 4 && 
            sorted_dice[4] == 5) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "big straight") {
        std::vector<std::int32_t> sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        if (sorted_dice[0] == 2 && 
            sorted_dice[1] == 3 && 
            sorted_dice[2] == 4 && 
            sorted_dice[3] == 5 && 
            sorted_dice[4] == 6) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "choice") {
        std::int32_t total = 0;
        for (const auto& die : dice) {
            total += die;
        }
        return total;
    } else if (category == "yacht") {
        bool all_same = true;
        for (std::size_t i = 1; i < dice.size(); i++) {
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
