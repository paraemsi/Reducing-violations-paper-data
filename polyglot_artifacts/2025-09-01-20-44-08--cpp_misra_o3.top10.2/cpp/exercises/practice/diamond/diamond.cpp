#include "diamond.h"

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstddef>

namespace diamond
{

namespace
{
/* Local helper: return the index of `letter` in the alphabet (A == 0U).
 * The scan avoids using the numeric value of the character, keeping us
 * compliant with the rule that forbids arithmetic on character values. */
auto letter_index(char letter) -> std::uint32_t
{
    static constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::uint32_t idx {0U};
    while (alphabet[idx] != '\0')
    {
        if (alphabet[idx] == letter)
        {
            return idx;
        }
        ++idx;
    }

    throw std::invalid_argument("letter must be an uppercase A-Z");
}

/* Local helper: obtain the alphabet character for a given index. */
auto letter_at(std::uint32_t idx) -> char
{
    static constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return alphabet[idx];
}

}  // namespace

DIAMOND_NODISCARD auto make(char letter) -> std::vector<std::string>
{
    const std::uint32_t max_idx {letter_index(letter)};
    const std::uint32_t size    {(max_idx * 2U) + 1U};  // width == height

    std::vector<std::string> rows;
    rows.reserve(static_cast<std::size_t>(size));

    const std::uint32_t mid {max_idx};

    for (std::uint32_t row_idx {0U}; row_idx < size; ++row_idx)
    {
        /* Mirror the top half onto the bottom half. */
        const std::uint32_t top_idx {(row_idx <= max_idx)
                                         ? row_idx
                                         : (size - 1U) - row_idx};

        std::string line(static_cast<std::size_t>(size), ' ');

        const std::uint32_t offset {top_idx};
        const char          ch     {letter_at(top_idx)};

        line[static_cast<std::size_t>(mid - offset)] = ch;
        line[static_cast<std::size_t>(mid + offset)] = ch;

        rows.push_back(line);
    }

    return rows;
}

DIAMOND_NODISCARD auto rows(char letter) -> std::vector<std::string>
{
    return make(letter);
}

DIAMOND_NODISCARD auto to_string(char letter) -> std::string
{
    const std::vector<std::string> row_vec {make(letter)};

    std::string result;
    const std::uint32_t row_count {static_cast<std::uint32_t>(row_vec.size())};
    for (std::uint32_t i {0U}; i < row_count; ++i)
    {
        result += row_vec[static_cast<std::size_t>(i)];
        if ((i + 1U) < row_count)
        {
            result += '\n';
        }
    }

    return result;
}

}  // namespace diamond
