#include "yacht.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <numeric>
#include <string>
using namespace std;

namespace yacht {

int score(vector<int> dice, const string& category) {
    sort(dice.begin(), dice.end());
    
    if (category == "ones") {
        int count = count_if(dice.begin(), dice.end(), [](int num) { return num == 1; });
        return count * 1;
    } else if (category == "twos") {
        int count = count_if(dice.begin(), dice.end(), [](int num) { return num == 2; });
        return count * 2;
    } else if (category == "threes") {
        int count = count_if(dice.begin(), dice.end(), [](int num) { return num == 3; });
        return count * 3;
    } else if (category == "fours") {
        int count = count_if(dice.begin(), dice.end(), [](int num) { return num == 4; });
        return count * 4;
    } else if (category == "fives") {
        int count = count_if(dice.begin(), dice.end(), [](int num) { return num == 5; });
        return count * 5;
    } else if (category == "sixes") {
        int count = count_if(dice.begin(), dice.end(), [](int num) { return num == 6; });
        return count * 6;
    } else if (category == "full house") {
        map<int, int> counts;
        for (int num : dice) counts[num]++;
        if (counts.size() != 2) return 0;
        bool valid = false;
        for (const auto& pair : counts) {
            if (pair.second == 2 || pair.second == 3) {
                valid = true;
            } else {
                valid = false;
                break;
            }
        }
        if (valid) {
            return accumulate(dice.begin(), dice.end(), 0);
        }
        return 0;
    } else if (category == "four of a kind") {
        // Check if at least four dice are the same
        // Since dice are sorted, check first four or last four
        if (dice[0] == dice[3]) {
            return 4 * dice[0];
        }
        if (dice[1] == dice[4]) {
            return 4 * dice[1];
        }
        return 0;
    } else if (category == "little straight") {
        // Check if dice are 1-5, all unique and in order
        // Sort first, then check
        for (int i = 0; i < 4; i++) {
            if (dice[i] + 1 != dice[i + 1]) {
                return 0;
            }
        }
        if (dice[0] == 1 && dice[4] == 5) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        // Check if dice are 2-6, all unique and in order
        for (int i = 0; i < 4; i++) {
            if (dice[i] + 1 != dice[i + 1]) {
                return 0;
            }
        }
        if (dice[0] == 2 && dice[4] == 6) {
            return 30;
        }
        return 0;
    } else if (category == "choice") {
        return accumulate(dice.begin(), dice.end(), 0);
    } else if (category == "yacht") {
        if (dice[0] == dice[4]) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
