#include "diamond.h"

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

[[nodiscard]] std::vector<std::string> make(char letter)
{
    /* Convert characters to integer domain without using their
       numerical values directly (MISRA compliance). */
    const std::int32_t first_int {
        static_cast<std::int32_t>(std::char_traits<char>::to_int_type('A'))
    };
    const std::int32_t last_int {
        static_cast<std::int32_t>(std::char_traits<char>::to_int_type('Z'))
    };
    const std::int32_t letter_int {
        static_cast<std::int32_t>(std::char_traits<char>::to_int_type(letter))
    };

    /* Validate input */
    if ((letter_int < first_int) || (letter_int > last_int)) {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const std::uint32_t offset {
        static_cast<std::uint32_t>(letter_int - first_int)
    };

    const std::uint32_t dimension { (offset * static_cast<std::uint32_t>(2U)) + static_cast<std::uint32_t>(1U) };

    std::vector<std::string> result {};
    result.reserve(dimension);

    for (std::uint32_t row { 0U }; row < dimension; ++row) {
        const std::uint32_t top_half_index { (row <= offset) ? row : (dimension - row - static_cast<std::uint32_t>(1U)) };

        const char current_char {
            std::char_traits<char>::to_char_type(
                static_cast<std::char_traits<char>::int_type>(
                    first_int + static_cast<std::int32_t>(top_half_index)
                )
            )
        };

        const std::uint32_t leading_spaces { offset - top_half_index };
        const std::uint32_t internal_spaces {
            (top_half_index == static_cast<std::uint32_t>(0U))
                ? static_cast<std::uint32_t>(0U)
                : ((top_half_index * static_cast<std::uint32_t>(2U)) - static_cast<std::uint32_t>(1U))
        };

        /* Build the current line */
        std::string line {};
        line.reserve(dimension);

        /* Leading spaces */
        line.append(leading_spaces, ' ');

        /* First letter */
        line.push_back(current_char);

        /* Internal spaces and second letter (if any) */
        if (top_half_index != static_cast<std::uint32_t>(0U)) {
            line.append(internal_spaces, ' ');
            line.push_back(current_char);
        }

        /* Trailing spaces */
        line.append(leading_spaces, ' ');

        result.emplace_back(std::move(line));
    }

    return result;
}

[[nodiscard]] std::vector<std::string> rows(char letter)
{
    /* Simply delegate to make() to preserve single implementation. */
    return make(letter);
}

}  // namespace diamond
