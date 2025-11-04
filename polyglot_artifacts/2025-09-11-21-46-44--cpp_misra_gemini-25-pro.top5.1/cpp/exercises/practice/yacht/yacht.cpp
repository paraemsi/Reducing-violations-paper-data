#include "yacht.h"

#include <cassert>
#include <map>
#include <numeric>
#include <string>

namespace yacht {

std::int32_t score(const std::array<std::int32_t, 5> &dice, category cat) {
    std::map<std::int32_t, std::int32_t> counts;
    for (std::int32_t d : dice) {
        counts[d]++;
    }

    switch (cat) {
    case category::yacht: {
        for (const auto &p : counts) {
            if (p.second == std::int32_t{5}) {
                return std::int32_t{50};
            }
        }
        return std::int32_t{0};
    }
    case category::ones: {
        return (counts.count(std::int32_t{1}) != 0U) ? counts.at(std::int32_t{1}) : std::int32_t{0};
    }
    case category::twos: {
        return (counts.count(std::int32_t{2}) != 0U) ? (counts.at(std::int32_t{2}) * std::int32_t{2}) : std::int32_t{0};
    }
    case category::threes: {
        return (counts.count(std::int32_t{3}) != 0U) ? (counts.at(std::int32_t{3}) * std::int32_t{3}) : std::int32_t{0};
    }
    case category::fours: {
        return (counts.count(std::int32_t{4}) != 0U) ? (counts.at(std::int32_t{4}) * std::int32_t{4}) : std::int32_t{0};
    }
    case category::fives: {
        return (counts.count(std::int32_t{5}) != 0U) ? (counts.at(std::int32_t{5}) * std::int32_t{5}) : std::int32_t{0};
    }
    case category::sixes: {
        return (counts.count(std::int32_t{6}) != 0U) ? (counts.at(std::int32_t{6}) * std::int32_t{6}) : std::int32_t{0};
    }
    case category::full_house: {
        bool has_three{false};
        bool has_two{false};
        for (const auto &p : counts) {
            if (p.second == std::int32_t{3}) {
                has_three = true;
            } else if (p.second == std::int32_t{2}) {
                has_two = true;
            }
        }
        if ((has_three) && (has_two)) {
            return std::accumulate(dice.cbegin(), dice.cend(),
                                     std::int32_t{0});
        } else {
            return std::int32_t{0};
        }
    }
    case category::four_of_a_kind: {
        for (const auto &p : counts) {
            if (p.second >= std::int32_t{4}) {
                return (p.first * std::int32_t{4});
            }
        }
        return std::int32_t{0};
    }
    case category::little_straight: {
        if ((counts.size() == 5U) && (counts.count(std::int32_t{6}) == 0U)) {
            return std::int32_t{30};
        } else {
            return std::int32_t{0};
        }
    }
    case category::big_straight: {
        if ((counts.size() == 5U) && (counts.count(std::int32_t{1}) == 0U)) {
            return std::int32_t{30};
        } else {
            return std::int32_t{0};
        }
    }
    case category::choice: {
        return std::accumulate(dice.cbegin(), dice.cend(), std::int32_t{0});
    }
    default:
        assert(false);
        return std::int32_t{0};
    }
}

std::int32_t score(const std::array<std::int32_t, 5> &dice,
                   const std::string &cat_name) {
    static const std::map<std::string, category> cat_map = {
        {"yacht", category::yacht},
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
        {"choice", category::choice}};

    auto it = cat_map.find(cat_name);
    if (it != cat_map.cend()) {
        return score(dice, it->second);
    } else {
        assert(false);
        return std::int32_t{0};
    }
}

} // namespace yacht
