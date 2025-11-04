#include "yacht.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <string>

namespace yacht {

int score(const std::vector<int>& dice, const std::string& category) {
    // Make a copy to sort
    std::vector<int> sorted_dice = dice;
    std::sort(sorted_dice.begin(), sorted_dice.end());
    
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
        std::map<int, int> counts;
        for (int num : sorted_dice) counts[num]++;
        if (counts.size() != 2) return 0;
        bool has_three = false;
        bool has_two = false;
        for (const auto& pair : counts) {
            if (pair.second == 3) has_three = true;
            else if (pair.second == 2) has_two = true;
            else return 0;
        }
        if (has_three && has_two) {
            int sum = 0;
            for (int num : sorted_dice) sum += num;
            return sum;
        }
        return 0;
    } else if (category == "four of a kind") {
        std::map<int, int> counts;
        for (int num : sorted_dice) counts[num]++;
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                return 4 * pair.first;
            }
        }
        return 0;
    } else if (category == "little straight") {
        std::set<int> s(sorted_dice.begin(), sorted_dice.end());
        if (s.size() == 5 && *s.rbegin() == 5 && *s.begin() == 1) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        std::set<int> s(sorted_dice.begin(), sorted_dice.end());
        if (s.size() == 5 && *s.rbegin() == 6 && *s.begin() == 2) {
            return 30;
        }
        return 0;
    } else if (category == "choice") {
        int sum = 0;
        for (int num : sorted_dice) sum += num;
        return sum;
    } else if (category == "yacht") {
        if (sorted_dice[0] == sorted_dice[1] && sorted_dice[0] == sorted_dice[2] && 
            sorted_dice[0] == sorted_dice[3] && sorted_dice[0] == sorted_dice[4]) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
