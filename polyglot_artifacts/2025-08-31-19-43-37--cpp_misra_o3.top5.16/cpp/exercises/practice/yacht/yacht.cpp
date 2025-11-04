#include "yacht.h"

#include <cstddef>
#include <algorithm>
#include <numeric>
#include <string_view>
#include <initializer_list>

namespace yacht {

auto score(Category category, std::array<std::uint8_t, 5U> const& dice) -> std::uint32_t
{
    /* Count occurrences of each face value (indices 1..6). */
    std::array<std::uint8_t, 7U> counts{}; /* index 0 left unused */
    for (std::uint8_t const die : dice) {
        ++counts[static_cast<std::size_t>(die)];
    }

    switch (category) {
        case Category::Ones: {
            return (static_cast<std::uint32_t>(counts[1U]) * static_cast<std::uint32_t>(1U));
        }
        case Category::Twos: {
            return (static_cast<std::uint32_t>(counts[2U]) * static_cast<std::uint32_t>(2U));
        }
        case Category::Threes: {
            return (static_cast<std::uint32_t>(counts[3U]) * static_cast<std::uint32_t>(3U));
        }
        case Category::Fours: {
            return (static_cast<std::uint32_t>(counts[4U]) * static_cast<std::uint32_t>(4U));
        }
        case Category::Fives: {
            return (static_cast<std::uint32_t>(counts[5U]) * static_cast<std::uint32_t>(5U));
        }
        case Category::Sixes: {
            return (static_cast<std::uint32_t>(counts[6U]) * static_cast<std::uint32_t>(6U));
        }
        case Category::FullHouse: {
            bool const has_three{std::any_of(counts.cbegin() + 1U, counts.cend(),
                                             [](std::uint8_t c) { return (c == 3U); })};
            bool const has_two{std::any_of(counts.cbegin() + 1U, counts.cend(),
                                           [](std::uint8_t c) { return (c == 2U); })};
            if (has_three && has_two) {
                return std::accumulate(dice.cbegin(), dice.cend(), std::uint32_t{0U});
            }
            return 0U;
        }
        case Category::FourOfAKind: {
            for (std::uint8_t face = 1U; face <= 6U; ++face) {
                if (counts[static_cast<std::size_t>(face)] >= 4U) {
                    return (static_cast<std::uint32_t>(face) * static_cast<std::uint32_t>(4U));
                }
            }
            return 0U;
        }
        case Category::LittleStraight: {
            if ((counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 1U)) {
                return 30U;
            }
            return 0U;
        }
        case Category::BigStraight: {
            if ((counts[2U] == 1U) && (counts[3U] == 1U) && (counts[4U] == 1U) &&
                (counts[5U] == 1U) && (counts[6U] == 1U)) {
                return 30U;
            }
            return 0U;
        }
        case Category::Choice: {
            return std::accumulate(dice.cbegin(), dice.cend(), std::uint32_t{0U});
        }
        case Category::Yacht: {
            if (std::any_of(counts.cbegin() + 1U, counts.cend(),
                            [](std::uint8_t c) { return (c == 5U); })) {
                return 50U;
            }
            return 0U;
        }
        default: {
            return 0U;
        }
    }
}

auto score(std::array<std::uint8_t, 5U> const& dice, std::string_view category) -> std::uint32_t
{
    Category cat{Category::Choice};

    if (category == "ones") {
        cat = Category::Ones;
    } else if (category == "twos") {
        cat = Category::Twos;
    } else if (category == "threes") {
        cat = Category::Threes;
    } else if (category == "fours") {
        cat = Category::Fours;
    } else if (category == "fives") {
        cat = Category::Fives;
    } else if (category == "sixes") {
        cat = Category::Sixes;
    } else if (category == "full house") {
        cat = Category::FullHouse;
    } else if (category == "four of a kind") {
        cat = Category::FourOfAKind;
    } else if (category == "little straight") {
        cat = Category::LittleStraight;
    } else if (category == "big straight") {
        cat = Category::BigStraight;
    } else if (category == "choice") {
        cat = Category::Choice;
    } else if (category == "yacht") {
        cat = Category::Yacht;
    } else {
        return 0U;
    }

    return score(cat, dice);
}

auto score(std::initializer_list<std::uint8_t> dice_init, std::string_view category) -> std::uint32_t
{
    if (dice_init.size() != 5U) {
        return 0U;
    }

    std::array<std::uint8_t, 5U> dice{};
    std::size_t idx{0U};
    for (std::uint8_t const value : dice_init) {
        dice[idx] = value;
        ++idx;
    }

    return score(dice, category);
}

}  // namespace yacht
