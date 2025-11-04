#include "diamond.h"

#include <algorithm>
#include <cstdint>
#include <sstream>
#include <stdexcept>

namespace diamond {

auto generate(char letter) -> std::vector<std::string>
{
    /* The canonical alphabet – look-up avoids using the
     * numerical value of characters directly.
     */
    const std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    const auto it = std::find(alphabet.begin(), alphabet.end(), letter);
    if (it == alphabet.end()) {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const std::uint32_t idx =
        static_cast<std::uint32_t>(std::distance(alphabet.begin(), it));

    /* height == width to keep the diamond square */
    const std::uint32_t size =
        (idx * static_cast<std::uint32_t>(2U)) + static_cast<std::uint32_t>(1U);

    std::vector<std::string> result{};
    result.reserve(size);

    for (std::uint32_t row{0U}; row < size; ++row) {
        /* Mirror the bottom half onto the top to simplify logic */
        const std::uint32_t mirrorRow =
            (row <= idx) ? row : (size - static_cast<std::uint32_t>(1U) - row);

        const std::uint32_t leadingSpaces = idx - mirrorRow;
        const char           rowLetter    = alphabet[mirrorRow];

        const std::uint32_t innerSpaces =
            (mirrorRow == static_cast<std::uint32_t>(0U))
                ? static_cast<std::uint32_t>(0U)
                : ((mirrorRow * static_cast<std::uint32_t>(2U)) -
                   static_cast<std::uint32_t>(1U));

        std::string line{};
        line.reserve(size);

        line.append(leadingSpaces, ' ');
        line.push_back(rowLetter);

        if (innerSpaces > static_cast<std::uint32_t>(0U)) {
            line.append(innerSpaces, ' ');
            line.push_back(rowLetter);
        }

        line.append(leadingSpaces, ' ');

        result.push_back(line);
    }

    return result;
}

/* Wrapper expected by the unit tests */
auto rows(char letter) -> std::vector<std::string>
{
    return generate(letter);
}

auto generate_string(char letter) -> std::string
{
    const auto lines = generate(letter);

    std::ostringstream oss{};
    for (std::uint32_t i{0U}; i < lines.size(); ++i) {
        oss << lines[i];
        if ((i + static_cast<std::uint32_t>(1U)) < lines.size()) {
            oss << '\n';
        }
    }
    return oss.str();
}

}  // namespace diamond
