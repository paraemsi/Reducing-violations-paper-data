#include "yacht.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <numeric>
#include <string>

namespace yacht {

int score(const std::vector<int>& dice, const std::string& cat) {
    // Frequency of faces 1..6; index 0 is unused.
    std::array<int, 7> counts{};
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            ++counts[static_cast<std::size_t>(d)];
        }
    }
    const int total = std::accumulate(dice.begin(), dice.end(), 0);

    auto sum_of_face = [&](int face) -> int {
        return face * counts[static_cast<std::size_t>(face)];
    };

    // Match category by string per tests
    if (cat == "ones")   return sum_of_face(1);
    else if (cat == "twos")   return sum_of_face(2);
    else if (cat == "threes") return sum_of_face(3);
    else if (cat == "fours")  return sum_of_face(4);
    else if (cat == "fives")  return sum_of_face(5);
    else if (cat == "sixes")  return sum_of_face(6);
    else if (cat == "full house") {
        // Collect non-zero frequencies and check for {2,3}.
        std::array<int, 5> freq{}; // at most 5 distinct faces in 5 dice
        std::size_t idx = 0;
        for (std::size_t f = 1; f <= 6; ++f) {
            if (counts[f] != 0) {
                freq[idx++] = counts[f];
            }
        }
        std::sort(freq.begin(), freq.begin() + idx);
        if (idx == 2 && freq[0] == 2 && freq[1] == 3) {
            return total;
        }
        return 0;
    } else if (cat == "four of a kind") {
        for (int face = 1; face <= 6; ++face) {
            if (counts[static_cast<std::size_t>(face)] >= 4) {
                return 4 * face;
            }
        }
        return 0;
    } else if (cat == "little straight") {
        // Exactly 1-2-3-4-5
        bool ok = counts[1] == 1 && counts[2] == 1 && counts[3] == 1 &&
                  counts[4] == 1 && counts[5] == 1 && counts[6] == 0;
        return ok ? 30 : 0;
    } else if (cat == "big straight") {
        // Exactly 2-3-4-5-6
        bool ok = counts[1] == 0 && counts[2] == 1 && counts[3] == 1 &&
                  counts[4] == 1 && counts[5] == 1 && counts[6] == 1;
        return ok ? 30 : 0;
    } else if (cat == "choice") {
        return total;
    } else if (cat == "yacht") {
        for (int face = 1; face <= 6; ++face) {
            if (counts[static_cast<std::size_t>(face)] == 5) {
                return 50;
            }
        }
        return 0;
    }

    // Should be unreachable, but return 0 defensively.
    return 0;
}


int score(const std::vector<int>& dice, category cat) {
    switch (cat) {
        case category::ones:            return score(dice, "ones");
        case category::twos:            return score(dice, "twos");
        case category::threes:          return score(dice, "threes");
        case category::fours:           return score(dice, "fours");
        case category::fives:           return score(dice, "fives");
        case category::sixes:           return score(dice, "sixes");
        case category::full_house:      return score(dice, "full house");
        case category::four_of_a_kind:  return score(dice, "four of a kind");
        case category::little_straight: return score(dice, "little straight");
        case category::big_straight:    return score(dice, "big straight");
        case category::choice:          return score(dice, "choice");
        case category::yacht:           return score(dice, "yacht");
    }
    return 0;
}

}  // namespace yacht
