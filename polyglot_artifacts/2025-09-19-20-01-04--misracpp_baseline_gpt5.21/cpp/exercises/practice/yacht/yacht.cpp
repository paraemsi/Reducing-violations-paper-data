#include "yacht.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <numeric>
#include <string>

namespace yacht {

namespace {
std::array<int, 7> make_counts(const std::vector<int>& dice) {
    std::array<int, 7> cnt{};  // indices 1..6 used
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            ++cnt[static_cast<std::size_t>(d)];
        }
    }
    return cnt;
}
}  // namespace

int score(const std::vector<int>& dice, category cat) {
    const auto cnt = make_counts(dice);
    const int total = std::accumulate(dice.begin(), dice.end(), 0);

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            // enum values for ones..sixes are 0..5; face is +1
            const int face = static_cast<int>(cat) + 1;
            return face * cnt[static_cast<std::size_t>(face)];
        }

        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (int face = 1; face <= 6; ++face) {
                if (cnt[static_cast<std::size_t>(face)] == 3) has_three = true;
                if (cnt[static_cast<std::size_t>(face)] == 2) has_two = true;
            }
            return (has_three && has_two) ? total : 0;
        }

        case category::four_of_a_kind: {
            for (int face = 1; face <= 6; ++face) {
                if (cnt[static_cast<std::size_t>(face)] >= 4) {
                    return 4 * face;
                }
            }
            return 0;
        }

        case category::little_straight: {
            // 1,2,3,4,5 each exactly once
            for (int face = 1; face <= 5; ++face) {
                if (cnt[static_cast<std::size_t>(face)] != 1) return 0;
            }
            return 30;
        }

        case category::big_straight: {
            // 2,3,4,5,6 each exactly once
            for (int face = 2; face <= 6; ++face) {
                if (cnt[static_cast<std::size_t>(face)] != 1) return 0;
            }
            return 30;
        }

        case category::choice:
            return total;

        case category::yacht:
            for (int face = 1; face <= 6; ++face) {
                if (cnt[static_cast<std::size_t>(face)] == 5) return 50;
            }
            return 0;
    }

    return 0;  // unreachable, but silences warnings
}

int score(const std::vector<int>& dice, const std::string& cat) {
    if (cat == "ones") return score(dice, category::ones);
    if (cat == "twos") return score(dice, category::twos);
    if (cat == "threes") return score(dice, category::threes);
    if (cat == "fours") return score(dice, category::fours);
    if (cat == "fives") return score(dice, category::fives);
    if (cat == "sixes") return score(dice, category::sixes);
    if (cat == "full house") return score(dice, category::full_house);
    if (cat == "four of a kind") return score(dice, category::four_of_a_kind);
    if (cat == "little straight") return score(dice, category::little_straight);
    if (cat == "big straight") return score(dice, category::big_straight);
    if (cat == "choice") return score(dice, category::choice);
    if (cat == "yacht") return score(dice, category::yacht);
    return 0;
}

int score(const std::vector<int>& dice, const char* cat) {
    if (cat == nullptr) return 0;
    return score(dice, std::string{cat});
}

}  // namespace yacht
