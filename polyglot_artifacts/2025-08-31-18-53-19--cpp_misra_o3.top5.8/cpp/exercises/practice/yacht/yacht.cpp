#include "yacht.h"

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <string_view>

namespace yacht {

auto score(const std::array<std::uint8_t, 5U>& dice,
           const Category                       category) -> std::uint32_t
{
    /* Count occurrences of each face value (indices 1-6 are used) */
    std::array<std::uint8_t, 7U> counts{};
    for (auto value : dice) {
        ++counts[static_cast<std::size_t>(value)];
    }

    switch (category) {
        case Category::ones: {
            return static_cast<std::uint32_t>(counts[1U] * 1U);
        }
        case Category::twos: {
            return static_cast<std::uint32_t>(counts[2U] * 2U);
        }
        case Category::threes: {
            return static_cast<std::uint32_t>(counts[3U] * 3U);
        }
        case Category::fours: {
            return static_cast<std::uint32_t>(counts[4U] * 4U);
        }
        case Category::fives: {
            return static_cast<std::uint32_t>(counts[5U] * 5U);
        }
        case Category::sixes: {
            return static_cast<std::uint32_t>(counts[6U] * 6U);
        }
        case Category::choice: {
            /* Sum all dice */
            const auto total =
                std::accumulate(dice.begin(), dice.end(), std::uint32_t{0U});
            return total;
        }
        case Category::yacht: {
            for (std::uint8_t face = 1U; face <= 6U; ++face) {
                if (counts[face] == 5U) {
                    return 50U;
                }
            }
            return 0U;
        }
        case Category::four_of_a_kind: {
            for (std::uint8_t face = 1U; face <= 6U; ++face) {
                if (counts[face] >= 4U) {
                    return static_cast<std::uint32_t>(face * 4U);
                }
            }
            return 0U;
        }
        case Category::full_house: {
            bool has_three{false};
            bool has_two{false};
            std::uint32_t total{0U};

            for (std::uint8_t face = 1U; face <= 6U; ++face) {
                if (counts[face] == 3U) {
                    has_three = true;
                } else if (counts[face] == 2U) {
                    has_two = true;
                }
                total += static_cast<std::uint32_t>(counts[face] * face);
            }

            if (has_three && has_two) {
                return total;
            }
            return 0U;
        }
        case Category::little_straight: {
            const bool is_match =
                (counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 0U);

            if (is_match) {
                return 30U;
            }
            return 0U;
        }
        case Category::big_straight: {
            const bool is_match =
                (counts[1U] == 0U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 1U);

            if (is_match) {
                return 30U;
            }
            return 0U;
        }
        default: {
            /* Unreachable with current enum values, but keeps GCC/clang happy */
            return 0U;
        }
    }
}

/* ------------------------------------------------------------- */
/* Overload accepting the category as a string_view               */
/* ------------------------------------------------------------- */
auto score(const std::array<std::uint8_t, 5U>& dice,
           const std::string_view              category) -> std::uint32_t
{
    Category cat{Category::choice}; /* default initialisation */

    if ((category == "ones")) {
        cat = Category::ones;
    } else if ((category == "twos")) {
        cat = Category::twos;
    } else if ((category == "threes")) {
        cat = Category::threes;
    } else if ((category == "fours")) {
        cat = Category::fours;
    } else if ((category == "fives")) {
        cat = Category::fives;
    } else if ((category == "sixes")) {
        cat = Category::sixes;
    } else if ((category == "full house")) {
        cat = Category::full_house;
    } else if ((category == "four of a kind")) {
        cat = Category::four_of_a_kind;
    } else if ((category == "little straight")) {
        cat = Category::little_straight;
    } else if ((category == "big straight")) {
        cat = Category::big_straight;
    } else if ((category == "choice")) {
        cat = Category::choice;
    } else if ((category == "yacht")) {
        cat = Category::yacht;
    } else {
        return 0U; /* Unknown category string */
    }

    return score(dice, cat);
}

}  // namespace yacht
