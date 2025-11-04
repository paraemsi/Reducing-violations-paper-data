#include "diamond.h"

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {
namespace
{

/* Alphabet lookup table – avoids treating the character as a number        */
constexpr std::array<char, 26U> alphabet{{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
}};

/* Return the position of @p letter in the alphabet array (0-based).         */
[[nodiscard]] std::uint32_t index_of_letter(char letter)
{
    std::uint32_t pos{0U};

    for (char c : alphabet)
    {
        if (c == letter)
        {
            return pos;
        }
        ++pos;
    }

    /* The caller is expected to supply a valid uppercase letter.            */
    return pos;
}

/* Build the string for one row of the diamond                               */
[[nodiscard]] std::string build_line(std::uint32_t max_index,
                                     std::uint32_t line_index,
                                     char          letter_char)
{
    const std::uint32_t leading_spaces{max_index - line_index};
    const std::uint32_t inner_spaces{
        (line_index == 0U) ? 0U : ((2U * line_index) - 1U)};

    std::string row{};
    row.append(leading_spaces, ' ');
    row.push_back(letter_char);

    if (inner_spaces > 0U)
    {
        row.append(inner_spaces, ' ');
        row.push_back(letter_char);
    }

    row.append(leading_spaces, ' ');
    return row;
}

}  // unnamed namespace

std::vector<std::string> make_diamond(char letter)
{
    const std::uint32_t idx{index_of_letter(letter)};

    /* Validate the input character – if it is not an uppercase letter
     * between 'A' and 'Z', return an empty result.                          */
    if (idx >= static_cast<std::uint32_t>(alphabet.size()))
    {
        return {};
    }

    /* The diamond has (2 * idx + 1) rows                                    */
    std::vector<std::string> result_rows{};
    result_rows.reserve((2U * idx) + 1U);

    /* Top-half including the middle row                                     */
    for (std::uint32_t line{0U}; line <= idx; ++line)
    {
        result_rows.push_back(build_line(idx, line, alphabet[line]));
    }

    /* Bottom-half – mirror of the top without the middle row                */
    for (std::uint32_t line{idx}; line > 0U; --line)
    {
        const std::uint32_t prev{line - 1U};
        result_rows.push_back(build_line(idx, prev, alphabet[prev]));
    }

    return result_rows;
}

/* ----------------------------------------------------------------------- */
/* Compatibility wrapper for the legacy test-suite.                        */
std::vector<std::string> rows(char letter)
{
    /* Directly forward to the primary implementation.                      */
    return make_diamond(letter);
}

}  // namespace diamond
