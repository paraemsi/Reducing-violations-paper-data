#include "diamond.h"

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace diamond {

[[nodiscard]] auto rows(char letter) -> std::vector<std::string>
{
    constexpr std::string_view alphabet{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

    const std::size_t alpha_index{ alphabet.find(letter) };
    if (alpha_index == std::string_view::npos)
    {
        /* Invalid input: character not in alphabet */
        return {};
    }

    const std::size_t size{ (alpha_index * 2U) + 1U };

    std::vector<std::string> result{};
    result.reserve(size);

    for (std::size_t row{ 0U }; row < size; ++row)
    {
        const std::size_t current_index{
            (row <= alpha_index) ? row : ((size - row) - 1U)
        };
        const std::size_t leading_spaces{ alpha_index - current_index };
        const std::size_t first_pos{ leading_spaces };
        const std::size_t second_pos{ (size - leading_spaces) - 1U };

        const char current_char{ alphabet[current_index] };

        std::string line(size, ' ');
        line[first_pos] = current_char;

        if (current_index != 0U)
        {
            line[second_pos] = current_char;
        }

        result.emplace_back(std::move(line));
    }

    return result;
}

[[nodiscard]] auto make_diamond(char letter) -> std::string
{
    const auto lines{ rows(letter) };
    if (lines.empty())
    {
        return {};
    }

    std::string diamond_str{};
    diamond_str.reserve(lines.size() * (lines.front().size() + 1U));

    for (std::size_t idx{ 0U }; idx < lines.size(); ++idx)
    {
        diamond_str.append(lines[idx]);
        if (idx + 1U < lines.size())
        {
            diamond_str.push_back('\n');
        }
    }

    return diamond_str;
}

}  // namespace diamond
