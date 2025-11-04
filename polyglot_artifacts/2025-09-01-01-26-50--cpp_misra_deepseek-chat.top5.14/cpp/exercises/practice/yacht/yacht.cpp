#include "yacht.h"
#include <vector>
#include <algorithm>
#include <map>
#include <cstdint>
#include <string>
#include <unordered_map>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
    // Map string to enum
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
    if (it == category_map.end()) {
        return 0;
    }
    Category cat = it->second;
    
    switch (cat) {
        case Category::Ones: {
            std::int32_t count = 0;
            for (const auto& die : dice) {
                if (die == 1) {
                    count++;
                }
            }
            return 1 * count;
        }
        case Category::Twos: {
            std::int32_t count = 0;
            for (const auto& die : dice) {
                if (die == 2) {
                    count++;
                }
            }
            return 2 * count;
        }
        case Category::Threes: {
            std::int32_t count = 0;
            for (const auto& die : dice) {
                if (die == 3) {
                    count++;
                }
            }
            return 3 * count;
        }
        case Category::Fours: {
            std::int32_t count = 0;
            for (const auto& die : dice) {
                if (die == 4) {
                    count++;
                }
            }
            return 4 * count;
        }
        case Category::Fives: {
            std::int32_t count = 0;
            for (const auto& die : dice) {
                if (die == 5) {
                    count++;
                }
            }
            return 5 * count;
        }
        case Category::Sixes: {
            std::int32_t count = 0;
            for (const auto& die : dice) {
                if (die == 6) {
                    count++;
                }
            }
            return 6 * count;
        }
        case Category::FullHouse: {
            std::map<std::int32_t, std::int32_t> counts;
            for (const auto& die : dice) {
                counts[die]++;
            }
            if (counts.size() != 2) {
                return 0;
            }
            bool has_three = false;
            bool has_two = false;
            for (const auto& pair : counts) {
                if (pair.second == 3) {
                    has_three = true;
                } else if (pair.second == 2) {
                    has_two = true;
                } else {
                    return 0;
                }
            }
            if (has_three && has_two) {
                std::int32_t total = 0;
                for (const auto& die : dice) {
                    total += die;
                }
                return total;
            } else {
                return 0;
            }
        }
        case Category::FourOfAKind: {
            std::map<std::int32_t, std::int32_t> counts;
            for (const auto& die : dice) {
                counts[die]++;
            }
            for (const auto& pair : counts) {
                if (pair.second >= 4) {
                    return 4 * pair.first;
                }
            }
            return 0;
        }
        case Category::LittleStraight: {
            std::vector<std::int32_t> sorted_dice = dice;
            std::sort(sorted_dice.begin(), sorted_dice.end());
            // Check for uniqueness first
            for (std::int32_t i = 0; i < 4; i++) {
                if (sorted_dice[i] == sorted_dice[i + 1]) {
                    return 0;
                }
            }
            // Check if it's 1-5
            if (sorted_dice[0] == 1 && 
                sorted_dice[1] == 2 && 
                sorted_dice[2] == 3 && 
                sorted_dice[3] == 4 && 
                sorted_dice[4] == 5) {
                return 30;
            }
            return 0;
        }
        case Category::BigStraight: {
            std::vector<std::int32_t> sorted_dice = dice;
            std::sort(sorted_dice.begin(), sorted_dice.end());
            // Check for uniqueness first
            for (std::int32_t i = 0; i < 4; i++) {
                if (sorted_dice[i] == sorted_dice[i + 1]) {
                    return 0;
                }
            }
            // Check if it's 2-6
            if (sorted_dice[0] == 2 && 
                sorted_dice[1] == 3 && 
                sorted_dice[2] == 4 && 
                sorted_dice[3] == 5 && 
                sorted_dice[4] == 6) {
                return 30;
            }
            return 0;
        }
        case Category::Choice: {
            std::int32_t total = 0;
            for (const auto& die : dice) {
                total += die;
            }
            return total;
        }
        case Category::Yacht: {
            std::int32_t first = dice[0];
            for (const auto& die : dice) {
                if (die != first) {
                    return 0;
                }
            }
            return 50;
        }
        default:
            return 0;
    }
}

}  // namespace yacht
