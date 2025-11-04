#include "yacht.h"

#include <algorithm>
#include <numeric>
#include <string_view>

namespace yacht {

namespace {

/*  Count the occurrences of each die face (1-6).                                           */
auto make_histogram(const hand_t& dice) -> std::array<std::uint8_t, 6U>
{
    std::array<std::uint8_t, 6U> counts{};                     /* all zero-initialised      */

    for (const die_t face : dice) {
        /* face is in the range 1-6; subtract 1 for zero-based index                         */
        counts[static_cast<std::size_t>(face) - 1U] =
            static_cast<std::uint8_t>(counts[static_cast<std::size_t>(face) - 1U] +
                                      static_cast<std::uint8_t>(1U));
    }

    return counts;
}

/*  Sum all dice values                                                                     */
auto sum_dice(const hand_t& dice) -> score_t
{
    return static_cast<score_t>(
        std::accumulate(dice.cbegin(), dice.cend(), static_cast<score_t>(0U), [](score_t acc, die_t v) {
            return static_cast<score_t>(acc + static_cast<score_t>(v));
        }));
}

}  // namespace

auto score(const hand_t& dice, category cat) -> score_t
{
    const auto counts = make_histogram(dice);

    switch (cat) {
        case category::ones: {
            return static_cast<score_t>(counts[0U]) * static_cast<score_t>(1U);
        }
        case category::twos: {
            return static_cast<score_t>(counts[1U]) * static_cast<score_t>(2U);
        }
        case category::threes: {
            return static_cast<score_t>(counts[2U]) * static_cast<score_t>(3U);
        }
        case category::fours: {
            return static_cast<score_t>(counts[3U]) * static_cast<score_t>(4U);
        }
        case category::fives: {
            return static_cast<score_t>(counts[4U]) * static_cast<score_t>(5U);
        }
        case category::sixes: {
            return static_cast<score_t>(counts[5U]) * static_cast<score_t>(6U);
        }
        case category::full_house: {
            const bool has_three =
                (std::find(counts.cbegin(), counts.cend(),
                           static_cast<std::uint8_t>(3U)) != counts.cend());
            const bool has_two   =
                (std::find(counts.cbegin(), counts.cend(),
                           static_cast<std::uint8_t>(2U)) != counts.cend());

            if (has_three && has_two) {
                return sum_dice(dice);
            } else {
                return static_cast<score_t>(0U);
            }
        }
        case category::four_of_a_kind: {
            for (std::size_t idx = 0U; idx < counts.size(); ++idx) {
                if (counts[idx] >= static_cast<std::uint8_t>(4U)) {
                    const score_t face_val =
                        static_cast<score_t>(static_cast<std::uint8_t>(idx) + 1U);
                    return face_val * static_cast<score_t>(4U);
                }
            }
            return static_cast<score_t>(0U);
        }
        case category::little_straight: {
            const std::array<std::uint8_t, 6U> pattern{1U, 1U, 1U, 1U, 1U, 0U};
            if (counts == pattern) {
                return static_cast<score_t>(30U);
            } else {
                return static_cast<score_t>(0U);
            }
        }
        case category::big_straight: {
            const std::array<std::uint8_t, 6U> pattern{0U, 1U, 1U, 1U, 1U, 1U};
            if (counts == pattern) {
                return static_cast<score_t>(30U);
            } else {
                return static_cast<score_t>(0U);
            }
        }
        case category::choice: {
            return sum_dice(dice);
        }
        case category::yacht: {
            const bool is_yacht =
                (std::find(counts.cbegin(), counts.cend(),
                           static_cast<std::uint8_t>(5U)) != counts.cend());
            if (is_yacht) {
                return static_cast<score_t>(50U);
            } else {
                return static_cast<score_t>(0U);
            }
        }
        default: {
            /* Defensive default, should not be reached.                                     */
            return static_cast<score_t>(0U);
        }
    }
}

auto category_from_string(std::string_view name) -> category
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
    } else {
        /* Default fall-back to choice for invalid input. */
        return category::choice;
    }
}

/*  Public API: score function accepting textual category name.                             */
auto score(const hand_t& dice, std::string_view cat_str) -> score_t
{
    return score(dice, category_from_string(cat_str));
}

}  // namespace yacht
