#include "yacht.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <numeric>
#include <type_traits>
#include <string_view>

namespace yacht {

namespace   /* unnamed */ {

/* Convert textual category names into the strongly-typed enumeration */
static auto parse_category(std::string_view name) -> category
{
    if (name == "ones") {
        return category::ones;
    } else if (name == "twos") {
        return category::twos;
    } else if (name == "threes") {
        return category::threes;
    } else if (name == "fours") {
        return category::fours;
    } else if (name == "fives") {
        return category::fives;
    } else if (name == "sixes") {
        return category::sixes;
    } else if (name == "full house") {
        return category::full_house;
    } else if (name == "four of a kind") {
        return category::four_of_a_kind;
    } else if (name == "little straight") {
        return category::little_straight;
    } else if (name == "big straight") {
        return category::big_straight;
    } else if (name == "choice") {
        return category::choice;
    } else if (name == "yacht") {
        return category::yacht;
    } else {            /* fall-back */
        return category::yacht;
    }
}

}   // unnamed namespace

/* Overload accepting a text category for compatibility with tests */
auto score(dice_array dice, std::string_view cat) -> std::int32_t
{
    return score(dice, parse_category(cat));
}

/* Calculate the score for the given dice hand and category */
auto score(dice_array dice, category cat) -> std::int32_t
{
    /* Sort dice once for straight detection */
    std::sort(dice.begin(), dice.end());

    /* Frequency table for faces 1-6 */
    std::array<std::uint8_t, 6U> counts{};
    for (std::uint8_t value : dice) {
        ++counts[static_cast<std::size_t>(value - static_cast<std::uint8_t>(1U))];
    }

    const auto sum_all =
        std::accumulate(dice.begin(),
                        dice.end(),
                        static_cast<std::int32_t>(0),
                        [](std::int32_t acc, std::uint8_t value) -> std::int32_t {
                            return (acc + static_cast<std::int32_t>(value));
                        });

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes:
        {
            const std::uint8_t face =
                static_cast<std::uint8_t>(static_cast<std::underlying_type_t<category>>(cat) + 1);
            const std::uint8_t count =
                counts[static_cast<std::size_t>(face - static_cast<std::uint8_t>(1U))];
            return static_cast<std::int32_t>(face) *
                   static_cast<std::int32_t>(count);
        }

        case category::full_house:
        {
            bool three_found{false};
            bool two_found{false};
            for (std::uint8_t c : counts) {
                if (c == static_cast<std::uint8_t>(3U)) {
                    three_found = true;
                } else if (c == static_cast<std::uint8_t>(2U)) {
                    two_found = true;
                }
            }
            if (three_found && two_found) {
                return sum_all;
            } else {
                return static_cast<std::int32_t>(0);
            }
        }

        case category::four_of_a_kind:
        {
            for (std::size_t idx = 0U; idx < counts.size(); ++idx) {
                if (counts[idx] >= static_cast<std::uint8_t>(4U)) {
                    const std::uint8_t face =
                        static_cast<std::uint8_t>(idx) + static_cast<std::uint8_t>(1U);
                    return static_cast<std::int32_t>(face) *
                           static_cast<std::int32_t>(4);
                }
            }
            return static_cast<std::int32_t>(0);
        }

        case category::little_straight:
        {
            const std::array<std::uint8_t, 5U> target{1U, 2U, 3U, 4U, 5U};
            if (std::equal(dice.begin(), dice.end(), target.begin())) {
                return static_cast<std::int32_t>(30);
            }
            return static_cast<std::int32_t>(0);
        }

        case category::big_straight:
        {
            const std::array<std::uint8_t, 5U> target{2U, 3U, 4U, 5U, 6U};
            if (std::equal(dice.begin(), dice.end(), target.begin())) {
                return static_cast<std::int32_t>(30);
            }
            return static_cast<std::int32_t>(0);
        }

        case category::choice:
        {
            return sum_all;
        }

        case category::yacht:
        {
            if (counts[static_cast<std::size_t>(dice.front() -
                                                static_cast<std::uint8_t>(1U))] ==
                static_cast<std::uint8_t>(5U)) {
                return static_cast<std::int32_t>(50);
            }
            return static_cast<std::int32_t>(0);
        }

        default:
            return static_cast<std::int32_t>(0);
    }
}

}  // namespace yacht
