#include "yacht.h"

#include <array>
#include <cstddef>  // for std::size_t
#include <string_view>

namespace yacht {

static auto sum_dice(dice_roll_t const& dice) -> score_t
{
    score_t sum = static_cast<score_t>(0U);
    for (die_value_t v : dice) {
        sum = static_cast<score_t>(sum + static_cast<score_t>(v));
    }
    return sum;
}

auto score(dice_roll_t const& dice, category cat) noexcept -> score_t
{
    // Frequency of faces 1..6; index 0 is unused.
    std::array<std::uint8_t, 7U> counts{};  // zero-initialized
    for (die_value_t v : dice) {
        if ((v >= static_cast<die_value_t>(1U)) && (v <= static_cast<die_value_t>(6U))) {
            ++counts[static_cast<std::size_t>(v)];
        } else {
            // Input is assumed valid per problem statement; ignore otherwise.
        }
    }

    switch (cat) {
        case category::ones: {
            return static_cast<score_t>(1U) * static_cast<score_t>(counts[1U]);
        }
        case category::twos: {
            return static_cast<score_t>(2U) * static_cast<score_t>(counts[2U]);
        }
        case category::threes: {
            return static_cast<score_t>(3U) * static_cast<score_t>(counts[3U]);
        }
        case category::fours: {
            return static_cast<score_t>(4U) * static_cast<score_t>(counts[4U]);
        }
        case category::fives: {
            return static_cast<score_t>(5U) * static_cast<score_t>(counts[5U]);
        }
        case category::sixes: {
            return static_cast<score_t>(6U) * static_cast<score_t>(counts[6U]);
        }
        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (std::uint32_t face = 1U; face <= 6U; ++face) {
                std::uint8_t const c = counts[static_cast<std::size_t>(face)];
                if (c == static_cast<std::uint8_t>(3U)) {
                    has_three = true;
                } else {
                    if (c == static_cast<std::uint8_t>(2U)) {
                        has_two = true;
                    } else {
                        // no-op
                    }
                }
            }
            if ((has_three) && (has_two)) {
                return sum_dice(dice);
            } else {
                return static_cast<score_t>(0U);
            }
        }
        case category::four_of_a_kind: {
            for (std::uint32_t face = 1U; face <= 6U; ++face) {
                if (counts[static_cast<std::size_t>(face)] >= static_cast<std::uint8_t>(4U)) {
                    return static_cast<score_t>(4U) * static_cast<score_t>(face);
                } else {
                    // continue
                }
            }
            return static_cast<score_t>(0U);
        }
        case category::little_straight: {
            bool ok = true;
            for (std::uint32_t face = 1U; face <= 5U; ++face) {
                if (counts[static_cast<std::size_t>(face)] != static_cast<std::uint8_t>(1U)) {
                    ok = false;
                } else {
                    // continue
                }
            }
            if (counts[6U] != static_cast<std::uint8_t>(0U)) {
                ok = false;
            } else {
                // continue
            }
            if (ok) {
                return static_cast<score_t>(30U);
            } else {
                return static_cast<score_t>(0U);
            }
        }
        case category::big_straight: {
            bool ok = true;
            for (std::uint32_t face = 2U; face <= 6U; ++face) {
                if (counts[static_cast<std::size_t>(face)] != static_cast<std::uint8_t>(1U)) {
                    ok = false;
                } else {
                    // continue
                }
            }
            if (counts[1U] != static_cast<std::uint8_t>(0U)) {
                ok = false;
            } else {
                // continue
            }
            if (ok) {
                return static_cast<score_t>(30U);
            } else {
                return static_cast<score_t>(0U);
            }
        }
        case category::choice: {
            return sum_dice(dice);
        }
        case category::yacht: {
            for (std::uint32_t face = 1U; face <= 6U; ++face) {
                if (counts[static_cast<std::size_t>(face)] == static_cast<std::uint8_t>(5U)) {
                    return static_cast<score_t>(50U);
                } else {
                    // continue
                }
            }
            return static_cast<score_t>(0U);
        }
        default: {
            return static_cast<score_t>(0U);
        }
    }
}

auto score(dice_roll_t const& dice, char const* cat) noexcept -> score_t
{
    // Map string category names used by tests to enum and dispatch.
    std::string_view const s = (cat != nullptr) ? std::string_view{cat} : std::string_view{};
    if ((s == "ones")) {
        return score(dice, category::ones);
    } else if ((s == "twos")) {
        return score(dice, category::twos);
    } else if ((s == "threes")) {
        return score(dice, category::threes);
    } else if ((s == "fours")) {
        return score(dice, category::fours);
    } else if ((s == "fives")) {
        return score(dice, category::fives);
    } else if ((s == "sixes")) {
        return score(dice, category::sixes);
    } else if ((s == "full house")) {
        return score(dice, category::full_house);
    } else if ((s == "four of a kind")) {
        return score(dice, category::four_of_a_kind);
    } else if ((s == "little straight")) {
        return score(dice, category::little_straight);
    } else if ((s == "big straight")) {
        return score(dice, category::big_straight);
    } else if ((s == "choice")) {
        return score(dice, category::choice);
    } else if ((s == "yacht")) {
        return score(dice, category::yacht);
    } else {
        return static_cast<score_t>(0U);
    }
}

}  // namespace yacht
