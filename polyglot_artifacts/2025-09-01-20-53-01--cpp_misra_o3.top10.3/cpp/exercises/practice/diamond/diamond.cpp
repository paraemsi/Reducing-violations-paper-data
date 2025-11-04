#include "diamond.h"

#include <cstddef>
#include <string>
#include <vector>

namespace diamond {

auto build(char letter) -> std::vector<std::string>
{
    constexpr const char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string alphabetStr{alphabet};

    const std::string::size_type idx = alphabetStr.find(letter);

    if(idx == std::string::npos)
    {
        return std::vector<std::string>{};
    }

    const std::size_t index = idx;
    const std::size_t height = (index * 2U) + 1U;

    std::vector<std::string> result{};
    result.reserve(height);

    const auto make_row =
        [index](std::size_t i) -> std::string
        {
            const std::size_t leading = index - i;
            const char currentChar = static_cast<char>("ABCDEFGHIJKLMNOPQRSTUVWXYZ"[i]);

            if(i == 0U)
            {
                return std::string(leading, ' ') + currentChar + std::string(leading, ' ');
            }
            else
            {
                const std::size_t inner = (i * 2U) - 1U;
                return std::string(leading, ' ') + currentChar + std::string(inner, ' ') + currentChar + std::string(leading, ' ');
            }
        };

    for(std::size_t i = 0U; i <= index; ++i)
    {
        result.push_back(make_row(i));
    }

    for(std::size_t i = index; i > 0U; --i)
    {
        result.push_back(make_row(i - 1U));
    }

    return result;
}

auto rows(char letter) -> std::vector<std::string>
{
    return build(letter);
}

}  // namespace diamond
