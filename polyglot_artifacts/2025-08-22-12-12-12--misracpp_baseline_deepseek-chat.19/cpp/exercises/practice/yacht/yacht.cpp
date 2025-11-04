#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <unordered_map>

namespace yacht {

int score(std::vector<int> dice, const std::string& category) {
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
        bool valid = true;
        int total = 0;
        for (const auto& pair : counts) {
            if (pair.second != 2 && pair.second != 3) {
                valid = false;
            }
            total += pair.first * pair.second;
        }
        return valid ? total : 0;
    } else if (category == "four of a kind") {
        // At least four dice showing the same face
        // Since dice are sorted, the four of a kind must be either the first four or last four
        bool valid1 = (dice[0] == dice[1] && dice[1] == dice[2] && dice[2] == dice[3]);
        bool valid2 = (dice[1] == dice[2] && dice[2] == dice[3] && dice[3] == dice[4]);
        if (valid1) {
            return 4 * dice[0];
        } else if (valid2) {
            return 4 * dice[1];
        } else {
            return 0;
        }
    } else if (category == "little straight") {
        // Check if it's 1-2-3-4-5
        std::set<int> s(dice.begin(), dice.end());
        if (s.size() == 5 && *s.rbegin() == 5 && *s.begin() == 1) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        // Check if it's 2-3-4-5-6
        std::set<int> s(dice.begin(), dice.end());
        if (s.size() == 5 && *s.rbegin() == 6 && *s.begin() == 2) {
            return 30;
        }
        return 0;
    } else if (category == "choice") {
        int total = 0;
        for (int num : dice) total += num;
        return total;
    } else if (category == "yacht") {
        // All dice are the same
        if (dice[0] == dice[1] && dice[1] == dice[2] && 
            dice[2] == dice[3] && dice[3] == dice[4]) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
