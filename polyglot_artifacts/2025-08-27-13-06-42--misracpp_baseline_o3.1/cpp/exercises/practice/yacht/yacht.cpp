#include "yacht.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <string>

namespace yacht {

namespace {

// Helper: frequency table for dice values 1‒6
std::array<int, 7> counts(const std::vector<int>& dice)
{
    std::array<int, 7> freq{0, 0, 0, 0, 0, 0, 0};
    for (int d : dice) {
        if (d >= 1 && d <= 6) {
            ++freq[d];
        }
    }
    return freq;
}

} // namespace

int score(const std::vector<int>& dice, category cat)
{
    const auto freq = counts(dice);
    const int total = std::accumulate(dice.begin(), dice.end(), 0);

    switch (cat) {
    // Singles ---------------------------------------------------------------
    case category::ones:   return freq[1] * 1;
    case category::twos:   return freq[2] * 2;
    case category::threes: return freq[3] * 3;
    case category::fours:  return freq[4] * 4;
    case category::fives:  return freq[5] * 5;
    case category::sixes:  return freq[6] * 6;

    // Choice ----------------------------------------------------------------
    case category::choice:
        return total;

    // Yacht -----------------------------------------------------------------
    case category::yacht:
        return *std::max_element(freq.begin() + 1, freq.end()) == 5 ? 50 : 0;

    // Four of a kind --------------------------------------------------------
    case category::four_of_a_kind: {
        for (int value = 1; value <= 6; ++value) {
            if (freq[value] >= 4) {
                return value * 4;
            }
        }
        return 0;
    }

    // Full house ------------------------------------------------------------
    case category::full_house: {
        bool has_three = false;
        bool has_two   = false;
        for (int value = 1; value <= 6; ++value) {
            if (freq[value] == 3)
                has_three = true;
            else if (freq[value] == 2)
                has_two = true;
        }
        return (has_three && has_two) ? total : 0;
    }

    // Straights -------------------------------------------------------------
    case category::little_straight:
        return (freq[1] == 1 && freq[2] == 1 && freq[3] == 1 &&
                freq[4] == 1 && freq[5] == 1 && freq[6] == 0)
                   ? 30
                   : 0;

    case category::big_straight:
        return (freq[1] == 0 && freq[2] == 1 && freq[3] == 1 &&
                freq[4] == 1 && freq[5] == 1 && freq[6] == 1)
                   ? 30
                   : 0;
    }

    // Should never be reached, but silence compiler warnings
    return 0;
}

int score(const std::vector<int>& dice, const std::string& cat_str)
{
    if (cat_str == "ones")             return score(dice, category::ones);
    if (cat_str == "twos")             return score(dice, category::twos);
    if (cat_str == "threes")           return score(dice, category::threes);
    if (cat_str == "fours")            return score(dice, category::fours);
    if (cat_str == "fives")            return score(dice, category::fives);
    if (cat_str == "sixes")            return score(dice, category::sixes);
    if (cat_str == "full house")       return score(dice, category::full_house);
    if (cat_str == "four of a kind")   return score(dice, category::four_of_a_kind);
    if (cat_str == "little straight")  return score(dice, category::little_straight);
    if (cat_str == "big straight")     return score(dice, category::big_straight);
    if (cat_str == "choice")           return score(dice, category::choice);
    if (cat_str == "yacht")            return score(dice, category::yacht);
    return 0; // Unknown category string
}

}  // namespace yacht
