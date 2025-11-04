#include "diamond.h"

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace diamond {

namespace {

/*
 * Return a string consisting of `count` copies of character `ch`.
 * A helper to avoid mixing character arithmetic with loops.
 */
auto repeat_char(std::size_t count, char ch) -> std::string
{
    return std::string(count, ch);
}

}  // unnamed namespace

[[nodiscard]] auto rows(char letter) -> std::vector<std::string>
{
    constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    const std::string_view alpha_view{alphabet};
    const std::size_t pos = alpha_view.find(letter);
    if (pos == std::string_view::npos) {
        return std::vector<std::string>{};
    }

    const std::size_t width = (pos * 2U) + 1U;

    std::vector<std::string> rows_vec;
    rows_vec.reserve(width);

    for (std::size_t i = 0U; i <= pos; ++i) {
        const char current = alphabet[i];

        const std::size_t leading = pos - i;
        const std::size_t inner   = (i == 0U) ? 0U : ((i * 2U) - 1U);

        std::string row = repeat_char(leading, ' ');
        row += current;
        if (inner != 0U) {
            row += repeat_char(inner, ' ');
            row += current;
        }
        row += repeat_char(leading, ' ');

        rows_vec.push_back(row);
    }

    for (std::size_t idx = (rows_vec.size() - 2U); idx < rows_vec.size(); --idx) {
        rows_vec.push_back(rows_vec[idx]);
        if (idx == 0U) {
            break;
        }
    }

    return rows_vec;
}

[[nodiscard]] auto make(char letter) -> std::string
{
    constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    /* Locate the requested letter inside the alphabet. */
    const std::string_view alpha_view{alphabet};
    const std::size_t pos = alpha_view.find(letter);
    if (pos == std::string_view::npos) {
        /* Unknown letter ‑ return an empty string to indicate failure. */
        return std::string{};
    }

    /* Overall width (and height) of the diamond. */
    const std::size_t width = (pos * 2U) + 1U;

    std::vector<std::string> rows;
    rows.reserve(width);

    /* Construct the top half including the middle row. */
    for (std::size_t i = 0U; i <= pos; ++i) {
        const char current = alphabet[i];

        const std::size_t leading = pos - i;
        const std::size_t inner   = (i == 0U) ? 0U : ((i * 2U) - 1U);

        std::string row = repeat_char(leading, ' ');
        row += current;
        if (inner != 0U) {
            row += repeat_char(inner, ' ');
            row += current;
        }
        row += repeat_char(leading, ' ');

        rows.push_back(row);
    }

    /* Mirror the top half to obtain the bottom half, excluding the middle. */
    for (std::size_t idx = (rows.size() - 2U); idx < rows.size(); --idx) {
        rows.push_back(rows[idx]);
        if (idx == 0U) {
            break;  /* Prevent wrap-around because size_type is unsigned. */
        }
    }

    /* Join all rows with newline separators. */
    std::string result;
    for (std::size_t r = 0U; r < rows.size(); ++r) {
        result += rows[r];
        if (r + 1U != rows.size()) {
            result += '\n';
        }
    }
    return result;
}

}  // namespace diamond
