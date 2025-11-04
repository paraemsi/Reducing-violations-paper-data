#include "diamond.h"

#include <cstdint>   // fixed-width integers
#include <string>
#include <vector>

namespace {

/* Alphabet used to avoid arithmetic on characters */
constexpr const char* ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/* Convenience alias – width always fits in 32 bits (max 51) */
using width_t = std::uint64_t;

}  // unnamed namespace

namespace diamond {

auto make(char last) -> std::vector<std::string>
{
    /* Locate requested letter without using its numeric value */
    const std::string alphabet{ALPHABET};
    const std::size_t pos = alphabet.find(last);

    if (pos == std::string::npos) {
        /* Not an uppercase letter – return empty result */
        return {};
    }

    const width_t diamond_width =
        (static_cast<width_t>(pos) * static_cast<width_t>(2U)) + static_cast<width_t>(1U);

    std::vector<std::string> top_half;
    top_half.reserve(pos + static_cast<std::size_t>(1U));

    for (std::size_t idx = static_cast<std::size_t>(0U); idx <= pos; ++idx) {
        const char letter = alphabet[idx];

        const width_t leading_spaces =
            static_cast<width_t>(pos - idx); /* safe: idx <= pos */

        width_t inner_spaces = static_cast<width_t>(0U);
        if (idx != static_cast<std::size_t>(0U)) {
            inner_spaces =
                static_cast<width_t>((idx * static_cast<std::size_t>(2U)) - static_cast<std::size_t>(1U));
        }

        std::string row(static_cast<std::size_t>(diamond_width), ' ');

        /* left letter */
        row[static_cast<std::size_t>(leading_spaces)] = letter;

        if (idx != static_cast<std::size_t>(0U)) {
            /* right letter */
            const width_t right_col =
                static_cast<width_t>((leading_spaces + static_cast<width_t>(1U)) + inner_spaces);
            row[static_cast<std::size_t>(right_col)] = letter;
        }

        top_half.emplace_back(row);
    }

    /* Build full diamond – mirror without duplicating the centre row */
    std::vector<std::string> diamond = top_half;

    for (std::size_t rev_idx = pos; rev_idx-- > static_cast<std::size_t>(0U);) {
        diamond.emplace_back(top_half[rev_idx]);
    }

    return diamond;
}

auto rows(char last) -> std::vector<std::string>
{
    /* Wrapper kept for backward-compatibility with tests */
    return make(last);
}

}  // namespace diamond
