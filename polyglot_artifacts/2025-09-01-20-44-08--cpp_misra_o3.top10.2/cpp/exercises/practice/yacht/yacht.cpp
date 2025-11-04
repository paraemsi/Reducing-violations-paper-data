#include "yacht.h"

#include <algorithm>
#include <numeric>
#include <string_view>

namespace yacht {

namespace {

/* Return a frequency table where the index represents the die face (1–6). */
auto counts(const std::array<std::uint8_t, 5U>& dice) -> std::array<std::uint8_t, 7U>
{
    std::array<std::uint8_t, 7U> cnt{}; /* All elements zero-initialised */
    for (std::uint8_t die : dice) {
        if ((die >= static_cast<std::uint8_t>(1U)) && (die <= static_cast<std::uint8_t>(6U))) {
            ++cnt[die];
        }
    }
    return cnt;
}

auto sum(const std::array<std::uint8_t, 5U>& dice) -> std::uint32_t
{
    return std::accumulate(dice.cbegin(), dice.cend(), static_cast<std::uint32_t>(0U));
}

} /* unnamed namespace */

auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint32_t
{
    const std::array<std::uint8_t, 7U> cnt = counts(dice);

    switch (cat) {
    case category::ones:
    case category::twos:
    case category::threes:
    case category::fours:
    case category::fives:
    case category::sixes: {
        const std::uint8_t face =
            static_cast<std::uint8_t>(static_cast<std::uint8_t>(cat) + static_cast<std::uint8_t>(1U));
        return static_cast<std::uint32_t>(face) * static_cast<std::uint32_t>(cnt[face]);
    }
    case category::full_house: {
        bool has_three{false};
        bool has_two{false};
        std::uint32_t total{0U};
        for (std::uint8_t value = static_cast<std::uint8_t>(1U); value <= static_cast<std::uint8_t>(6U); ++value) {
            if (cnt[value] == static_cast<std::uint8_t>(3U)) { has_three = true; }
            if (cnt[value] == static_cast<std::uint8_t>(2U)) { has_two = true; }
            total += static_cast<std::uint32_t>(value) * static_cast<std::uint32_t>(cnt[value]);
        }
        if (has_three && has_two) {
            return total;
        }
        return static_cast<std::uint32_t>(0U);
    }
    case category::four_of_a_kind: {
        for (std::uint8_t value = static_cast<std::uint8_t>(1U); value <= static_cast<std::uint8_t>(6U); ++value) {
            if (cnt[value] >= static_cast<std::uint8_t>(4U)) {
                return static_cast<std::uint32_t>(value) * static_cast<std::uint32_t>(4U);
            }
        }
        return static_cast<std::uint32_t>(0U);
    }
    case category::little_straight: {
        if ((cnt[1U] == static_cast<std::uint8_t>(1U)) && (cnt[2U] == static_cast<std::uint8_t>(1U)) &&
            (cnt[3U] == static_cast<std::uint8_t>(1U)) && (cnt[4U] == static_cast<std::uint8_t>(1U)) &&
            (cnt[5U] == static_cast<std::uint8_t>(1U))) {
            return static_cast<std::uint32_t>(30U);
        }
        return static_cast<std::uint32_t>(0U);
    }
    case category::big_straight: {
        if ((cnt[2U] == static_cast<std::uint8_t>(1U)) && (cnt[3U] == static_cast<std::uint8_t>(1U)) &&
            (cnt[4U] == static_cast<std::uint8_t>(1U)) && (cnt[5U] == static_cast<std::uint8_t>(1U)) &&
            (cnt[6U] == static_cast<std::uint8_t>(1U))) {
            return static_cast<std::uint32_t>(30U);
        }
        return static_cast<std::uint32_t>(0U);
    }
    case category::choice: {
        return sum(dice);
    }
    case category::yacht: {
        for (std::uint8_t value = static_cast<std::uint8_t>(1U); value <= static_cast<std::uint8_t>(6U); ++value) {
            if (cnt[value] == static_cast<std::uint8_t>(5U)) {
                return static_cast<std::uint32_t>(50U);
            }
        }
        return static_cast<std::uint32_t>(0U);
    }
    default:
        return static_cast<std::uint32_t>(0U);
    }
}

auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view cat) -> std::uint32_t
{
    if (cat == "ones") {
        return score(dice, category::ones);
    } else if (cat == "twos") {
        return score(dice, category::twos);
    } else if (cat == "threes") {
        return score(dice, category::threes);
    } else if (cat == "fours") {
        return score(dice, category::fours);
    } else if (cat == "fives") {
        return score(dice, category::fives);
    } else if (cat == "sixes") {
        return score(dice, category::sixes);
    } else if (cat == "full house") {
        return score(dice, category::full_house);
    } else if (cat == "four of a kind") {
        return score(dice, category::four_of_a_kind);
    } else if (cat == "little straight") {
        return score(dice, category::little_straight);
    } else if (cat == "big straight") {
        return score(dice, category::big_straight);
    } else if (cat == "choice") {
        return score(dice, category::choice);
    } else if (cat == "yacht") {
        return score(dice, category::yacht);
    }
    return static_cast<std::uint32_t>(0U);
}

auto score(const std::array<int, 5U>& dice, category cat) -> std::uint32_t
{
    std::array<std::uint8_t, 5U> conv{};
    for (std::size_t idx = 0U; idx < 5U; ++idx) {
        conv[idx] = static_cast<std::uint8_t>(dice[idx]);
    }
    return score(conv, cat);
}

auto score(const std::array<int, 5U>& dice, std::string_view cat) -> std::uint32_t
{
    std::array<std::uint8_t, 5U> conv{};
    for (std::size_t idx = 0U; idx < 5U; ++idx) {
        conv[idx] = static_cast<std::uint8_t>(dice[idx]);
    }
    return score(conv, cat);
}

} /* namespace yacht */
