#include "yacht.h"
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
using namespace std;

namespace yacht {

int score(const vector<int>& dice, const string& category) {
    if (category == "Ones") {
        int count = 0;
        for (int num : dice) {
            if (num == 1) count++;
        }
        return count * 1;
    } else if (category == "Twos") {
        int count = 0;
        for (int num : dice) {
            if (num == 2) count++;
        }
        return count * 2;
    } else if (category == "Threes") {
        int count = 0;
        for (int num : dice) {
            if (num == 3) count++;
        }
        return count * 3;
    } else if (category == "Fours") {
        int count = 0;
        for (int num : dice) {
            if (num == 4) count++;
        }
        return count * 4;
    } else if (category == "Fives") {
        int count = 0;
        for (int num : dice) {
            if (num == 5) count++;
        }
        return count * 5;
    } else if (category == "Sixes") {
        int count = 0;
        for (int num : dice) {
            if (num == 6) count++;
        }
        return count * 6;
    } else if (category == "Full House") {
        map<int, int> counts;
        for (int num : dice) {
            counts[num]++;
        }
        if (counts.size() != 2) return 0;
        bool hasThree = false;
        bool hasTwo = false;
        for (const auto& pair : counts) {
            if (pair.second == 3) hasThree = true;
            else if (pair.second == 2) hasTwo = true;
            else return 0;
        }
        if (hasThree && hasTwo) {
            int total = 0;
            for (int num : dice) total += num;
            return total;
        } else {
            return 0;
        }
    } else if (category == "Four of a Kind") {
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
    } else if (category == "Little Straight") {
        set<int> s(dice.begin(), dice.end());
        // Check if all numbers are unique and from 1 to 5
        if (s.size() == 5) {
            // Check if it contains 1 through 5
            if (s.find(1) != s.end() && s.find(2) != s.end() && 
                s.find(3) != s.end() && s.find(4) != s.end() && 
                s.find(5) != s.end()) {
                return 30;
            }
        }
        return 0;
    } else if (category == "Big Straight") {
        set<int> s(dice.begin(), dice.end());
        // Check if all numbers are unique and from 2 to 6
        if (s.size() == 5) {
            // Check if it contains 2 through 6
            if (s.find(2) != s.end() && s.find(3) != s.end() && 
                s.find(4) != s.end() && s.find(5) != s.end() && 
                s.find(6) != s.end()) {
                return 30;
            }
        }
        return 0;
    } else if (category == "Choice") {
        int total = 0;
        for (int num : dice) total += num;
        return total;
    } else if (category == "Yacht") {
        // Check if all dice are the same
        bool allSame = true;
        for (size_t i = 1; i < dice.size(); i++) {
            if (dice[i] != dice[0]) {
                allSame = false;
                break;
            }
        }
        if (allSame) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
