#include "diamond.h"

#include <algorithm>
#include <cstddef>   // std::size_t
#include <iterator>  // std::distance
#include <string>

namespace diamond {

auto rows(char letter) -> std::vector<std::string>
{
    /* Lookup table avoids using the numerical value of characters. */
    constexpr char alphabet[] { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

    const auto it { std::find(std::begin(alphabet),
                              (std::end(alphabet) - 1),
                              letter) };

    if (it == (std::end(alphabet) - 1)) {
        return {};  /* Unsupported letter. */
    }

    const std::size_t pos { static_cast<std::size_t>(
        std::distance(std::begin(alphabet), it)) };

    const std::size_t size { (pos * static_cast<std::size_t>(2U))
                             + static_cast<std::size_t>(1U) };

    std::vector<std::string> result {};
    result.reserve(size);

    /* Top half including middle row. */
    for (std::size_t row { 0U }; row <= pos; ++row) {
        const std::size_t leading_spaces { pos - row };
        const std::size_t inner_spaces { (row == static_cast<std::size_t>(0U))
                                             ? static_cast<std::size_t>(0U)
                                             : ((row * static_cast<std::size_t>(2U))
                                                - static_cast<std::size_t>(1U)) };

        std::string current_row {};
        current_row.append(leading_spaces, ' ');

        const char current_letter { alphabet[row] };
        current_row.push_back(current_letter);

        if (row != static_cast<std::size_t>(0U)) {
            current_row.append(inner_spaces, ' ');
            current_row.push_back(current_letter);
        }

        result.emplace_back(current_row);
    }

    /* Bottom half (mirror of the top half, excluding the middle row). */
    for (std::size_t idx { pos }; idx-- > static_cast<std::size_t>(0U); ) {
        result.emplace_back(result[idx]);
    }

    return result;
}

}  // namespace diamond
