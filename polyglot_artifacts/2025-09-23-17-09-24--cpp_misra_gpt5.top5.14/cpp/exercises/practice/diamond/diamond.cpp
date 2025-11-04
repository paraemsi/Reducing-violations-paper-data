#include "diamond.h"

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include <ostream>
#include <istream>
#include <limits>
#include <string_view>
#include <type_traits>
#include <ios>
#include <new>
#include <charconv>
#include <locale>

namespace diamond {

namespace {

// Normalize input to uppercase alphabetic char; return false if not A–Z.
auto normalize_upper_letter(char in, char& out_upper) -> bool
{
    // Use classification; avoid undefined behavior by using locale-aware overloads taking char.
    const bool is_alpha = (std::isalpha(in, std::locale{}) != 0);
    if (!is_alpha) {
        out_upper = '\0';
        return false;
    }

    const char upper_c = std::toupper(in, std::locale{});
    const std::char_traits<char>::int_type upper_int =
        std::char_traits<char>::to_int_type(upper_c);

    const std::char_traits<char>::int_type a_int =
        std::char_traits<char>::to_int_type('A');
    const std::char_traits<char>::int_type z_int =
        std::char_traits<char>::to_int_type('Z');

    const bool in_range = ((upper_int >= a_int) && (upper_int <= z_int));
    if (!in_range) {
        out_upper = '\0';
        return false;
    }

    out_upper = std::char_traits<char>::to_char_type(upper_int);
    return true;
}

}  // namespace

auto make_diamond(char letter) -> std::vector<std::string>
{
    char upper_letter = '\0';
    const bool ok = normalize_upper_letter(letter, upper_letter);
    if (!ok) {
        return {};
    }

    const std::char_traits<char>::int_type upper_int =
        std::char_traits<char>::to_int_type(upper_letter);
    const std::char_traits<char>::int_type a_int =
        std::char_traits<char>::to_int_type('A');

    // offset from 'A' (0 for 'A', 1 for 'B', ...)
    const std::char_traits<char>::int_type diff_int = (upper_int - a_int);
    // Safe: diff_int is guaranteed in [0, 25].
    const std::uint32_t letter_index = static_cast<std::uint32_t>(diff_int);

    const std::size_t n = static_cast<std::size_t>(letter_index);
    const std::size_t width =
        ((n * static_cast<std::size_t>(2U)) + static_cast<std::size_t>(1U));
    const std::size_t height = width;
    const std::size_t mid = (width / static_cast<std::size_t>(2U));

    std::vector<std::string> lines;
    lines.reserve(height);

    // Build top half including middle row.
    for (std::size_t i = static_cast<std::size_t>(0U);
         i <= n;
         i = (i + static_cast<std::size_t>(1U))) {
        // Determine the character for this row: 'A' + i
        const std::char_traits<char>::int_type row_char_int =
            (a_int + static_cast<std::char_traits<char>::int_type>(i));
        const char row_char =
            std::char_traits<char>::to_char_type(row_char_int);

        std::string line(width, ' ');
        const std::size_t left = (mid - i);
        const std::size_t right = (mid + i);

        line[left] = row_char;
        line[right] = row_char;

        lines.push_back(std::move(line));
    }

    // Build bottom half (excluding middle row), descending.
    if (n > static_cast<std::size_t>(0U)) {
        std::size_t i = (n - static_cast<std::size_t>(1U));
        for (;;) {
            const std::char_traits<char>::int_type row_char_int =
                (a_int + static_cast<std::char_traits<char>::int_type>(i));
            const char row_char =
                std::char_traits<char>::to_char_type(row_char_int);

            std::string line(width, ' ');
            const std::size_t left = (mid - i);
            const std::size_t right = (mid + i);

            line[left] = row_char;
            line[right] = row_char;

            lines.push_back(std::move(line));

            if (i == static_cast<std::size_t>(0U)) {
                break;
            }
            i = (i - static_cast<std::size_t>(1U));
        }
    }

    return lines;
}

auto rows(char letter) -> std::vector<std::string>
{
    return make_diamond(letter);
}

auto make_diamond_string(char letter) -> std::string
{
    const std::vector<std::string> lines = make_diamond(letter);
    if (lines.empty()) {
        return std::string{};
    }

    // Reserve approximate size: height * (width + 1 for newline) - 1 (no trailing newline)
    const std::size_t height = lines.size();
    const std::size_t width = lines[static_cast<std::size_t>(0U)].size();
    const std::size_t approx =
        ((height * (width + static_cast<std::size_t>(1U))) - static_cast<std::size_t>(1U));

    std::string out;
    out.reserve(approx);

    for (std::size_t i = static_cast<std::size_t>(0U);
         i < height;
         i = (i + static_cast<std::size_t>(1U))) {
        out.append(lines[i]);
        if (i + static_cast<std::size_t>(1U) < height) {
            out.push_back('\n');
        }
    }

    return out;
}

}  // namespace diamond
