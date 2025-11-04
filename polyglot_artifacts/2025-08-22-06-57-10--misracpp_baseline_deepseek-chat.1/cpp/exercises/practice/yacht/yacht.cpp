#include "yacht.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
using namespace std;

namespace yacht {

int score(vector<int> dice, const string& category) {
    sort(dice.begin(), dice.end());
    
    if (category == "ones") {
        int sum = 0;
        for (int num : dice) {
            if (num == 1) sum += 1;
        }
        return sum;
    } else if (category == "twos") {
        int sum = 0;
        for (int num : dice) {
            if (num == 2) sum += 2;
        }
        return sum;
    } else if (category == "threes") {
        int sum = 0;
        for (int num : dice) {
            if (num == 3) sum += 3;
        }
        return sum;
    } else if (category == "fours") {
        int sum = 0;
        for (int num : dice) {
            if (num == 4) sum += 4;
        }
        return sum;
    } else if (category == "fives") {
        int sum = 0;
        for (int num : dice) {
            if (num == 5) sum += 5;
        }
        return sum;
    } else if (category == "sixes") {
        int sum = 0;
        for (int num : dice) {
            if (num == 6) sum += 6;
        }
        return sum;
    } else if (category == "full house") {
        map<int, int> counts;
        for (int num : dice) {
            counts[num]++;
        }
        if (counts.size() != 2) return 0;
        bool has_three = false;
        bool has_two = false;
        int total = 0;
        for (const auto& pair : counts) {
            if (pair.second == 3) has_three = true;
            if (pair.second == 2) has_two = true;
            total += pair.first * pair.second;
        }
        return (has_three && has_two) ? total : 0;
    } else if (category == "four of a kind") {
        map<int, int> counts;
        for (int num : dice) {
            counts[num]++;
        }
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                return pair.first * 4;
            }
        }
        return 0;
    } else if (category == "little straight") {
        set<int> s(dice.begin(), dice.end());
        if (s.size() == 5 && *s.rbegin() == 5 && *s.begin() == 1) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        set<int> s(dice.begin(), dice.end());
        if (s.size() == 5 && *s.rbegin() == 6 && *s.begin() == 2) {
            return 30;
        }
        return 0;
    } else if (category == "choice") {
        int total = 0;
        for (int num : dice) {
            total += num;
        }
        return total;
    } else if (category == "yacht") {
        if (dice[0] == dice[1] && dice[1] == dice[2] && 
            dice[2] == dice[3] && dice[3] == dice[4]) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
