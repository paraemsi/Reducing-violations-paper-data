#include "yacht.h"
#include <array>
#include <algorithm>
#include <functional>
#include <map>
#include <cstdint>
#include <string>
#include <cstddef>

namespace yacht {

std::int32_t score(std::array<std::int8_t, 5> dice, const std::string& category) {
    if (category == "ones") {
        std::int32_t count = 0;
        for (const auto& die : dice) {
            if (die == 1) {
                count++;
            }
        }
        return count * 1;
    } else if (category == "twos") {
        std::int32_t count = 0;
        for (const auto& die : dice) {
            if (die == 2) {
                count++;
            }
        }
        return count * 2;
    } else if (category == "threes") {
        std::int32_t count = 0;
        for (const auto& die : dice) {
            if (die == 3) {
                count++;
            }
        }
        return count * 3;
    } else if (category == "fours") {
        std::int32_t count = 0;
        for (const auto& die : dice) {
            if (die == 4) {
                count++;
            }
        }
        return count * 4;
    } else if (category == "fives") {
        std::int32_t count = 0;
        for (const auto& die : dice) {
            if (die == 5) {
                count++;
            }
        }
        return count * 5;
    } else if (category == "sixes") {
        std::int32_t count = 0;
        for (const auto& die : dice) {
            if (die == 6) {
                count++;
            }
        }
        return count * 6;
    } else if (category == "full house") {
        std::map<std::int8_t, std::int32_t> counts;
        for (const auto& die : dice) {
            counts[die]++;
        }
        if (counts.size() != 2) {
            return 0;
        }
        auto it = counts.begin();
        std::int32_t firstCount = it->second;
        it++;
        std::int32_t secondCount = it->second;
        if (((firstCount == 2) && (secondCount == 3)) || ((firstCount == 3) && (secondCount == 2))) {
            std::int32_t total = 0;
            for (const auto& die : dice) {
                total += static_cast<std::int32_t>(die);
            }
            return total;
        }
        return 0;
    } else if (category == "four of a kind") {
        std::map<std::int8_t, std::int32_t> counts;
        for (const auto& die : dice) {
            counts[die]++;
        }
        for (const auto& pair : counts) {
            if (pair.second >= 4) {
                return 4 * static_cast<std::int32_t>(pair.first);
            }
        }
        return 0;
    } else if (category == "little straight") {
        std::sort(dice.begin(), dice.end());
        if (dice[0] == 1 && dice[1] == 2 && dice[2] == 3 && dice[3] == 4 && dice[4] == 5) {
            return 30;
        }
        return 0;
    } else if (category == "big straight") {
        std::sort(dice.begin(), dice.end());
        if (dice[0] == 2 && dice[1] == 3 && dice[2] == 4 && dice[3] == 5 && dice[4] == 6) {
            return 30;
        }
        return 0;
    } else if (category == "choice") {
        std::int32_t total = 0;
        for (const auto& die : dice) {
            total += static_cast<std::int32_t>(die);
        }
        return total;
    } else if (category == "yacht") {
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
