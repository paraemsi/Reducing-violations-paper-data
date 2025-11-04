#include "yacht.h"

#include <array>
#include <cstdint>
#include <cstddef>
#include <string_view>

namespace yacht {

/*---------------------------------------------------------------------------*/
/* Helper to translate a textual category name into the corresponding enum.  */
/*---------------------------------------------------------------------------*/
static auto to_category(const std::string_view name) noexcept -> category
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
    } else if (name == "yacht") {
        return category::yacht;
    } else {
        /* Defensive default – the test-suite only provides valid names. */
        return category::choice;
    }
}

auto score(const std::array<std::uint8_t, 5U>& dice,
           const category                      cat) noexcept -> std::uint32_t
{
    // Frequency table: indices 1-6 hold the occurrence count
    std::array<std::uint8_t, 7U> counts{};

    std::uint32_t total {0U};

    for (const std::uint8_t die : dice) {
        const std::size_t idx = static_cast<std::size_t>(die);
        ++counts[idx];
        total += static_cast<std::uint32_t>(die);
    }

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            const std::uint8_t face =
                static_cast<std::uint8_t>(static_cast<std::uint8_t>(cat) + 1U);
            return (static_cast<std::uint32_t>(counts[face]) *
                    static_cast<std::uint32_t>(face));
        }

        case category::full_house: {
            std::uint8_t triple_face {0U};
            std::uint8_t pair_face   {0U};

            for (std::uint8_t face = 1U; face <= 6U; ++face) {
                if (counts[face] == 3U) {
                    triple_face = face;
                } else if (counts[face] == 2U) {
                    pair_face = face;
                }
            }

            if ((triple_face != 0U) && (pair_face != 0U)) {
                return total;
            }

            return 0U;
        }

        case category::four_of_a_kind: {
            for (std::uint8_t face = 1U; face <= 6U; ++face) {
                if (counts[face] >= 4U) {
                    return (static_cast<std::uint32_t>(face) * 4U);
                }
            }
            return 0U;
        }

        case category::little_straight: {
            if ((counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 0U)) {
                return 30U;
            }
            return 0U;
        }

        case category::big_straight: {
            if ((counts[1U] == 0U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 1U)) {
                return 30U;
            }
            return 0U;
        }

        case category::choice: {
            return total;
        }

        case category::yacht: {
            for (std::uint8_t face = 1U; face <= 6U; ++face) {
                if (counts[face] == 5U) {
                    return 50U;
                }
            }
            return 0U;
        }

        default: {
            return 0U;  // Defensive: unreachable with current enum list
        }
    }
}

/*---------------------------------------------------------------------------*/
/* Overload that accepts a textual category.                                  */
/*---------------------------------------------------------------------------*/
auto score(const std::array<std::uint8_t, 5U>& dice,
           const std::string_view               cat_name) noexcept -> std::uint32_t
{
    const category cat_enum = to_category(cat_name);
    return score(dice, cat_enum);
}

}  // namespace yacht
