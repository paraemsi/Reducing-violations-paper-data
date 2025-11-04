#include "yacht.h"

#include <array>
#include <cstdint>
#include <string_view>
#include <numeric>
#include <type_traits>

namespace yacht {

score_t score(const std::array<die_t, 5U>& dice, category cat)
{
    std::array<std::uint8_t, 6U> counts {};
    counts.fill(static_cast<std::uint8_t>(0U));

    for (die_t d : dice) {
        /* valid dice values are 1..6 inclusive */
        if ((d >= static_cast<die_t>(1U)) && (d <= static_cast<die_t>(6U))) {
            const std::size_t idx =
                static_cast<std::size_t>(static_cast<std::uint8_t>(d) - static_cast<std::uint8_t>(1U));
            ++counts[idx];
        } else {
            /* invalid die value yields zero score */
            return static_cast<score_t>(0U);
        }
    }

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes:
        {
            const die_t face = static_cast<die_t>(static_cast<std::uint8_t>(cat) + static_cast<std::uint8_t>(1U));
            return (static_cast<score_t>(face) *
                    static_cast<score_t>(counts[static_cast<std::size_t>(face - static_cast<die_t>(1U))]));
        }

        case category::full_house:
        {
            bool has_three = false;
            bool has_two   = false;

            for (std::uint8_t cnt : counts) {
                if (cnt == static_cast<std::uint8_t>(3U)) {
                    has_three = true;
                } else if (cnt == static_cast<std::uint8_t>(2U)) {
                    has_two = true;
                }
            }

            if (has_three && has_two) {
                score_t total = static_cast<score_t>(0U);
                for (die_t d : dice) {
                    total += static_cast<score_t>(d);
                }
                return total;
            }
            return static_cast<score_t>(0U);
        }

        case category::four_of_a_kind:
        {
            for (std::size_t i = 0U; i < counts.size(); ++i) {
                if (counts[i] >= static_cast<std::uint8_t>(4U)) {
                    const score_t face_value = static_cast<score_t>(i + 1U);
                    return (face_value * static_cast<score_t>(4U));
                }
            }
            return static_cast<score_t>(0U);
        }

        case category::little_straight:
        {
            if ((counts[0U] == static_cast<std::uint8_t>(1U)) &&
                (counts[1U] == static_cast<std::uint8_t>(1U)) &&
                (counts[2U] == static_cast<std::uint8_t>(1U)) &&
                (counts[3U] == static_cast<std::uint8_t>(1U)) &&
                (counts[4U] == static_cast<std::uint8_t>(1U)) &&
                (counts[5U] == static_cast<std::uint8_t>(0U))) {
                return static_cast<score_t>(30U);
            }
            return static_cast<score_t>(0U);
        }

        case category::big_straight:
        {
            if ((counts[0U] == static_cast<std::uint8_t>(0U)) &&
                (counts[1U] == static_cast<std::uint8_t>(1U)) &&
                (counts[2U] == static_cast<std::uint8_t>(1U)) &&
                (counts[3U] == static_cast<std::uint8_t>(1U)) &&
                (counts[4U] == static_cast<std::uint8_t>(1U)) &&
                (counts[5U] == static_cast<std::uint8_t>(1U))) {
                return static_cast<score_t>(30U);
            }
            return static_cast<score_t>(0U);
        }

        case category::choice:
        {
            score_t total = static_cast<score_t>(0U);
            for (die_t d : dice) {
                total += static_cast<score_t>(d);
            }
            return total;
        }

        case category::yacht:
        {
            for (std::uint8_t cnt : counts) {
                if (cnt == static_cast<std::uint8_t>(5U)) {
                    return static_cast<score_t>(50U);
                }
            }
            return static_cast<score_t>(0U);
        }

        default:
        {
            /* Should not reach here */
            return static_cast<score_t>(0U);
        }
    }
}



[[nodiscard]] score_t score(const std::array<die_t, 5U>& dice, std::string_view category_name)
{
    if (category_name == std::string_view {"ones"}) {
        return score(dice, category::ones);
    } else if (category_name == std::string_view {"twos"}) {
        return score(dice, category::twos);
    } else if (category_name == std::string_view {"threes"}) {
        return score(dice, category::threes);
    } else if (category_name == std::string_view {"fours"}) {
        return score(dice, category::fours);
    } else if (category_name == std::string_view {"fives"}) {
        return score(dice, category::fives);
    } else if (category_name == std::string_view {"sixes"}) {
        return score(dice, category::sixes);
    } else if (category_name == std::string_view {"full house"}) {
        return score(dice, category::full_house);
    } else if (category_name == std::string_view {"four of a kind"}) {
        return score(dice, category::four_of_a_kind);
    } else if (category_name == std::string_view {"little straight"}) {
        return score(dice, category::little_straight);
    } else if (category_name == std::string_view {"big straight"}) {
        return score(dice, category::big_straight);
    } else if (category_name == std::string_view {"choice"}) {
        return score(dice, category::choice);
    } else if (category_name == std::string_view {"yacht"}) {
        return score(dice, category::yacht);
    }

    return static_cast<score_t>(0U);
}

}  // namespace yacht
