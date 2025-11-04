#include "yacht.h"

#include <array>
#include <string>

namespace yacht {

std::int32_t score(const std::vector<std::uint8_t>& dice, const std::string& category) {
    if (dice.size() != 5) {
        return 0;
    }
    std::array<std::uint8_t, 7> counts{};
    for (auto d : dice) {
        if ((d < 1) || (d > 6)) {
            return 0;
        }
        counts[d]++;
    }
    if (category == "ones") {
        return (1 * counts[1]);
    } else if (category == "twos") {
        return (2 * counts[2]);
    } else if (category == "threes") {
        return (3 * counts[3]);
    } else if (category == "fours") {
        return (4 * counts[4]);
    } else if (category == "fives") {
        return (5 * counts[5]);
    } else if (category == "sixes") {
        return (6 * counts[6]);
    } else if (category == "full house") {
        std::uint8_t three_count = 0;
        std::uint8_t two_count = 0;
        for (std::uint8_t i = 1; i <= 6; ++i) {
            if (counts[i] == 3) {
                three_count++;
            } else if (counts[i] == 2) {
                two_count++;
            }
        }
        if ((three_count == 1) && (two_count == 1)) {
            std::int32_t sum = 0;
            for (auto d : dice) {
                sum += d;
            }
            return sum;
        } else {
            return 0;
        }
    } else if (category == "four of a kind") {
        for (std::uint8_t i = 1; i <= 6; ++i) {
            if (counts[i] >= 4) {
                return (i * 4);
            }
        }
        return 0;
    } else if (category == "little straight") {
        if ((counts[1] == 1) && (counts[2] == 1) && (counts[3] == 1) && (counts[4] == 1) && (counts[5] == 1) && (counts[6] == 0)) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "big straight") {
        if ((counts[1] == 0) && (counts[2] == 1) && (counts[3] == 1) && (counts[4] == 1) && (counts[5] == 1) && (counts[6] == 1)) {
            return 30;
        } else {
            return 0;
        }
    } else if (category == "choice") {
        std::int32_t sum = 0;
        for (auto d : dice) {
            sum += d;
        }
        return sum;
    } else if (category == "yacht") {
        for (std::uint8_t i = 1; i <= 6; ++i) {
            if (counts[i] == 5) {
                return 50;
            }
        }
        return 0;
    } else {
        return 0;
    }
}

}  // namespace yacht
