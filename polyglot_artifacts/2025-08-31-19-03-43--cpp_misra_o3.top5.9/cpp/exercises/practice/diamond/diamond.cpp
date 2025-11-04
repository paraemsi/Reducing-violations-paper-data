#include "diamond.h"

#include <algorithm>    // std::find
#include <stdexcept>    // std::invalid_argument
#include <string>       // std::string
#include <vector>       // std::vector
#include <cstddef>      // std::ptrdiff_t
#include <cstdint>      // std::uint32_t

namespace diamond {

auto make_diamond(char letter) -> std::vector<std::string>
{
    constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    /*  Locate the supplied letter inside the alphabet array.          */
    const char* const position_ptr = std::find(
        std::begin(alphabet),
        (std::end(alphabet) - static_cast<std::ptrdiff_t>(1)), /* exclude '\0' */
        letter
    );

    if (position_ptr == (std::end(alphabet) - static_cast<std::ptrdiff_t>(1))) {
        /*  Letter not found – input is invalid.                       */
        throw std::invalid_argument("Letter must be an uppercase character from 'A' to 'Z'.");
    }

    const std::uint32_t index = static_cast<std::uint32_t>(position_ptr - std::begin(alphabet));
    const std::uint32_t dimension = (index * static_cast<std::uint32_t>(2U)) + static_cast<std::uint32_t>(1U);

    std::vector<std::string> result;
    result.reserve(dimension);

    /*  Helper to build one row of the diamond.                       */
    const auto build_row = [index](std::uint32_t row_idx) -> std::string
    {
        const std::uint32_t leading_spaces = index - row_idx;
        const std::uint32_t between_spaces = (row_idx == static_cast<std::uint32_t>(0U))
                                             ? static_cast<std::uint32_t>(0U)
                                             : ((row_idx * static_cast<std::uint32_t>(2U)) - static_cast<std::uint32_t>(1U));

        std::string row;
        row.append(leading_spaces, ' ');
        row.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZ"[row_idx]);
        if (between_spaces != static_cast<std::uint32_t>(0U)) {
            row.append(between_spaces, ' ');
            row.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZ"[row_idx]);
        }
        row.append(leading_spaces, ' ');
        return row;
    };

    /*  Top half including the widest row.                            */
    for (std::uint32_t i = static_cast<std::uint32_t>(0U); i <= index; ++i) {
        result.push_back(build_row(i));
    }

    /*  Bottom half (mirror of the top, excluding the middle row).    */
    for (std::uint32_t i = index; i > static_cast<std::uint32_t>(0U); --i) {
        result.push_back(build_row(i - static_cast<std::uint32_t>(1U)));
    }

    return result;
}

auto rows(char letter) -> std::vector<std::string>
{
    /*  Delegate to the main implementation while keeping public API
     *  name expected by the test suite.
     */
    return make_diamond(letter);
}

}  // namespace diamond
