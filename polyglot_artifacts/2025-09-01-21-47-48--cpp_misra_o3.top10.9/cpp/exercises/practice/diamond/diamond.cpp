#include "diamond.h"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>
#include <locale>

namespace diamond {

[[nodiscard]] auto make(char up_to) -> std::vector<std::string>
{
    // Validate input – must be an uppercase letter 'A'-'Z'
    if(!std::isupper(up_to, std::locale{}))
    {
        throw std::invalid_argument("diamond::make – argument must be 'A'-'Z'");
    }

    // Determine the 0-based index of the widest letter without relying on the
    // numeric value of the character.
    const std::string letters{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    const std::size_t max_level = letters.find(up_to);

    if(max_level == std::string::npos)
    {
        throw std::invalid_argument("diamond::make – argument must be 'A'-'Z'");
    }

    // The diamond is a square: width == height
    const std::size_t width = (max_level * 2U) + 1U;
    const std::size_t height = width;  // square, by definition


    std::vector<std::string> result;
    result.reserve(height);

    for(std::size_t row = 0U; row < height; ++row)
    {
        const std::size_t level = (row <= max_level) ? row
                                                    : (height - 1U - row);

        const char letter = letters.at(static_cast<std::size_t>(level));

        std::string line(width, ' ');  // pre-fill with spaces

        const std::size_t leading_spaces =
            static_cast<std::size_t>(max_level - level);

        line.at(leading_spaces) = letter;
        if(level != 0U)
        {
            const std::size_t trailing_index =
                static_cast<std::size_t>((width - 1U) - leading_spaces);
            line.at(trailing_index) = letter;
        }

        result.push_back(line);
    }

    return result;
}

auto rows(char up_to) -> std::vector<std::string>
{
    return make(up_to);
}

}  // namespace diamond
