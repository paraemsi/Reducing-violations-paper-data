#include "diamond.h"

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

auto rows(char target) -> std::vector<std::string>
{
    const std::string letters{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    /* Validate target letter */
    const std::size_t radius{letters.find(target)};
    if(radius == std::string::npos)
    {
        throw std::invalid_argument("target letter must be between 'A' and 'Z'");
    }

    const std::size_t dimension{(radius * static_cast<std::size_t>(2U)) + static_cast<std::size_t>(1U)};

    std::vector<std::string> result{};
    result.reserve(dimension);

    for(std::size_t i{0U}; i <= radius; ++i)
    {
        const char current_letter{letters[i]};
        const std::size_t leading_spaces{radius - i};
        const std::size_t inner_spaces{(i == static_cast<std::size_t>(0U))
                                           ? static_cast<std::size_t>(0U)
                                           : ((i * static_cast<std::size_t>(2U)) - static_cast<std::size_t>(1U))};

        std::string row{};
        row.append(leading_spaces, ' ');
        row.push_back(current_letter);

        if(inner_spaces > static_cast<std::size_t>(0U))
        {
            row.append(inner_spaces, ' ');
            row.push_back(current_letter);
        }

        row.append(leading_spaces, ' ');
        result.push_back(row);
    }

    /* Mirror upper part excluding middle row */
    for(std::size_t i{radius}; i > static_cast<std::size_t>(0U); --i)
    {
        result.push_back(result[i - static_cast<std::size_t>(1U)]);
    }

    return result;
}

auto make(char target) -> std::string
{
    const auto vec_rows{rows(target)};

    std::string result{};
    for(std::size_t idx{0U}; idx < vec_rows.size(); ++idx)
    {
        result += vec_rows[idx];
        if((idx + static_cast<std::size_t>(1U)) < vec_rows.size())
        {
            result += '\n';
        }
    }

    return result;
}

}  // namespace diamond
