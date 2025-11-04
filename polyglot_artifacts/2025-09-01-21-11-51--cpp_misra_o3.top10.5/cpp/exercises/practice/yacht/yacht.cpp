#include "yacht.h"

#include <array>
#include <algorithm>
#include <numeric>
#include <string_view>

namespace yacht {

namespace {

// Helper to sum all dice that match a given face value
auto total_of_face(dice_array const& dice, std::uint8_t face) -> std::int32_t
{
    return std::accumulate(
        dice.begin(),
        dice.end(),
        std::int32_t{0},
        [face](std::int32_t acc, std::uint8_t value) -> std::int32_t {
            return (acc + ((value == face) ? static_cast<std::int32_t>(value) : 0));
        });
}

auto to_category(std::string_view str) -> category
{
    if (str == "ones")            { return category::ones; }
    if (str == "twos")            { return category::twos; }
    if (str == "threes")          { return category::threes; }
    if (str == "fours")           { return category::fours; }
    if (str == "fives")           { return category::fives; }
    if (str == "sixes")           { return category::sixes; }
    if (str == "full house")      { return category::full_house; }
    if (str == "four of a kind")  { return category::four_of_a_kind; }
    if (str == "little straight") { return category::little_straight; }
    if (str == "big straight")    { return category::big_straight; }
    if (str == "choice")          { return category::choice; }
    if (str == "yacht")           { return category::yacht; }

    /* Fallback: treat unknown text as choice */
    return category::choice;
}

}  // namespace

auto score(dice_array const& dice, category cat) -> std::int32_t
{
    std::array<std::uint8_t, 7U> counts{};  // index 0 unused
    for (std::uint8_t v : dice) {
        ++counts[static_cast<std::size_t>(v)];
    }

    switch (cat) {
        case category::ones: {
            return total_of_face(dice, static_cast<std::uint8_t>(1U));
        }
        case category::twos: {
            return total_of_face(dice, static_cast<std::uint8_t>(2U));
        }
        case category::threes: {
            return total_of_face(dice, static_cast<std::uint8_t>(3U));
        }
        case category::fours: {
            return total_of_face(dice, static_cast<std::uint8_t>(4U));
        }
        case category::fives: {
            return total_of_face(dice, static_cast<std::uint8_t>(5U));
        }
        case category::sixes: {
            return total_of_face(dice, static_cast<std::uint8_t>(6U));
        }
        case category::full_house: {
            bool has_three{false};
            bool has_two{false};
            std::int32_t sum{0};

            for (std::size_t face{1U}; face <= 6U; ++face) {
                if (counts[face] == 3U) {
                    has_three = true;
                } else if (counts[face] == 2U) {
                    has_two = true;
                }
                sum = (sum + static_cast<std::int32_t>(face) *
                             static_cast<std::int32_t>(counts[face]));
            }

            if (has_three && has_two) {
                return sum;
            }
            return 0;
        }
        case category::four_of_a_kind: {
            for (std::size_t face{1U}; face <= 6U; ++face) {
                if (counts[face] >= 4U) {
                    return static_cast<std::int32_t>(face) * static_cast<std::int32_t>(4);
                }
            }
            return 0;
        }
        case category::little_straight: {
            bool is_match{true};
            for (std::size_t face{1U}; face <= 5U; ++face) {
                if (counts[face] != 1U) {
                    is_match = false;
                }
            }
            if ((is_match) && (counts[static_cast<std::size_t>(6U)] == static_cast<std::uint8_t>(0U))) {
                return 30;
            }
            return 0;
        }
        case category::big_straight: {
            bool is_match{true};
            for (std::size_t face{2U}; face <= 6U; ++face) {
                if (counts[face] != 1U) {
                    is_match = false;
                }
            }
            if ((is_match) && (counts[static_cast<std::size_t>(1U)] == static_cast<std::uint8_t>(0U))) {
                return 30;
            }
            return 0;
        }
        case category::choice: {
            return std::accumulate(
                dice.begin(),
                dice.end(),
                std::int32_t{0},
                [](std::int32_t acc, std::uint8_t v) -> std::int32_t {
                    return (acc + static_cast<std::int32_t>(v));
                });
        }
        case category::yacht: {
            if (counts[static_cast<std::size_t>(dice.front())] == static_cast<std::uint8_t>(5U)) {
                return 50;
            }
            return 0;
        }
        default: {
            return 0;
        }
    }
}

auto score(dice_array const& dice, std::string_view cat) -> std::int32_t
{
    return score(dice, to_category(cat));
}

auto score(dice_array const& dice, char const* cat) -> std::int32_t
{
    return score(dice, std::string_view{cat});
}

}  // namespace yacht
