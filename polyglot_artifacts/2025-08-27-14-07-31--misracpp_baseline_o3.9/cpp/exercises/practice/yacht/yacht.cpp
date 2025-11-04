#include "yacht.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <string_view>
#include <string>
#include <cctype>
#include <initializer_list>

namespace yacht {

int score(const std::array<int, 5>& dice, category cat)
{
    // Frequency of each die face (1..6)
    std::array<int, 7> freq{0};
    for (int d : dice) {
        if (d < 1 || d > 6) {
            return 0; // Defensive: dice values are guaranteed, but be safe.
        }
        ++freq[d];
    }

    const int total = std::accumulate(dice.begin(), dice.end(), 0);

    switch (cat) {
    case category::ones:
    case category::twos:
    case category::threes:
    case category::fours:
    case category::fives:
    case category::sixes: {
        int face = static_cast<int>(cat) + 1; // enum ordered so ones == 0
        return freq[face] * face;
    }
    case category::full_house: {
        bool has_three = false;
        bool has_two   = false;
        for (int face = 1; face <= 6; ++face) {
            if (freq[face] == 3) has_three = true;
            else if (freq[face] == 2) has_two = true;
        }
        return (has_three && has_two) ? total : 0;
    }
    case category::four_of_a_kind: {
        for (int face = 1; face <= 6; ++face) {
            if (freq[face] >= 4) {
                return face * 4;
            }
        }
        return 0;
    }
    case category::little_straight: {
        std::array<int, 5> sorted;
        std::copy(dice.begin(), dice.end(), sorted.begin());
        std::sort(sorted.begin(), sorted.end());
        return (sorted == std::array<int, 5>{1, 2, 3, 4, 5}) ? 30 : 0;
    }
    case category::big_straight: {
        std::array<int, 5> sorted;
        std::copy(dice.begin(), dice.end(), sorted.begin());
        std::sort(sorted.begin(), sorted.end());
        return (sorted == std::array<int, 5>{2, 3, 4, 5, 6}) ? 30 : 0;
    }
    case category::choice:
        return total;
    case category::yacht:
        for (int face = 1; face <= 6; ++face) {
            if (freq[face] == 5) return 50;
        }
        return 0;
    }

    return 0; // Should be unreachable.
}

// Overload accepting a category name as string
int score(const std::array<int, 5>& dice, std::string_view cat_name)
{
    std::string normalized;
    normalized.reserve(cat_name.size());
    for (char c : cat_name) {
        if (c != ' ' && c != '_') {
            normalized.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
        }
    }

    if (normalized == "ones")            return score(dice, category::ones);
    if (normalized == "twos")            return score(dice, category::twos);
    if (normalized == "threes")          return score(dice, category::threes);
    if (normalized == "fours")           return score(dice, category::fours);
    if (normalized == "fives")           return score(dice, category::fives);
    if (normalized == "sixes")           return score(dice, category::sixes);
    if (normalized == "fullhouse")       return score(dice, category::full_house);
    if (normalized == "fourofakind")     return score(dice, category::four_of_a_kind);
    if (normalized == "littlestraight")  return score(dice, category::little_straight);
    if (normalized == "bigstraight")     return score(dice, category::big_straight);
    if (normalized == "choice")          return score(dice, category::choice);
    if (normalized == "yacht")           return score(dice, category::yacht);

    return 0; // Unknown category string
}

// overloads taking initializer_list for test convenience
int score(std::initializer_list<int> dice_list, category cat)
{
    if (dice_list.size() != 5) {
        return 0; // Defensive – tests always pass exactly five dice
    }
    std::array<int, 5> dice;
    std::copy(dice_list.begin(), dice_list.end(), dice.begin());
    return score(dice, cat);
}

int score(std::initializer_list<int> dice_list, std::string_view cat_name)
{
    if (dice_list.size() != 5) {
        return 0;
    }
    std::array<int, 5> dice;
    std::copy(dice_list.begin(), dice_list.end(), dice.begin());
    return score(dice, cat_name);
}

}  // namespace yacht
