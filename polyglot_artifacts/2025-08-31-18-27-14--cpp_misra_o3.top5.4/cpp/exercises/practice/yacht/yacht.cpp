#include "yacht.h"

#include <algorithm>   // for std::count_if, std::max_element
#include <numeric>     // for std::accumulate
#include <string_view>

namespace yacht {

auto score(const std::array<std::int32_t, 5U>& dice, category cat) -> std::int32_t
{
    std::array<std::uint8_t, 7U> counts {};
    for (const std::int32_t value : dice) {
        /* Every die is guaranteed to be within [1,6] */
        const std::uint8_t face { static_cast<std::uint8_t>(value) };
        ++counts[static_cast<std::size_t>(face)];
    }

    const auto total { std::accumulate(dice.begin(), dice.end(), static_cast<std::int32_t>(0)) };

    switch (cat) {
        case category::ones: {
            return (static_cast<std::int32_t>(1) * static_cast<std::int32_t>(counts[1U]));
        }
        case category::twos: {
            return (static_cast<std::int32_t>(2) * static_cast<std::int32_t>(counts[2U]));
        }
        case category::threes: {
            return (static_cast<std::int32_t>(3) * static_cast<std::int32_t>(counts[3U]));
        }
        case category::fours: {
            return (static_cast<std::int32_t>(4) * static_cast<std::int32_t>(counts[4U]));
        }
        case category::fives: {
            return (static_cast<std::int32_t>(5) * static_cast<std::int32_t>(counts[5U]));
        }
        case category::sixes: {
            return (static_cast<std::int32_t>(6) * static_cast<std::int32_t>(counts[6U]));
        }
        case category::full_house: {
            bool has_three { false };
            bool has_two   { false };
            for (std::uint8_t face { 1U }; face <= 6U; ++face) {
                if (counts[face] == 3U) {
                    has_three = true;
                } else if (counts[face] == 2U) {
                    has_two = true;
                }
            }
            if (has_three && has_two) {
                return total;
            }
            return static_cast<std::int32_t>(0);
        }
        case category::four_of_a_kind: {
            for (std::uint8_t face { 1U }; face <= 6U; ++face) {
                if (counts[face] >= 4U) {
                    return static_cast<std::int32_t>(static_cast<std::uint32_t>(face) * 4U);
                }
            }
            return static_cast<std::int32_t>(0);
        }
        case category::little_straight: {
            const bool straight {
                (counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 0U)
            };
            if (straight) {
                return static_cast<std::int32_t>(30);
            }
            return static_cast<std::int32_t>(0);
        }
        case category::big_straight: {
            const bool straight {
                (counts[1U] == 0U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 1U)
            };
            if (straight) {
                return static_cast<std::int32_t>(30);
            }
            return static_cast<std::int32_t>(0);
        }
        case category::choice: {
            return total;
        }
        case category::yacht: {
            const bool all_same { (*std::max_element(counts.begin() + 1U, counts.end()) == static_cast<std::uint8_t>(5U)) };
            if (all_same) {
                return static_cast<std::int32_t>(50);
            }
            return static_cast<std::int32_t>(0);
        }
        default: {
            /* Defensive: unreachable, but required to silence some compilers */
            return static_cast<std::int32_t>(0);
        }
    }
}

auto to_category(std::string_view name) -> category
{
    if(name == "ones") {
        return category::ones;
    } else if(name == "twos") {
        return category::twos;
    } else if(name == "threes") {
        return category::threes;
    } else if(name == "fours") {
        return category::fours;
    } else if(name == "fives") {
        return category::fives;
    } else if(name == "sixes") {
        return category::sixes;
    } else if(name == "full house") {
        return category::full_house;
    } else if(name == "four of a kind") {
        return category::four_of_a_kind;
    } else if(name == "little straight") {
        return category::little_straight;
    } else if(name == "big straight") {
        return category::big_straight;
    } else if(name == "choice") {
        return category::choice;
    } else { /* default to yacht */
        return category::yacht;
    }
}

auto score(const std::array<std::int32_t, 5U>& dice, std::string_view cat) -> std::int32_t
{
    const category cat_enum { to_category(cat) };
    return score(dice, cat_enum);
}

}  // namespace yacht
