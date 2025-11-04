#include "yacht.h"
#include <algorithm>
#include <numeric>
#include <string_view>
#include <initializer_list>

namespace yacht {

namespace {

/* Translate lowercase category strings used in the unit tests into the
 * corresponding enumeration value. */
auto to_category(std::string_view cat_str) -> category
{
    if(cat_str == "ones") {
        return category::ones;
    } else if(cat_str == "twos") {
        return category::twos;
    } else if(cat_str == "threes") {
        return category::threes;
    } else if(cat_str == "fours") {
        return category::fours;
    } else if(cat_str == "fives") {
        return category::fives;
    } else if(cat_str == "sixes") {
        return category::sixes;
    } else if(cat_str == "full house") {
        return category::full_house;
    } else if(cat_str == "four of a kind") {
        return category::four_of_a_kind;
    } else if(cat_str == "little straight") {
        return category::little_straight;
    } else if(cat_str == "big straight") {
        return category::big_straight;
    } else if(cat_str == "choice") {
        return category::choice;
    } else { /* "yacht" */
        return category::yacht;
    }
}

}  // unnamed namespace

auto score(std::initializer_list<int> dice_init, std::string_view cat_str) -> std::uint32_t
{
    if(dice_init.size() != 5U) {
        return static_cast<std::uint32_t>(0U);
    }

    std::array<std::uint8_t, 5U> converted{};
    std::size_t idx{0U};
    for(const int value : dice_init) {
        converted[idx] = static_cast<std::uint8_t>(value);
        ++idx;
    }

    const category cat_enum = to_category(cat_str);
    return detail::score(converted, cat_enum);
}

namespace detail {

auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint32_t
{
    /* Count occurrences of each face value (1-6) */
    std::array<std::uint8_t, 7U> counts{};
    for(const std::uint8_t value : dice) {
        /* value expected to be in the range 1-6 */
        ++counts[value];
    }

    const std::uint32_t total =
        std::accumulate(dice.begin(), dice.end(), static_cast<std::uint32_t>(0U));

    switch(cat) {
        case category::ones: {
            return static_cast<std::uint32_t>(counts[1U]) * static_cast<std::uint32_t>(1U);
        }
        case category::twos: {
            return static_cast<std::uint32_t>(counts[2U]) * static_cast<std::uint32_t>(2U);
        }
        case category::threes: {
            return static_cast<std::uint32_t>(counts[3U]) * static_cast<std::uint32_t>(3U);
        }
        case category::fours: {
            return static_cast<std::uint32_t>(counts[4U]) * static_cast<std::uint32_t>(4U);
        }
        case category::fives: {
            return static_cast<std::uint32_t>(counts[5U]) * static_cast<std::uint32_t>(5U);
        }
        case category::sixes: {
            return static_cast<std::uint32_t>(counts[6U]) * static_cast<std::uint32_t>(6U);
        }
        case category::full_house: {
            bool has_three{false};
            bool has_two{false};
            for(std::uint8_t face = 1U; face <= 6U; ++face) {
                if(counts[face] == 3U) {
                    has_three = true;
                } else if(counts[face] == 2U) {
                    has_two = true;
                }
            }
            if(has_three && has_two) {
                return total;
            }
            return static_cast<std::uint32_t>(0U);
        }
        case category::four_of_a_kind: {
            for(std::uint8_t face = 1U; face <= 6U; ++face) {
                if(counts[face] >= 4U) {
                    return static_cast<std::uint32_t>(face) * static_cast<std::uint32_t>(4U);
                }
            }
            return static_cast<std::uint32_t>(0U);
        }
        case category::little_straight: {
            if((counts[1U] == 1U) &&
               (counts[2U] == 1U) &&
               (counts[3U] == 1U) &&
               (counts[4U] == 1U) &&
               (counts[5U] == 1U) &&
               (counts[6U] == 0U)) {
                return static_cast<std::uint32_t>(30U);
            }
            return static_cast<std::uint32_t>(0U);
        }
        case category::big_straight: {
            if((counts[1U] == 0U) &&
               (counts[2U] == 1U) &&
               (counts[3U] == 1U) &&
               (counts[4U] == 1U) &&
               (counts[5U] == 1U) &&
               (counts[6U] == 1U)) {
                return static_cast<std::uint32_t>(30U);
            }
            return static_cast<std::uint32_t>(0U);
        }
        case category::choice: {
            return total;
        }
        case category::yacht: {
            for(std::uint8_t face = 1U; face <= 6U; ++face) {
                if(counts[face] == 5U) {
                    return static_cast<std::uint32_t>(50U);
                }
            }
            return static_cast<std::uint32_t>(0U);
        }
        default: {
            return static_cast<std::uint32_t>(0U);
        }
    }
}

}  // namespace detail
}  // namespace yacht
