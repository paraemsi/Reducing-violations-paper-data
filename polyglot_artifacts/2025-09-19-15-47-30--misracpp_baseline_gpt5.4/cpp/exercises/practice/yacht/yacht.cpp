#include "yacht.h"

#include <array>
#include <numeric>
#include <string>

namespace yacht {

namespace {
std::array<int, 7> make_counts(std::vector<int> const& dice) {
    std::array<int, 7> freq{};  // indices 1..6 used
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            ++freq[d];
        }
    }
    return freq;
}
category parse_category(std::string const& name) {
    if (name == "ones") return category::ones;
    if (name == "twos") return category::twos;
    if (name == "threes") return category::threes;
    if (name == "fours") return category::fours;
    if (name == "fives") return category::fives;
    if (name == "sixes") return category::sixes;
    if (name == "full house") return category::full_house;
    if (name == "four of a kind") return category::four_of_a_kind;
    if (name == "little straight") return category::little_straight;
    if (name == "big straight") return category::big_straight;
    if (name == "choice") return category::choice;
    if (name == "yacht") return category::yacht;
    return category::choice;
}
}  // namespace

int score(std::vector<int> const& dice, std::string const& cat_name) {
    category cat = parse_category(cat_name);
    const auto freq = make_counts(dice);
    const int sum = std::accumulate(dice.begin(), dice.end(), 0);

    switch (cat) {
        case category::ones:   return 1 * freq[1];
        case category::twos:   return 2 * freq[2];
        case category::threes: return 3 * freq[3];
        case category::fours:  return 4 * freq[4];
        case category::fives:  return 5 * freq[5];
        case category::sixes:  return 6 * freq[6];

        case category::choice:
            return sum;

        case category::yacht: {
            for (int p = 1; p <= 6; ++p) {
                if (freq[p] == 5) return 50;
            }
            return 0;
        }

        case category::four_of_a_kind: {
            for (int p = 1; p <= 6; ++p) {
                if (freq[p] >= 4) return 4 * p;
            }
            return 0;
        }

        case category::full_house: {
            bool has3 = false, has2 = false;
            int distinct = 0;
            for (int p = 1; p <= 6; ++p) {
                if (freq[p] > 0) {
                    ++distinct;
                    if (freq[p] == 3) has3 = true;
                    else if (freq[p] == 2) has2 = true;
                }
            }
            return (distinct == 2 && has3 && has2) ? sum : 0;
        }

        case category::little_straight: {
            for (int p = 1; p <= 5; ++p) {
                if (freq[p] != 1) return 0;
            }
            return freq[6] == 0 ? 30 : 0;
        }

        case category::big_straight: {
            for (int p = 2; p <= 6; ++p) {
                if (freq[p] != 1) return 0;
            }
            return freq[1] == 0 ? 30 : 0;
        }
    }

    return 0;  // Unreachable, but keeps some compilers happy.
}

int score(const std::vector<int>& dice, const char* cat_name) {
    return score(dice, std::string{cat_name ? cat_name : ""});
}

}  // namespace yacht
