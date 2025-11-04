#include "yacht.h"
#include <array>
#include <cstdint>
#include <cstddef>
#include <string_view>

namespace yacht {

/* Translate textual category names used by the tests to the strongly-typed enum. */
static auto to_category(std::string_view name) -> category
{
    if (name == "ones")              { return category::ones; }
    if (name == "twos")              { return category::twos; }
    if (name == "threes")            { return category::threes; }
    if (name == "fours")             { return category::fours; }
    if (name == "fives")             { return category::fives; }
    if (name == "sixes")             { return category::sixes; }
    if (name == "full house")        { return category::full_house; }
    if (name == "four of a kind")    { return category::four_of_a_kind; }
    if (name == "little straight")   { return category::little_straight; }
    if (name == "big straight")      { return category::big_straight; }
    if (name == "choice")            { return category::choice; }
    if (name == "yacht")             { return category::yacht; }

    /* Default to choice on unrecognised input (scores zero) */
    return category::choice;
}

/* Overload that accepts a textual category, converts it, and delegates. */
[[nodiscard]] auto score(const dice_array& dice, const char* cat) -> std::uint32_t
{
    std::string_view const name { (cat != nullptr) ? std::string_view{cat} : std::string_view{} };
    return score(dice, to_category(name));
}

[[nodiscard]] auto score(const dice_array& dice, const category cat) -> std::uint32_t
{
    /* Count occurrences of each face (1-6) */
    std::array<std::uint8_t, 6U> counts {{0U, 0U, 0U, 0U, 0U, 0U}};
    for (const std::uint8_t die : dice) {
        const std::size_t idx { static_cast<std::size_t>(die - static_cast<std::uint8_t>(1U)) };
        ++counts[idx];
    }

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            const std::uint8_t face { static_cast<std::uint8_t>(cat) };
            const std::uint32_t total {
                static_cast<std::uint32_t>(face)
                * static_cast<std::uint32_t>(counts[static_cast<std::size_t>(face - static_cast<std::uint8_t>(1U))])
            };
            return total;
        }

        case category::full_house: {
            bool has_three { false };
            bool has_two   { false };
            std::uint32_t sum { 0U };
            for (const std::uint8_t die : dice) {
                sum += static_cast<std::uint32_t>(die);
            }
            for (const std::uint8_t cnt : counts) {
                if (cnt == static_cast<std::uint8_t>(3U)) { has_three = true; }
                if (cnt == static_cast<std::uint8_t>(2U)) { has_two   = true; }
            }
            if (has_three && has_two) {
                return sum;
            }
            return 0U;
        }

        case category::four_of_a_kind: {
            for (std::uint8_t face = 1U; face <= static_cast<std::uint8_t>(6U); ++face) {
                if (counts[static_cast<std::size_t>(face - static_cast<std::uint8_t>(1U))]
                    >= static_cast<std::uint8_t>(4U)) {
                    return static_cast<std::uint32_t>(face) * static_cast<std::uint32_t>(4U);
                }
            }
            return 0U;
        }

        case category::little_straight: {
            const bool is_seq {
                (counts[0] == static_cast<std::uint8_t>(1U)) &&
                (counts[1] == static_cast<std::uint8_t>(1U)) &&
                (counts[2] == static_cast<std::uint8_t>(1U)) &&
                (counts[3] == static_cast<std::uint8_t>(1U)) &&
                (counts[4] == static_cast<std::uint8_t>(1U)) &&
                (counts[5] == static_cast<std::uint8_t>(0U))
            };
            if (is_seq) {
                return 30U;
            }
            return 0U;
        }

        case category::big_straight: {
            const bool is_seq {
                (counts[0] == static_cast<std::uint8_t>(0U)) &&
                (counts[1] == static_cast<std::uint8_t>(1U)) &&
                (counts[2] == static_cast<std::uint8_t>(1U)) &&
                (counts[3] == static_cast<std::uint8_t>(1U)) &&
                (counts[4] == static_cast<std::uint8_t>(1U)) &&
                (counts[5] == static_cast<std::uint8_t>(1U))
            };
            if (is_seq) {
                return 30U;
            }
            return 0U;
        }

        case category::choice: {
            std::uint32_t sum { 0U };
            for (const std::uint8_t die : dice) {
                sum += static_cast<std::uint32_t>(die);
            }
            return sum;
        }

        case category::yacht: {
            for (const std::uint8_t cnt : counts) {
                if (cnt == static_cast<std::uint8_t>(5U)) {
                    return 50U;
                }
            }
            return 0U;
        }

        default: {
            return 0U;
        }
    }
}

/* Accept std::array<int,5> that the tests form via brace-initialisation and
 * convert it into our internal dice_array. */
[[nodiscard]] auto score(const std::array<int, 5>& dice, const category cat) -> std::uint32_t
{
    dice_array conv {};
    for (std::size_t i { 0U }; i < 5U; ++i) {
        conv[i] = static_cast<std::uint8_t>(dice[i]);
    }
    return score(conv, cat);
}

[[nodiscard]] auto score(const std::array<int, 5>& dice, const char* cat) -> std::uint32_t
{
    dice_array conv {};
    for (std::size_t i { 0U }; i < 5U; ++i) {
        conv[i] = static_cast<std::uint8_t>(dice[i]);
    }
    return score(conv, cat);
}

}  // namespace yacht
