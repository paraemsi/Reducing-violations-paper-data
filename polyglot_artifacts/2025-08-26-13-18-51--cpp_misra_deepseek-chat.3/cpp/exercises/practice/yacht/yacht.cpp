#include "yacht.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <cstdint>
#include <string>
#include <unordered_map>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
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
            std::int32_t sum = 0;
            for (const auto& die : dice) {
                if (die == 1) {
                    sum += 1;
                }
            }
            return sum;
        }
        case Category::Twos: {
            std::int32_t sum = 0;
            for (const auto& die : dice) {
                if (die == 2) {
                    sum += 2;
                }
            }
            return sum;
        }
        case Category::Threes: {
            std::int32_t sum = 0;
            for (const auto& die : dice) {
                if (die == 3) {
                    sum += 3;
                }
            }
            return sum;
        }
        case Category::Fours: {
            std::int32_t sum = 0;
            for (const auto& die : dice) {
                if (die == 4) {
                    sum += 4;
                }
            }
            return sum;
        }
        case Category::Fives: {
            std::int32_t sum = 0;
            for (const auto& die : dice) {
                if (die == 5) {
                    sum += 5;
                }
            }
            return sum;
        }
        case Category::Sixes: {
            std::int32_t sum = 0;
            for (const auto& die : dice) {
                if (die == 6) {
                    sum += 6;
                }
            }
            return sum;
        }
        case Category::FullHouse: {
            std::map<std::int32_t, std::int32_t> counts;
            for (const auto& die : dice) {
                counts[die]++;
            }
            bool has_three = false;
            bool has_two = false;
            for (const auto& pair : counts) {
                if (pair.second == 3) {
                    has_three = true;
                } else if (pair.second == 2) {
                    has_two = true;
                }
            }
            if (has_three && has_two) {
                std::int32_t total = 0;
                for (const auto& die : dice) {
                    total += die;
                }
                return total;
            }
            return 0;
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
            // Check for 1-2-3-4-5
            if (sorted_dice == std::vector<std::int32_t>{1, 2, 3, 4, 5}) {
                return 30;
            }
            return 0;
        }
        case Category::BigStraight: {
            std::vector<std::int32_t> sorted_dice = dice;
            std::sort(sorted_dice.begin(), sorted_dice.end());
            // Check for 2-3-4-5-6
            if (sorted_dice == std::vector<std::int32_t>{2, 3, 4, 5, 6}) {
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
