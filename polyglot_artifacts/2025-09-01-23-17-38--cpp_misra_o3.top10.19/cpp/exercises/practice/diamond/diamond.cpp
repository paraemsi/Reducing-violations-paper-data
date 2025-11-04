#include "diamond.h"

#include <array>
#include <cstddef>
#include <string>
#include <vector>

namespace diamond {

[[nodiscard]] auto generate(char letter) -> std::string
{
    /*  Fixed alphabet – look-up is done with equality comparisons only,
        thus avoiding any arithmetic on characters. */
    static constexpr std::array<char, 26U> alphabet{
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    /* Determine the position of the requested letter in the alphabet. */
    std::size_t max_index{0U};

    for (std::size_t i{0U}; i < alphabet.size(); ++i) {
        if (alphabet[i] == letter) {
            max_index = i;
            break;
        }
    }

    /* If the letter is not supported, return an empty result. */
    if (alphabet[max_index] != letter) {
        return std::string{};
    }

    const std::size_t dimension{(max_index * 2U) + 1U};

    std::vector<std::string> diamond_rows{};
    diamond_rows.reserve(dimension);

    /* Build the upper half (including the middle row). */
    for (std::size_t i{0U}; i <= max_index; ++i) {
        const std::size_t leading{max_index - i};
        const std::size_t gap{(i == 0U) ? 0U : ((2U * i) - 1U)};

        std::string row{};
        row.reserve(dimension);

        row.append(leading, ' ');
        row.push_back(alphabet[i]);

        if (gap != 0U) {
            row.append(gap, ' ');
            row.push_back(alphabet[i]);
        }

        row.append(leading, ' ');

        diamond_rows.push_back(row);
    }

    /* Build the lower half by mirroring the upper half (excluding center). */
    if (max_index != 0U) {
        for (std::size_t i{max_index - 1U}; ; --i) {
            const std::size_t leading{max_index - i};
            const std::size_t gap{(i == 0U) ? 0U : ((2U * i) - 1U)};

            std::string row{};
            row.reserve(dimension);

            row.append(leading, ' ');
            row.push_back(alphabet[i]);

            if (gap != 0U) {
                row.append(gap, ' ');
                row.push_back(alphabet[i]);
            }

            row.append(leading, ' ');

            diamond_rows.push_back(row);

            if (i == 0U) {
                break; /* Prevent underflow on the next decrement */
            }
        }
    }

    /*  Join rows with newline separators to build the final string. */
    std::string result{};
    for (std::size_t i{0U}; i < diamond_rows.size(); ++i) {
        result += diamond_rows[i];
        if ((i + 1U) < diamond_rows.size()) {
            result += '\n';
        }
    }

    return result;
}

/*  Build and return the diamond as separate rows (vector of strings). */
[[nodiscard]] auto rows(char letter) -> std::vector<std::string>
{
    /*  Fixed alphabet – look-up is done with equality comparisons only,
        thus avoiding any arithmetic on characters. */
    static constexpr std::array<char, 26U> alphabet{
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    /* Determine the position of the requested letter in the alphabet. */
    std::size_t max_index{0U};
    for (std::size_t i{0U}; i < alphabet.size(); ++i) {
        if (alphabet[i] == letter) {
            max_index = i;
            break;
        }
    }

    /* If the letter is not supported, return an empty result. */
    if (alphabet[max_index] != letter) {
        return std::vector<std::string>{};
    }

    const std::size_t dimension{(max_index * 2U) + 1U};

    std::vector<std::string> rows_result{};
    rows_result.reserve(dimension);

    /* Build the upper half (including the middle row). */
    for (std::size_t i{0U}; i <= max_index; ++i) {
        const std::size_t leading{max_index - i};
        const std::size_t gap{(i == 0U) ? 0U : ((2U * i) - 1U)};

        std::string row{};
        row.reserve(dimension);

        row.append(leading, ' ');
        row.push_back(alphabet[i]);

        if (gap != 0U) {
            row.append(gap, ' ');
            row.push_back(alphabet[i]);
        }

        row.append(leading, ' ');

        rows_result.push_back(row);
    }

    /* Build the lower half by mirroring the upper half (excluding center). */
    if (max_index != 0U) {
        for (std::size_t i{max_index - 1U}; ; --i) {
            const std::size_t leading{max_index - i};
            const std::size_t gap{(i == 0U) ? 0U : ((2U * i) - 1U)};

            std::string row{};
            row.reserve(dimension);

            row.append(leading, ' ');
            row.push_back(alphabet[i]);

            if (gap != 0U) {
                row.append(gap, ' ');
                row.push_back(alphabet[i]);
            }

            row.append(leading, ' ');

            rows_result.push_back(row);

            if (i == 0U) {
                break; /* Prevent underflow on the next decrement */
            }
        }
    }

    return rows_result;
}

}  // namespace diamond
