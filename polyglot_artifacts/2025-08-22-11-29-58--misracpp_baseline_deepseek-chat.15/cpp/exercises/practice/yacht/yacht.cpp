#include "yacht.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
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
        auto it = counts.begin();
        int count1 = it->second;
        it++;
        int count2 = it->second;
        if ((count1 == 2 && count2 == 3) || (count1 == 3 && count2 == 2)) {
            return accumulate(dice.begin(), dice.end(), 0);
        }
        return 0;
    } else if (category == "four of a kind") {
        // Check if first four or last four are the same
        if (dice[0] == dice[3]) {
            return 4 * dice[0];
        }
        if (dice[1] == dice[4]) {
            return 4 * dice[1];
        }
        return 0;
    } else if (category == "little straight") {
        // Check if all numbers are distinct and form 1-5
        vector<int> expected = {1, 2, 3, 4, 5};
        if (equal(dice.begin(), dice.end(), expected.begin())) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        // Check if all numbers are distinct and form 2-6
        vector<int> expected = {2, 3, 4, 5, 6};
        if (equal(dice.begin(), dice.end(), expected.begin())) {
            return 30;
        }
        return 0;
    } else if (category == "choice") {
        return accumulate(dice.begin(), dice.end(), 0);
    } else if (category == "yacht") {
        if (all_of(dice.begin(), dice.end(), [&](int num) { return num == dice[0]; })) {
            return 50;
        }
        return 0;
    }
    return 0;
}

}  // namespace yacht
