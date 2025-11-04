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
    // Sort the dice to make some checks easier
    std::sort(dice.begin(), dice.end());
    
    // Map category names to their implementations
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
    
    // Get the enum value from the string
    auto it = category_map.find(category);
    if (it == category_map.end()) {
        return 0;
    }
    Category cat = it->second;
    
    switch (cat) {
        case Category::Ones: {
            int count = 0;
            for (int num : dice) {
                if (num == 1) count++;
            }
            return count * 1;
        }
        case Category::Twos: {
            int count = 0;
            for (int num : dice) {
                if (num == 2) count++;
            }
            return count * 2;
        }
        case Category::Threes: {
            int count = 0;
            for (int num : dice) {
                if (num == 3) count++;
            }
            return count * 3;
        }
        case Category::Fours: {
            int count = 0;
            for (int num : dice) {
                if (num == 4) count++;
            }
            return count * 4;
        }
        case Category::Fives: {
            int count = 0;
            for (int num : dice) {
                if (num == 5) count++;
            }
            return count * 5;
        }
        case Category::Sixes: {
            int count = 0;
            for (int num : dice) {
                if (num == 6) count++;
            }
            return count * 6;
        }
        case Category::FullHouse: {
            // Check if it's three of one number and two of another
            std::map<int, int> counts;
            for (int num : dice) {
                counts[num]++;
            }
            // Check if we have exactly two different numbers
            if (counts.size() == 2) {
                // Check if one appears 3 times and the other 2 times
                bool valid = true;
                bool has_three = false;
                bool has_two = false;
                for (const auto& pair : counts) {
                    if (pair.second == 3) has_three = true;
                    else if (pair.second == 2) has_two = true;
                    else valid = false;
                }
                if (valid && has_three && has_two) {
                    int total = 0;
                    for (int num : dice) total += num;
                    return total;
                }
            }
            return 0;
        }
        case Category::FourOfAKind: {
            std::map<int, int> counts;
            for (int num : dice) {
                counts[num]++;
            }
            // Find a number that appears at least 4 times
            for (const auto& pair : counts) {
                if (pair.second >= 4) {
                    return 4 * pair.first;
                }
            }
            return 0;
        }
        case Category::LittleStraight: {
            // Check if all numbers are unique and exactly 1-5
            std::set<int> s(dice.begin(), dice.end());
            if (s.size() == 5) {
                // Check if the set contains exactly 1,2,3,4,5
                if (s.count(1) && s.count(2) && s.count(3) && s.count(4) && s.count(5)) {
                    return 30;
                }
            }
            return 0;
        }
        case Category::BigStraight: {
            // Check if all numbers are unique and exactly 2-6
            std::set<int> s(dice.begin(), dice.end());
            if (s.size() == 5) {
                // Check if the set contains exactly 2,3,4,5,6
                if (s.count(2) && s.count(3) && s.count(4) && s.count(5) && s.count(6)) {
                    return 30;
                }
            }
            return 0;
        }
        case Category::Choice: {
            int total = 0;
            for (int num : dice) {
                total += num;
            }
            return total;
        }
        case Category::Yacht: {
            // Check if all dice are the same
            if (dice[0] == dice[1] && dice[1] == dice[2] && dice[2] == dice[3] && dice[3] == dice[4]) {
                return 50;
            }
            return 0;
        }
        default:
            return 0;
    }
}

}  // namespace yacht
