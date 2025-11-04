#include "spiral_matrix.h"

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> matrix_t
{
    if (size == 0U)
    {
        return matrix_t{};
    }

    matrix_t matrix(size, std::vector<std::uint32_t>(size, 0U));

    std::uint32_t min_row = 0U;
    std::uint32_t max_row = size - 1U;
    std::uint32_t min_col = 0U;
    std::uint32_t max_col = size - 1U;

    std::uint32_t value = 1U;

    while ((min_row <= max_row) && (min_col <= max_col))
    {
        for (std::uint32_t col = min_col; col <= max_col; ++col)
        {
            matrix[min_row][col] = value;
            ++value;
        }
        ++min_row;

        for (std::uint32_t row = min_row; row <= max_row; ++row)
        {
            matrix[row][max_col] = value;
            ++value;
        }
        if (max_col == 0U)
        {
            break;
        }
        --max_col;

        if (min_row <= max_row)
        {
            for (std::uint32_t col = max_col + 1U; col-- > min_col;)
            {
                matrix[max_row][col] = value;
                ++value;
            }
            if (max_row == 0U)
            {
                break;
            }
            --max_row;
        }

        if (min_col <= max_col)
        {
            for (std::uint32_t row = max_row + 1U; row-- > min_row;)
            {
                matrix[row][min_col] = value;
                ++value;
            }
            ++min_col;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
