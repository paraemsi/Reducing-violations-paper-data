#include "yacht.h"

#include <array>
#include <numeric>
#include <string_view>

namespace yacht {

/*----------------------------------------------------------
 * Helper : count_faces
 *----------------------------------------------------------
 * Returns an array where index i (0-based) stores the number
 * of occurrences of face value (i + 1) in `dice`.
 *---------------------------------------------------------*/
static auto count_faces(const std::vector<die_t>& dice)
    -> std::array<std::uint16_t, 6U>
{
    std::array<std::uint16_t, 6U> counts{};  // zero-initialised

    for (const die_t die : dice) {
        if ((die >= static_cast<die_t>(1U))
            && (die <= static_cast<die_t>(6U))) {
            const die_t index =
                static_cast<die_t>(die - static_cast<die_t>(1U));
            ++counts[static_cast<std::size_t>(index)];
        }
    }
    return counts;
}

/*----------------------------------------------------------
 * Helper : parse_category
 *----------------------------------------------------------
 * Convert a textual category name into the corresponding
 * enumeration value. Returns true on success.
 *---------------------------------------------------------*/
static auto parse_category(std::string_view name, category& out) -> bool
{
    if (name == "ones") { out = category::ones; }
    else if (name == "twos") { out = category::twos; }
    else if (name == "threes") { out = category::threes; }
    else if (name == "fours") { out = category::fours; }
    else if (name == "fives") { out = category::fives; }
    else if (name == "sixes") { out = category::sixes; }
    else if (name == "full house") { out = category::full_house; }
    else if (name == "four of a kind") { out = category::four_of_a_kind; }
    else if (name == "little straight") { out = category::little_straight; }
    else if (name == "big straight") { out = category::big_straight; }
    else if (name == "choice") { out = category::choice; }
    else if (name == "yacht") { out = category::yacht; }
    else { return false; }

    return true;
}

/*----------------------------------------------------------
 * Public  : score
 *---------------------------------------------------------*/
auto score(const std::vector<die_t>& dice, const category cat)
    -> std::uint32_t
{
    const std::array<std::uint16_t, 6U> counts = count_faces(dice);
    std::uint32_t                      result = static_cast<std::uint32_t>(0U);

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            const die_t face_value =
                static_cast<die_t>(static_cast<die_t>(cat)
                                   + static_cast<die_t>(1U));
            result =
                static_cast<std::uint32_t>(
                    counts[static_cast<std::size_t>(face_value
                                                    - static_cast<die_t>(
                                                        1U))])
                * static_cast<std::uint32_t>(face_value);
            break;
        }

        case category::full_house: {
            bool        has_three = false;
            bool        has_two   = false;
            std::uint32_t sum =
                static_cast<std::uint32_t>(0U);

            for (std::size_t i = 0U; i < counts.size(); ++i) {
                if (counts[i] == static_cast<std::uint16_t>(3U)) {
                    has_three = true;
                } else if (counts[i] == static_cast<std::uint16_t>(2U)) {
                    has_two = true;
                }
                sum += static_cast<std::uint32_t>(counts[i])
                       * static_cast<std::uint32_t>(i + 1U);
            }
            if (has_three && has_two) {
                result = sum;
            }
            break;
        }

        case category::four_of_a_kind: {
            for (std::size_t i = 0U; i < counts.size(); ++i) {
                if (counts[i] >= static_cast<std::uint16_t>(4U)) {
                    result =
                        static_cast<std::uint32_t>(4U)
                        * static_cast<std::uint32_t>(i + 1U);
                    break;
                }
            }
            break;
        }

        case category::little_straight: {
            if ((counts[0U] == static_cast<std::uint16_t>(1U))
                && (counts[1U] == static_cast<std::uint16_t>(1U))
                && (counts[2U] == static_cast<std::uint16_t>(1U))
                && (counts[3U] == static_cast<std::uint16_t>(1U))
                && (counts[4U] == static_cast<std::uint16_t>(1U))
                && (counts[5U] == static_cast<std::uint16_t>(0U))) {
                result = static_cast<std::uint32_t>(30U);
            }
            break;
        }

        case category::big_straight: {
            if ((counts[0U] == static_cast<std::uint16_t>(0U))
                && (counts[1U] == static_cast<std::uint16_t>(1U))
                && (counts[2U] == static_cast<std::uint16_t>(1U))
                && (counts[3U] == static_cast<std::uint16_t>(1U))
                && (counts[4U] == static_cast<std::uint16_t>(1U))
                && (counts[5U] == static_cast<std::uint16_t>(1U))) {
                result = static_cast<std::uint32_t>(30U);
            }
            break;
        }

        case category::choice: {
            for (std::size_t i = 0U; i < counts.size(); ++i) {
                result += static_cast<std::uint32_t>(counts[i])
                          * static_cast<std::uint32_t>(i + 1U);
            }
            break;
        }

        case category::yacht: {
            for (std::size_t i = 0U; i < counts.size(); ++i) {
                if (counts[i] == static_cast<std::uint16_t>(5U)) {
                    result = static_cast<std::uint32_t>(50U);
                    break;
                }
            }
            break;
        }

        default: {
            /* Unknown category -> score remains zero */
            break;
        }
    }

    return result;
}

/*----------------------------------------------------------
 * Overload accepting std::vector<int>
 *---------------------------------------------------------*/
auto score(const std::vector<int>& dice, const category cat) -> std::uint32_t
{
    std::vector<die_t> converted{};
    converted.reserve(dice.size());

    for (const int die : dice) {
        if ((die < 1) || (die > 6)) {
            /* Invalid die value – consistent with base function behaviour     */
            return static_cast<std::uint32_t>(0U);
        }
        converted.push_back(static_cast<die_t>(die));
    }

    return score(converted, cat);
}

/*----------------------------------------------------------
 * Overloads accepting textual category
 *---------------------------------------------------------*/
auto score(const std::vector<die_t>& dice, std::string_view cat_name)
    -> std::uint32_t
{
    category cat_enum{};
    if (!parse_category(cat_name, cat_enum)) {
        return static_cast<std::uint32_t>(0U);
    }
    return score(dice, cat_enum);
}

auto score(const std::vector<int>& dice, std::string_view cat_name)
    -> std::uint32_t
{
    std::vector<die_t> converted{};
    converted.reserve(dice.size());

    for (const int die : dice) {
        if ((die < 1) || (die > 6)) {
            return static_cast<std::uint32_t>(0U);
        }
        converted.push_back(static_cast<die_t>(die));
    }

    return score(converted, cat_name);
}

}  // namespace yacht
