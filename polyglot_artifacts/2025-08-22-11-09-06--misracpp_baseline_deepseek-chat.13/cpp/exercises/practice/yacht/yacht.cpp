#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>
using namespace std;

namespace yacht {

int score(const std::vector<int>& dice, const std::string& category) {
    // Make a copy to sort
    std::vector<int> sorted_dice = dice;
    sort(sorted_dice.begin(), sorted_dice.end());
    
    if (category == "ones") {
        int count = 0;
        for (int num : sorted_dice) if (num == 1) count++;
        return count * 1;
    } else if (category == "twos") {
        int count = 0;
        for (int num : sorted_dice) if (num == 2) count++;
        return count * 2;
    } else if (category == "threes") {
        int count = 0;
        for (int num : sorted_dice) if (num == 3) count++;
        return count * 3;
    } else if (category == "fours") {
        int count = 0;
        for (int num : sorted_dice) if (num == 4) count++;
        return count * 4;
    } else if (category == "fives") {
        int count = 0;
        for (int num : sorted_dice) if (num == 5) count++;
        return count * 5;
    } else if (category == "sixes") {
        int count = 0;
        for (int num : sorted_dice) if (num == 6) count++;
        return count * 6;
    } else if (category == "full house") {
        map<int, int> counts;
        for (int num : sorted_dice) counts[num]++;
        if (counts.size() == 2) {
            auto it = counts.begin();
            int first_count = it->second;
            it++;
            int second_count = it->second;
            if ((first_count == 2 && second_count == 3) || (first_count == 3 && second_count == 2)) {
                int total = 0;
                for (int num : sorted_dice) total += num;
                return total;
            }
        }
        return 0;
    } else if (category == "four of a kind") {
        map<int, int> counts;
        for (int num : sorted_dice) counts[num]++;
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                return 4 * pair.first;
            }
        }
        return 0;
    } else if (category == "little straight") {
        set<int> unique_dice(sorted_dice.begin(), sorted_dice.end());
        if (unique_dice.size() == 5 && *unique_dice.rbegin() == 5 && *unique_dice.begin() == 1) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        set<int> unique_dice(sorted_dice.begin(), sorted_dice.end());
        if (unique_dice.size() == 5 && *unique_dice.rbegin() == 6 && *unique_dice.begin() == 2) {
            return 30;
        }
        return 0;
    } else if (category == "choice") {
        int total = 0;
        for (int num : sorted_dice) total += num;
        return total;
    } else if (category == "yacht") {
        if (sorted_dice[0] == sorted_dice[1] && sorted_dice[1] == sorted_dice[2] && 
            sorted_dice[2] == sorted_dice[3] && sorted_dice[3] == sorted_dice[4]) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
