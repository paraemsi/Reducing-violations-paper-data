#include "diamond.h"

#include <array>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

namespace {

/*
 * Fixed alphabet lookup table – avoids relying on the numeric
 * value of a character, which is forbidden by the MISRA rule set.
 */
constexpr std::array<char, 26U> kAlphabet{{'A', 'B', 'C', 'D', 'E', 'F', 'G',
                                           'H', 'I', 'J', 'K', 'L', 'M', 'N',
                                           'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                                           'V', 'W', 'X', 'Y', 'Z'}};

/*
 * Return the zero-based index of a letter inside kAlphabet;
 * throws std::invalid_argument if the letter is not present.
 */
DIAMOND_NODISCARD auto index_of(char const letter) -> std::size_t
{
    for (std::size_t i{0U}; i < kAlphabet.size(); ++i)
    {
        if (kAlphabet[i] == letter)
        {
            return i;
        }
    }
    throw std::invalid_argument{"Unsupported letter"};
}

}  // namespace

/*
 * Produce the vector of rows that form the diamond.  Each row string
 * has the same length and contains embedded spaces but no newline.
 */
auto rows(char const letter) -> std::vector<std::string>
{
    auto const idx{index_of(letter)};
    auto const size{(idx * 2U) + 1U};

    std::vector<std::string> lines{};
    lines.reserve(size);

    for (std::size_t row{0U}; row < size; ++row)
    {
        std::size_t const mirror_row{(row <= idx) ? row : ((idx * 2U) - row)};
        char const ch{kAlphabet[mirror_row]};

        std::size_t const leading_spaces{idx - mirror_row};
        std::size_t const between_spaces{(mirror_row == 0U) ? 0U
                                                            : ((mirror_row * 2U) - 1U)};

        std::string line(size, ' ');
        line[leading_spaces] = ch;

        if (between_spaces != 0U)
        {
            line[leading_spaces + between_spaces + 1U] = ch;
        }

        lines.push_back(line);
    }
    return lines;
}

/*
 * Create the diamond string that satisfies the kata requirements.
 */
auto make(char const letter) -> std::string
{
    auto const lines{rows(letter)};

    std::string result{};
    for (std::size_t i{0U}; i < lines.size(); ++i)
    {
        result += lines[i];
        if ((i + 1U) < lines.size())
        {
            result += '\n';
        }
    }
    return result;
}

}  // namespace diamond
