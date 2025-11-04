#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>
using namespace std;

namespace yacht {

int score(vector<int> dice, string category) {
    sort(dice.begin(), dice.end());
    
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
        map<int, int> counts;
        for (int num : dice) counts[num]++;
        if (counts.size() == 2) {
            auto it = counts.begin();
            int count1 = it->second;
            it++;
            int count2 = it->second;
            if ((count1 == 2 && count2 == 3) || (count1 == 3 && count2 == 2)) {
                int total = 0;
                for (int num : dice) total += num;
                return total;
            }
        }
        return 0;
    } else if (category == "four of a kind") {
        if (dice[0] == dice[3]) return 4 * dice[0];
        if (dice[1] == dice[4]) return 4 * dice[1];
        return 0;
    } else if (category == "little straight") {
        set<int> s(dice.begin(), dice.end());
        if (s.size() == 5 && *s.begin() == 1 && *s.rbegin() == 5) return 30;
        return 0;
    } else if (category == "big straight") {
        set<int> s(dice.begin(), dice.end());
        if (s.size() == 5 && *s.begin() == 2 && *s.rbegin() == 6) return 30;
        return 0;
    } else if (category == "choice") {
        int total = 0;
        for (int num : dice) total += num;
        return total;
    } else if (category == "yacht") {
        if (dice[0] == dice[4]) return 50;
        return 0;
    }
    return 0;
}

}  // namespace yacht
