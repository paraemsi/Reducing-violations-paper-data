#include "yacht.h"

#include <array>
#include <cstdint>
#include <type_traits>
#include <string_view>

namespace yacht {

auto score(const std::array<std::uint8_t, 5U>& dice,
           category cat) noexcept -> score_t
{
    // Count occurrences of each face value (1-6)
    std::array<std::uint8_t, 7U> counts{};  // index 0 unused
    for (const auto value : dice) {
        ++counts[static_cast<std::size_t>(value)];
    }

    // Total of all dice (CHOICE or FULL HOUSE score)
    auto sum_all = static_cast<score_t>(0U);
    for (const auto value : dice) {
        sum_all += static_cast<score_t>(value);
    }

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes:
        {
            const auto face = static_cast<std::uint8_t>(
                static_cast<std::underlying_type_t<category>>(cat) +
                static_cast<std::underlying_type_t<category>>(1U));
            return static_cast<score_t>(counts[face]) * static_cast<score_t>(face);
        }

        case category::choice:
        {
            return sum_all;
        }

        case category::full_house:
        {
            bool has_three = false;
            bool has_two = false;

            for (std::uint8_t face = static_cast<std::uint8_t>(1U);
                 face <= static_cast<std::uint8_t>(6U);
                 ++face) {
                if (counts[face] == static_cast<std::uint8_t>(3U)) {
                    has_three = true;
                } else if (counts[face] == static_cast<std::uint8_t>(2U)) {
                    has_two = true;
                }
            }

            if (has_three && has_two) {
                return sum_all;
            }
            return 0U;
        }

        case category::four_of_a_kind:
        {
            for (std::uint8_t face = static_cast<std::uint8_t>(1U);
                 face <= static_cast<std::uint8_t>(6U);
                 ++face) {
                if (counts[face] >= static_cast<std::uint8_t>(4U)) {
                    return static_cast<score_t>(face) * static_cast<score_t>(4U);
                }
            }
            return 0U;
        }

        case category::little_straight:
        {
            if ((counts[1U] == static_cast<std::uint8_t>(1U)) &&
                (counts[2U] == static_cast<std::uint8_t>(1U)) &&
                (counts[3U] == static_cast<std::uint8_t>(1U)) &&
                (counts[4U] == static_cast<std::uint8_t>(1U)) &&
                (counts[5U] == static_cast<std::uint8_t>(1U))) {
                return 30U;
            }
            return 0U;
        }

        case category::big_straight:
        {
            if ((counts[2U] == static_cast<std::uint8_t>(1U)) &&
                (counts[3U] == static_cast<std::uint8_t>(1U)) &&
                (counts[4U] == static_cast<std::uint8_t>(1U)) &&
                (counts[5U] == static_cast<std::uint8_t>(1U)) &&
                (counts[6U] == static_cast<std::uint8_t>(1U))) {
                return 30U;
            }
            return 0U;
        }

        case category::yacht:
        {
            for (std::uint8_t face = static_cast<std::uint8_t>(1U);
                 face <= static_cast<std::uint8_t>(6U);
                 ++face) {
                if (counts[face] == static_cast<std::uint8_t>(5U)) {
                    return 50U;
                }
            }
            return 0U;
        }

        default:
            // Defensive programming – unreachable
            return 0U;
    }
}

auto score(const std::array<std::uint8_t, 5U>& dice,
           std::string_view cat) noexcept -> score_t
{
    category mapped_cat{};

    if (cat == "ones") {
        mapped_cat = category::ones;
    } else if (cat == "twos") {
        mapped_cat = category::twos;
    } else if (cat == "threes") {
        mapped_cat = category::threes;
    } else if (cat == "fours") {
        mapped_cat = category::fours;
    } else if (cat == "fives") {
        mapped_cat = category::fives;
    } else if (cat == "sixes") {
        mapped_cat = category::sixes;
    } else if (cat == "full house") {
        mapped_cat = category::full_house;
    } else if (cat == "four of a kind") {
        mapped_cat = category::four_of_a_kind;
    } else if (cat == "little straight") {
        mapped_cat = category::little_straight;
    } else if (cat == "big straight") {
        mapped_cat = category::big_straight;
    } else if (cat == "choice") {
        mapped_cat = category::choice;
    } else if (cat == "yacht") {
        mapped_cat = category::yacht;
    } else {
        // Unknown category string – not defined by rules
        return static_cast<score_t>(0U);
    }

    return score(dice, mapped_cat);
}

}  // namespace yacht
