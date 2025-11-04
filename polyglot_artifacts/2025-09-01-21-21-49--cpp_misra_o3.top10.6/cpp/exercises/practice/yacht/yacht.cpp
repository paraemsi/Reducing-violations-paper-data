#include "yacht.h"

#include <array>
#include <cstddef>   // for std::size_t
#include <string>
#include <vector>
#include <cstdint>

namespace yacht {

/*  Helper: accumulate face counts and total.                                           */
static void analyse_dice(const std::array<std::uint8_t, 5U>& dice,
                         std::array<std::uint8_t, 7U>& counts,
                         std::uint32_t&                total) noexcept
{
    counts.fill(static_cast<std::uint8_t>(0U));
    total = 0U;

    for (std::uint8_t die : dice) {
        if ((die < static_cast<std::uint8_t>(1U)) || (die > static_cast<std::uint8_t>(6U))) {
            /*  Any illegal die value yields a score of zero for the whole turn.      */
            counts.fill(static_cast<std::uint8_t>(0U));
            total = 0U;
            return;
        }
        ++counts[static_cast<std::size_t>(die)];
        total += die;
    }
}

static auto compute_score(category cat, const std::array<std::uint8_t, 5U>& dice) -> std::uint32_t
{
    std::array<std::uint8_t, 7U> counts{};  /* index 1-6 used */
    std::uint32_t                total{0U};

    analyse_dice(dice, counts, total);

    switch (cat) {
        case category::ones:
            return static_cast<std::uint32_t>(counts[1U]);
        case category::twos:
            return static_cast<std::uint32_t>(2U) * static_cast<std::uint32_t>(counts[2U]);
        case category::threes:
            return static_cast<std::uint32_t>(3U) * static_cast<std::uint32_t>(counts[3U]);
        case category::fours:
            return static_cast<std::uint32_t>(4U) * static_cast<std::uint32_t>(counts[4U]);
        case category::fives:
            return static_cast<std::uint32_t>(5U) * static_cast<std::uint32_t>(counts[5U]);
        case category::sixes:
            return static_cast<std::uint32_t>(6U) * static_cast<std::uint32_t>(counts[6U]);

        case category::full_house: {
            bool has_three{false};
            bool has_two{false};
            for (std::size_t face = 1U; face <= 6U; ++face) {
                if (counts[face] == static_cast<std::uint8_t>(3U)) {
                    has_three = true;
                } else if (counts[face] == static_cast<std::uint8_t>(2U)) {
                    has_two = true;
                }
            }
            return (has_three && has_two) ? total : 0U;
        }

        case category::four_of_a_kind: {
            for (std::size_t face = 1U; face <= 6U; ++face) {
                if (counts[face] >= static_cast<std::uint8_t>(4U)) {
                    return static_cast<std::uint32_t>(face) * static_cast<std::uint32_t>(4U);
                }
            }
            return 0U;
        }

        case category::little_straight:
            return ((counts[1U] == static_cast<std::uint8_t>(1U)) &&
                    (counts[2U] == static_cast<std::uint8_t>(1U)) &&
                    (counts[3U] == static_cast<std::uint8_t>(1U)) &&
                    (counts[4U] == static_cast<std::uint8_t>(1U)) &&
                    (counts[5U] == static_cast<std::uint8_t>(1U)) &&
                    (counts[6U] == static_cast<std::uint8_t>(0U)))
                       ? 30U
                       : 0U;

        case category::big_straight:
            return ((counts[2U] == static_cast<std::uint8_t>(1U)) &&
                    (counts[3U] == static_cast<std::uint8_t>(1U)) &&
                    (counts[4U] == static_cast<std::uint8_t>(1U)) &&
                    (counts[5U] == static_cast<std::uint8_t>(1U)) &&
                    (counts[6U] == static_cast<std::uint8_t>(1U)) &&
                    (counts[1U] == static_cast<std::uint8_t>(0U)))
                       ? 30U
                       : 0U;

        case category::choice:
            return total;

        case category::yacht:
            for (std::size_t face = 1U; face <= 6U; ++face) {
                if (counts[face] == static_cast<std::uint8_t>(5U)) {
                    return 50U;
                }
            }
            return 0U;

        default:
            return 0U;
    }
}

/*  Translate the category string used by the tests into the enumeration value used
 *  internally. Returns category::choice as a harmless default for any unknown text.   */
static category parse_category_string(const std::string& str) noexcept
{
    if (str == "yacht") {
        return category::yacht;
    } else if (str == "four of a kind") {
        return category::four_of_a_kind;
    } else if (str == "full house") {
        return category::full_house;
    } else if (str == "little straight") {
        return category::little_straight;
    } else if (str == "big straight") {
        return category::big_straight;
    } else if (str == "choice") {
        return category::choice;
    } else if (str == "ones") {
        return category::ones;
    } else if (str == "twos") {
        return category::twos;
    } else if (str == "threes") {
        return category::threes;
    } else if (str == "fours") {
        return category::fours;
    } else if (str == "fives") {
        return category::fives;
    } else if (str == "sixes") {
        return category::sixes;
    } else {
        return category::choice;
    }
}

/*  Public interface expected by the unit-tests: dice first, category as text second.  */
auto score(const std::vector<std::int32_t>& dice, const std::string& category_str) -> std::uint32_t
{
    if (dice.size() != 5U) {
        return 0U;
    }

    std::array<std::uint8_t, 5U> dice_arr{};

    for (std::size_t i = 0U; i < 5U; ++i) {
        const std::int32_t val{dice[i]};
        if ((val < 1) || (val > 6)) {
            return 0U;
        }
        dice_arr[i] = static_cast<std::uint8_t>(val);
    }

    const category cat{parse_category_string(category_str)};
    return compute_score(cat, dice_arr);
}

}  // namespace yacht
