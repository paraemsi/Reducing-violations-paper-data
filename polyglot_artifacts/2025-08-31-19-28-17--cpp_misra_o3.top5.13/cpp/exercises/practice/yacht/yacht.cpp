#include "yacht.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <string_view>

namespace yacht {

auto score(const std::array<std::uint8_t, 5U>& dice, Category category) -> std::uint32_t
{
    /* Count occurrences of each face (1 – 6). */
    std::array<std::uint8_t, 6U> counts{};
    for (const std::uint8_t die : dice) {
        /* Index adjustment: faces start at 1. */
        const std::size_t index {static_cast<std::size_t>(die) - 1U};
        ++counts[index];
    }

    /* Helper lambdas. */
    const auto sum_of_dice = [&dice]() -> std::uint32_t {
        return std::accumulate(
            dice.cbegin(),
            dice.cend(),
            static_cast<std::uint32_t>(0U),
            [](const std::uint32_t acc, const std::uint8_t value) -> std::uint32_t {
                return (acc + static_cast<std::uint32_t>(value));
            });
    };

    const auto find_n_of_a_kind = [&counts](const std::uint8_t n) -> std::uint8_t {
        for (std::uint8_t face {1U}; face <= 6U; ++face) {
            if (counts[static_cast<std::size_t>(face) - 1U] >= n) {
                return face;
            }
        }
        return 0U;
    };

    switch (category) {
        case Category::ones:
        case Category::twos:
        case Category::threes:
        case Category::fours:
        case Category::fives:
        case Category::sixes: {
            const std::uint8_t face {static_cast<std::uint8_t>(category) + 1U};
            const std::uint32_t occurrences {static_cast<std::uint32_t>(
                counts[static_cast<std::size_t>(face) - 1U])};
            return (static_cast<std::uint32_t>(face) * occurrences);
        }

        case Category::full_house: {
            bool has_three {false};
            bool has_two {false};
            for (const std::uint8_t c : counts) {
                if (c == 3U) {
                    has_three = true;
                } else if (c == 2U) {
                    has_two = true;
                }
            }
            if ((has_three) && (has_two)) {
                return sum_of_dice();
            }
            return 0U;
        }

        case Category::four_of_a_kind: {
            const std::uint8_t face {find_n_of_a_kind(4U)};
            if (face != 0U) {
                return (static_cast<std::uint32_t>(face) * 4U);
            }
            return 0U;
        }

        case Category::little_straight: {
            const bool is_straight {std::all_of(
                                         counts.cbegin(),
                                         counts.cbegin() + 5U,
                                         [](const std::uint8_t c) -> bool { return (c == 1U); }) &&
                                     (counts[5U] == 0U)};
            if (is_straight) {
                return 30U;
            }
            return 0U;
        }

        case Category::big_straight: {
            const bool is_straight {(counts[0U] == 0U) &&
                                    std::all_of(
                                        counts.cbegin() + 1U,
                                        counts.cend(),
                                        [](const std::uint8_t c) -> bool { return (c == 1U); })};
            if (is_straight) {
                return 30U;
            }
            return 0U;
        }

        case Category::choice: {
            return sum_of_dice();
        }

        case Category::yacht: {
            if (find_n_of_a_kind(5U) != 0U) {
                return 50U;
            }
            return 0U;
        }

        default:
            return 0U;
    }
}

auto to_category(std::string_view name) -> Category
{
    if (name == "ones") {
        return Category::ones;
    } else if (name == "twos") {
        return Category::twos;
    } else if (name == "threes") {
        return Category::threes;
    } else if (name == "fours") {
        return Category::fours;
    } else if (name == "fives") {
        return Category::fives;
    } else if (name == "sixes") {
        return Category::sixes;
    } else if (name == "full house") {
        return Category::full_house;
    } else if (name == "four of a kind") {
        return Category::four_of_a_kind;
    } else if (name == "little straight") {
        return Category::little_straight;
    } else if (name == "big straight") {
        return Category::big_straight;
    } else if (name == "choice") {
        return Category::choice;
    } else if (name == "yacht") {
        return Category::yacht;
    }
    /* Unknown name – default to choice. */
    return Category::choice;
}

auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view category_name) -> std::uint32_t
{
    const Category cat {to_category(category_name)};
    return score(dice, cat);
}

}  // namespace yacht
