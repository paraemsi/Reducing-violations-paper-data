#include "yacht.h"
#include <algorithm>
#include <array>
#include <numeric>
#include <string>
#include <stdexcept>

namespace yacht {

int score(const std::vector<int>& dice, const std::string& cat) {
    std::array<int, 6> counts{};
    for (int die : dice) {
        ++counts[die - 1];
    }

    auto sum_all = [&dice]() {
        return std::accumulate(dice.begin(), dice.end(), 0);
    };

    // convert category string to enum
    category cat_enum;
    if      (cat == "ones")            cat_enum = category::ones;
    else if (cat == "twos")            cat_enum = category::twos;
    else if (cat == "threes")          cat_enum = category::threes;
    else if (cat == "fours")           cat_enum = category::fours;
    else if (cat == "fives")           cat_enum = category::fives;
    else if (cat == "sixes")           cat_enum = category::sixes;
    else if (cat == "full house")      cat_enum = category::full_house;
    else if (cat == "four of a kind")  cat_enum = category::four_of_a_kind;
    else if (cat == "little straight") cat_enum = category::little_straight;
    else if (cat == "big straight")    cat_enum = category::big_straight;
    else if (cat == "choice")          cat_enum = category::choice;
    else if (cat == "yacht")           cat_enum = category::yacht;
    else
        throw std::invalid_argument("Unknown category");

    switch (cat_enum) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            int value = static_cast<int>(cat_enum); // enum values: ones=1, twos=2, ...
            return value * counts[value - 1];
        }

        case category::full_house: {
            bool has_three = std::find(counts.begin(), counts.end(), 3) != counts.end();
            bool has_two   = std::find(counts.begin(), counts.end(), 2) != counts.end();
            return (has_three && has_two) ? sum_all() : 0;
        }

        case category::four_of_a_kind: {
            for (size_t i = 0; i < counts.size(); ++i) {
                if (counts[i] >= 4) {
                    return static_cast<int>(4 * (i + 1));
                }
            }
            return 0;
        }

        case category::little_straight:
            return (counts[0]==1 && counts[1]==1 && counts[2]==1 && counts[3]==1 && counts[4]==1 && counts[5]==0) ? 30 : 0;

        case category::big_straight:
            return (counts[0]==0 && counts[1]==1 && counts[2]==1 && counts[3]==1 && counts[4]==1 && counts[5]==1) ? 30 : 0;

        case category::choice:
            return sum_all();

        case category::yacht:
            return (std::find(counts.begin(), counts.end(), 5) != counts.end()) ? 50 : 0;
    }
    return 0;
}

}  // namespace yacht
