#include "yacht.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <string_view>
#include <initializer_list>

namespace yacht {

// helper: count occurrences of each die face (1..6)
static auto make_counts(const std::array<std::uint8_t, 5U>& dice)
    -> std::array<std::uint8_t, 7U>  // index 0 unused
{
    std::array<std::uint8_t, 7U> counts{};
    for (const std::uint8_t die : dice) {
        ++counts[static_cast<std::size_t>(die)];
    }
    return counts;
}

auto score(Category cat, const std::array<std::uint8_t, 5U>& dice) -> std::int32_t
{
    const auto counts { make_counts(dice) };
    const std::int32_t total { std::accumulate(
        dice.cbegin(),
        dice.cend(),
        static_cast<std::int32_t>(0),
        [](std::int32_t acc, std::uint8_t v) { return acc + static_cast<std::int32_t>(v); }) };

    switch (cat) {
        case Category::ones:
        case Category::twos:
        case Category::threes:
        case Category::fours:
        case Category::fives:
        case Category::sixes: {
            const std::uint8_t face { static_cast<std::uint8_t>(static_cast<std::uint8_t>(cat) + 1U) };
            const std::int32_t result { static_cast<std::int32_t>(counts[face]) *
                                        static_cast<std::int32_t>(face) };
            return result;
        }

        case Category::full_house: {
            bool has_three { false };
            bool has_two   { false };
            for (std::size_t face { 1U }; face <= 6U; ++face) {
                if (counts[face] == 3U) {
                    has_three = true;
                } else if (counts[face] == 2U) {
                    has_two = true;
                }
            }
            if ((has_three) && (has_two)) {
                return total;
            }
            return 0;
        }

        case Category::four_of_a_kind: {
            for (std::size_t face { 1U }; face <= 6U; ++face) {
                if (counts[face] >= 4U) {
                    return static_cast<std::int32_t>(face) * static_cast<std::int32_t>(4);
                }
            }
            return static_cast<std::int32_t>(0);
        }

        case Category::little_straight: {
            const bool is_straight { (counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                                     (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 0U) };
            return is_straight ? static_cast<std::int32_t>(30) : static_cast<std::int32_t>(0);
        }

        case Category::big_straight: {
            const bool is_straight { (counts[1U] == 0U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                                     (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 1U) };
            return is_straight ? static_cast<std::int32_t>(30) : static_cast<std::int32_t>(0);
        }

        case Category::choice: {
            return total;
        }

        case Category::yacht: {
            for (std::size_t face { 1U }; face <= 6U; ++face) {
                if (counts[face] == 5U) {
                    return static_cast<std::int32_t>(50);
                }
            }
            return static_cast<std::int32_t>(0);
        }

        default:
            // unreachable, but keeps compilers happy without violating rules
            return static_cast<std::int32_t>(0);
    }
}

auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view category) -> std::int32_t
{
    Category cat {};

    if (category == "ones") {
        cat = Category::ones;
    } else if (category == "twos") {
        cat = Category::twos;
    } else if (category == "threes") {
        cat = Category::threes;
    } else if (category == "fours") {
        cat = Category::fours;
    } else if (category == "fives") {
        cat = Category::fives;
    } else if (category == "sixes") {
        cat = Category::sixes;
    } else if (category == "full house") {
        cat = Category::full_house;
    } else if (category == "four of a kind") {
        cat = Category::four_of_a_kind;
    } else if (category == "little straight") {
        cat = Category::little_straight;
    } else if (category == "big straight") {
        cat = Category::big_straight;
    } else if (category == "choice") {
        cat = Category::choice;
    } else if (category == "yacht") {
        cat = Category::yacht;
    } else {
        /* Unknown category string - return zero. */
        return static_cast<std::int32_t>(0);
    }

        return score(cat, dice);
    }

template <typename IntegerT>
auto score(std::initializer_list<IntegerT> dice_init, std::string_view category) -> std::int32_t
    {
        /* Convert initializer list to the std::array<std::uint8_t, 5U> expected by
         * the main scoring routine. */
        std::array<std::uint8_t, 5U> dice_array{};

        if (dice_init.size() != 5U) {
            /* Defensive – input should always be 5 dice; otherwise, zero score. */
            return static_cast<std::int32_t>(0);
        }

        std::size_t idx { 0U };
        for (const int val : dice_init) {
            /* Values are guaranteed by the exercise to be in the range [1,6]. */
            dice_array[idx] = static_cast<std::uint8_t>(val);
            ++idx;
        }

        return score(dice_array, category);
}

}  // namespace yacht
