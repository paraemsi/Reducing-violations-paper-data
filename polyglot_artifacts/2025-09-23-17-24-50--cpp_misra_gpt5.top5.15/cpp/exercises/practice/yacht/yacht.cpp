#include "yacht.h"

#include <array>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <initializer_list>

namespace yacht {

static auto sum_dice(const std::array<std::uint8_t, 5U>& dice) -> std::uint32_t
{
    std::uint32_t s = static_cast<std::uint32_t>(0U);
    for (std::uint8_t v : dice) {
        s = (s + static_cast<std::uint32_t>(v));
    }
    return s;
}

auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint32_t
{
    std::array<std::uint32_t, 7U> counts{};
    for (std::uint8_t v : dice) {
        if ((v >= static_cast<std::uint8_t>(1U)) && (v <= static_cast<std::uint8_t>(6U))) {
            const std::size_t idx = static_cast<std::size_t>(v);
            counts[idx] = (counts[idx] + static_cast<std::uint32_t>(1U));
        } else {
            // Out-of-range value: Ignore for scoring; counts unchanged.
        }
    }

    switch (cat) {
        case category::ones: {
            return (static_cast<std::uint32_t>(1U) * static_cast<std::uint32_t>(counts[static_cast<std::size_t>(1U)]));
        }
        case category::twos: {
            return (static_cast<std::uint32_t>(2U) * static_cast<std::uint32_t>(counts[static_cast<std::size_t>(2U)]));
        }
        case category::threes: {
            return (static_cast<std::uint32_t>(3U) * static_cast<std::uint32_t>(counts[static_cast<std::size_t>(3U)]));
        }
        case category::fours: {
            return (static_cast<std::uint32_t>(4U) * static_cast<std::uint32_t>(counts[static_cast<std::size_t>(4U)]));
        }
        case category::fives: {
            return (static_cast<std::uint32_t>(5U) * static_cast<std::uint32_t>(counts[static_cast<std::size_t>(5U)]));
        }
        case category::sixes: {
            return (static_cast<std::uint32_t>(6U) * static_cast<std::uint32_t>(counts[static_cast<std::size_t>(6U)]));
        }
        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (std::uint8_t face = static_cast<std::uint8_t>(1U); face <= static_cast<std::uint8_t>(6U); ++face) {
                if ((counts[static_cast<std::size_t>(face)] == static_cast<std::uint32_t>(3U))) {
                    has_three = true;
                } else if ((counts[static_cast<std::size_t>(face)] == static_cast<std::uint32_t>(2U))) {
                    has_two = true;
                }
            }
            if ((has_three) && (has_two)) {
                return sum_dice(dice);
            } else {
                return static_cast<std::uint32_t>(0U);
            }
        }
        case category::four_of_a_kind: {
            for (std::uint8_t face = static_cast<std::uint8_t>(1U); face <= static_cast<std::uint8_t>(6U); ++face) {
                if ((counts[static_cast<std::size_t>(face)] >= static_cast<std::uint32_t>(4U))) {
                    return (static_cast<std::uint32_t>(4U) * static_cast<std::uint32_t>(face));
                }
            }
            return static_cast<std::uint32_t>(0U);
        }
        case category::little_straight: {
            bool ok = true;
            for (std::uint8_t face = static_cast<std::uint8_t>(1U); face <= static_cast<std::uint8_t>(5U); ++face) {
                if (!(counts[static_cast<std::size_t>(face)] == static_cast<std::uint32_t>(1U))) {
                    ok = false;
                }
            }
            if ((ok) && (counts[static_cast<std::size_t>(6U)] == static_cast<std::uint32_t>(0U))) {
                return static_cast<std::uint32_t>(30U);
            } else {
                return static_cast<std::uint32_t>(0U);
            }
        }
        case category::big_straight: {
            bool ok = true;
            for (std::uint8_t face = static_cast<std::uint8_t>(2U); face <= static_cast<std::uint8_t>(6U); ++face) {
                if (!(counts[static_cast<std::size_t>(face)] == static_cast<std::uint32_t>(1U))) {
                    ok = false;
                }
            }
            if ((ok) && (counts[static_cast<std::size_t>(1U)] == static_cast<std::uint32_t>(0U))) {
                return static_cast<std::uint32_t>(30U);
            } else {
                return static_cast<std::uint32_t>(0U);
            }
        }
        case category::choice: {
            return sum_dice(dice);
        }
        case category::yacht: {
            for (std::uint8_t face = static_cast<std::uint8_t>(1U); face <= static_cast<std::uint8_t>(6U); ++face) {
                if ((counts[static_cast<std::size_t>(face)] == static_cast<std::uint32_t>(5U))) {
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

auto score(const std::array<std::uint8_t, 5U>& dice, const char* cat) -> std::uint32_t
{
    if ((cat == nullptr)) {
        return static_cast<std::uint32_t>(0U);
    }

    category mapped = category::choice;

    if ((std::strcmp(cat, "ones") == 0)) {
        mapped = category::ones;
    } else if ((std::strcmp(cat, "twos") == 0)) {
        mapped = category::twos;
    } else if ((std::strcmp(cat, "threes") == 0)) {
        mapped = category::threes;
    } else if ((std::strcmp(cat, "fours") == 0)) {
        mapped = category::fours;
    } else if ((std::strcmp(cat, "fives") == 0)) {
        mapped = category::fives;
    } else if ((std::strcmp(cat, "sixes") == 0)) {
        mapped = category::sixes;
    } else if ((std::strcmp(cat, "full house") == 0)) {
        mapped = category::full_house;
    } else if ((std::strcmp(cat, "four of a kind") == 0)) {
        mapped = category::four_of_a_kind;
    } else if ((std::strcmp(cat, "little straight") == 0)) {
        mapped = category::little_straight;
    } else if ((std::strcmp(cat, "big straight") == 0)) {
        mapped = category::big_straight;
    } else if ((std::strcmp(cat, "choice") == 0)) {
        mapped = category::choice;
    } else if ((std::strcmp(cat, "yacht") == 0)) {
        mapped = category::yacht;
    } else {
        return static_cast<std::uint32_t>(0U);
    }

    return score(dice, mapped);
}

auto score(std::initializer_list<std::uint8_t> dice, const char* cat) -> std::uint32_t
{
    if ((cat == nullptr)) {
        return static_cast<std::uint32_t>(0U);
    }
    if (!(dice.size() == static_cast<std::size_t>(5U))) {
        return static_cast<std::uint32_t>(0U);
    }

    category mapped = category::choice;

    if ((std::strcmp(cat, "ones") == 0)) {
        mapped = category::ones;
    } else if ((std::strcmp(cat, "twos") == 0)) {
        mapped = category::twos;
    } else if ((std::strcmp(cat, "threes") == 0)) {
        mapped = category::threes;
    } else if ((std::strcmp(cat, "fours") == 0)) {
        mapped = category::fours;
    } else if ((std::strcmp(cat, "fives") == 0)) {
        mapped = category::fives;
    } else if ((std::strcmp(cat, "sixes") == 0)) {
        mapped = category::sixes;
    } else if ((std::strcmp(cat, "full house") == 0)) {
        mapped = category::full_house;
    } else if ((std::strcmp(cat, "four of a kind") == 0)) {
        mapped = category::four_of_a_kind;
    } else if ((std::strcmp(cat, "little straight") == 0)) {
        mapped = category::little_straight;
    } else if ((std::strcmp(cat, "big straight") == 0)) {
        mapped = category::big_straight;
    } else if ((std::strcmp(cat, "choice") == 0)) {
        mapped = category::choice;
    } else if ((std::strcmp(cat, "yacht") == 0)) {
        mapped = category::yacht;
    } else {
        return static_cast<std::uint32_t>(0U);
    }

    std::array<std::uint32_t, 7U> counts{};
    std::uint32_t s = static_cast<std::uint32_t>(0U);
    for (std::uint8_t v : dice) {
        if ((v >= static_cast<std::uint8_t>(1U)) && (v <= static_cast<std::uint8_t>(6U))) {
            const std::size_t idx = static_cast<std::size_t>(v);
            counts[idx] = (counts[idx] + static_cast<std::uint32_t>(1U));
            s = (s + static_cast<std::uint32_t>(v));
        } else {
            // Out-of-range value: Ignore for scoring; counts and sum unchanged.
        }
    }

    switch (mapped) {
        case category::ones: {
            return (static_cast<std::uint32_t>(1U) * counts[static_cast<std::size_t>(1U)]);
        }
        case category::twos: {
            return (static_cast<std::uint32_t>(2U) * counts[static_cast<std::size_t>(2U)]);
        }
        case category::threes: {
            return (static_cast<std::uint32_t>(3U) * counts[static_cast<std::size_t>(3U)]);
        }
        case category::fours: {
            return (static_cast<std::uint32_t>(4U) * counts[static_cast<std::size_t>(4U)]);
        }
        case category::fives: {
            return (static_cast<std::uint32_t>(5U) * counts[static_cast<std::size_t>(5U)]);
        }
        case category::sixes: {
            return (static_cast<std::uint32_t>(6U) * counts[static_cast<std::size_t>(6U)]);
        }
        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (std::uint32_t face = static_cast<std::uint32_t>(1U); face <= static_cast<std::uint32_t>(6U); ++face) {
                if ((counts[static_cast<std::size_t>(face)] == static_cast<std::uint32_t>(3U))) {
                    has_three = true;
                } else if ((counts[static_cast<std::size_t>(face)] == static_cast<std::uint32_t>(2U))) {
                    has_two = true;
                }
            }
            if ((has_three) && (has_two)) {
                return s;
            } else {
                return static_cast<std::uint32_t>(0U);
            }
        }
        case category::four_of_a_kind: {
            for (std::uint32_t face = static_cast<std::uint32_t>(1U); face <= static_cast<std::uint32_t>(6U); ++face) {
                if ((counts[static_cast<std::size_t>(face)] >= static_cast<std::uint32_t>(4U))) {
                    return (static_cast<std::uint32_t>(4U) * face);
                }
            }
            return static_cast<std::uint32_t>(0U);
        }
        case category::little_straight: {
            bool ok = true;
            for (std::uint32_t face = static_cast<std::uint32_t>(1U); face <= static_cast<std::uint32_t>(5U); ++face) {
                if (!(counts[static_cast<std::size_t>(face)] == static_cast<std::uint32_t>(1U))) {
                    ok = false;
                }
            }
            if ((ok) && (counts[static_cast<std::size_t>(6U)] == static_cast<std::uint32_t>(0U))) {
                return static_cast<std::uint32_t>(30U);
            } else {
                return static_cast<std::uint32_t>(0U);
            }
        }
        case category::big_straight: {
            bool ok = true;
            for (std::uint32_t face = static_cast<std::uint32_t>(2U); face <= static_cast<std::uint32_t>(6U); ++face) {
                if (!(counts[static_cast<std::size_t>(face)] == static_cast<std::uint32_t>(1U))) {
                    ok = false;
                }
            }
            if ((ok) && (counts[static_cast<std::size_t>(1U)] == static_cast<std::uint32_t>(0U))) {
                return static_cast<std::uint32_t>(30U);
            } else {
                return static_cast<std::uint32_t>(0U);
            }
        }
        case category::choice: {
            return s;
        }
        case category::yacht: {
            for (std::uint32_t face = static_cast<std::uint32_t>(1U); face <= static_cast<std::uint32_t>(6U); ++face) {
                if ((counts[static_cast<std::size_t>(face)] == static_cast<std::uint32_t>(5U))) {
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

}  // namespace yacht
