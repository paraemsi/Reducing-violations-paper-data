#include "yacht.h"

#include <array>
#include <numeric>
#include <string>
#include <string_view>
#include <algorithm>
#include <cctype>

namespace yacht {

static constexpr Category InvalidCategory =
    static_cast<Category>(0);  // enum values start at 1, so 0 is safe sentinel

static Category parse_category(std::string_view input) {
    std::string s{input};
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
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
    return InvalidCategory;                // invalid
}

int score(const std::vector<int>& dice, std::string_view category) {
    Category cat = parse_category(category);
    if (cat == InvalidCategory) {
        return 0;                          // unknown category string
    }
    return score(dice, cat);               // delegate to enum overload
}

int score(const std::vector<int>& dice, Category category) {
    // Validate input and count occurrences of each face (index 1–6)
    if (dice.size() != 5) {
        return 0;                         // invalid number of dice – no score
    }
    std::array<int, 7> counts{};          // zero-initialised
    for (int die : dice) {
        if (die < 1 || die > 6) {
            return 0;                     // invalid die value – no score
        }
        ++counts[die];
    }

    const int total = std::accumulate(dice.begin(), dice.end(), 0);

    // Simple face categories (Ones … Sixes)
    {
        const int cat_val = static_cast<int>(category);
        if (cat_val >= static_cast<int>(Category::Ones) &&
            cat_val <= static_cast<int>(Category::Sixes)) {
            return counts[cat_val] * cat_val;
        }
    }

    switch (category) {
        case Category::FullHouse: {
            bool has_three = false, has_two = false;
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 3) has_three = true;
                if (counts[face] == 2) has_two = true;
            }
            return (has_three && has_two) ? total : 0;
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
            return total;

        case Category::Yacht:
            for (int face = 1; face <= 6; ++face) {
                if (counts[face] == 5) {
                    return 50;
                }
            }
            return 0;

        default:
            return 0;  // Should never be reached
    }
}

}  // namespace yacht
