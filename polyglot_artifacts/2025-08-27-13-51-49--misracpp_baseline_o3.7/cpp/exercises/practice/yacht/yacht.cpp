#include "yacht.h"

#include <array>
#include <algorithm>
#include <numeric>
#include <string>
#include <cctype>

namespace yacht {

// Helper: count how many times each face appears (index 1..6)
static std::array<int, 7> count_faces(const std::vector<int>& dice) {
    std::array<int, 7> counts{};
    for (int die : dice) {
        if (die >= 1 && die <= 6) {
            ++counts[die];
        }
    }
    return counts;
}

// Helper: convert string category name to enum Category
static Category parse_category(const std::string& cat_str_input) {
    std::string s;
    s.reserve(cat_str_input.size());
    std::transform(cat_str_input.begin(), cat_str_input.end(),
                   std::back_inserter(s),
                   [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

    if (s == "ones") return Category::Ones;
    if (s == "twos") return Category::Twos;
    if (s == "threes") return Category::Threes;
    if (s == "fours") return Category::Fours;
    if (s == "fives") return Category::Fives;
    if (s == "sixes") return Category::Sixes;
    if (s == "full house") return Category::FullHouse;
    if (s == "four of a kind") return Category::FourOfAKind;
    if (s == "little straight") return Category::LittleStraight;
    if (s == "big straight") return Category::BigStraight;
    if (s == "choice") return Category::Choice;
    if (s == "yacht") return Category::Yacht;

    // Default fallback – treat as Choice if unrecognised
    return Category::Choice;
}

int score(const std::vector<int>& dice, Category category) {
    auto counts = count_faces(dice);

    switch (category) {
        case Category::Ones:
        case Category::Twos:
        case Category::Threes:
        case Category::Fours:
        case Category::Fives:
        case Category::Sixes: {
            int face = static_cast<int>(category);  // Ones == 1, …, Sixes == 6
            return face * counts[face];
        }

        case Category::FullHouse: {
            bool three_found = false, two_found = false;
            for (int c : counts) {
                if (c == 3)
                    three_found = true;
                else if (c == 2)
                    two_found = true;
            }
            return (three_found && two_found)
                       ? std::accumulate(dice.begin(), dice.end(), 0)
                       : 0;
        }

        case Category::FourOfAKind: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] >= 4) {
                    return face * 4;
                }
            }
            return 0;
        }

        case Category::LittleStraight: {
            bool ok = counts[1] == 1 && counts[2] == 1 && counts[3] == 1 &&
                      counts[4] == 1 && counts[5] == 1 && counts[6] == 0;
            return ok ? 30 : 0;
        }

        case Category::BigStraight: {
            bool ok = counts[2] == 1 && counts[3] == 1 && counts[4] == 1 &&
                      counts[5] == 1 && counts[6] == 1 && counts[1] == 0;
            return ok ? 30 : 0;
        }

        case Category::Choice:
            return std::accumulate(dice.begin(), dice.end(), 0);

        case Category::Yacht: {
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 5) {
                    return 50;
                }
            }
            return 0;
        }
    }

    // Should be unreachable, but keeps compiler happy
    return 0;
}

// Overload taking string category name and delegating to the enum version
int score(const std::vector<int>& dice, const std::string& category_str) {
    return score(dice, parse_category(category_str));
}


}  // namespace yacht
