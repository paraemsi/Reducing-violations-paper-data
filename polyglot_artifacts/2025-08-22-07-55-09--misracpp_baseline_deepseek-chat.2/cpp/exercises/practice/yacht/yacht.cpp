#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <set>

namespace yacht {

int score(std::vector<int> dice, const std::string& category) {
    // Sort the dice to make some checks easier
    std::sort(dice.begin(), dice.end());
    
    if (category == "ones") {
        int count = 0;
        for (int num : dice) if (num == 1) count++;
        return count * 1;
    } else if (category == "twos") {
        int count = 0;
        for (int num : dice) if (num == 2) count++;
        return count * 2;
    } else if (category == "threes") {
        int count = 0;
        for (int num : dice) if (num == 3) count++;
        return count * 3;
    } else if (category == "fours") {
        int count = 0;
        for (int num : dice) if (num == 4) count++;
        return count * 4;
    } else if (category == "fives") {
        int count = 0;
        for (int num : dice) if (num == 5) count++;
        return count * 5;
    } else if (category == "sixes") {
        int count = 0;
        for (int num : dice) if (num == 6) count++;
        return count * 6;
    } else if (category == "full house") {
        std::map<int, int> counts;
        for (int num : dice) counts[num]++;
        if (counts.size() != 2) return 0;
        auto it = counts.begin();
        int first_count = it->second;
        it++;
        int second_count = it->second;
        if ((first_count == 2 && second_count == 3) || (first_count == 3 && second_count == 2)) {
            int total = 0;
            for (int num : dice) total += num;
            return total;
        }
        return 0;
    } else if (category == "four of a kind") {
        std::map<int, int> counts;
        for (int num : dice) counts[num]++;
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                return 4 * pair.first;
            }
        }
        return 0;
    } else if (category == "little straight") {
        std::set<int> unique_dice(dice.begin(), dice.end());
        if (unique_dice.size() == 5 && *unique_dice.rbegin() == 5 && *unique_dice.begin() == 1) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        std::set<int> unique_dice(dice.begin(), dice.end());
        if (unique_dice.size() == 5 && *unique_dice.rbegin() == 6 && *unique_dice.begin() == 2) {
            return 30;
        }
        return 0;
    } else if (category == "choice") {
        int total = 0;
        for (int num : dice) total += num;
        return total;
    } else if (category == "yacht") {
        if (dice[0] == dice[1] && dice[1] == dice[2] && dice[2] == dice[3] && dice[3] == dice[4]) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
