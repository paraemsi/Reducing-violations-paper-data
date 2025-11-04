#include "yacht.h"
#include <string>
#include <vector>
#include <algorithm>
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
        // Check if we have exactly two distinct numbers, and the counts are 3 and 2
        // Since dice are sorted, this can be checked by comparing certain elements
        bool is_full_house = false;
        // Case 1: first three are equal, last two are equal, and they're different
        if (dice[0] == dice[2] && dice[3] == dice[4] && dice[2] != dice[3]) {
            is_full_house = true;
        }
        // Case 2: first two are equal, last three are equal, and they're different
        else if (dice[0] == dice[1] && dice[2] == dice[4] && dice[1] != dice[2]) {
            is_full_house = true;
        }
        if (is_full_house) {
            return dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
        }
        return 0;
    } else if (category == "four of a kind") {
        // Check if at least four dice are the same
        // Since dice are sorted, the four of a kind must be either the first four or last four
        if (dice[0] == dice[3]) {
            return 4 * dice[0];
        } else if (dice[1] == dice[4]) {
            return 4 * dice[1];
        }
        return 0;
    } else if (category == "little straight") {
        // Check if all numbers are unique and form 1-5
        // First, check if all are unique by using adjacent elements
        bool all_unique = true;
        for (int i = 0; i < 4; i++) {
            if (dice[i] == dice[i + 1]) {
                all_unique = false;
                break;
            }
        }
        if (all_unique && dice[0] == 1 && dice[4] == 5) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        // Check if all numbers are unique and form 2-6
        bool all_unique = true;
        for (int i = 0; i < 4; i++) {
            if (dice[i] == dice[i + 1]) {
                all_unique = false;
                break;
            }
        }
        if (all_unique && dice[0] == 2 && dice[4] == 6) {
            return 30;
        }
        return 0;
    } else if (category == "choice") {
        return dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
    } else if (category == "yacht") {
        if (dice[0] == dice[4]) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
