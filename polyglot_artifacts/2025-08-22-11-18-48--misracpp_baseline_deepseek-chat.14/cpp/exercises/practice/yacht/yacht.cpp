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
        int sum = 0;
        for (int num : sorted_dice) {
            if (num == 1) sum += 1;
        }
        return sum;
    } else if (category == "twos") {
        int sum = 0;
        for (int num : sorted_dice) {
            if (num == 2) sum += 2;
        }
        return sum;
    } else if (category == "threes") {
        int sum = 0;
        for (int num : sorted_dice) {
            if (num == 3) sum += 3;
        }
        return sum;
    } else if (category == "fours") {
        int sum = 0;
        for (int num : sorted_dice) {
            if (num == 4) sum += 4;
        }
        return sum;
    } else if (category == "fives") {
        int sum = 0;
        for (int num : sorted_dice) {
            if (num == 5) sum += 5;
        }
        return sum;
    } else if (category == "sixes") {
        int sum = 0;
        for (int num : sorted_dice) {
            if (num == 6) sum += 6;
        }
        return sum;
    } else if (category == "full house") {
        // Check if it's a full house: three of one number and two of another
        // All dice must be used, and exactly two distinct numbers
        std::map<int, int> counts;
        for (int num : sorted_dice) {
            counts[num]++;
        }
        if (counts.size() != 2) return 0;
        auto it = counts.begin();
        int first_count = it->second;
        it++;
        int second_count = it->second;
        if ((first_count == 2 && second_count == 3) || (first_count == 3 && second_count == 2)) {
            int total = 0;
            for (int num : sorted_dice) total += num;
            return total;
        }
        return 0;
    } else if (category == "four of a kind") {
        // At least four dice showing the same face
        std::map<int, int> counts;
        for (int num : sorted_dice) {
            counts[num]++;
        }
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                return pair.first * 4;
            }
        }
        return 0;
    } else if (category == "little straight") {
        // Check if dice are 1-2-3-4-5
        std::set<int> unique_dice(sorted_dice.begin(), sorted_dice.end());
        if (unique_dice.size() != 5) return 0;
        for (int i = 1; i <= 5; i++) {
            if (unique_dice.find(i) == unique_dice.end()) {
                return 0;
            }
        }
        return 30;
    } else if (category == "big straight") {
        // Check if dice are 2-3-4-5-6
        std::set<int> unique_dice(sorted_dice.begin(), sorted_dice.end());
        if (unique_dice.size() != 5) return 0;
        for (int i = 2; i <= 6; i++) {
            if (unique_dice.find(i) == unique_dice.end()) {
                return 0;
            }
        }
        return 30;
    } else if (category == "choice") {
        // Sum of all dice
        int total = 0;
        for (int num : sorted_dice) total += num;
        return total;
    } else if (category == "yacht") {
        // All dice are the same
        bool all_equal = true;
        for (size_t i = 1; i < sorted_dice.size(); i++) {
            if (sorted_dice[i] != sorted_dice[0]) {
                all_equal = false;
                break;
            }
        }
        if (all_equal) {
            return 50;
        }
        return 0;
    } else {
        return 0;
    }
}

}  // namespace yacht
