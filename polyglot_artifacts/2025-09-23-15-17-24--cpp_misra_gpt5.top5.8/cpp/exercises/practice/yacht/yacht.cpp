#include "yacht.h"

#include <cstddef>
#include <cstdint>
#include <array>
#include <string_view>

namespace yacht {

namespace {
    constexpr auto straight_points() -> std::uint32_t
    {
        return static_cast<std::uint32_t>(30U);
    }

    constexpr auto yacht_points() -> std::uint32_t
    {
        return static_cast<std::uint32_t>(50U);
    }
}  // namespace

auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint32_t
{
    // Tally counts for faces 1..6 (index 0 unused)
    std::array<std::uint8_t, 7U> counts{};
    for (std::uint8_t v : dice) {
        if ((v >= static_cast<std::uint8_t>(1U)) && (v <= static_cast<std::uint8_t>(6U))) {
            counts[static_cast<std::size_t>(v)] =
                static_cast<std::uint8_t>(static_cast<std::uint32_t>(counts[static_cast<std::size_t>(v)]) + static_cast<std::uint32_t>(1U));
        }
    }

    auto sum_dice = [&dice]() -> std::uint32_t {
        std::uint32_t sum{0U};
        for (std::uint8_t v : dice) {
            sum = static_cast<std::uint32_t>(sum + static_cast<std::uint32_t>(v));
        }
        return sum;
    };

    switch (cat) {
        case category::ones: {
            return static_cast<std::uint32_t>(
                static_cast<std::uint32_t>(1U) * static_cast<std::uint32_t>(counts[static_cast<std::size_t>(1U)])
            );
        }
        case category::twos: {
            return static_cast<std::uint32_t>(
                static_cast<std::uint32_t>(2U) * static_cast<std::uint32_t>(counts[static_cast<std::size_t>(2U)])
            );
        }
        case category::threes: {
            return static_cast<std::uint32_t>(
                static_cast<std::uint32_t>(3U) * static_cast<std::uint32_t>(counts[static_cast<std::size_t>(3U)])
            );
        }
        case category::fours: {
            return static_cast<std::uint32_t>(
                static_cast<std::uint32_t>(4U) * static_cast<std::uint32_t>(counts[static_cast<std::size_t>(4U)])
            );
        }
        case category::fives: {
            return static_cast<std::uint32_t>(
                static_cast<std::uint32_t>(5U) * static_cast<std::uint32_t>(counts[static_cast<std::size_t>(5U)])
            );
        }
        case category::sixes: {
            return static_cast<std::uint32_t>(
                static_cast<std::uint32_t>(6U) * static_cast<std::uint32_t>(counts[static_cast<std::size_t>(6U)])
            );
        }
        case category::full_house: {
            bool has_three{false};
            bool has_two{false};
            for (std::uint8_t face = static_cast<std::uint8_t>(1U); face <= static_cast<std::uint8_t>(6U); ++face) {
                const std::uint8_t cnt = counts[static_cast<std::size_t>(face)];
                if (cnt == static_cast<std::uint8_t>(3U)) {
                    has_three = true;
                } else if (cnt == static_cast<std::uint8_t>(2U)) {
                    has_two = true;
                }
            }
            if (has_three && has_two) {
                return sum_dice();
            } else {
                return static_cast<std::uint32_t>(0U);
            }
        }
        case category::four_of_a_kind: {
            for (std::uint8_t face = static_cast<std::uint8_t>(1U); face <= static_cast<std::uint8_t>(6U); ++face) {
                if (counts[static_cast<std::size_t>(face)] >= static_cast<std::uint8_t>(4U)) {
                    const std::uint32_t fv = static_cast<std::uint32_t>(face);
                    return static_cast<std::uint32_t>(fv * static_cast<std::uint32_t>(4U));
                }
            }
            return static_cast<std::uint32_t>(0U);
        }
        case category::little_straight: {
            bool ok{true};
            for (std::uint8_t face = static_cast<std::uint8_t>(1U); face <= static_cast<std::uint8_t>(5U); ++face) {
                if (counts[static_cast<std::size_t>(face)] != static_cast<std::uint8_t>(1U)) {
                    ok = false;
                }
            }
            if (ok) {
                return straight_points();
            } else {
                return static_cast<std::uint32_t>(0U);
            }
        }
        case category::big_straight: {
            bool ok{true};
            for (std::uint8_t face = static_cast<std::uint8_t>(2U); face <= static_cast<std::uint8_t>(6U); ++face) {
                if (counts[static_cast<std::size_t>(face)] != static_cast<std::uint8_t>(1U)) {
                    ok = false;
                }
            }
            if (ok) {
                return straight_points();
            } else {
                return static_cast<std::uint32_t>(0U);
            }
        }
        case category::choice: {
            return sum_dice();
        }
        case category::yacht: {
            for (std::uint8_t face = static_cast<std::uint8_t>(1U); face <= static_cast<std::uint8_t>(6U); ++face) {
                if (counts[static_cast<std::size_t>(face)] == static_cast<std::uint8_t>(5U)) {
                    return yacht_points();
                }
            }
            return static_cast<std::uint32_t>(0U);
        }
        default: {
            return static_cast<std::uint32_t>(0U);
        }
    }
}

auto score(const std::array<std::uint8_t, 5U>& dice, const char* cat) -> std::uint32_t
{
    std::string_view name{(cat != nullptr) ? cat : ""};
    category mapped{};
    if ((name == "ones")) {
        mapped = category::ones;
    } else if ((name == "twos")) {
        mapped = category::twos;
    } else if ((name == "threes")) {
        mapped = category::threes;
    } else if ((name == "fours")) {
        mapped = category::fours;
    } else if ((name == "fives")) {
        mapped = category::fives;
    } else if ((name == "sixes")) {
        mapped = category::sixes;
    } else if ((name == "full house")) {
        mapped = category::full_house;
    } else if ((name == "four of a kind")) {
        mapped = category::four_of_a_kind;
    } else if ((name == "little straight")) {
        mapped = category::little_straight;
    } else if ((name == "big straight")) {
        mapped = category::big_straight;
    } else if ((name == "choice")) {
        mapped = category::choice;
    } else if ((name == "yacht")) {
        mapped = category::yacht;
    } else {
        return static_cast<std::uint32_t>(0U);
    }
    return score(dice, mapped);
}

}  // namespace yacht
