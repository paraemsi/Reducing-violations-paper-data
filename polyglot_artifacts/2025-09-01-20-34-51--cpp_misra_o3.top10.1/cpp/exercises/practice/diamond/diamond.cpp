#include "diamond.h"

#include <array>
#include <cstddef>
#include <stdexcept>   // for std::invalid_argument
#include <string>
#include <vector>

namespace diamond {

// Helper: fixed alphabet lookup table (index supplies the ordering)
static constexpr std::array<char, 26U> alphabet{
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
     'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}};

/**
 * @brief Find the zero-based position of a letter inside alphabet.
 *        Only equality comparisons are used to comply with MISRA rules.
 *
 * @param letter An upper-case letter expected to be in alphabet.
 * @return std::size_t The index of the letter.
 *
 * @throws std::invalid_argument If the letter is not found.
 */
[[nodiscard]] static auto index_of(char letter) -> std::size_t
{
    std::size_t idx{0U};

    for (char c : alphabet) {
        if (c == letter) {
            return idx;
        }
        ++idx;
    }

    throw std::invalid_argument("letter not in alphabet");
}

/**
 * @brief Build a single line of the diamond.
 *
 * @param width_half How far this line’s letter is from 'A'.
 * @param widest_half Index of the widest letter (same as diamond half height).
 * @return std::string A single line without newline termination.
 */
[[nodiscard]] static auto build_line(std::size_t width_half,
                                     std::size_t widest_half) -> std::string
{
    const std::size_t leading_spaces{widest_half - width_half};
    const char         letter{alphabet[width_half]};

    std::string line(leading_spaces, ' ');
    line.push_back(letter);

    if (width_half != 0U) {
        const std::size_t inner_spaces{(width_half * 2U) - 1U};
        line.append(inner_spaces, ' ');
        line.push_back(letter);
    }

    line.append(leading_spaces, ' ');
    return line;
}

/**
 * @brief Generate the diamond as individual rows.
 *
 * @param letter The widest letter in the diamond.
 * @return std::vector<std::string> Collection of rows without newlines.
 */
auto rows(char letter) -> std::vector<std::string>
{
    const std::size_t widest_half{index_of(letter)};
    std::vector<std::string>    result{};

    for (std::size_t row{0U}; row <= widest_half; ++row) {
        result.push_back(build_line(row, widest_half));
    }

    std::size_t row{widest_half};
    while (row > 0U) {
        --row;
        result.push_back(build_line(row, widest_half));
    }

    return result;
}

auto make_diamond(char letter) -> std::string
{
    const auto lines{rows(letter)};
    std::string       result{};

    for (std::size_t idx{0U}; idx < lines.size(); ++idx) {
        result += lines[idx];
        if ((idx + 1U) < lines.size()) {
            result.push_back('\n');
        }
    }

    return result;
}

}  // namespace diamond
