#include "yacht.h"

#include <array>
#include <cstddef>
#include <string_view>

namespace yacht {

[[nodiscard]] auto score(const std::array<std::uint8_t, 5U>& dice, const category cat) -> std::int32_t
{
    /* Count occurrences of each face (1..6) */
    std::array<std::uint8_t, 7U> counts{}; /* index 0 unused */
    for (const std::uint8_t value : dice) {
        ++counts[static_cast<std::size_t>(value)];
    }

    std::int32_t total {0};
    for (const std::uint8_t value : dice) {
        total += static_cast<std::int32_t>(value);
    }

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            const std::uint8_t face {static_cast<std::uint8_t>(cat)};
            return static_cast<std::int32_t>(face) * static_cast<std::int32_t>(counts[face]);
        }

        case category::full_house: {
            bool has_three {false};
            bool has_two {false};
            for (std::uint8_t face {static_cast<std::uint8_t>(1)}; face <= static_cast<std::uint8_t>(6); ++face) {
                if (counts[static_cast<std::size_t>(face)] == static_cast<std::uint8_t>(3)) {
                    has_three = true;
                } else if (counts[static_cast<std::size_t>(face)] == static_cast<std::uint8_t>(2)) {
                    has_two = true;
                }
            }
            if ((has_three) && (has_two)) {
                return total;
            }
            return static_cast<std::int32_t>(0);
        }

        case category::four_of_a_kind: {
            for (std::uint8_t face {static_cast<std::uint8_t>(1)}; face <= static_cast<std::uint8_t>(6); ++face) {
                if (counts[static_cast<std::size_t>(face)] >= static_cast<std::uint8_t>(4)) {
                    return static_cast<std::int32_t>(face) * static_cast<std::int32_t>(4);
                }
            }
            return static_cast<std::int32_t>(0);
        }

        case category::little_straight: {
            const bool is_little {(counts[static_cast<std::size_t>(1)] == static_cast<std::uint8_t>(1)) &&
                                  (counts[static_cast<std::size_t>(2)] == static_cast<std::uint8_t>(1)) &&
                                  (counts[static_cast<std::size_t>(3)] == static_cast<std::uint8_t>(1)) &&
                                  (counts[static_cast<std::size_t>(4)] == static_cast<std::uint8_t>(1)) &&
                                  (counts[static_cast<std::size_t>(5)] == static_cast<std::uint8_t>(1)) &&
                                  (counts[static_cast<std::size_t>(6)] == static_cast<std::uint8_t>(0))};
            return is_little ? static_cast<std::int32_t>(30) : static_cast<std::int32_t>(0);
        }

        case category::big_straight: {
            const bool is_big {(counts[static_cast<std::size_t>(2)] == static_cast<std::uint8_t>(1)) &&
                               (counts[static_cast<std::size_t>(3)] == static_cast<std::uint8_t>(1)) &&
                               (counts[static_cast<std::size_t>(4)] == static_cast<std::uint8_t>(1)) &&
                               (counts[static_cast<std::size_t>(5)] == static_cast<std::uint8_t>(1)) &&
                               (counts[static_cast<std::size_t>(6)] == static_cast<std::uint8_t>(1)) &&
                               (counts[static_cast<std::size_t>(1)] == static_cast<std::uint8_t>(0))};
            return is_big ? static_cast<std::int32_t>(30) : static_cast<std::int32_t>(0);
        }

        case category::choice: {
            return total;
        }

        case category::yacht: {
            for (std::uint8_t face {static_cast<std::uint8_t>(1)}; face <= static_cast<std::uint8_t>(6); ++face) {
                if (counts[static_cast<std::size_t>(face)] == static_cast<std::uint8_t>(5)) {
                    return static_cast<std::int32_t>(50);
                }
            }
            return static_cast<std::int32_t>(0);
        }

        default: {
            return static_cast<std::int32_t>(0);
        }
    }
}

/* Internal helper: map category name used in tests to enum */
namespace {

[[nodiscard]] auto to_category(std::string_view name) -> yacht::category
{
    using yacht::category;
    if (name == "ones") {
        return category::ones;
    }
    if (name == "twos") {
        return category::twos;
    }
    if (name == "threes") {
        return category::threes;
    }
    if (name == "fours") {
        return category::fours;
    }
    if (name == "fives") {
        return category::fives;
    }
    if (name == "sixes") {
        return category::sixes;
    }
    if (name == "full house") {
        return category::full_house;
    }
    if (name == "four of a kind") {
        return category::four_of_a_kind;
    }
    if (name == "little straight") {
        return category::little_straight;
    }
    if (name == "big straight") {
        return category::big_straight;
    }
    if (name == "choice") {
        return category::choice;
    }
    /* default to yacht for any other string (the tests only provide valid names) */
    return category::yacht;
}

}  // namespace

[[nodiscard]] auto score(const std::array<std::uint8_t, 5U>& dice,
                         const std::string_view              cat_name) -> std::int32_t
{
    return score(dice, to_category(cat_name));
}

}  // namespace yacht
