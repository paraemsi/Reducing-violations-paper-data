#include "yacht.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <string_view>

namespace yacht {

auto score(const std::array<std::uint8_t, 5U>& dice, Category category) -> std::uint32_t
{
    std::array<std::uint8_t, 6U> counts {};
    for (std::uint8_t value : dice) {
        if ((value >= static_cast<std::uint8_t>(1U)) && (value <= static_cast<std::uint8_t>(6U))) {
            ++counts[static_cast<std::size_t>(value) - static_cast<std::size_t>(1U)];
        }
    }

    switch (category) {
        case Category::ones:
        case Category::twos:
        case Category::threes:
        case Category::fours:
        case Category::fives:
        case Category::sixes:
        {
            const std::uint8_t face {static_cast<std::uint8_t>(static_cast<std::uint8_t>(category) + static_cast<std::uint8_t>(1U))};
            return static_cast<std::uint32_t>(face) *
                   static_cast<std::uint32_t>(counts[static_cast<std::size_t>(face) - static_cast<std::size_t>(1U)]);
        }

        case Category::full_house:
        {
            bool has_three {false};
            bool has_two {false};
            for (std::uint8_t cnt : counts) {
                if (cnt == static_cast<std::uint8_t>(3U)) {
                    has_three = true;
                } else if (cnt == static_cast<std::uint8_t>(2U)) {
                    has_two = true;
                }
            }
            if (has_three && has_two) {
                return std::accumulate(dice.begin(), dice.end(), static_cast<std::uint32_t>(0U),
                                       [](std::uint32_t sum, std::uint8_t v) { return sum + static_cast<std::uint32_t>(v); });
            }
            return 0U;
        }

        case Category::four_of_a_kind:
        {
            for (std::size_t i {0U}; i < counts.size(); ++i) {
                if (counts[i] >= static_cast<std::uint8_t>(4U)) {
                    const std::uint32_t face {static_cast<std::uint32_t>(i + 1U)};
                    return face * static_cast<std::uint32_t>(4U);
                }
            }
            return 0U;
        }

        case Category::little_straight:
        {
            constexpr std::array<std::uint8_t, 5U> target {1U, 2U, 3U, 4U, 5U};
            auto sorted = dice;  // copy dice values
            std::sort(sorted.begin(), sorted.end());
            if (sorted == target) {
                return 30U;
            }
            return 0U;
        }

        case Category::big_straight:
        {
            constexpr std::array<std::uint8_t, 5U> target {2U, 3U, 4U, 5U, 6U};
            auto sorted = dice;  // copy dice values
            std::sort(sorted.begin(), sorted.end());
            if (sorted == target) {
                return 30U;
            }
            return 0U;
        }

        case Category::choice:
        {
            return std::accumulate(dice.begin(), dice.end(), static_cast<std::uint32_t>(0U),
                                   [](std::uint32_t sum, std::uint8_t v) { return sum + static_cast<std::uint32_t>(v); });
        }

        case Category::yacht:
        {
            for (std::uint8_t cnt : counts) {
                if (cnt == static_cast<std::uint8_t>(5U)) {
                    return 50U;
                }
            }
            return 0U;
        }

        default:
            return 0U;
    }
}

auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view category) -> std::uint32_t
{
    const auto to_category = [](std::string_view s) -> Category {
        if ((s == "ones")) {
            return Category::ones;
        } else if ((s == "twos")) {
            return Category::twos;
        } else if ((s == "threes")) {
            return Category::threes;
        } else if ((s == "fours")) {
            return Category::fours;
        } else if ((s == "fives")) {
            return Category::fives;
        } else if ((s == "sixes")) {
            return Category::sixes;
        } else if ((s == "full house")) {
            return Category::full_house;
        } else if ((s == "four of a kind")) {
            return Category::four_of_a_kind;
        } else if ((s == "little straight")) {
            return Category::little_straight;
        } else if ((s == "big straight")) {
            return Category::big_straight;
        } else if ((s == "choice")) {
            return Category::choice;
        } else if ((s == "yacht")) {
            return Category::yacht;
        } else {
            /* Unknown string: treat as zero-score choice */
            return Category::choice;
        }
    };

    return score(dice, to_category(category));
}

}  // namespace yacht
