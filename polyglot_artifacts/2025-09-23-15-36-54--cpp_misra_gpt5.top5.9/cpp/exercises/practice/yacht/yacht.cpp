#include "yacht.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <string_view>

namespace yacht {

namespace {
    std::array<std::uint8_t, 7U> build_counts(const std::vector<std::uint8_t>& dice)
    {
        std::array<std::uint8_t, 7U> counts{};  // indices 1..6 used
        for (const std::uint8_t v : dice) {
            if ((v >= static_cast<std::uint8_t>(1U)) && (v <= static_cast<std::uint8_t>(6U))) {
                const std::size_t idx = static_cast<std::size_t>(v);
                counts[idx] = static_cast<std::uint8_t>(counts[idx] + static_cast<std::uint8_t>(1U));
            } else {
                // Out-of-range value ignored by contract; inputs are specified as 1..6
            }
        }
        return counts;
    }
}  // namespace

 // Removed int-based overload to comply with MISRA: use std::uint8_t overload instead.

std::uint16_t score(const std::vector<std::uint8_t>& dice, const char* cat)
{
    const std::string_view name = std::string_view(cat);
    category c = category::choice;
    bool matched = false;

    if ((name == "ones")) { c = category::ones; matched = true; }
    else if ((name == "twos")) { c = category::twos; matched = true; }
    else if ((name == "threes")) { c = category::threes; matched = true; }
    else if ((name == "fours")) { c = category::fours; matched = true; }
    else if ((name == "fives")) { c = category::fives; matched = true; }
    else if ((name == "sixes")) { c = category::sixes; matched = true; }
    else if ((name == "full house")) { c = category::full_house; matched = true; }
    else if ((name == "four of a kind")) { c = category::four_of_a_kind; matched = true; }
    else if ((name == "little straight")) { c = category::little_straight; matched = true; }
    else if ((name == "big straight")) { c = category::big_straight; matched = true; }
    else if ((name == "choice")) { c = category::choice; matched = true; }
    else if ((name == "yacht")) { c = category::yacht; matched = true; }
    else { /* unknown category */ }

    if (matched) {
        return score(dice, c);
    } else {
        return static_cast<std::uint16_t>(0U);
    }
}

std::uint16_t score(const std::vector<std::uint8_t>& dice, category cat)
{
    const std::array<std::uint8_t, 7U> counts = build_counts(dice);

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            const std::uint8_t offset = static_cast<std::uint8_t>(cat);  // 0..5 within these cases
            const std::uint8_t face_u8 = static_cast<std::uint8_t>(static_cast<std::uint16_t>(offset) + static_cast<std::uint16_t>(1U));
            const std::size_t face_idx = static_cast<std::size_t>(face_u8);
            const std::uint16_t result = (static_cast<std::uint16_t>(face_idx) * static_cast<std::uint16_t>(counts[face_idx]));
            return result;
        }
        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (std::size_t face = 1U; face <= 6U; face = face + 1U) {
                if (counts[face] == static_cast<std::uint8_t>(3U)) {
                    has_three = true;
                } else if (counts[face] == static_cast<std::uint8_t>(2U)) {
                    has_two = true;
                } else {
                    // no-op
                }
            }
            if ((has_three) && (has_two)) {
                std::uint16_t total = static_cast<std::uint16_t>(0U);
                for (std::size_t face = 1U; face <= 6U; face = face + 1U) {
                    total = static_cast<std::uint16_t>(total + (static_cast<std::uint16_t>(face) * static_cast<std::uint16_t>(counts[face])));
                }
                return total;
            } else {
                return static_cast<std::uint16_t>(0U);
            }
        }
        case category::four_of_a_kind: {
            for (std::size_t face = 1U; face <= 6U; face = face + 1U) {
                if (counts[face] >= static_cast<std::uint8_t>(4U)) {
                    const std::uint16_t result = (static_cast<std::uint16_t>(4U) * static_cast<std::uint16_t>(face));
                    return result;
                } else {
                    // continue
                }
            }
            return static_cast<std::uint16_t>(0U);
        }
        case category::little_straight: {
            const bool ok =
                (counts[1U] == static_cast<std::uint8_t>(1U)) &&
                (counts[2U] == static_cast<std::uint8_t>(1U)) &&
                (counts[3U] == static_cast<std::uint8_t>(1U)) &&
                (counts[4U] == static_cast<std::uint8_t>(1U)) &&
                (counts[5U] == static_cast<std::uint8_t>(1U)) &&
                (counts[6U] == static_cast<std::uint8_t>(0U));
            if (ok) {
                return static_cast<std::uint16_t>(30U);
            } else {
                return static_cast<std::uint16_t>(0U);
            }
        }
        case category::big_straight: {
            const bool ok =
                (counts[1U] == static_cast<std::uint8_t>(0U)) &&
                (counts[2U] == static_cast<std::uint8_t>(1U)) &&
                (counts[3U] == static_cast<std::uint8_t>(1U)) &&
                (counts[4U] == static_cast<std::uint8_t>(1U)) &&
                (counts[5U] == static_cast<std::uint8_t>(1U)) &&
                (counts[6U] == static_cast<std::uint8_t>(1U));
            if (ok) {
                return static_cast<std::uint16_t>(30U);
            } else {
                return static_cast<std::uint16_t>(0U);
            }
        }
        case category::choice: {
            std::uint16_t total = static_cast<std::uint16_t>(0U);
            for (std::size_t face = 1U; face <= 6U; face = face + 1U) {
                total = static_cast<std::uint16_t>(total + (static_cast<std::uint16_t>(face) * static_cast<std::uint16_t>(counts[face])));
            }
            return total;
        }
        case category::yacht: {
            for (std::size_t face = 1U; face <= 6U; face = face + 1U) {
                if (counts[face] == static_cast<std::uint8_t>(5U)) {
                    return static_cast<std::uint16_t>(50U);
                } else {
                    // continue
                }
            }
            return static_cast<std::uint16_t>(0U);
        }
        default: {
            return static_cast<std::uint16_t>(0U);
        }
    }
}

}  // namespace yacht
