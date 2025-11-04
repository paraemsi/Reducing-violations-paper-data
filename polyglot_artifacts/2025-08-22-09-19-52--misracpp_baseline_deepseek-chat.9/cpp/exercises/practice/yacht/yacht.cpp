#include "yacht.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <numeric>
#include <string>
#include <unordered_map>

namespace yacht {

int score(std::vector<int> dice, const std::string& category) {
    std::sort(dice.begin(), dice.end());
    
    if (category == "ones") {
        int count = std::count_if(dice.begin(), dice.end(), [](int num) { return num == 1; });
        return count * 1;
    } else if (category == "twos") {
        int count = std::count_if(dice.begin(), dice.end(), [](int num) { return num == 2; });
        return count * 2;
    } else if (category == "threes") {
        int count = std::count_if(dice.begin(), dice.end(), [](int num) { return num == 3; });
        return count * 3;
    } else if (category == "fours") {
        int count = std::count_if(dice.begin(), dice.end(), [](int num) { return num == 4; });
        return count * 4;
    } else if (category == "fives") {
        int count = std::count_if(dice.begin(), dice.end(), [](int num) { return num == 5; });
        return count * 5;
    } else if (category == "sixes") {
        int count = std::count_if(dice.begin(), dice.end(), [](int num) { return num == 6; });
        return count * 6;
    } else if (category == "full house") {
        std::unordered_map<int, int> counts;
        for (int num : dice) counts[num]++;
        // Check if we have exactly two distinct numbers and neither has count 1 or 4
        if (counts.size() == 2) {
            auto it = counts.begin();
            int count1 = it->second;
            int count2 = (++it)->second;
            // One must be 2 and the other must be 3
            if ((count1 == 2 && count2 == 3) || (count1 == 3 && count2 == 2)) {
                return std::accumulate(dice.begin(), dice.end(), 0);
            }
        }
        return 0;
    } else if (category == "four of a kind") {
        // Check if at least four dice are the same
        // Since dice are sorted, the four of a kind can be the first four or last four
        bool first_four_same = (dice[0] == dice[3]);
        bool last_four_same = (dice[1] == dice[4]);
        
        if (first_four_same) {
            return 4 * dice[0];
        } else if (last_four_same) {
            return 4 * dice[1];
        }
        return 0;
    } else if (category == "little straight") {
        // After sorting, check if dice are exactly 1,2,3,4,5
        if (dice.size() == 5 && 
            dice[0] == 1 && dice[1] == 2 && dice[2] == 3 && dice[3] == 4 && dice[4] == 5) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        // After sorting, check if dice are exactly 2,3,4,5,6
        if (dice.size() == 5 && 
            dice[0] == 2 && dice[1] == 3 && dice[2] == 4 && dice[3] == 5 && dice[4] == 6) {
            return 30;
        }
        return 0;
    } else if (category == "choice") {
        return std::accumulate(dice.begin(), dice.end(), 0);
    } else if (category == "yacht") {
        if (std::all_of(dice.begin(), dice.end(), [&](int num) { return num == dice[0]; })) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
