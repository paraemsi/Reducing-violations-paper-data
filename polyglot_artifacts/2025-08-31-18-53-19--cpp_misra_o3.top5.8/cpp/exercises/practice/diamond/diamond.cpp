#include "diamond.h"

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

/*  Implementation notes
 *  --------------------
 *  – Follows MISRA C++ rules supplied by the user.
 *  – Avoids arithmetic on character objects by working with the
 *    integer representation obtained via std::char_traits.
 *  – Uses fixed-width unsigned integers from <cstdint>.
 */

namespace diamond {

auto make(char letter) -> std::vector<std::string>
{
    using std::uint32_t;

    constexpr int base_code { std::char_traits<char>::to_int_type('A') };
    const int input_code { std::char_traits<char>::to_int_type(letter) };

    if((input_code < base_code) || (input_code > std::char_traits<char>::to_int_type('Z')))
    {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const uint32_t diff { static_cast<uint32_t>(input_code - base_code) };
    const uint32_t size { (diff * 2U) + 1U };

    std::vector<std::string> lines {};
    lines.reserve(size);

    /* Top half (including middle row) */
    for(uint32_t i { 0U }; i <= diff; ++i)
    {
        const uint32_t leading { diff - i };

        std::string row(size, ' ');

        const int code_row { base_code + static_cast<int>(i) };
        const char ch      { std::char_traits<char>::to_char_type(code_row) };

        row[leading] = ch;
        row[(size - 1U) - leading] = ch;  /* symmetric position */

        lines.push_back(row);
    }

    /* Bottom half (mirror of the top half without the middle row) */
    for(uint32_t i { diff }; (i-- > 0U); )
    {
        lines.push_back(lines[i]);
    }

    return lines;
}

auto rows(char letter) -> std::vector<std::string>
{
    return make(letter);
}

}  // namespace diamond
