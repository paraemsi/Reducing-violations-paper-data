#include "yacht.h"

#include <array>
#include <cstdint>
#include <vector>
#include <string_view>

namespace yacht {

auto score(const std::array<std::uint8_t, 5U>& dice,
           Category cat) -> std::uint32_t
{
    /* Count occurrences of each face (1-6) */
    std::array<std::uint8_t, 6U> counts{};
    for (std::uint8_t die : dice) {
        /* die is in the range 1-6 per problem statement                    */
        const std::size_t index{static_cast<std::size_t>(die) - 1U};
        ++counts[index];
    }

    switch (cat) {
        case Category::ones:
        {
            return static_cast<std::uint32_t>(counts[0U]);
        }

        case Category::twos:
        {
            return static_cast<std::uint32_t>(2U * counts[1U]);
        }

        case Category::threes:
        {
            return static_cast<std::uint32_t>(3U * counts[2U]);
        }

        case Category::fours:
        {
            return static_cast<std::uint32_t>(4U * counts[3U]);
        }

        case Category::fives:
        {
            return static_cast<std::uint32_t>(5U * counts[4U]);
        }

        case Category::sixes:
        {
            return static_cast<std::uint32_t>(6U * counts[5U]);
        }

        case Category::full_house:
        {
            bool has_three{false};
            bool has_two{false};
            std::uint32_t total{0U};

            for (std::size_t i{0U}; i < 6U; ++i) {
                if (counts[i] == 3U) {
                    has_three = true;
                }
                if (counts[i] == 2U) {
                    has_two = true;
                }
                total += static_cast<std::uint32_t>(((i + 1U)) * counts[i]);
            }

            if (has_three && has_two) {
                return total;
            }
            return 0U;
        }

        case Category::four_of_a_kind:
        {
            for (std::size_t i{0U}; i < 6U; ++i) {
                if (counts[i] >= 4U) {
                    return static_cast<std::uint32_t>(((i + 1U)) * 4U);
                }
            }
            return 0U;
        }

        case Category::little_straight:
        {
            if ((counts[0U] == 1U) && (counts[1U] == 1U) &&
                (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U)) {
                return 30U;
            }
            return 0U;
        }

        case Category::big_straight:
        {
            if ((counts[1U] == 1U) && (counts[2U] == 1U) &&
                (counts[3U] == 1U) && (counts[4U] == 1U) &&
                (counts[5U] == 1U)) {
                return 30U;
            }
            return 0U;
        }

        case Category::choice:
        {
            std::uint32_t total{0U};
            for (std::size_t i{0U}; i < 6U; ++i) {
                total += static_cast<std::uint32_t>(((i + 1U)) * counts[i]);
            }
            return total;
        }

        case Category::yacht:
        {
            for (std::size_t i{0U}; i < 6U; ++i) {
                if (counts[i] == 5U) {
                    return 50U;
                }
            }
            return 0U;
        }

        default:
        {
            /* Defensive default – should never be reached */
            return 0U;
        }
    }
    /* Unreachable, but required to satisfy all control paths */
    return 0;
}

/*  Adapter overload that converts the std::vector interface required by the
 *  tests into the fixed-width, MISRA-compliant implementation above.        */
auto score(const std::vector<int_alias>& dice,
           category cat) -> int_alias
{
    std::array<std::uint8_t, 5U> dice_arr{};

    /*  Exactly five dice are always supplied as per the problem statement   */
    for (std::size_t i{0U}; i < 5U; ++i) {
        dice_arr[i] = static_cast<std::uint8_t>(dice[i]);
    }

    return static_cast<int_alias>(score(dice_arr, cat));
}

/*  Overload accepting a textual category name (required by the tests).      */
auto score(const std::vector<int_alias>& dice,
           const char* category_name) -> int_alias
{
    if(dice.size() != 5U) {
        return 0;
    }

    std::string_view name{category_name};
    Category         cat_enum{Category::yacht};   /* default initial value   */

    if(name == "ones") {
        cat_enum = Category::ones;
    } else if(name == "twos") {
        cat_enum = Category::twos;
    } else if(name == "threes") {
        cat_enum = Category::threes;
    } else if(name == "fours") {
        cat_enum = Category::fours;
    } else if(name == "fives") {
        cat_enum = Category::fives;
    } else if(name == "sixes") {
        cat_enum = Category::sixes;
    } else if(name == "full house") {
        cat_enum = Category::full_house;
    } else if(name == "four of a kind") {
        cat_enum = Category::four_of_a_kind;
    } else if(name == "little straight") {
        cat_enum = Category::little_straight;
    } else if(name == "big straight") {
        cat_enum = Category::big_straight;
    } else if(name == "choice") {
        cat_enum = Category::choice;
    } else if(name == "yacht") {
        cat_enum = Category::yacht;
    } else {
        /*  Unknown category name                                            */
        return 0;
    }

    return score(dice, cat_enum);
}

}  // namespace yacht
