#include "yacht.h"

#include <array>
#include <numeric>
#include <string_view>

namespace yacht {

auto score(const std::vector<std::uint8_t> & dice, category cat) -> std::uint32_t
{
    constexpr std::uint8_t faces{6U};

    /* Count occurrences of each face (index 0 unused) */
    std::array<std::uint8_t, faces + 1U> counts{};
    for (const std::uint8_t die : dice) {
        counts[static_cast<std::size_t>(die)] =
            static_cast<std::uint8_t>(counts[static_cast<std::size_t>(die)] + static_cast<std::uint8_t>(1U));
    }

    const std::uint32_t sum_of_dice =
        std::accumulate(dice.begin(), dice.end(), static_cast<std::uint32_t>(0U),
            [](std::uint32_t acc, std::uint8_t v) { return static_cast<std::uint32_t>(acc + v); });

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            const std::uint8_t face_value =
                static_cast<std::uint8_t>(static_cast<std::uint8_t>(cat) + static_cast<std::uint8_t>(1U));
            return static_cast<std::uint32_t>(counts[face_value]) *
                   static_cast<std::uint32_t>(face_value);
        }

        case category::full_house: {
            std::uint8_t triple_face{0U};
            std::uint8_t pair_face{0U};

            for (std::uint8_t face{1U}; face <= faces; ++face) {
                if (counts[face] == static_cast<std::uint8_t>(3U)) {
                    triple_face = face;
                } else if (counts[face] == static_cast<std::uint8_t>(2U)) {
                    pair_face = face;
                }
            }

            if ((triple_face != static_cast<std::uint8_t>(0U)) &&
                (pair_face != static_cast<std::uint8_t>(0U))) {
                return sum_of_dice;
            }
            return static_cast<std::uint32_t>(0U);
        }

        case category::four_of_a_kind: {
            for (std::uint8_t face{1U}; face <= faces; ++face) {
                if (counts[face] >= static_cast<std::uint8_t>(4U)) {
                    return static_cast<std::uint32_t>(face) *
                           static_cast<std::uint32_t>(4U);
                }
            }
            return static_cast<std::uint32_t>(0U);
        }

        case category::little_straight: {
            const bool is_little_straight =
                (counts[1U] == static_cast<std::uint8_t>(1U)) &&
                (counts[2U] == static_cast<std::uint8_t>(1U)) &&
                (counts[3U] == static_cast<std::uint8_t>(1U)) &&
                (counts[4U] == static_cast<std::uint8_t>(1U)) &&
                (counts[5U] == static_cast<std::uint8_t>(1U)) &&
                (counts[6U] == static_cast<std::uint8_t>(0U));
            return is_little_straight ? static_cast<std::uint32_t>(30U)
                                      : static_cast<std::uint32_t>(0U);
        }

        case category::big_straight: {
            const bool is_big_straight =
                (counts[1U] == static_cast<std::uint8_t>(0U)) &&
                (counts[2U] == static_cast<std::uint8_t>(1U)) &&
                (counts[3U] == static_cast<std::uint8_t>(1U)) &&
                (counts[4U] == static_cast<std::uint8_t>(1U)) &&
                (counts[5U] == static_cast<std::uint8_t>(1U)) &&
                (counts[6U] == static_cast<std::uint8_t>(1U));
            return is_big_straight ? static_cast<std::uint32_t>(30U)
                                   : static_cast<std::uint32_t>(0U);
        }

        case category::choice: {
            return sum_of_dice;
        }

        case category::yacht: {
            for (std::uint8_t face{1U}; face <= faces; ++face) {
                if (counts[face] == static_cast<std::uint8_t>(5U)) {
                    return static_cast<std::uint32_t>(50U);
                }
            }
            return static_cast<std::uint32_t>(0U);
        }

        default:
            return static_cast<std::uint32_t>(0U);
    }
}

/* overload converting textual category name to enum and forwarding */
auto score(const std::vector<std::uint8_t> & dice, std::string_view cat_name) -> std::uint32_t
{
    category cat{category::choice};

    if (cat_name == std::string_view{"ones"}) {
        cat = category::ones;
    } else if (cat_name == std::string_view{"twos"}) {
        cat = category::twos;
    } else if (cat_name == std::string_view{"threes"}) {
        cat = category::threes;
    } else if (cat_name == std::string_view{"fours"}) {
        cat = category::fours;
    } else if (cat_name == std::string_view{"fives"}) {
        cat = category::fives;
    } else if (cat_name == std::string_view{"sixes"}) {
        cat = category::sixes;
    } else if (cat_name == std::string_view{"full house"}) {
        cat = category::full_house;
    } else if (cat_name == std::string_view{"four of a kind"}) {
        cat = category::four_of_a_kind;
    } else if (cat_name == std::string_view{"little straight"}) {
        cat = category::little_straight;
    } else if (cat_name == std::string_view{"big straight"}) {
        cat = category::big_straight;
    } else if (cat_name == std::string_view{"choice"}) {
        cat = category::choice;
    } else if (cat_name == std::string_view{"yacht"}) {
        cat = category::yacht;
    } else {
        return static_cast<std::uint32_t>(0U); /* Unknown category name */
    }

    return score(dice, cat);
}

}  // namespace yacht
