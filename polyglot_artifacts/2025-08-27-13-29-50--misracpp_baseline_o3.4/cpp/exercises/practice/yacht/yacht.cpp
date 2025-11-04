#include "yacht.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <cctype>
#include <optional>
#include <string_view>

namespace yacht {

namespace {

/* Convert a string (or string_view) to lower-case ASCII. */
std::string to_lower(std::string_view in) {
    std::string out;
    out.reserve(in.size());
    for (char ch : in) {
        out.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
    }
    return out;
}

/* Map a case-insensitive string to a Category enum. */
std::optional<Category> category_from_string(std::string_view name) {
    const std::string lower = to_lower(name);
    if (lower == "ones")              return Category::Ones;
    if (lower == "twos")              return Category::Twos;
    if (lower == "threes")            return Category::Threes;
    if (lower == "fours")             return Category::Fours;
    if (lower == "fives")             return Category::Fives;
    if (lower == "sixes")             return Category::Sixes;
    if (lower == "full house")        return Category::FullHouse;
    if (lower == "four of a kind")    return Category::FourOfAKind;
    if (lower == "little straight")   return Category::LittleStraight;
    if (lower == "big straight")      return Category::BigStraight;
    if (lower == "choice")            return Category::Choice;
    if (lower == "yacht")             return Category::Yacht;
    return std::nullopt;
}

}  // namespace

int score(const std::vector<int>& dice, const std::string& category_str) {
    auto cat = category_from_string(category_str);
    return cat ? score(dice, *cat) : 0;
}

int score(const std::vector<int>& dice, Category category) {
    if (dice.size() != 5) {
        return 0;  // Defensive: invalid input size.
    }

    // Frequency of each die face: index 1..6 are used.
    std::array<int, 7> counts{};
    for (int die : dice) {
        if (die < 1 || die > 6) {
            return 0;  // Defensive: invalid die value.
        }
        counts[die]++;
    }

    auto sum = std::accumulate(dice.begin(), dice.end(), 0);

    switch (category) {
        case Category::Ones:   return counts[1] * 1;
        case Category::Twos:   return counts[2] * 2;
        case Category::Threes: return counts[3] * 3;
        case Category::Fours:  return counts[4] * 4;
        case Category::Fives:  return counts[5] * 5;
        case Category::Sixes:  return counts[6] * 6;

        case Category::FullHouse: {
            bool three_of_kind = false;
            bool pair          = false;
            for (int face = 1; face <= 6; ++face) {
                three_of_kind |= counts[face] == 3;
                pair          |= counts[face] == 2;
            }
            return (three_of_kind && pair) ? sum : 0;
        }

        case Category::FourOfAKind: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] >= 4) {
                    return face * 4;
                }
            }
            return 0;
        }

        case Category::LittleStraight:
            return (counts[1] == 1 && counts[2] == 1 && counts[3] == 1 &&
                    counts[4] == 1 && counts[5] == 1 && counts[6] == 0)
                       ? 30
                       : 0;

        case Category::BigStraight:
            return (counts[1] == 0 && counts[2] == 1 && counts[3] == 1 &&
                    counts[4] == 1 && counts[5] == 1 && counts[6] == 1)
                       ? 30
                       : 0;

        case Category::Choice:
            return sum;

        case Category::Yacht:
            return std::any_of(counts.begin(), counts.end(),
                               [](int c) { return c == 5; })
                       ? 50
                       : 0;
    }

    return 0;  // Should be unreachable.
}

}  // namespace yacht
