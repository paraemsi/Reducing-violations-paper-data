#include "yacht.h"

#include <algorithm>
#include <numeric>
#include <string_view>

namespace yacht {

//  Convert category name (exact, lowercase) to enum value
static auto category_from_string(std::string_view const name) -> category
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
    } else {  //  "yacht" or any unrecognised string
        return category::yacht;
    }
}

//  Overload accepting a category name string
auto score(dice_t const& dice, std::string_view const name) -> score_t
{
    return score(dice, category_from_string(name));
}

auto score(dice_t const& dice, category const cat) -> score_t
{
    //  Frequency table for the six faces
    std::array<std::uint8_t, 6U> counts{};
    counts.fill(0U);

    for (die_t const d : dice) {
        std::size_t const idx { static_cast<std::size_t>(d) - 1U };
        ++counts[idx];    // safe: value never exceeds 5
    }

    score_t const total { std::accumulate(
        dice.cbegin(),
        dice.cend(),
        score_t{ 0U },
        [](score_t const acc, die_t const v) -> score_t {
            return static_cast<score_t>(acc + static_cast<score_t>(v));
        }) };

    auto count_of = [&counts](std::uint8_t const face) noexcept -> std::uint8_t {
        /* face is 1-based, counts is 0-based */
        return counts[static_cast<std::size_t>(face) - 1U];
    };

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            die_t const face { static_cast<die_t>(static_cast<die_t>(cat) + static_cast<die_t>(1U)) };
            return static_cast<score_t>(face) * static_cast<score_t>(count_of(face));
        }

        case category::full_house: {
            bool has_three { false };
            bool has_two   { false };
            for (std::uint8_t idx { 0U }; idx < 6U; ++idx) {
                if (counts[idx] == 3U) {
                    has_three = true;
                } else if (counts[idx] == 2U) {
                    has_two = true;
                }
            }
            return (has_three && has_two) ? total : score_t{ 0U };
        }

        case category::four_of_a_kind: {
            for (std::uint8_t idx { 0U }; idx < 6U; ++idx) {
                if (counts[idx] >= 4U) {
                    std::uint8_t const face { static_cast<std::uint8_t>(idx + 1U) };
                    return static_cast<score_t>(face) * static_cast<score_t>(4U);
                }
            }
            return score_t{ 0U };
        }

        case category::little_straight: {
            bool const is_match {
                (counts[0U] == 1U) && (counts[1U] == 1U) &&
                (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 0U)
            };
            return is_match ? static_cast<score_t>(30U) : score_t{ 0U };
        }

        case category::big_straight: {
            bool const is_match {
                (counts[0U] == 0U) && (counts[1U] == 1U) &&
                (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 1U)
            };
            return is_match ? static_cast<score_t>(30U) : score_t{ 0U };
        }

        case category::choice: {
            return total;
        }

        case category::yacht: {
            for (std::uint8_t idx { 0U }; idx < 6U; ++idx) {
                if (counts[idx] == 5U) {
                    return static_cast<score_t>(50U);
                }
            }
            return score_t{ 0U };
        }

        default: {
            return score_t{ 0U };
        }
    }
}

}  // namespace yacht
