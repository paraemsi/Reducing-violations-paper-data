#include "yacht.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace yacht {

namespace {
constexpr die_value_t die_min = static_cast<die_value_t>(1);
constexpr die_value_t die_max = static_cast<die_value_t>(6);
constexpr score_t yacht_points = static_cast<score_t>(50);
constexpr score_t straight_points = static_cast<score_t>(30);
}  // namespace

[[nodiscard]] auto score(dice_roll const& dice, category cat) noexcept -> score_t
{
    // Count occurrences for faces 1..6 at indices 1..6
    std::array<std::uint8_t, 7U> counts{};
    for (die_value_t d : dice) {
        if ((d >= die_min) && (d <= die_max)) {
            counts[static_cast<std::size_t>(d)] =
                static_cast<std::uint8_t>(counts[static_cast<std::size_t>(d)] + static_cast<std::uint8_t>(1U));
        }
    }

    // Precompute sum of dice as score_t
    score_t sum = static_cast<score_t>(0);
    for (die_value_t d : dice) {
        sum = static_cast<score_t>(sum + static_cast<score_t>(d));
    }

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            // face index: ones=1 ... sixes=6
            std::size_t face_index =
                static_cast<std::size_t>(static_cast<std::uint8_t>(cat)) + static_cast<std::size_t>(1U);
            score_t face = static_cast<score_t>(face_index);
            score_t cnt = static_cast<score_t>(counts[face_index]);
            return static_cast<score_t>(cnt * face);
        }
        case category::full_house: {
            bool has_three = (false);
            bool has_two = (false);
            for (std::size_t f = static_cast<std::size_t>(1U);
                 f <= static_cast<std::size_t>(6U);
                 f = static_cast<std::size_t>(f + static_cast<std::size_t>(1U))) {
                if (counts[f] == static_cast<std::uint8_t>(3U)) {
                    has_three = (true);
                }
                if (counts[f] == static_cast<std::uint8_t>(2U)) {
                    has_two = (true);
                }
            }
            if ((has_three) && (has_two)) {
                return sum;
            } else {
                return static_cast<score_t>(0);
            }
        }
        case category::four_of_a_kind: {
            for (std::size_t f = static_cast<std::size_t>(1U);
                 f <= static_cast<std::size_t>(6U);
                 f = static_cast<std::size_t>(f + static_cast<std::size_t>(1U))) {
                if ((counts[f] >= static_cast<std::uint8_t>(4U))) {
                    score_t face = static_cast<score_t>(f);
                    return static_cast<score_t>(face * static_cast<score_t>(4));
                }
            }
            return static_cast<score_t>(0);
        }
        case category::little_straight: {
            bool ok = (true);
            for (std::size_t f = static_cast<std::size_t>(1U);
                 f <= static_cast<std::size_t>(5U);
                 f = static_cast<std::size_t>(f + static_cast<std::size_t>(1U))) {
                if (!(counts[f] == static_cast<std::uint8_t>(1U))) {
                    ok = (false);
                }
            }
            if (!(counts[static_cast<std::size_t>(6U)] == static_cast<std::uint8_t>(0U))) {
                ok = (false);
            }
            if (ok) {
                return straight_points;
            } else {
                return static_cast<score_t>(0);
            }
        }
        case category::big_straight: {
            bool ok = (true);
            for (std::size_t f = static_cast<std::size_t>(2U);
                 f <= static_cast<std::size_t>(6U);
                 f = static_cast<std::size_t>(f + static_cast<std::size_t>(1U))) {
                if (!(counts[f] == static_cast<std::uint8_t>(1U))) {
                    ok = (false);
                }
            }
            if (!(counts[static_cast<std::size_t>(1U)] == static_cast<std::uint8_t>(0U))) {
                ok = (false);
            }
            if (ok) {
                return straight_points;
            } else {
                return static_cast<score_t>(0);
            }
        }
        case category::choice: {
            return sum;
        }
        case category::yacht: {
            for (std::size_t f = static_cast<std::size_t>(1U);
                 f <= static_cast<std::size_t>(6U);
                 f = static_cast<std::size_t>(f + static_cast<std::size_t>(1U))) {
                if (counts[f] == static_cast<std::uint8_t>(5U)) {
                    return yacht_points;
                }
            }
            return static_cast<score_t>(0);
        }
        default: {
            return static_cast<score_t>(0);
        }
    }
}

[[nodiscard]] auto score(dice_roll const& dice, char const* cat) noexcept -> score_t
{
    if (cat == nullptr) {
        return static_cast<score_t>(0);
    }

    category mapped = category::choice;
    bool recognized = (true);

    if ((std::strcmp(cat, "ones") == 0)) {
        mapped = category::ones;
    } else if ((std::strcmp(cat, "twos") == 0)) {
        mapped = category::twos;
    } else if ((std::strcmp(cat, "threes") == 0)) {
        mapped = category::threes;
    } else if ((std::strcmp(cat, "fours") == 0)) {
        mapped = category::fours;
    } else if ((std::strcmp(cat, "fives") == 0)) {
        mapped = category::fives;
    } else if ((std::strcmp(cat, "sixes") == 0)) {
        mapped = category::sixes;
    } else if ((std::strcmp(cat, "full house") == 0)) {
        mapped = category::full_house;
    } else if ((std::strcmp(cat, "four of a kind") == 0)) {
        mapped = category::four_of_a_kind;
    } else if ((std::strcmp(cat, "little straight") == 0)) {
        mapped = category::little_straight;
    } else if ((std::strcmp(cat, "big straight") == 0)) {
        mapped = category::big_straight;
    } else if ((std::strcmp(cat, "choice") == 0)) {
        mapped = category::choice;
    } else if ((std::strcmp(cat, "yacht") == 0)) {
        mapped = category::yacht;
    } else {
        recognized = (false);
    }

    if (recognized) {
        return score(dice, mapped);
    } else {
        return static_cast<score_t>(0);
    }
}

}  // namespace yacht
