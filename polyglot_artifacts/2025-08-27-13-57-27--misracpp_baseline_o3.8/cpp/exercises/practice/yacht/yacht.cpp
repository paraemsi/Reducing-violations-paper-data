#include "yacht.h"

#include <array>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <stdexcept>

namespace yacht {

int score(category c, const std::vector<int>& dice) {
    // frequency table where index == face value (1‥6)
    std::array<int, 7> freq{};              // freq[0] unused
    for (int d : dice) {
        ++freq[d];
    }

    switch (c) {
        case category::ones:   return freq[1] * 1;
        case category::twos:   return freq[2] * 2;
        case category::threes: return freq[3] * 3;
        case category::fours:  return freq[4] * 4;
        case category::fives:  return freq[5] * 5;
        case category::sixes:  return freq[6] * 6;

        case category::full_house: {
            bool has_three = false, has_two = false;
            int total = 0;
            for (int face = 1; face <= 6; ++face) {
                if (freq[face] == 3) has_three = true;
                else if (freq[face] == 2) has_two = true;
                total += face * freq[face];
            }
            return (has_three && has_two) ? total : 0;
        }

        case category::four_of_a_kind:
            for (int face = 1; face <= 6; ++face) {
                if (freq[face] >= 4) return face * 4;
            }
            return 0;

        case category::little_straight:
            return std::all_of(freq.begin() + 1, freq.begin() + 6,
                               [](int c) { return c == 1; })
                   && freq[6] == 0 ? 30 : 0;

        case category::big_straight:
            return freq[1] == 0 &&
                   std::all_of(freq.begin() + 2, freq.begin() + 7,
                               [](int c) { return c == 1; })
                   ? 30
                   : 0;

        case category::choice: {
            int sum = 0;
            for (int face = 1; face <= 6; ++face) {
                sum += face * freq[face];
            }
            return sum;
        }

        case category::yacht:
            for (int face = 1; face <= 6; ++face) {
                if (freq[face] == 5) return 50;
            }
            return 0;
    }
    return 0;  // should be unreachable
}

int score(const std::vector<int>& dice, const std::string& cat) {
    static const std::unordered_map<std::string, category> lookup{
        {"ones", category::ones},
        {"twos", category::twos},
        {"threes", category::threes},
        {"fours", category::fours},
        {"fives", category::fives},
        {"sixes", category::sixes},
        {"full house", category::full_house},
        {"four of a kind", category::four_of_a_kind},
        {"little straight", category::little_straight},
        {"big straight", category::big_straight},
        {"choice", category::choice},
        {"yacht", category::yacht},
    };

    auto it = lookup.find(cat);
    if (it == lookup.end()) {
        throw std::invalid_argument("unknown category");
    }
    return score(it->second, dice);
}

}  // namespace yacht
