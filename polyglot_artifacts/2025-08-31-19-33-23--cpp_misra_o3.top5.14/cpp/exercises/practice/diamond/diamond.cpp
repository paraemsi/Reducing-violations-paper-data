#include "diamond.h"

#include <cstddef>
#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

namespace {
/* helper alias to shorten char_traits usage */
using traits = std::char_traits<char>;

/* ------------------------------------------------------------------ */
/* Construct one row of the diamond                                   */
/* ------------------------------------------------------------------ */
auto make_row(std::uint32_t row,
              std::uint32_t outer_spaces) -> std::string
{
    /* Convert 'A' + row to the required character without using
       direct arithmetic on the character type itself.              */
    const std::uint32_t a_int { static_cast<std::uint32_t>(traits::to_int_type('A')) };
    const char          letter { traits::to_char_type(static_cast<int>(a_int + row)) };

    const std::uint32_t inner_spaces {
        (row == static_cast<std::uint32_t>(0)) ? static_cast<std::uint32_t>(0)
                                               : ((row * static_cast<std::uint32_t>(2)) - static_cast<std::uint32_t>(1))
    };

    std::string result;
    result.append(static_cast<std::size_t>(outer_spaces), ' ');
    result.push_back(letter);

    if (row != static_cast<std::uint32_t>(0)) {
        result.append(static_cast<std::size_t>(inner_spaces), ' ');
        result.push_back(letter);
    }

    result.append(static_cast<std::size_t>(outer_spaces), ' ');

    return result;
}

}  // unnamed namespace

auto rows(char letter) -> std::vector<std::string>
{
    const std::uint32_t letter_int { static_cast<std::uint32_t>(traits::to_int_type(letter)) };
    const std::uint32_t a_int      { static_cast<std::uint32_t>(traits::to_int_type('A')) };
    const std::uint32_t z_int      { static_cast<std::uint32_t>(traits::to_int_type('Z')) };

    if ((letter_int < a_int) || (letter_int > z_int)) {
        throw std::invalid_argument("diamond::rows expects an uppercase letter A–Z");
    }

    const std::uint32_t index { letter_int - a_int };
    const std::uint32_t size  { (index * static_cast<std::uint32_t>(2)) + static_cast<std::uint32_t>(1) };

    std::vector<std::string> result;
    result.reserve(static_cast<std::size_t>(size));

    /* top half including middle row */
    for (std::uint32_t row { static_cast<std::uint32_t>(0) }; row <= index; ++row) {
        const std::uint32_t outer_spaces { index - row };
        result.emplace_back(make_row(row, outer_spaces));
    }

    /* bottom half (mirror of the top without the centre row) */
    for (std::uint32_t row { static_cast<std::uint32_t>(0) }; row < index; ++row) {
        result.emplace_back(result[static_cast<std::size_t>(index - row - static_cast<std::uint32_t>(1))]);
    }

    return result;
}

auto build(char letter) -> std::string
{
    /* Generate the individual lines first and then join them, re-using
       the verified logic already present in diamond::rows               */
    const std::vector<std::string> lines { rows(letter) };

    std::ostringstream oss;
    const std::size_t last { lines.size() - static_cast<std::size_t>(1) };

    for (std::size_t i { static_cast<std::size_t>(0) }; i < lines.size(); ++i) {
        oss << lines[i];
        if (i != last) {
            oss << '\n';
        }
    }

    return oss.str();
}

}  // namespace diamond
