#include "yacht.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <string_view>

namespace yacht {

/* Forward declaration of the enumeration-based overload. */
auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint32_t;

/* Translate textual category names (as used in the tests) into the enum. */
static auto to_category(std::string_view name) -> category
{
    if (name == "ones") { return category::ones; }
    if (name == "twos") { return category::twos; }
    if (name == "threes") { return category::threes; }
    if (name == "fours") { return category::fours; }
    if (name == "fives") { return category::fives; }
    if (name == "sixes") { return category::sixes; }
    if (name == "full house") { return category::full_house; }
    if (name == "four of a kind") { return category::four_of_a_kind; }
    if (name == "little straight") { return category::little_straight; }
    if (name == "big straight") { return category::big_straight; }
    if (name == "choice") { return category::choice; }
    if (name == "yacht") { return category::yacht; }
    /* Unknown input: map to 'choice' giving score 0 via later rules. */
    return category::choice;
}

/* Overload that the unit-tests call (category given as a string). */
auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view category_name)
    -> std::uint32_t
{
    return score(dice, to_category(category_name));
}

auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint32_t
{
    /* Frequency table – index equals the face value (1-6). */
    std::array<std::uint8_t, 7U> freq{}; /* element 0 unused */

    for (const auto value : dice) {
        ++freq[static_cast<std::size_t>(value)];
    }

    const std::uint32_t sum_all =
        std::accumulate(
            dice.begin(),
            dice.end(),
            static_cast<std::uint32_t>(0U),
            [](std::uint32_t acc, std::uint8_t v) {
                /* Explicit cast prevents implicit promotion (MISRA compliance). */
                return (acc + static_cast<std::uint32_t>(v));
            });

    switch (cat) {
        case category::ones: {
            return (static_cast<std::uint32_t>(freq[1U]) * static_cast<std::uint32_t>(1U));
        }
        case category::twos: {
            return (static_cast<std::uint32_t>(freq[2U]) * static_cast<std::uint32_t>(2U));
        }
        case category::threes: {
            return (static_cast<std::uint32_t>(freq[3U]) * static_cast<std::uint32_t>(3U));
        }
        case category::fours: {
            return (static_cast<std::uint32_t>(freq[4U]) * static_cast<std::uint32_t>(4U));
        }
        case category::fives: {
            return (static_cast<std::uint32_t>(freq[5U]) * static_cast<std::uint32_t>(5U));
        }
        case category::sixes: {
            return (static_cast<std::uint32_t>(freq[6U]) * static_cast<std::uint32_t>(6U));
        }

        case category::full_house: {
            bool has_three = false;
            bool has_two   = false;
            std::uint32_t full_house_sum = static_cast<std::uint32_t>(0U);

            for (std::uint8_t face = static_cast<std::uint8_t>(1U);
                 face <= static_cast<std::uint8_t>(6U);
                 ++face) {
                const std::uint8_t count = freq[static_cast<std::size_t>(face)];
                if (count == static_cast<std::uint8_t>(3U)) {
                    has_three = true;
                    full_house_sum +=
                        (static_cast<std::uint32_t>(count) *
                         static_cast<std::uint32_t>(face));
                } else if (count == static_cast<std::uint8_t>(2U)) {
                    has_two = true;
                    full_house_sum +=
                        (static_cast<std::uint32_t>(count) *
                         static_cast<std::uint32_t>(face));
                }
            }
            return ((has_three && has_two) ? full_house_sum : static_cast<std::uint32_t>(0U));
        }

        case category::four_of_a_kind: {
            for (std::uint8_t face = static_cast<std::uint8_t>(1U);
                 face <= static_cast<std::uint8_t>(6U);
                 ++face) {
                const std::uint8_t count = freq[static_cast<std::size_t>(face)];
                if (count >= static_cast<std::uint8_t>(4U)) {
                    return (static_cast<std::uint32_t>(4U) *
                            static_cast<std::uint32_t>(face));
                }
            }
            return static_cast<std::uint32_t>(0U);
        }

        case category::little_straight: {
            bool is_straight = true;
            for (std::uint8_t face = static_cast<std::uint8_t>(1U);
                 face <= static_cast<std::uint8_t>(5U);
                 ++face) {
                if (freq[static_cast<std::size_t>(face)] != static_cast<std::uint8_t>(1U)) {
                    is_straight = false;
                    break;
                }
            }
            return (is_straight ? static_cast<std::uint32_t>(30U)
                                : static_cast<std::uint32_t>(0U));
        }

        case category::big_straight: {
            bool is_straight = true;
            for (std::uint8_t face = static_cast<std::uint8_t>(2U);
                 face <= static_cast<std::uint8_t>(6U);
                 ++face) {
                if (freq[static_cast<std::size_t>(face)] != static_cast<std::uint8_t>(1U)) {
                    is_straight = false;
                    break;
                }
            }
            return (is_straight ? static_cast<std::uint32_t>(30U)
                                : static_cast<std::uint32_t>(0U));
        }

        case category::choice: {
            return sum_all;
        }

        case category::yacht: {
            for (std::uint8_t face = static_cast<std::uint8_t>(1U);
                 face <= static_cast<std::uint8_t>(6U);
                 ++face) {
                if (freq[static_cast<std::size_t>(face)] == static_cast<std::uint8_t>(5U)) {
                    return static_cast<std::uint32_t>(50U);
                }
            }
            return static_cast<std::uint32_t>(0U);
        }

        default: {
            /* Defensive default – should never be reached. */
            return static_cast<std::uint32_t>(0U);
        }
    }
}

}  // namespace yacht
