#include "yacht.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

namespace yacht {

namespace {
    using counts_t = std::array<std::uint8_t, 7U>;

    auto make_counts(const std::array<die_t, dice_count>& dice) noexcept -> counts_t {
        counts_t counts{};
        for (die_t v : dice) {
            if ((v >= static_cast<die_t>(1U)) && (v <= static_cast<die_t>(6U))) {
                const std::size_t idx = static_cast<std::size_t>(v);
                counts[idx] = static_cast<std::uint8_t>(
                    static_cast<std::uint16_t>(counts[idx]) + static_cast<std::uint16_t>(1U));
            } else {
                // Out-of-range values are ignored per defensive programming; inputs are expected 1..6.
            }
        }
        return counts;
    }

    auto sum_dice(const std::array<die_t, dice_count>& dice) noexcept -> score_t {
        score_t s = static_cast<score_t>(0U);
        for (die_t v : dice) {
            s = static_cast<score_t>(s + static_cast<score_t>(v));
        }
        return s;
    }

    auto n_of_a_kind_score(const counts_t& counts, std::uint8_t n) noexcept -> score_t {
        for (std::uint8_t face = static_cast<std::uint8_t>(1U);
             face <= static_cast<std::uint8_t>(6U);
             face = static_cast<std::uint8_t>(face + static_cast<std::uint8_t>(1U))) {
            if (counts[static_cast<std::size_t>(face)] >= n) {
                return static_cast<score_t>(
                    static_cast<score_t>(face) * static_cast<score_t>(n));
            }
        }
        return static_cast<score_t>(0U);
    }

}  // namespace

auto score(const std::array<die_t, dice_count>& dice, category cat) noexcept -> score_t {
    const counts_t counts = make_counts(dice);

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            const std::uint8_t face = static_cast<std::uint8_t>(
                static_cast<std::uint8_t>(cat) + static_cast<std::uint8_t>(1U));
            const std::uint8_t cnt = counts[static_cast<std::size_t>(face)];
            return static_cast<score_t>(
                static_cast<score_t>(face) * static_cast<score_t>(cnt));
        }
        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            const score_t total = sum_dice(dice);
            for (std::uint8_t face = static_cast<std::uint8_t>(1U);
                 face <= static_cast<std::uint8_t>(6U);
                 face = static_cast<std::uint8_t>(face + static_cast<std::uint8_t>(1U))) {
                const std::uint8_t cnt = counts[static_cast<std::size_t>(face)];
                if (cnt == static_cast<std::uint8_t>(3U)) {
                    has_three = true;
                } else if (cnt == static_cast<std::uint8_t>(2U)) {
                    has_two = true;
                } else {
                    // no-op
                }
            }
            if ((has_three) && (has_two)) {
                return total;
            } else {
                return static_cast<score_t>(0U);
            }
        }
        case category::four_of_a_kind: {
            return n_of_a_kind_score(counts, static_cast<std::uint8_t>(4U));
        }
        case category::little_straight: {
            bool ok = true;
            for (std::uint8_t face = static_cast<std::uint8_t>(1U);
                 face <= static_cast<std::uint8_t>(5U);
                 face = static_cast<std::uint8_t>(face + static_cast<std::uint8_t>(1U))) {
                if (!(counts[static_cast<std::size_t>(face)] == static_cast<std::uint8_t>(1U))) {
                    ok = false;
                } else {
                    // still OK
                }
            }
            if ((ok) && (counts[static_cast<std::size_t>(6U)] == static_cast<std::uint8_t>(0U))) {
                return static_cast<score_t>(30U);
            } else {
                return static_cast<score_t>(0U);
            }
        }
        case category::big_straight: {
            bool ok = true;
            for (std::uint8_t face = static_cast<std::uint8_t>(2U);
                 face <= static_cast<std::uint8_t>(6U);
                 face = static_cast<std::uint8_t>(face + static_cast<std::uint8_t>(1U))) {
                if (!(counts[static_cast<std::size_t>(face)] == static_cast<std::uint8_t>(1U))) {
                    ok = false;
                } else {
                    // still OK
                }
            }
            if ((ok) && (counts[static_cast<std::size_t>(1U)] == static_cast<std::uint8_t>(0U))) {
                return static_cast<score_t>(30U);
            } else {
                return static_cast<score_t>(0U);
            }
        }
        case category::choice: {
            return sum_dice(dice);
        }
        case category::yacht: {
            for (std::uint8_t face = static_cast<std::uint8_t>(1U);
                 face <= static_cast<std::uint8_t>(6U);
                 face = static_cast<std::uint8_t>(face + static_cast<std::uint8_t>(1U))) {
                if (counts[static_cast<std::size_t>(face)] == static_cast<std::uint8_t>(5U)) {
                    return static_cast<score_t>(50U);
                } else {
                    // not a yacht for this face
                }
            }
            return static_cast<score_t>(0U);
        }
        default: {
            return static_cast<score_t>(0U);
        }
    }
}

auto score(const std::array<die_t, dice_count>& dice, const char* cat) noexcept -> score_t {
    if (cat == nullptr) {
        return static_cast<score_t>(0U);
    } else {
        // continue to comparisons
    }

    if ((std::strcmp(cat, "ones") == 0)) {
        return score(dice, category::ones);
    } else if ((std::strcmp(cat, "twos") == 0)) {
        return score(dice, category::twos);
    } else if ((std::strcmp(cat, "threes") == 0)) {
        return score(dice, category::threes);
    } else if ((std::strcmp(cat, "fours") == 0)) {
        return score(dice, category::fours);
    } else if ((std::strcmp(cat, "fives") == 0)) {
        return score(dice, category::fives);
    } else if ((std::strcmp(cat, "sixes") == 0)) {
        return score(dice, category::sixes);
    } else if ((std::strcmp(cat, "full house") == 0)) {
        return score(dice, category::full_house);
    } else if ((std::strcmp(cat, "four of a kind") == 0)) {
        return score(dice, category::four_of_a_kind);
    } else if ((std::strcmp(cat, "little straight") == 0)) {
        return score(dice, category::little_straight);
    } else if ((std::strcmp(cat, "big straight") == 0)) {
        return score(dice, category::big_straight);
    } else if ((std::strcmp(cat, "choice") == 0)) {
        return score(dice, category::choice);
    } else if ((std::strcmp(cat, "yacht") == 0)) {
        return score(dice, category::yacht);
    } else {
        return static_cast<score_t>(0U);
    }
}

auto score(const std::array<die_t, dice_count>& dice, const std::string& cat) noexcept -> score_t {
    return score(dice, cat.c_str());
}

}  // namespace yacht
