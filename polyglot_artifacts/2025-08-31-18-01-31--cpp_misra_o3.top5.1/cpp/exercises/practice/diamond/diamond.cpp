#include "diamond.h"

#include <string>
#include <cstddef>
#include <vector>
#include <utility>

namespace diamond {

auto make(char letter) -> std::vector<std::string> {
    /* Alphabet constant used to look-up positions without converting characters
     * to their numerical values, in compliance with MISRA rules.                 */
    static const std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    const std::size_t pos{alphabet.find(letter)};

    /* Validate input: only accept characters present in the alphabet constant.   */
    if (pos == std::string::npos) {
        return {}; /* Return empty result on invalid input.                       */
    }

    const std::size_t max_offset{pos};
    const std::size_t dimension{(max_offset * static_cast<std::size_t>(2)) + static_cast<std::size_t>(1)};

    std::vector<std::string> lines{};
    lines.reserve(dimension);

    for (std::size_t row = static_cast<std::size_t>(0); row < dimension; ++row) {
        const std::size_t current_offset{
            (row <= max_offset) ? row : ((dimension - row) - static_cast<std::size_t>(1))
        };

        const std::size_t leading_spaces{max_offset - current_offset};
        std::string line{};
        line.append(leading_spaces, ' ');

        const char current_char{alphabet[current_offset]};
        line.push_back(current_char);

        if (current_offset != static_cast<std::size_t>(0)) {
            const std::size_t inner_spaces{
                (current_offset * static_cast<std::size_t>(2)) - static_cast<std::size_t>(1)
            };
            line.append(inner_spaces, ' ');
            line.push_back(current_char);
        }

        line.append(leading_spaces, ' ');
        lines.emplace_back(std::move(line));
    }

    return lines;
}

/* -------------------------------------------------------------------------- */
/* Convenience wrapper required by the test suite.                            */
/* -------------------------------------------------------------------------- */
auto rows(char letter) -> std::vector<std::string> {
    return make(letter);
}

}  // namespace diamond
