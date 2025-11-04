#include "yacht.h"

#include <algorithm>
#include <numeric>
#include <string_view>
#include <stdexcept>

namespace yacht {

auto score(const std::array<std::uint8_t, 5U>& dice,
           const category                         cat) -> std::uint32_t
{
    /* Count occurrences of each face (1-6). */
    std::array<std::uint8_t, 6U> counts {};
    for (const std::uint8_t die : dice) {
        /* Defensive check – input is expected to be 1-6 */
        if ((die >= static_cast<std::uint8_t>(1U)) &&
            (die <= static_cast<std::uint8_t>(6U))) {
            ++counts[static_cast<std::size_t>(die - static_cast<std::uint8_t>(1U))];
        }
    }

    /* Helper to sum all dice without implicit promotions. */
    const auto total = std::accumulate(
        dice.begin(),
        dice.end(),
        std::uint32_t {0U},
        [](const std::uint32_t acc, const std::uint8_t val) -> std::uint32_t {
            return (acc + static_cast<std::uint32_t>(val));
        });

    switch (cat) {
        case category::ones: {
            return (static_cast<std::uint32_t>(counts[0U]) *
                    static_cast<std::uint32_t>(1U));
        }
        case category::twos: {
            return (static_cast<std::uint32_t>(counts[1U]) *
                    static_cast<std::uint32_t>(2U));
        }
        case category::threes: {
            return (static_cast<std::uint32_t>(counts[2U]) *
                    static_cast<std::uint32_t>(3U));
        }
        case category::fours: {
            return (static_cast<std::uint32_t>(counts[3U]) *
                    static_cast<std::uint32_t>(4U));
        }
        case category::fives: {
            return (static_cast<std::uint32_t>(counts[4U]) *
                    static_cast<std::uint32_t>(5U));
        }
        case category::sixes: {
            return (static_cast<std::uint32_t>(counts[5U]) *
                    static_cast<std::uint32_t>(6U));
        }
        case category::full_house: {
            bool has_three {false};
            bool has_two   {false};
            for (std::size_t idx {0U}; idx < counts.size(); ++idx) {
                if (counts[idx] == static_cast<std::uint8_t>(3U)) {
                    has_three = true;
                } else if (counts[idx] == static_cast<std::uint8_t>(2U)) {
                    has_two = true;
                }
            }
            return ((has_three && has_two) ? total : static_cast<std::uint32_t>(0U));
        }
        case category::four_of_a_kind: {
            for (std::size_t idx {0U}; idx < counts.size(); ++idx) {
                if (counts[idx] >= static_cast<std::uint8_t>(4U)) {
                    const std::uint32_t face {static_cast<std::uint32_t>(idx + 1U)};
                    return (face * static_cast<std::uint32_t>(4U));
                }
            }
            return static_cast<std::uint32_t>(0U);
        }
        case category::little_straight: {
            const bool is_little { (counts[0U] == static_cast<std::uint8_t>(1U)) &&
                                   (counts[1U] == static_cast<std::uint8_t>(1U)) &&
                                   (counts[2U] == static_cast<std::uint8_t>(1U)) &&
                                   (counts[3U] == static_cast<std::uint8_t>(1U)) &&
                                   (counts[4U] == static_cast<std::uint8_t>(1U)) &&
                                   (counts[5U] == static_cast<std::uint8_t>(0U)) };
            return (is_little ? static_cast<std::uint32_t>(30U)
                              : static_cast<std::uint32_t>(0U));
        }
        case category::big_straight: {
            const bool is_big { (counts[0U] == static_cast<std::uint8_t>(0U)) &&
                                (counts[1U] == static_cast<std::uint8_t>(1U)) &&
                                (counts[2U] == static_cast<std::uint8_t>(1U)) &&
                                (counts[3U] == static_cast<std::uint8_t>(1U)) &&
                                (counts[4U] == static_cast<std::uint8_t>(1U)) &&
                                (counts[5U] == static_cast<std::uint8_t>(1U)) };
            return (is_big ? static_cast<std::uint32_t>(30U)
                           : static_cast<std::uint32_t>(0U));
        }
        case category::choice: {
            return total;
        }
        case category::yacht: {
            for (const std::uint8_t c : counts) {
                if (c == static_cast<std::uint8_t>(5U)) {
                    return static_cast<std::uint32_t>(50U);
                }
            }
            return static_cast<std::uint32_t>(0U);
        }
        default: {
            /* Should not be reached – return 0U defensively. */
            return static_cast<std::uint32_t>(0U);
        }
    }
}

auto score(const std::array<std::uint8_t, 5U>& dice,
           std::string_view                             cat) -> std::uint32_t
{
    category cat_enum {category::choice};

    if (cat == std::string_view {"ones"}) {
        cat_enum = category::ones;
    } else if (cat == std::string_view {"twos"}) {
        cat_enum = category::twos;
    } else if (cat == std::string_view {"threes"}) {
        cat_enum = category::threes;
    } else if (cat == std::string_view {"fours"}) {
        cat_enum = category::fours;
    } else if (cat == std::string_view {"fives"}) {
        cat_enum = category::fives;
    } else if (cat == std::string_view {"sixes"}) {
        cat_enum = category::sixes;
    } else if (cat == std::string_view {"full house"}) {
        cat_enum = category::full_house;
    } else if (cat == std::string_view {"four of a kind"}) {
        cat_enum = category::four_of_a_kind;
    } else if (cat == std::string_view {"little straight"}) {
        cat_enum = category::little_straight;
    } else if (cat == std::string_view {"big straight"}) {
        cat_enum = category::big_straight;
    } else if (cat == std::string_view {"choice"}) {
        cat_enum = category::choice;
    } else if (cat == std::string_view {"yacht"}) {
        cat_enum = category::yacht;
    } else {
        return static_cast<std::uint32_t>(0U);
    }

    return score(dice, cat_enum);
}

/* Overload that accepts a braced-initializer list of exactly five integers and
 * forwards to the main implementation after converting to std::uint8_t. */
auto score(std::initializer_list<die_input_t> dice, std::string_view cat)
    -> std::uint32_t
{
    if (dice.size() != 5U) {
        /* The test-suite always supplies five dice; fail fast if not. */
        throw std::invalid_argument("exactly five dice required");
    }

    std::array<std::uint8_t, 5U> dice_u8 {};
    std::size_t                  idx {0U};
    for (const die_input_t v : dice) {
        /* Values are guaranteed 1-6 by the exercise; perform explicit cast. */
        dice_u8[idx] = static_cast<std::uint8_t>(v);
        ++idx;
    }

    return score(dice_u8, cat);
}

}  // namespace yacht
