#include "spiral_matrix.h"

#include <vector>
#include <cstdint>

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> matrix_t
{
    matrix_t result(size, std::vector<std::uint32_t>(size, 0U));

    if (size == 0U)
    {
        return result;
    }

    std::uint32_t min_row = 0U;
    std::uint32_t max_row = size - 1U;
    std::uint32_t min_col = 0U;
    std::uint32_t max_col = size - 1U;

    std::uint32_t current = 1U;

    while ((min_row <= max_row) && (min_col <= max_col))
    {
        /* top edge → */
        for (std::uint32_t col = min_col; col <= max_col; ++col)
        {
            result[min_row][col] = current;
            ++current;
        }
        ++min_row;

        /* right edge ↓ */
        for (std::uint32_t row = min_row; row <= max_row; ++row)
        {
            result[row][max_col] = current;
            ++current;
        }

        if (max_row < min_row)
        {
            break;
        }

        if (max_col > 0U)
        {
            --max_col;
        }
        else
        {
            break;
        }

        /* bottom edge ← */
        for (std::int32_t col = static_cast<std::int32_t>(max_col);
             col >= static_cast<std::int32_t>(min_col);
             --col)
        {
            result[max_row][static_cast<std::uint32_t>(col)] = current;
            ++current;
        }

        if (max_row > 0U)
        {
            --max_row;
        }
        else
        {
            break;
        }

        /* left edge ↑ */
        for (std::int32_t row = static_cast<std::int32_t>(max_row);
             row >= static_cast<std::int32_t>(min_row);
             --row)
        {
            result[static_cast<std::uint32_t>(row)][min_col] = current;
            ++current;
        }
        ++min_col;
    }

    return result;
}

}  // namespace spiral_matrix
