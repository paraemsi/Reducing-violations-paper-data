#include "diamond.h"

#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

auto generate(char letter) -> std::string
{
    const std::int32_t int_letter =
        std::char_traits<char>::to_int_type(letter);
    const std::int32_t int_a =
        std::char_traits<char>::to_int_type('A');
    const std::int32_t int_z =
        std::char_traits<char>::to_int_type('Z');

    /* Validate input: must be an uppercase ASCII letter */
    if ((int_letter < int_a) || (int_letter > int_z))
    {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const std::int32_t n = int_letter - int_a;
    const std::int32_t size = (n * 2) + 1;

    std::ostringstream oss;

    for (std::int32_t row = 0; row < size; ++row)
    {
        const std::int32_t idx =
            (row <= n) ? row : ((n * 2) - row);
        const std::int32_t leading_spaces = n - idx;
        const std::int32_t inner_spaces =
            (idx == 0) ? 0 : ((idx * 2) - 1);

        /* Leading spaces */
        for (std::int32_t s = 0; s < leading_spaces; ++s)
        {
            oss.put(' ');
        }

        /* First character */
        const std::int32_t int_c = int_a + idx;
        const char ch = std::char_traits<char>::to_char_type(int_c);
        oss.put(ch);

        /* Inner spaces and second character (when needed) */
        if (inner_spaces > 0)
        {
            for (std::int32_t s = 0; s < inner_spaces; ++s)
            {
                oss.put(' ');
            }
            oss.put(ch);
        }

        /* Trailing spaces (mirror of leading) */
        for (std::int32_t s = 0; s < leading_spaces; ++s)
        {
            oss.put(' ');
        }

        if (row != (size - 1))
        {
            oss.put('\n');
        }
    }

    return oss.str();
}

auto rows(char letter) -> std::vector<std::string>
{
    const std::string full = generate(letter);
    std::vector<std::string> output {};
    std::string current {};

    for (char ch : full)
    {
        if (ch == '\n')
        {
            output.push_back(current);
            current.clear();
        }
        else
        {
            current.push_back(ch);
        }
    }

    /* Push the final line that does not end with '\n'. */
    output.push_back(current);

    return output;
}

}  // namespace diamond
