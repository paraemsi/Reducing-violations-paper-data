#include "diamond.h"

#include <cstddef>
#include <cctype>
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> make_diamond(const char letter) noexcept {
    using Traits = std::char_traits<char>;

    // Normalize input: to uppercase if alphabetic; otherwise default to 'A'
    const Traits::int_type li = Traits::to_int_type(letter);
    char normalized = 'A';
    // Convert to unsigned 8-bit to satisfy <cctype> preconditions without using unsigned char
    const std::uint8_t uch = static_cast<std::uint8_t>(li);
    const Traits::int_type uch_i = static_cast<Traits::int_type>(uch);
    if ((std::isalpha(uch_i) != 0)) {
        const Traits::int_type upper = static_cast<Traits::int_type>(std::toupper(uch_i));
        normalized = Traits::to_char_type(upper);
    } else {
        normalized = 'A';
    }

    // Ensure normalized is within 'A'..'Z'; otherwise, default to 'A'
    const Traits::int_type ia = Traits::to_int_type('A');
    const Traits::int_type iz = Traits::to_int_type('Z');
    const Traits::int_type in = Traits::to_int_type(normalized);
    char base_char = 'A';
    if (((in >= ia) && (in <= iz))) {
        base_char = normalized;
    } else {
        base_char = 'A';
    }

    // Compute distance from 'A' as an unsigned width/height parameter
    const Traits::int_type ib = Traits::to_int_type(base_char);
    std::uint32_t distance = 0U;
    if ((ib >= ia)) {
        const std::uint32_t ibu = static_cast<std::uint32_t>(ib);
        const std::uint32_t iau = static_cast<std::uint32_t>(ia);
        distance = (ibu - iau);
    } else {
        distance = 0U;
    }

    const std::uint32_t height = (((distance + 1U) * 2U) - 1U);
    const std::uint32_t width = height;
    const std::uint32_t center = distance;

    std::vector<std::string> top;
    top.reserve(static_cast<std::size_t>(distance + 1U));

    for (std::uint32_t i = 0U; (i <= distance); i += 1U) {
        // Determine the letter for this row
        const Traits::int_type il = (ia + static_cast<Traits::int_type>(i));
        const char row_char = Traits::to_char_type(il);

        // Prepare an empty row filled with spaces
        std::string row(static_cast<std::size_t>(width), ' ');

        // Compute left and right positions for the row's letters
        const std::uint32_t left_u = (center - i);
        const std::uint32_t right_u = (center + i);

        const std::size_t left = static_cast<std::size_t>(left_u);
        const std::size_t right = static_cast<std::size_t>(right_u);

        row[left] = row_char;
        row[right] = row_char;

        top.push_back(row);
    }

    // Build full diamond: top + mirrored bottom (excluding the middle line)
    std::vector<std::string> diamond_lines;
    diamond_lines.reserve(static_cast<std::size_t>(height));

    for (const auto& row : top) {
        diamond_lines.push_back(row);
    }

    std::uint32_t idx = distance;
    while ((idx > 0U)) {
        idx -= 1U;
        diamond_lines.push_back(top[static_cast<std::size_t>(idx)]);
    }

    return diamond_lines;
}

std::vector<std::string> rows(const char letter) noexcept {
    return make_diamond(letter);
}

}  // namespace diamond
