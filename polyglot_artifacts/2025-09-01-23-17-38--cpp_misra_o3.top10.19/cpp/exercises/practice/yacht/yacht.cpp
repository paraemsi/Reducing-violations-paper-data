#include "yacht.h"

#include <cstdint>
#include <stdexcept>   // for std::invalid_argument
#include <string_view>

namespace yacht {

/* Convert textual category to enumeration. */
static auto to_category(const std::string_view cat) -> category
{
    if (cat == "ones") {
        return category::ones;
    } else if (cat == "twos") {
        return category::twos;
    } else if (cat == "threes") {
        return category::threes;
    } else if (cat == "fours") {
        return category::fours;
    } else if (cat == "fives") {
        return category::fives;
    } else if (cat == "sixes") {
        return category::sixes;
    } else if (cat == "full house") {
        return category::full_house;
    } else if (cat == "four of a kind") {
        return category::four_of_a_kind;
    } else if (cat == "little straight") {
        return category::little_straight;
    } else if (cat == "big straight") {
        return category::big_straight;
    } else if (cat == "choice") {
        return category::choice;
    } else if (cat == "yacht") {
        return category::yacht;
    } else {
        throw std::invalid_argument("Unknown category");
    }
}

/* Helper: build a frequency table for die faces 1-6 inclusive. */
static auto build_frequency(const std::vector<std::uint8_t>& dice)
    -> std::array<std::uint8_t, 6U>
{
    /* The rules guarantee exactly five dice, but we defensively
     * verify this to avoid undefined behaviour further on. */
    if (dice.size() != 5U) {
        throw std::invalid_argument("Exactly five dice are required");
    }

    std::array<std::uint8_t, 6U> freq{};      // zero-initialised
    for (const std::uint8_t val : dice) {
        /* Ensure each die lies in the valid range 1-6. */
        if ((val < static_cast<std::uint8_t>(1U)) ||
            (val > static_cast<std::uint8_t>(6U))) {
            throw std::invalid_argument("Die values must be in range 1-6");
        }

        const std::uint8_t idx =
            static_cast<std::uint8_t>(val - static_cast<std::uint8_t>(1U));
        freq[idx] =
            static_cast<std::uint8_t>(freq[idx] + static_cast<std::uint8_t>(1U));
    }
    return freq;
}

auto score(const std::vector<std::uint8_t>& dice, std::string_view cat) -> std::uint32_t
{
    const category c = to_category(cat);
    return yacht::score(dice, c);
}

auto score(const std::vector<std::uint8_t>& dice, const category cat) -> std::uint32_t
{
    const std::array<std::uint8_t, 6U> freq = build_frequency(dice);

    /* Convenience lambda to compute the sum of all dice. */
    const auto sum_all = [&dice]() -> std::uint32_t {
        std::uint32_t total = 0U;
        for (const std::uint8_t v : dice) {
            total = static_cast<std::uint32_t>(total + static_cast<std::uint32_t>(v));
        }
        return total;
    };

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            const std::uint8_t face =
                static_cast<std::uint8_t>(static_cast<std::uint8_t>(cat) + static_cast<std::uint8_t>(1U));
            const std::uint8_t count = freq[static_cast<std::size_t>(cat)];
            return static_cast<std::uint32_t>(
                static_cast<std::uint32_t>(face) * static_cast<std::uint32_t>(count));
        }

        case category::full_house: {
            bool has_three = false;
            bool has_two   = false;
            for (const std::uint8_t f : freq) {
                if (f == static_cast<std::uint8_t>(3U)) {
                    has_three = true;
                } else if (f == static_cast<std::uint8_t>(2U)) {
                    has_two = true;
                }
            }
            if (has_three && has_two) {
                return sum_all();
            } else {
                return 0U;
            }
        }

        case category::four_of_a_kind: {
            for (std::uint8_t i = 0U; i < static_cast<std::uint8_t>(6U); ++i) {
                if (freq[static_cast<std::size_t>(i)] >= static_cast<std::uint8_t>(4U)) {
                    const std::uint32_t face =
                        static_cast<std::uint32_t>(static_cast<std::uint32_t>(i) + static_cast<std::uint32_t>(1U));
                    return static_cast<std::uint32_t>(face * static_cast<std::uint32_t>(4U));
                }
            }
            return 0U;
        }

        case category::little_straight: {
            bool is_match = true;
            for (std::uint8_t i = 0U; i < static_cast<std::uint8_t>(5U); ++i) {
                if (freq[static_cast<std::size_t>(i)] != static_cast<std::uint8_t>(1U)) {
                    is_match = false;
                }
            }
            if ((is_match) && (freq[5U] == static_cast<std::uint8_t>(0U))) {
                return 30U;
            } else {
                return 0U;
            }
        }

        case category::big_straight: {
            bool is_match = true;
            if (freq[0U] == static_cast<std::uint8_t>(0U)) {
                for (std::uint8_t i = static_cast<std::uint8_t>(1U);
                     i < static_cast<std::uint8_t>(6U);
                     ++i) {
                    if (freq[static_cast<std::size_t>(i)] != static_cast<std::uint8_t>(1U)) {
                        is_match = false;
                    }
                }
            } else {
                is_match = false;
            }
            return (is_match ? 30U : 0U);
        }

        case category::choice: {
            return sum_all();
        }

        case category::yacht: {
            for (const std::uint8_t f : freq) {
                if (f == static_cast<std::uint8_t>(5U)) {
                    return 50U;
                }
            }
            return 0U;
        }

        default:
            /* Defensive: should never reach here. */
            return 0U;
    }
}

}  // namespace yacht
