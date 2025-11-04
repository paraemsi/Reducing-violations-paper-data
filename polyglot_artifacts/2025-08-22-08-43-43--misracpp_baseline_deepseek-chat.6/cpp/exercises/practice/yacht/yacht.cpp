#include "yacht.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
using namespace std;

namespace yacht {

int score(vector<int> dice, const string& category) {
    sort(dice.begin(), dice.end());
    
    // Map category names to enum values
    static const unordered_map<string, Category> category_map = {
        {"ones", Category::Ones},
        {"twos", Category::Twos},
        {"threes", Category::Threes},
        {"fours", Category::Fours},
        {"fives", Category::Fives},
        {"sixes", Category::Sixes},
        {"full house", Category::FullHouse},
        {"four of a kind", Category::FourOfAKind},
        {"little straight", Category::LittleStraight},
        {"big straight", Category::BigStraight},
        {"choice", Category::Choice},
        {"yacht", Category::Yacht}
    };
    
    // Get the enum value from the string
    auto it = category_map.find(category);
    if (it == category_map.end()) {
        return 0;
    }
    Category cat = it->second;
    
    switch (cat) {
        case Category::Ones: {
            int count = 0;
            for (int num : dice) if (num == 1) count++;
            return count * 1;
        }
        case Category::Twos: {
            int count = 0;
            for (int num : dice) if (num == 2) count++;
            return count * 2;
        }
        case Category::Threes: {
            int count = 0;
            for (int num : dice) if (num == 3) count++;
            return count * 3;
        }
        case Category::Fours: {
            int count = 0;
            for (int num : dice) if (num == 4) count++;
            return count * 4;
        }
        case Category::Fives: {
            int count = 0;
            for (int num : dice) if (num == 5) count++;
            return count * 5;
        }
        case Category::Sixes: {
            int count = 0;
            for (int num : dice) if (num == 6) count++;
            return count * 6;
        }
        case Category::FullHouse: {
            // Check if it's three of one number and two of another
            map<int, int> counts;
            for (int num : dice) counts[num]++;
            if (counts.size() != 2) return 0;
            auto it = counts.begin();
            int firstCount = it->second;
            it++;
            int secondCount = it->second;
            if ((firstCount == 2 && secondCount == 3) || (firstCount == 3 && secondCount == 2)) {
                int sum = 0;
                for (int num : dice) sum += num;
                return sum;
            }
            return 0;
        }
        case Category::FourOfAKind: {
            // At least four dice showing the same face
            map<int, int> counts;
            for (int num : dice) counts[num]++;
            for (const auto& pair : counts) {
                if (pair.second >= 4) {
                    return 4 * pair.first;
                }
            }
            return 0;
        }
        case Category::LittleStraight: {
            // Check if it's 1-2-3-4-5
            set<int> s(dice.begin(), dice.end());
            if (s.size() == 5) {
                // Check if all numbers are between 1 and 5 and no duplicates
                if (*s.begin() == 1 && *s.rbegin() == 5) {
                    return 30;
                }
            }
            return 0;
        }
        case Category::BigStraight: {
            // Check if it's 2-3-4-5-6
            set<int> s(dice.begin(), dice.end());
            if (s.size() == 5) {
                // Check if all numbers are between 2 and 6 and no duplicates
                if (*s.begin() == 2 && *s.rbegin() == 6) {
                    return 30;
                }
            }
            return 0;
        }
        case Category::Choice: {
            int sum = 0;
            for (int num : dice) sum += num;
            return sum;
        }
        case Category::Yacht: {
            // All dice are the same
            if (dice[0] == dice[1] && dice[0] == dice[2] && dice[0] == dice[3] && dice[0] == dice[4]) {
                return 50;
            }
            return 0;
        }
        default:
            return 0;
    }
}

}  // namespace yacht
