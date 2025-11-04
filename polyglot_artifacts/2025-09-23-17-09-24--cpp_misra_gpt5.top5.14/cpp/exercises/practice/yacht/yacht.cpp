#include "yacht.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <numeric>
#include <cstring>

namespace yacht {

[[nodiscard]] auto score(dice_t const& dice, category cat) noexcept -> score_t
{
    // Frequency of each face value (1..6). Index 0 is unused.
    std::array<std::uint8_t, 7U> freq{};
    for (die_t const die : dice) {
        if ((die >= static_cast<die_t>(1U)) && (die <= static_cast<die_t>(6U))) {
            ++freq[static_cast<std::size_t>(die)];
        }
    }

    // Pre-computed total for categories that are the sum of dice
    score_t const sum_all = std::accumulate(
        dice.begin(),
        dice.end(),
        static_cast<score_t>(0U),
        [](score_t acc, die_t v) -> score_t {
            return (acc + static_cast<score_t>(v));
        });

    // Helper to get count for a specific face safely
    auto const count_of = [&freq](std::uint8_t face) -> std::uint8_t {
        return freq[static_cast<std::size_t>(face)];
    };

    // Check for yacht (five of a kind)
    bool is_yacht = false;
    for (std::uint8_t face = static_cast<std::uint8_t>(1U); face <= static_cast<std::uint8_t>(6U); ++face) {
        if (count_of(face) == static_cast<std::uint8_t>(5U)) {
            is_yacht = true;
            break;
        }
    }

    constexpr score_t straight_score = static_cast<score_t>(30U);
    constexpr score_t yacht_score    = static_cast<score_t>(50U);

    switch (cat) {
        case category::ones: {
            return (static_cast<score_t>(1U) * static_cast<score_t>(count_of(static_cast<std::uint8_t>(1U))));
        }
        case category::twos: {
            return (static_cast<score_t>(2U) * static_cast<score_t>(count_of(static_cast<std::uint8_t>(2U))));
        }
        case category::threes: {
            return (static_cast<score_t>(3U) * static_cast<score_t>(count_of(static_cast<std::uint8_t>(3U))));
        }
        case category::fours: {
            return (static_cast<score_t>(4U) * static_cast<score_t>(count_of(static_cast<std::uint8_t>(4U))));
        }
        case category::fives: {
            return (static_cast<score_t>(5U) * static_cast<score_t>(count_of(static_cast<std::uint8_t>(5U))));
        }
        case category::sixes: {
            return (static_cast<score_t>(6U) * static_cast<score_t>(count_of(static_cast<std::uint8_t>(6U))));
        }
        case category::full_house: {
            bool has_three = false;
            bool has_two   = false;

            for (std::uint8_t face = static_cast<std::uint8_t>(1U); face <= static_cast<std::uint8_t>(6U); ++face) {
                std::uint8_t const c = count_of(face);
                if (c == static_cast<std::uint8_t>(3U)) {
                    has_three = true;
                } else if (c == static_cast<std::uint8_t>(2U)) {
                    has_two = true;
                }
            }

            if (has_three && has_two) {
                return sum_all;
            } else {
                return static_cast<score_t>(0U);
            }
        }
        case category::four_of_a_kind: {
            for (std::uint8_t face = static_cast<std::uint8_t>(1U); face <= static_cast<std::uint8_t>(6U); ++face) {
                if (count_of(face) >= static_cast<std::uint8_t>(4U)) {
                    return (static_cast<score_t>(4U) * static_cast<score_t>(face));
                }
            }
            return static_cast<score_t>(0U);
        }
        case category::little_straight: {
            bool ok = true;
            for (std::uint8_t face = static_cast<std::uint8_t>(1U); face <= static_cast<std::uint8_t>(5U); ++face) {
                if (count_of(face) != static_cast<std::uint8_t>(1U)) {
                    ok = false;
                }
            }
            if (count_of(static_cast<std::uint8_t>(6U)) != static_cast<std::uint8_t>(0U)) {
                ok = false;
            }
            if (ok) {
                return straight_score;
            } else {
                return static_cast<score_t>(0U);
            }
        }
        case category::big_straight: {
            bool ok = true;
            for (std::uint8_t face = static_cast<std::uint8_t>(2U); face <= static_cast<std::uint8_t>(6U); ++face) {
                if (count_of(face) != static_cast<std::uint8_t>(1U)) {
                    ok = false;
                }
            }
            if (count_of(static_cast<std::uint8_t>(1U)) != static_cast<std::uint8_t>(0U)) {
                ok = false;
            }
            if (ok) {
                return straight_score;
            } else {
                return static_cast<score_t>(0U);
            }
        }
        case category::choice: {
            return sum_all;
        }
        case category::yacht: {
            if (is_yacht) {
                return yacht_score;
            } else {
                return static_cast<score_t>(0U);
            }
        }
        default: {
            return static_cast<score_t>(0U);
        }
    }
}

[[nodiscard]] auto score(dice_t const& dice, char const* cat) noexcept -> score_t
{
    if ((cat == nullptr)) {
        return static_cast<score_t>(0U);
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

}  // namespace yacht
