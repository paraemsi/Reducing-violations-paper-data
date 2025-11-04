#include "diamond.h"
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

namespace {
using char_t = char;
using size_t = std::size_t;

static size_t get_diamond_size(char_t letter)
{
    // 'A' is 0, 'B' is 1, etc.
    return static_cast<size_t>((static_cast<std::uint8_t>(letter) - static_cast<std::uint8_t>('A')) * 2U + 1U);
}

static std::string make_row(char_t row_letter, char_t max_letter)
{
    size_t n = get_diamond_size(max_letter);
    size_t row = static_cast<size_t>(static_cast<std::uint8_t>(row_letter) - static_cast<std::uint8_t>('A'));
    size_t leading = (n - (row * 2U + 1U)) / 2U;

    std::string s(n, ' ');

    if(row_letter == 'A')
    {
        s.at(leading) = 'A';
    }
    else
    {
        s.at(leading) = row_letter;
        s.at(n - leading - 1U) = row_letter;
    }
    return s;
}
} // anonymous namespace

std::vector<std::string> make_diamond(char_t letter)
{
    std::vector<std::string> result;
    size_t n_rows = get_diamond_size(letter);

    // Top half (including middle)
    for(size_t i = 0U; i <= (static_cast<size_t>(static_cast<std::uint8_t>(letter) - static_cast<std::uint8_t>('A'))); ++i)
    {
        char_t row_letter = static_cast<char_t>(static_cast<std::uint8_t>('A') + static_cast<std::uint8_t>(i));
        result.push_back(make_row(row_letter, letter));
    }
    // Bottom half (excluding middle)
    for(size_t i = (static_cast<size_t>(static_cast<std::uint8_t>(letter) - static_cast<std::uint8_t>('A'))); i-- > 0U; )
    {
        char_t row_letter = static_cast<char_t>(static_cast<std::uint8_t>('A') + static_cast<std::uint8_t>(i));
        result.push_back(make_row(row_letter, letter));
    }
    return result;
}

// Alias for compatibility with tests
std::vector<std::string> rows(char letter)
{
    return make_diamond(letter);
}

}  // namespace diamond
