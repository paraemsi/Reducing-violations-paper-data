#include "diamond.h"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

// Generate the rows constituting the diamond; helper needed by make_diamond.
auto rows(char letter) -> std::vector<std::string>
{
    constexpr const char * alphabet_cstr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string alphabet{alphabet_cstr};

    const std::string::size_type pos = alphabet.find(letter);

    if (pos == std::string::npos)
    {
        return std::vector<std::string>{};
    }

    const std::uint32_t n = static_cast<std::uint32_t>(pos);

    std::vector<std::string> result_rows;
    result_rows.reserve((n * 2U) + 1U);

    for (std::uint32_t i = 0U; i <= n; ++i)
    {
        result_rows.push_back(std::string{});
        std::string & row = result_rows.back();

        const std::uint32_t outer_spaces = n - i;
        const std::uint32_t inner_spaces =
            (i == 0U) ? 0U : ((static_cast<std::uint32_t>(2U * i)) - 1U);

        row.append(outer_spaces, ' ');
        row.push_back(alphabet[static_cast<std::string::size_type>(i)]);

        if (i != 0U)
        {
            row.append(inner_spaces, ' ');
            row.push_back(alphabet[static_cast<std::string::size_type>(i)]);
        }

        row.append(outer_spaces, ' ');
    }

    if (n > 0U)
    {
        for (std::uint32_t i = n; (i--) > 0U; )
        {
            result_rows.push_back(result_rows[i]);
        }
    }

    return result_rows;
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
auto make_diamond(char letter) -> std::string
{
    const std::vector<std::string> all_rows = rows(letter);

    if (all_rows.empty())
    {
        return std::string{};
    }

    const std::size_t width = all_rows[0].size();

    std::string result;
    result.reserve((all_rows.size() * width) + all_rows.size()); // rough estimate

    for (std::size_t i = 0U; i < all_rows.size(); ++i)
    {
        result += all_rows[i];

        if ((i + 1U) < all_rows.size())
        {
            result.push_back('\n');
        }
    }

    return result;
}

}  // namespace diamond
