#include "yacht.h"

#include <array>
#include <numeric>
#include <string>

namespace yacht {

int score(const std::vector<int>& dice, const std::string& cat) noexcept {
    // Tally counts of faces 1..6 at indices 1..6 (index 0 unused)
    std::array<int, 7> cnt{};
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            ++cnt[d];
        }
    }

    const int sum = std::accumulate(dice.begin(), dice.end(), 0);

    if (cat == "ones")   return 1 * cnt[1];
    else if (cat == "twos")   return 2 * cnt[2];
    else if (cat == "threes") return 3 * cnt[3];
    else if (cat == "fours")  return 4 * cnt[4];
    else if (cat == "fives")  return 5 * cnt[5];
    else if (cat == "sixes")  return 6 * cnt[6];

    else if (cat == "full house") {
        bool has_three = false;
        bool has_two = false;
        for (int face = 1; face <= 6; ++face) {
            if (cnt[face] == 3) has_three = true;
            else if (cnt[face] == 2) has_two = true;
        }
        return (has_three && has_two) ? sum : 0;
    }

    else if (cat == "four of a kind") {
        for (int face = 1; face <= 6; ++face) {
            if (cnt[face] >= 4) {
                return 4 * face;
            }
        }
        return 0;
    }

    else if (cat == "little straight") {
        return (cnt[1] == 1 && cnt[2] == 1 && cnt[3] == 1 &&
                cnt[4] == 1 && cnt[5] == 1 && cnt[6] == 0)
               ? 30 : 0;
    }

    else if (cat == "big straight") {
        return (cnt[1] == 0 && cnt[2] == 1 && cnt[3] == 1 &&
                cnt[4] == 1 && cnt[5] == 1 && cnt[6] == 1)
               ? 30 : 0;
    }

    else if (cat == "choice") {
        return sum;
    }

    else if (cat == "yacht") {
        for (int face = 1; face <= 6; ++face) {
            if (cnt[face] == 5) {
                return 50;
            }
        }
        return 0;
    }

    return 0; // Fallback (should be unreachable)
}

}  // namespace yacht
