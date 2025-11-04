#include "yacht.h"

#include <array>
#include <numeric>
#include <string_view>

namespace yacht {

int score(const std::vector<int>& dice, category cat) {
    // Frequency count for dice faces 1-6 (index 0 unused)
    std::array<int, 7> freq{};  
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            ++freq[d];
        }
    }

    const int sum = std::accumulate(dice.begin(), dice.end(), 0);

    switch (cat) {
        case category::ones:   return freq[1] * 1;
        case category::twos:   return freq[2] * 2;
        case category::threes: return freq[3] * 3;
        case category::fours:  return freq[4] * 4;
        case category::fives:  return freq[5] * 5;
        case category::sixes:  return freq[6] * 6;

        case category::full_house: {
            bool has_three = false, has_two = false;
            for (int f = 1; f <= 6; ++f) {
                if (freq[f] == 3) has_three = true;
                if (freq[f] == 2) has_two  = true;
            }
            return (has_three && has_two) ? sum : 0;
        }

        case category::four_of_a_kind: {
            for (int f = 1; f <= 6; ++f) {
                if (freq[f] >= 4) {
                    return f * 4;
                }
            }
            return 0;
        }

        case category::little_straight:
            return (freq[1] == 1 && freq[2] == 1 && freq[3] == 1 &&
                    freq[4] == 1 && freq[5] == 1) ? 30 : 0;

        case category::big_straight:
            return (freq[2] == 1 && freq[3] == 1 && freq[4] == 1 &&
                    freq[5] == 1 && freq[6] == 1) ? 30 : 0;

        case category::choice:
            return sum;

        case category::yacht:
            for (int f = 1; f <= 6; ++f) {
                if (freq[f] == 5) {
                    return 50;
                }
            }
            return 0;
    }

    return 0; // Should never reach here
}

int score(const std::vector<int>& dice, std::string_view cat) {
    using namespace std::literals;
    if (cat == "ones"sv)                return score(dice, category::ones);
    else if (cat == "twos"sv)           return score(dice, category::twos);
    else if (cat == "threes"sv)         return score(dice, category::threes);
    else if (cat == "fours"sv)          return score(dice, category::fours);
    else if (cat == "fives"sv)          return score(dice, category::fives);
    else if (cat == "sixes"sv)          return score(dice, category::sixes);
    else if (cat == "full house"sv)     return score(dice, category::full_house);
    else if (cat == "four of a kind"sv) return score(dice, category::four_of_a_kind);
    else if (cat == "little straight"sv)return score(dice, category::little_straight);
    else if (cat == "big straight"sv)   return score(dice, category::big_straight);
    else if (cat == "choice"sv)         return score(dice, category::choice);
    else if (cat == "yacht"sv)          return score(dice, category::yacht);
    return 0;
}

}  // namespace yacht
