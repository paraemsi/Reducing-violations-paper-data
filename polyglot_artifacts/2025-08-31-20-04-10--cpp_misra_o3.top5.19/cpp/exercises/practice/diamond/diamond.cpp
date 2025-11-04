#include "diamond.h"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

namespace {

/* Constant list of uppercase alphabet letters. */
static const std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

/* Obtain the (zero-based) index of a letter inside the alphabet string. */
/* Local helper that converts the requested widest letter into an index
 * inside the alphabet (A->0, B->1, ...).  No arithmetic is performed on
 * the character value itself – we merely search inside the constant
 * string of legal letters, thus complying with the “numerical value of a
 * character shall not be used” rule.
 */
auto letter_index(char letter) -> std::size_t
{
    const std::size_t pos{alphabet.find(letter)};
    assert(pos != std::string::npos); /* external validation should ensure validity */
    return pos;
}

/* Convert zero-based alphabet index back to its letter without
 * performing arithmetic on character values. */
auto letter_for_index(std::size_t idx) -> char
{
    assert(idx < alphabet.size());
    return alphabet[idx];
}
}  // namespace

/* Forward declaration needed so that rows() can call make() before its
 * full definition appears further below. */
auto make(char letter) -> std::vector<std::string>;

auto rows(char letter) -> std::vector<std::string>
{
    return make(letter); /* delegate to the primary implementation */
}

auto make(char letter) -> std::vector<std::string>
{
    const std::size_t idx{letter_index(letter)};
    const std::size_t width{(idx * 2U) + 1U};

    std::vector<std::string> rows{};
    rows.reserve(width);

    /* Build top half (including middle row) */
    for (std::size_t row_idx{0U}; row_idx <= idx; ++row_idx)
    {
        const std::size_t left_pad{idx - row_idx};
        const std::size_t inner_space{(row_idx == 0U) ? 0U : ((row_idx * 2U) - 1U)};
        std::string row(width, ' ');

        /* Place the pair of identical letters (only one when row_idx == 0) */
        const char current_letter{letter_for_index(row_idx)};
        row[left_pad] = current_letter;
        if (row_idx != 0U)
        {
            row[(left_pad + inner_space) + 1U] = current_letter;
        }

        rows.push_back(row);
    }

    /* Mirror the top half (excluding middle) to obtain the bottom half */
    for (std::size_t row_idx{idx}; row_idx-- > 0U;)
    {
        rows.push_back(rows[row_idx]);
    }

    return rows;
}

auto make_string(char letter) -> std::string
{
    const std::vector<std::string> rows{make(letter)};

    std::string result{};
    result.reserve(rows.size() * rows.front().size());

    for (std::size_t i{0U}; i < rows.size(); ++i)
    {
        result += rows[i];
        if (i + 1U < rows.size())
        {
            result += '\n';
        }
    }
    return result;
}

}  // namespace diamond
