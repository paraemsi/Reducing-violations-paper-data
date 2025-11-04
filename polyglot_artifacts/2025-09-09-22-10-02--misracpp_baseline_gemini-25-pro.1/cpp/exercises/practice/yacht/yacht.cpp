#include "yacht.h"

#include <algorithm>
#include <array>
#include <utility>
#include <numeric>
#include <string_view>

namespace yacht {

namespace {

enum class category {
    Ones,
    Twos,
    Threes,
    Fours,
    Fives,
    Sixes,
    FullHouse,
    FourOfAKind,
    LittleStraight,
    BigStraight,
    Choice,
    Yacht
};

constexpr int score_impl(const std::array<int, 5>& dice, category c) {
    std::array<int, 7> counts{};
    for (int die : dice) {
        counts[die]++;
    }

    switch (c) {
    case category::Ones:
        return counts[1] * 1;
    case category::Twos:
        return counts[2] * 2;
    case category::Threes:
        return counts[3] * 3;
    case category::Fours:
        return counts[4] * 4;
    case category::Fives:
        return counts[5] * 5;
    case category::Sixes:
        return counts[6] * 6;
    case category::FullHouse: {
        bool has_three = false;
        bool has_two = false;
        for (int count : counts) {
            if (count == 3)
                has_three = true;
            if (count == 2)
                has_two = true;
        }
        if (has_three && has_two) {
            return std::accumulate(dice.begin(), dice.end(), 0);
        }
        return 0;
    }
    case category::FourOfAKind: {
        for (int i = 1; i <= 6; ++i) {
            if (counts[i] >= 4) {
                return i * 4;
            }
        }
        return 0;
    }
    case category::LittleStraight: {
        auto sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        const std::array<int, 5> expected = {1, 2, 3, 4, 5};
        if (sorted_dice == expected) {
            return 30;
        }
        return 0;
    }
    case category::BigStraight: {
        auto sorted_dice = dice;
        std::sort(sorted_dice.begin(), sorted_dice.end());
        const std::array<int, 5> expected = {2, 3, 4, 5, 6};
        if (sorted_dice == expected) {
            return 30;
        }
        return 0;
    }
    case category::Choice:
        return std::accumulate(dice.begin(), dice.end(), 0);
    case category::Yacht: {
        for (int count : counts) {
            if (count == 5) {
                return 50;
            }
        }
        return 0;
    }
    }

    return 0;
}

}  // namespace

constexpr int score(const std::array<int, 5>& dice, std::string_view category) {
    using cat_pair = std::pair<std::string_view, category>;
    static constexpr std::array<cat_pair, 12> category_map{{
        {"yacht", category::Yacht},
        {"ones", category::Ones},
        {"twos", category::Twos},
        {"threes", category::Threes},
        {"fours", category::Fours},
        {"fives", category::Fives},
        {"sixes", category::Sixes},
        {"full house", category::FullHouse},
        {"four of a kind", category::FourOfAKind},
        {"little straight", category::LittleStraight},
        {"big straight", category::BigStraight},
        {"choice", category::Choice},
    }};

    auto it = std::find_if(category_map.begin(), category_map.end(),
        [&category](const auto& p) { return p.first == category; });

    if (it != category_map.end()) {
        return score_impl(dice, it->second);
    }

    return 0;
}

}  // namespace yacht
