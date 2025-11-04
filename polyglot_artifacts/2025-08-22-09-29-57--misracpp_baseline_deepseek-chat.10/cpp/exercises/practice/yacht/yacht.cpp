#include "yacht.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <string>
#include <unordered_map>

namespace yacht {

int score(std::vector<int> dice, const std::string& category) {
    std::sort(dice.begin(), dice.end());
    
    // Map category string to enum
    static const std::unordered_map<std::string, Category> category_map = {
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
    
    auto it = category_map.find(category);
    if (it == category_map.end()) return 0;
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
            std::map<int, int> counts;
            for (int num : dice) counts[num]++;
            if (counts.size() != 2) return 0;
            auto it = counts.begin();
            int firstCount = it->second;
            it++;
            int secondCount = it->second;
            if ((firstCount == 2 && secondCount == 3) || (firstCount == 3 && secondCount == 2)) {
                return dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
            }
            return 0;
        }
        case Category::FourOfAKind: {
            // Since dice are sorted, check if first 4 are equal or last 4 are equal
            if (dice[0] == dice[3]) {
                return 4 * dice[0];
            }
            if (dice[1] == dice[4]) {
                return 4 * dice[1];
            }
            return 0;
        }
        case Category::LittleStraight: {
            // Check if dice are 1,2,3,4,5
            if (dice[0] == 1 && dice[1] == 2 && dice[2] == 3 && dice[3] == 4 && dice[4] == 5) {
                return 30;
            }
            return 0;
        }
        case Category::BigStraight: {
            // Check if dice are 2,3,4,5,6
            if (dice[0] == 2 && dice[1] == 3 && dice[2] == 4 && dice[3] == 5 && dice[4] == 6) {
                return 30;
            }
            return 0;
        }
        case Category::Choice: {
            return dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
        }
        case Category::Yacht: {
            if (dice[0] == dice[4]) {
                return 50;
            }
            return 0;
        }
        default:
            return 0;
    }
}

}  // namespace yacht
